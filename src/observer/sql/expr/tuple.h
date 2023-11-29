/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <memory>
#include <vector>

#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "sql/expr/tuple_cell.h"
#include "sql/expr/expression.h"
#include "storage/record/record.h"

class Table;

class TupleCellSpec {
public:
  TupleCellSpec() = default;
  TupleCellSpec(Expression *expr) : expression_(expr)
  {}

  ~TupleCellSpec()
  {
    if (expression_) {
      delete expression_;
      expression_ = nullptr;
    }
  }

  void set_alias(const char *alias)
  {
    this->alias_ = alias;
  }
  const char *alias() const
  {
    return alias_;
  }

  Expression *expression() const
  {
    return expression_;
  }

private:
  const char *alias_ = nullptr;
  Expression *expression_ = nullptr;
};

class Tuple {
public:
  Tuple() = default;
  virtual ~Tuple() = default;

  virtual int cell_num() const = 0;
  virtual RC cell_at(int index, TupleCell &cell) const = 0;
  virtual RC find_cell(const Field &field, TupleCell &cell) const = 0;

  virtual RC cell_spec_at(int index, const TupleCellSpec *&spec) const = 0;

  // add new virtual function
  virtual void get_record(JoinRecord &join_record) const = 0;
  virtual void set_record(JoinRecord &join_record) = 0;
  virtual void set_right_record(JoinRecord &join_record) = 0;
};

class RowTuple : public Tuple {
public:
  RowTuple() = default;
  virtual ~RowTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_record(Record *record)
  {
    this->record_ = record;
  }

  void set_schema(const Table *table, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new TupleCellSpec(new FieldExpr(table, &field)));
    }
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    const TupleCellSpec *spec = speces_[index];
    FieldExpr *field_expr = (FieldExpr *)spec->expression();
    const FieldMeta *field_meta = field_expr->field().meta();
    cell.set_type(field_meta->type());
    cell.set_data(this->record_->data() + field_meta->offset());
    cell.set_length(field_meta->len());
    return RC::SUCCESS;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    const char *table_name = field.table_name();
    if (0 != strcmp(table_name, table_->name())) {
      return RC::NOTFOUND;
    }

    const char *field_name = field.field_name();
    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr *field_expr = (const FieldExpr *)speces_[i]->expression();
      const Field &field = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        return cell_at(i, cell);
      }
    }
    return RC::NOTFOUND;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  Record &record()
  {
    return *record_;
  }

  const Record &record() const
  {
    return *record_;
  }

  // add new function
  void set_record(JoinRecord &join_record) override
  {
    assert(join_record.size() >= 1);
    this->record_ = join_record.front();
    join_record.erase(join_record.begin());
  }

  void set_right_record(JoinRecord &join_record) override
  {
    assert(!join_record.empty());
    set_record(join_record);
  }

  void get_record(JoinRecord &join_record) const override
  {
    join_record.emplace_back(this->record_);
  }

private:
  Record *record_ = nullptr;
  const Table *table_ = nullptr;
  std::vector<TupleCellSpec *> speces_;
};

/*
class CompositeTuple : public Tuple
{
public:
  int cell_num() const override;
  RC  cell_at(int index, TupleCell &cell) const = 0;
private:
  int cell_num_ = 0;
  std::vector<Tuple *> tuples_;
};
*/

class ProjectTuple : public Tuple {
public:
  ProjectTuple() = default;
  virtual ~ProjectTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_tuple(Tuple *tuple)
  {
    this->tuple_ = tuple;
  }

  void add_cell_spec(TupleCellSpec *spec)
  {
    speces_.push_back(spec);
  }
  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::GENERIC_ERROR;
    }
    if (tuple_ == nullptr) {
      return RC::GENERIC_ERROR;
    }

    const TupleCellSpec *spec = speces_[index];
    return spec->expression()->get_value(*tuple_, cell);
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    return tuple_->find_cell(field, cell);
  }
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  // add new function
  void set_record(JoinRecord &join_record) override
  {
    tuple_->set_record(join_record);
  }
  void set_right_record(JoinRecord &join_record) override
  {
    tuple_->set_right_record(join_record);
  }
  void get_record(JoinRecord &join_record) const override
  {
    tuple_->get_record(join_record);
  }

private:
  std::vector<TupleCellSpec *> speces_;
  Tuple *tuple_ = nullptr;
  // Different from RowTuple, Here ProjectTuple is a tuple_ and isn't a record_
};

class JoinTuple : public Tuple {
public:
  void init(Tuple *left_tuple, Tuple *right_tuple)
  {
    left_tuple_ = left_tuple;
    right_tuple_ = right_tuple;
  }
  int cell_num() const override
  {
    return left_tuple_->cell_num() + right_tuple_->cell_num();
  }
  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= cell_num()) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    // get left side cell num;
    int num = left_tuple_->cell_num();
    if (index < num) {
      return left_tuple_->cell_at(index, cell);
    }
    // get from right table by id values of (index - num)
    return right_tuple_->cell_at(index - num, cell);
  }
  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    if (left_tuple_->find_cell(field, cell) != RC::SUCCESS) {
      return right_tuple_->find_cell(field, cell);
    }
    return RC::SUCCESS;
  }
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= cell_num()) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    int num = left_tuple_->cell_num();
    if (index < num) {
      return left_tuple_->cell_spec_at(index, spec);
    }
    return right_tuple_->cell_spec_at(index - num, spec);
  }

  // add new function
  void set_record(JoinRecord &join_record) override
  {
    left_tuple_->set_record(join_record);
    right_tuple_->set_record(join_record);
  }
  void set_right_record(JoinRecord &join_record) override
  {
    right_tuple_->set_right_record(join_record);
    assert(join_record.empty());
  }
  void get_record(JoinRecord &join_record) const override
  {
    left_tuple_->get_record(join_record);
    right_tuple_->get_record(join_record);
  }

private:
  Tuple *left_tuple_;
  Tuple *right_tuple_;
};