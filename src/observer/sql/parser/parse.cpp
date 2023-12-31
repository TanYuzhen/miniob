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
// Created by Meiyi
//

#include <mutex>
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name)
{
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
}

void relation_attr_destroy(RelAttr *relation_attr)
{
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
}

void value_init_integer(Value *value, int v)
{
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_float(Value *value, float v)
{
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_string(Value *value, const char *v)
{
  value->type = CHARS;
  value->data = strdup(v);
}
bool check_date(int y, int m, int d)
{
  static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool leap = (y % 400 == 0 || (y % 100 && y % 4 == 0));
  return y > 0 && (m > 0) && (m <= 12) && (d > 0) && (d <= ((m == 2 && leap) ? 1 : 0) + mon[m]);
}
int value_init_date(Value *value, const char *v)
{
  value->type = DATE;
  int y, m, d;
  sscanf(v, "%d-%d-%d", &y, &m, &d);
  bool whether_right_day = check_date(y, m, d);
  if (!whether_right_day)
    return -1;
  int data = y * 10000 + m * 100 + d;
  value->data = malloc(sizeof(data));
  memcpy(value->data, &data, sizeof(data));
  return 0;
}
void value_destroy(Value *value)
{
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
}

void unary_expr_init_attr(UnaryExpr *expr, RelAttr *relation_attr)
{
  expr->is_attr = 1;
  expr->attr = *relation_attr;
}
void unary_expr_init_value(UnaryExpr *expr, Value *value)
{
  expr->is_attr = 0;
  expr->value = *value;
}
void unary_expr_destroy(UnaryExpr *expr)
{
  if (expr->is_attr) {
    relation_attr_destroy(&expr->attr);
  } else {
    value_destroy(&expr->value);
  }
  return;
}

void binary_expr_init(BinaryExpr *expr, ExpOp op, Expr *left_expr, Expr *right_expr)
{
  expr->op = op;
  expr->left_expr = left_expr;
  expr->right_expr = right_expr;
  expr->minus = 0;
}
void binary_expr_set_minus(BinaryExpr *expr)
{
  expr->minus = 1;
}
void binary_expr_destroy(BinaryExpr *expr)
{
  expr_destroy(expr->left_expr);
  expr_destroy(expr->right_expr);
}

void expr_init_unary(Expr *expr, UnaryExpr *u_expr)
{
  expr->type = 0;
  expr->binaryExpr = nullptr;
  expr->unaryExpr = u_expr;
  expr->brace = 0;
}
void expr_init_binary(Expr *expr, BinaryExpr *b_expr)
{
  expr->type = 1;
  expr->binaryExpr = b_expr;
  expr->unaryExpr = nullptr;
  expr->brace = 0;
}
void expr_set_with_brace(Expr *expr)
{
  expr->brace = 1;
}
void expr_destroy(Expr *expr)
{
  if (expr->type == 0) {
    unary_expr_destroy(expr->unaryExpr);
  } else if (expr->type == 1) {
    binary_expr_destroy(expr->binaryExpr);
  }
}

void condition_init(Condition *condition, CompOp op, Expr *left_expr, Expr *right_expr)
{
  condition->comp = op;
  condition->left_expr = left_expr;
  condition->right_expr = right_expr;
}
void condition_destroy(Condition *condition)
{
  expr_destroy(condition->left_expr);
  expr_destroy(condition->right_expr);
}

void project_init_star(ProjectCol *project_col, const char *relation_name)
{
  project_col->is_star = 1;
  if (relation_name != nullptr) {
    project_col->relation_name = strdup(relation_name);
  } else {
    project_col->relation_name = nullptr;
  }
  project_col->expr = nullptr;
}
void project_init_expr(ProjectCol *project_col, Expr *expr)
{
  project_col->is_star = 0;
  project_col->expr = expr;
  project_col->relation_name = nullptr;
}
void project_destroy(ProjectCol *project_col)
{
  if (project_col->relation_name != nullptr) {
    free(project_col->relation_name);
  }
  if (project_col->expr != nullptr) {
    expr_destroy(project_col->expr);
  }
}

// void condition_init(Condition *condition, CompOp comp, int left_is_attr, RelAttr *left_attr, Value *left_value,
//     int right_is_attr, RelAttr *right_attr, Value *right_value)
//{
//   condition->comp = comp;
//   condition->left_is_attr = left_is_attr;
//   if (left_is_attr) {
//     condition->left_attr = *left_attr;
//   } else {
//     condition->left_value = *left_value;
//   }
//
//   condition->right_is_attr = right_is_attr;
//   if (right_is_attr) {
//     condition->right_attr = *right_attr;
//   } else {
//     condition->right_value = *right_value;
//   }
// }
// void condition_destroy(Condition *condition)
//{
//   if (condition->left_is_attr) {
//     relation_attr_destroy(&condition->left_attr);
//   } else {
//     value_destroy(&condition->left_value);
//   }
//   if (condition->right_is_attr) {
//     relation_attr_destroy(&condition->right_attr);
//   } else {
//     value_destroy(&condition->right_value);
//   }
// }

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length)
{
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->length = length;
}
void attr_info_destroy(AttrInfo *attr_info)
{
  free(attr_info->name);
  attr_info->name = nullptr;
}

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr)
{
  selects->attributes[selects->attr_num++] = *rel_attr;
}
void selects_append_relation(Selects *selects, const char *relation_name)
{
  selects->relations[selects->relation_num++] = strdup(relation_name);
}
void selects_append_projects(Selects *selects, ProjectCol *project_col)
{
  selects->projects[selects->project_num++] = *project_col;
}
void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(selects->conditions) / sizeof(selects->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    selects->conditions[i] = conditions[i];
  }
  selects->condition_num = condition_num;
}

void selects_destroy(Selects *selects)
{
  for (size_t i = 0; i < selects->attr_num; i++) {
    relation_attr_destroy(&selects->attributes[i]);
  }
  selects->attr_num = 0;

  for (size_t i = 0; i < selects->relation_num; i++) {
    free(selects->relations[i]);
    selects->relations[i] = NULL;
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    condition_destroy(&selects->conditions[i]);
  }
  selects->condition_num = 0;

  for (size_t i = 0; i < selects->project_num; i++) {
    project_destroy(&selects->projects[i]);
  }
  selects->project_num = 0;
}

void inserts_init(Inserts *inserts, const char *relation_name)
{
  inserts->relation_name = strdup(relation_name);
}
void inserts_data_init(Inserts *inserts, Value values[], size_t value_num)
{
  assert(value_num <= sizeof(inserts->values[0]) / sizeof(inserts->values[0][0]));
  inserts->value_num = value_num;
  for (size_t i = 0; i < value_num; i++) {
    inserts->values[inserts->row_num][i] = values[i];
  }
  (inserts->row_num)++;
}
void inserts_destroy(Inserts *inserts)
{
  free(inserts->relation_name);
  inserts->relation_name = nullptr;

  for (size_t i = 0; i < inserts->row_num; i++)
    for (size_t j = 0; j < inserts->value_num; j++) {
      value_destroy(&inserts->values[i][j]);
    }
  inserts->value_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name)
{
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(deletes->conditions) / sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes)
{
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
    Condition conditions[], size_t condition_num)
{
  updates->relation_name = strdup(relation_name);
  updates->attribute_name = strdup(attribute_name);
  updates->value = *value;

  assert(condition_num <= sizeof(updates->conditions) / sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_destroy(Updates *updates)
{
  free(updates->relation_name);
  free(updates->attribute_name);
  updates->relation_name = nullptr;
  updates->attribute_name = nullptr;

  value_destroy(&updates->value);

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info)
{
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}

void create_table_init_name(CreateTable *create_table, const char *relation_name)
{
  create_table->relation_name = strdup(relation_name);
}

void create_table_destroy(CreateTable *create_table)
{
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name)
{
  drop_table->relation_name = strdup(relation_name);
}

void drop_table_destroy(DropTable *drop_table)
{
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void create_index_init(CreateIndex *create_index, bool unique, const char *index_name, const char *relation_name)
{
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->unique = unique;
}
void create_index_append_attribute(CreateIndex *createIndex, const char *attr_name)
{
  createIndex->attribute[createIndex->attr_count].name = strdup(attr_name);
  (createIndex->attr_count)++;
}

void create_index_destroy(CreateIndex *create_index)
{
  free(create_index->index_name);
  free(create_index->relation_name);

  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;

  for (int i = 0; i < create_index->attr_count; i++) {
    attr_info_destroy(&(create_index->attribute[i]));
  }

  create_index->attr_count = 0;
  create_index->unique = false;
}

void drop_index_init(DropIndex *drop_index, const char *index_name)
{
  drop_index->index_name = strdup(index_name);
}

void drop_index_destroy(DropIndex *drop_index)
{
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name)
{
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table)
{
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name)
{
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data)
{
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query)
{
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create()
{
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query)
{
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection);
    } break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    } break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    } break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    } break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    } break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    } break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    } break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    } break;
    case SCF_SYNC: {

    } break;
    case SCF_SHOW_TABLES:
      break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    } break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    } break;
    case SCF_CLOG_SYNC:
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
      break;
  }
}

void query_destroy(Query *query)
{
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query *sqls);

RC parse(const char *st, Query *sqln)
{
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}