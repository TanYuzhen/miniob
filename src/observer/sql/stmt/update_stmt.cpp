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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/field_meta.h"

UpdateStmt::UpdateStmt(Table *table, FilterStmt *filter_stmt, Value *values, const char *filed_name)
    : table_(table), filter_stmt_(filter_stmt), values_(values), filed_name(filed_name)
{}

RC UpdateStmt::create(Db *db, const Updates &update, Stmt *&stmt)
{
  // TODO
  const char *table_name = update.relation_name;
  // Firstly, Check the argument whether valid
  if (nullptr == db || nullptr == table_name || update.condition_num < 0) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, condition_num=%d", db, table_name, update.condition_num);
    return RC::INVALID_ARGUMENT;
  }
  // Secondly, Get the table;
  Table *table = db->find_table(table_name);
  if (table == nullptr) {
    LOG_ERROR("Update table %s is exist", table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  // Thirdly, Get the value, check the value whether valid
  Value *value = new Value(update.value);  // There choose new to make sure the point is valid
  const TableMeta &table_meta = table->table_meta();
  const FieldMeta *field_meta = table_meta.field(update.attribute_name);
  if (field_meta == nullptr) {
    LOG_ERROR("Update field %s don't exist", update.attribute_name);
    return RC::INVALID_ARGUMENT;
  }
  const AttrType field_type = field_meta->type();
  const AttrType value_type = update.value.type;
  if (field_type != value_type) {
    LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
        table_name,
        field_meta->name(),
        field_type,
        value_type);
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
  // Forth, Get the FilterStmt
  std::unordered_map<std::string, Table *> table_map;
  table_map[table_name] = table;
  FilterStmt *filterStmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map, update.conditions, update.condition_num, filterStmt);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  stmt = new UpdateStmt(table, filterStmt, value, update.attribute_name);
  return RC::SUCCESS;
}
