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
// Created by WangYunlai on 2022/6/27.
//

#include "common/log/log.h"
#include "sql/operator/predicate_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/field.h"
#include "util/typecast.h"
#include "common/lang/defer.h"
#include <regex>

RC PredicateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open();
}

RC PredicateOperator::next()
{
  RC rc = RC::SUCCESS;
  Operator *oper = children_[0];

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    if (do_predicate(static_cast<RowTuple &>(*tuple))) {
      return rc;
    }
  }
  return rc;
}

RC PredicateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicateOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

bool PredicateOperator::do_predicate(RowTuple &tuple)
{
  if (filter_stmt_ == nullptr || filter_stmt_->filter_units().empty()) {
    return true;
  }

  for (const FilterUnit *filter_unit : filter_stmt_->filter_units()) {
    Expression *left_expr = filter_unit->left();
    Expression *right_expr = filter_unit->right();
    CompOp comp = filter_unit->comp();
    TupleCell left_cell;
    TupleCell right_cell;
    left_expr->get_value(tuple, left_cell);
    right_expr->get_value(tuple, right_cell);

    // when compared, the expr type is different, should cast the type
    // when left type is different from the right type, all cast it to float type to compare
    AttrType left_type = left_cell.attr_type();
    AttrType right_type = right_cell.attr_type();

    if (comp == LIKE_OP || comp == NOT_LIKE_OP) {
      assert(left_type == CHARS && right_type == CHARS);
      std::string regex_string(right_cell.data());
      size_t found = regex_string.find('%');
      while (found != std::string::npos) {
        regex_string.replace(found, 1, "[^']*");
        found = regex_string.find('%', found + 1);
      }
      found = regex_string.find('_');
      while (found != std::string::npos) {
        regex_string.replace(found, 1, "[^']");
        found = regex_string.find('_', found + 1);
      }
      std::regex reg(regex_string.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
      bool result = std::regex_match(left_cell.data(), reg);
      if ((result && comp == LIKE_OP) || (!result && comp == NOT_LIKE_OP)) {
        continue;
      } else {
        return false;
      }
    }

    float *left_temp_data = nullptr;
    float *right_temp_data = nullptr;
    DEFER([&]() {
      if (left_temp_data)
        delete left_temp_data;
      if (right_temp_data)
        delete right_temp_data;
    });
    if (left_type != right_type) {
      if (left_type == FLOATS) {
        std::unique_ptr<TypeCast> right_type_cast = std::make_unique<TypeCast>(right_type, FLOATS);
        right_temp_data = (float *)right_type_cast->cast((void *)right_cell.data());
        right_cell.set_data((char *)right_temp_data);
        right_cell.set_type(FLOATS);
      } else if (right_type == FLOATS) {
        std::unique_ptr<TypeCast> left_type_cast = std::make_unique<TypeCast>(left_type, FLOATS);
        left_temp_data = (float *)left_type_cast->cast((void *)left_cell.data());
        left_cell.set_data((char *)left_temp_data);
        left_cell.set_type(FLOATS);
      } else {
        std::unique_ptr<TypeCast> left_type_cast = std::make_unique<TypeCast>(left_type, FLOATS);
        std::unique_ptr<TypeCast> right_type_cast = std::make_unique<TypeCast>(right_type, FLOATS);
        left_temp_data = (float *)left_type_cast->cast((void *)left_cell.data());
        right_temp_data = (float *)right_type_cast->cast((void *)right_cell.data());
        // reset the float data
        left_cell.set_data((char *)left_temp_data);
        left_cell.set_type(FLOATS);
        right_cell.set_data((char *)right_temp_data);
        right_cell.set_type(FLOATS);
      }
    }

    const int compare = left_cell.compare(right_cell);
    bool filter_result = false;
    switch (comp) {
      case EQUAL_TO: {
        filter_result = (0 == compare);
      } break;
      case LESS_EQUAL: {
        filter_result = (compare <= 0);
      } break;
      case NOT_EQUAL: {
        filter_result = (compare != 0);
      } break;
      case LESS_THAN: {
        filter_result = (compare < 0);
      } break;
      case GREAT_EQUAL: {
        filter_result = (compare >= 0);
      } break;
      case GREAT_THAN: {
        filter_result = (compare > 0);
      } break;
      default: {
        LOG_WARN("invalid compare type: %d", comp);
      } break;
    }
    if (!filter_result) {
      return false;
    }
  }
  return true;
}

// int PredicateOperator::tuple_cell_num() const
// {
//   return children_[0]->tuple_cell_num();
// }
// RC PredicateOperator::tuple_cell_spec_at(int index, TupleCellSpec &spec) const
// {
//   return children_[0]->tuple_cell_spec_at(index, spec);
// }
