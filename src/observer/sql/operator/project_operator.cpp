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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/operator/project_operator.h"
#include "storage/record/record.h"
#include "storage/common/table.h"

RC ProjectOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("project operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectOperator::next()
{
  return children_[0]->next();
}

RC ProjectOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}
Tuple *ProjectOperator::current_tuple()
{
  tuple_.set_tuple(children_[0]->current_tuple());
  return &tuple_;
}

void gen_project_name(const Expression *expr, bool is_single_table, std::string &result_name)
{
  if (expr->with_brace()) {
    result_name += '(';
  }
  switch (expr->type()) {
    case ExprType::FIELD: {
      FieldExpr *fexpr = (FieldExpr *)expr;
      const Table *table = fexpr->table();
      const FieldMeta *field_meta = fexpr->field().meta();
      if (!is_single_table) {
        result_name += std::string(table->name()) + '.' + std::string(field_meta->name());
      } else {
        result_name += std::string(field_meta->name());
      }
      break;
    }
    case ExprType::VALUE: {
      ValueExpr *vexpr = (ValueExpr *)expr;
      TupleCell cell;
      vexpr->get_tuple_cell(cell);
      std::stringstream ss;
      cell.to_string(ss);
      result_name += ss.str();
      break;
    }
    case ExprType::BINARY: {
      BinaryExpression *bexpr = (BinaryExpression *)expr;
      if (bexpr->is_minus()) {
        // 为-1这样的形式，只需要处理bexpr->right_expr即可
        result_name += '-';
      } else {
        gen_project_name(bexpr->get_left(), is_single_table, result_name);
        result_name += bexpr->get_op_char();
      }
      gen_project_name(bexpr->get_right(), is_single_table, result_name);
      break;
    }
    default:
      break;
  }
  if (expr->with_brace()) {
    result_name += ')';
  }
}

void ProjectOperator::add_projection(Expression *expression, bool is_single)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  // TupleCellSpec代表一个表的第一行，那一行属性名
  TupleCellSpec *spec = new TupleCellSpec(expression);
  std::string *alias_name = new std::string("");
  gen_project_name(expression, is_single, *alias_name);
  spec->set_alias(alias_name->c_str());
  tuple_.add_cell_spec(spec);
}

RC ProjectOperator::tuple_cell_spec_at(int index, const TupleCellSpec *&spec) const
{
  return tuple_.cell_spec_at(index, spec);
}
