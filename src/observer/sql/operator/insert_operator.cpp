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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/insert_operator.h"
#include "sql/stmt/insert_stmt.h"
#include "storage/common/table.h"
#include "rc.h"

RC InsertOperator::open()
{
  Table *table = insert_stmt_->table();
  const Value *values = insert_stmt_->values();
  int value_amount = insert_stmt_->value_amount();
  RC rc;
  if (insert_stmt_->row_amount() > 1) {
    rc = table->insert_record(trx_, value_amount, insert_stmt_->rows());
  } else {
    rc = table->insert_record(trx_, value_amount, insert_stmt_->rows()->at(0).values);  // TODO trx
  }
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert operator open() function execute error");
  }
  return rc;
}

RC InsertOperator::next()
{
  return RC::RECORD_EOF;
}

RC InsertOperator::close()
{
  return RC::SUCCESS;
}
Tuple *InsertOperator::current_tuple()
{
  return nullptr;
}
