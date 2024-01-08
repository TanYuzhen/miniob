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

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <stddef.h>
#include <stdbool.h>

#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50

//属性结构体
typedef struct {
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
} RelAttr;

typedef enum {
  EQUAL_TO,     //"="     0
  LESS_EQUAL,   //"<="    1
  NOT_EQUAL,    //"<>"    2
  LESS_THAN,    //"<"     3
  GREAT_EQUAL,  //">="    4
  GREAT_THAN,   //">"     5
  LIKE_OP,
  NOT_LIKE_OP,
  NO_OP
} CompOp;

//属性值类型
typedef enum { NO_EXP_OP, ADD_OP, SUB_OP, MUL_OP, DIV_OP, EXP_OP_NUM } ExpOp;
typedef enum { UNDEFINED, CHARS, INTS, DATE, FLOATS } AttrType;

//属性值
typedef struct Value {
  AttrType type;  // type of value
  void *data;     // value
} Value;

typedef struct Expr Expr;
typedef struct UnaryExpr {
  int is_attr;  // whether is the table field
  Value value;
  RelAttr attr;
} UnaryExpr;  // 单目表达式

typedef struct BinaryExpr {
  ExpOp op;
  Expr *left_expr;
  Expr *right_expr;
  int minus;
} BinaryExpr;  // 双目表达式

typedef struct Expr {
  int type;   // 0->unaryExpr;1->binaryExpr;2->agg-function
  int brace;  // whether contain ()
  UnaryExpr *unaryExpr;
  BinaryExpr *binaryExpr;
} Expr;

typedef struct Condition {
  //  int left_is_attr;    // TRUE if left-hand side is an attribute
  //                       // 1时，操作符左边是属性名，0时，是属性值
  //  Value left_value;    // left-hand side value if left_is_attr = FALSE
  //  RelAttr left_attr;   // left-hand side attribute
  //  CompOp comp;         // comparison operator
  //  int right_is_attr;   // TRUE if right-hand side is an attribute
  //                       // 1时，操作符右边是属性名，0时，是属性值
  //  RelAttr right_attr;  // right-hand side attribute if right_is_attr = TRUE 右边的属性
  //  Value right_value;   // right-hand side value if right_is_attr = FALSE
  CompOp comp;
  // cpp中，引用被设计为必须在声明时初始化，并且一旦绑定到一个对象，就不能再绑定到另一个对象。
  // 所以在cpp中，引用不能被拷贝，此处应该为指针
  Expr *left_expr;
  Expr *right_expr;
} Condition;

typedef struct ProjectCol {
  int is_star;  // 0->not '*', 1->'*'
  char *relation_name;
  Expr *expr;
} ProjectCol;

// struct of select
typedef struct {
  size_t attr_num;  // Length of attrs in Select clause
  // in bison file,when syntactic parsing 'select' SQL,the attributes array is useless
  RelAttr attributes[MAX_NUM];    // attrs in Select clause
  size_t relation_num;            // Length of relations in Fro clause
  char *relations[MAX_NUM];       // relations in From clause
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
  size_t project_num;             // Length of projects
  ProjectCol projects[MAX_NUM];   // project items
} Selects;

typedef struct {
  const Value *values;
} Row;

// struct of insert
typedef struct {
  char *relation_name;             // Relation to insert into
  size_t value_num;                // Length of values
  size_t row_num;                  // one more values in one insert SQL
  Value values[MAX_NUM][MAX_NUM];  // values to insert
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;            // Relation to delete from
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Deletes;

// struct of update
typedef struct {
  char *relation_name;            // Relation to update
  char *attribute_name;           // Attribute to update
  Value value;                    // update value
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Updates;

typedef struct {
  char *name;     // Attribute name
  AttrType type;  // Type of attribute
  size_t length;  // Length of attribute
} AttrInfo;

// struct of craete_table
typedef struct {
  char *relation_name;           // Relation name
  size_t attribute_count;        // Length of attribute
  AttrInfo attributes[MAX_NUM];  // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name;  // Relation name
} DropTable;

// struct of create_index
typedef struct {
  char *index_name;             // Index name
  char *relation_name;          // Relation name
                                //  char *attribute_name;  // Attribute name
  bool unique;                  // whether unique index
  int attr_count;               // multiple index
  AttrInfo attribute[MAX_NUM];  // multiple index attribute
} CreateIndex;

// struct of  drop_index
typedef struct {
  const char *index_name;  // Index name
} DropIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;

union Queries {
  Selects selection;
  Inserts insertion;
  Deletes deletion;
  Updates update;
  CreateTable create_table;
  DropTable drop_table;
  CreateIndex create_index;
  DropIndex drop_index;
  DescTable desc_table;
  LoadData load_data;
  char *errors;
};

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_SHOW_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT
};
// struct of flag and sql_struct
typedef struct Query {
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void unary_expr_init_attr(UnaryExpr *expr, RelAttr *relation_attr);
void unary_expr_init_value(UnaryExpr *expr, Value *value);
void unary_expr_destroy(UnaryExpr *expr);

void binary_expr_init(BinaryExpr *expr, ExpOp op, Expr *left_expr, Expr *right_expr);
void binary_expr_set_minus(BinaryExpr *expr);
void binary_expr_destroy(BinaryExpr *expr);

void expr_init_unary(Expr *expr, UnaryExpr *u_expr);
void expr_init_binary(Expr *expr, BinaryExpr *b_expr);
void expr_set_with_brace(Expr *expr);
void expr_destroy(Expr *expr);

void condition_init(Condition *condition, CompOp op, Expr *left_expr, Expr *right_expr);
void condition_destroy(Condition *condition);

void project_init_star(ProjectCol *project_col, const char *relation_name);
void project_init_expr(ProjectCol *project_col, Expr *expr);
void project_destroy(ProjectCol *project_col);

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name);
void relation_attr_destroy(RelAttr *relation_attr);

void value_init_integer(Value *value, int v);
void value_init_float(Value *value, float v);
int value_init_date(Value *value, const char *v);
void value_init_string(Value *value, const char *v);
void value_destroy(Value *value);

// void condition_init(Condition *condition, CompOp comp, int left_is_attr, RelAttr *left_attr, Value *left_value,
//     int right_is_attr, RelAttr *right_attr, Value *right_value);
// void condition_destroy(Condition *condition);

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length);
void attr_info_destroy(AttrInfo *attr_info);

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr);
void selects_append_relation(Selects *selects, const char *relation_name);
void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num);
void selects_append_projects(Selects *selects, ProjectCol *project_col);
void selects_destroy(Selects *selects);

void inserts_init(Inserts *inserts, const char *relation_name);
void inserts_data_init(Inserts *inserts, Value values[], size_t value_num);
void inserts_destroy(Inserts *inserts);

void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num);
void deletes_destroy(Deletes *deletes);

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
    Condition conditions[], size_t condition_num);
void updates_destroy(Updates *updates);

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table, const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void create_index_init(CreateIndex *create_index, bool unique, const char *index_name, const char *relation_name);
void create_index_append_attribute(CreateIndex *createIndex, const char *attr_name);
void create_index_destroy(CreateIndex *create_index);

void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create();  // create and init
void query_reset(Query *query);
void query_destroy(Query *query);  // reset and delete

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
