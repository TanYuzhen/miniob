
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
	char id[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        INNER
        JOIN
        ON
        LOAD
        DATA
        INFILE
        EQ
        LT
        GT
        LE
        GE
        NE
        ADD
        SUB
        DIV
        NOT
        LIKE
        UNIQUE

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  struct Expr* exp1;
  struct Expr* exp2;
  struct Expr* exp3;
  char *string;
  int number;
  float floats;
	char *position;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
%token <string> DATE_STR
//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <exp1> unary_expr;
%type <exp2> mul_expr;
%type <exp3> add_expr;
%type <number> number;

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index
	| show_index
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ix ix_list RBRACE SEMICOLON {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, false, $3, $5);
		}
	| CREATE UNIQUE INDEX ID ON ID LBRACE ix ix_list RBRACE SEMICOLON
	    {
	        CONTEXT->ssql->flag = SCF_CREATE_INDEX;
	        create_index_init(&CONTEXT->ssql->sstr.create_index, true, $4, $6);
	    }
    ;

ix : ID
    {
        create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, $1);
    }
    ;

ix_list : | COMMA ix ix_list
    {

    }
    ;

show_index:
    SHOW INDEX FROM ID SEMICOLON
        {
            CONTEXT->ssql->flag = SCF_SHOW_INDEX;
            desc_table_init(&CONTEXT->ssql->sstr.desc_table, $4);
        }
    ;

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    |ID_get type
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    ;
number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
       | STRING_T { $$=CHARS; }
       | FLOAT_T { $$=FLOATS; }
       | DATE_T { $$=DATE; }
       ;
ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES row_values row_values_list SEMICOLON
		{
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			//inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->values, CONTEXT->value_length);
            inserts_init(&CONTEXT->ssql->sstr.insertion, $3);
    }

row_values_list:
            |  COMMA row_values row_values_list
            {
            //Nothing to do here
     }

row_values :
        LBRACE value value_list RBRACE
        {
            inserts_data_init(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
            memset(CONTEXT->values, 0, sizeof(CONTEXT->values));
            //临时变量清零
            CONTEXT->value_length=0;
     }

value_list:
    /* empty */
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;

unary_expr:
    value {
        Expr *expr = malloc(sizeof(Expr));
        UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
        unary_expr_init_value(u_expr, &CONTEXT->values[CONTEXT->value_length-1]);
        expr_init_unary(expr, u_expr);
        $$ = expr;
    }
    | ID {
    	Expr *expr = malloc(sizeof(Expr));
        RelAttr* attr = malloc(sizeof(RelAttr));
        relation_attr_init(attr, NULL, $1);
        UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
        unary_expr_init_attr(u_expr, attr);
        expr_init_unary(expr, u_expr);
        $$ = expr;
    }
    | ID DOT ID {
    	Expr *expr = malloc(sizeof(Expr));
        RelAttr* attr = malloc(sizeof(RelAttr));
        relation_attr_init(&attr, $1, $3);
        UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
        unary_expr_init_attr(u_expr, &attr);
        expr_init_unary(expr, u_expr);
        $$ = expr;
    }
    | LBRACE add_expr RBRACE {
        expr_set_with_brace($2);
        $$ = $2;
    }
    ;

mul_expr:
    unary_expr {
        $$ = $1;
    }
    | SUB unary_expr {
        Value * tmp_val = malloc(sizeof(Value));
        value_init_integer(tmp_val, -1);
        UnaryExpr * tmp_uexpr = malloc(sizeof(UnaryExpr));
        unary_expr_init_value(tmp_uexpr, tmp_val);
        Expr * tmp_expr = malloc(sizeof(Expr));
        expr_init_unary(tmp_expr, tmp_uexpr);

        Expr * expr = malloc(sizeof(Expr));
        BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
        binary_expr_init(b_expr, MUL_OP, tmp_expr, $2);
        binary_expr_set_minus(b_expr);
        expr_init_binary(expr, b_expr);
        $$ = expr;
    }
    | mul_expr STAR unary_expr {
        Expr * expr = malloc(sizeof(Expr));
        BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
        binary_expr_init(b_expr, MUL_OP, $1, $3);
        expr_init_binary(expr, b_expr);
        $$ = expr;
    }
    | mul_expr DIV unary_expr {
    	Expr * expr = malloc(sizeof(Expr));
        BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
        binary_expr_init(b_expr, DIV_OP, $1, $3);
        expr_init_binary(expr, b_expr);
        $$ = expr;
    }
    ;

add_expr:
    mul_expr { $$ = $1; }
    | add_expr ADD mul_expr {
    	Expr * expr = malloc(sizeof(Expr));
        BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
        binary_expr_init(b_expr, ADD_OP, $1, $3);
        expr_init_binary(expr, b_expr);
        $$ = expr;
    }
    | add_expr SUB mul_expr {
    	Expr * expr = malloc(sizeof(Expr));
        BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
        binary_expr_init(b_expr, SUB_OP, $1, $3);
        expr_init_binary(expr, b_expr);
        $$ = expr;
    }
    ;

condition:
    add_expr comOp add_expr{
        Condition* expr = malloc(sizeof(Condition));
        condition_init(expr, CONTEXT->comp, $1, $3);
        CONTEXT->conditions[CONTEXT->condition_length++] = *expr;
    }
    ;

value:
    NUMBER{	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
	|SUB NUMBER{
        value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -($2));
    	}
    |FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
	|SUB FLOAT{
        value_init_float(&CONTEXT->values[CONTEXT->value_length++], -($2));
        }
    |SSS {
			$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
	|DATE_STR{
	        $1 = substr($1,1,strlen($1)-2);
	    if(0 != value_init_date(&CONTEXT->values[CONTEXT->value_length++], $1))
	        return -1;
	}
    ;
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
    ;
select:				/*  select 语句的语法解析树*/
    SELECT select_attr FROM ID rel_list where SEMICOLON
		{
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, $4);

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
	;

select_attr:
    STAR attr_list {
        ProjectCol project_col;
        project_init_star(&project_col, NULL);
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
    |ID DOT STAR attr_list {
        ProjectCol project_col;
        project_init_star(&project_col, $1);
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
    |add_expr attr_list {
        ProjectCol project_col;
        project_init_expr(&project_col, $1);
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
    ;

attr_list:
    /* empty */
    |COMMA STAR attr_list {
        ProjectCol project_col;
        project_init_star(&project_col, NULL);
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
    |COMMA ID DOT STAR attr_list {
        ProjectCol project_col;
        project_init_star(&project_col, $2);
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
    |COMMA add_expr attr_list {
        ProjectCol project_col;
        project_init_expr(&project_col, $2);
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
    ;

rel_list:
    /* empty */
    | COMMA ID rel_list {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, $2);
		  }
    | INNER JOIN ID inner_join_condition_lists rel_list {
                selects_append_relation(&CONTEXT->ssql->sstr.selection, $3);
          }
    ;
inner_join_condition_lists:
    | ON condition condition_list {

         }
    ;
where:
    /* empty */ 
    | WHERE condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
condition_list:
    /* empty */
    | AND condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
//condition:
//  ID comOp value
//  {
//    RelAttr left_attr;
//    relation_attr_init(&left_attr, NULL, $1);
//
//    Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
//
//    Condition condition;
//    condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
//    CONTEXT->conditions[CONTEXT->condition_length++] = condition;
//    // $$ = ( Condition *)malloc(sizeof( Condition));
//    // $$->left_is_attr = 1;
//    // $$->left_attr.relation_name = NULL;
//    // $$->left_attr.attribute_name= $1;
//    // $$->comp = CONTEXT->comp;
//    // $$->right_is_attr = 0;
//    // $$->right_attr.relation_name = NULL;
//    // $$->right_attr.attribute_name = NULL;
//    // $$->right_value = *$3;
//
//  }
//  |value comOp value
//  {
//    Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
//    Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
//
//    Condition condition;
//    condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
//    CONTEXT->conditions[CONTEXT->condition_length++] = condition;
//    // $$ = ( Condition *)malloc(sizeof( Condition));
//    // $$->left_is_attr = 0;
//    // $$->left_attr.relation_name=NULL;
//    // $$->left_attr.attribute_name=NULL;
//    // $$->left_value = *$1;
//    // $$->comp = CONTEXT->comp;
//    // $$->right_is_attr = 0;
//    // $$->right_attr.relation_name = NULL;
//    // $$->right_attr.attribute_name = NULL;
//    // $$->right_value = *$3;
//
//  }
//  |ID comOp ID
//  {
//    RelAttr left_attr;
//    relation_attr_init(&left_attr, NULL, $1);
//    RelAttr right_attr;
//    relation_attr_init(&right_attr, NULL, $3);
//
//    Condition condition;
//    condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
//    CONTEXT->conditions[CONTEXT->condition_length++] = condition;
//    // $$=( Condition *)malloc(sizeof( Condition));
//    // $$->left_is_attr = 1;
//    // $$->left_attr.relation_name=NULL;
//    // $$->left_attr.attribute_name=$1;
//    // $$->comp = CONTEXT->comp;
//    // $$->right_is_attr = 1;
//    // $$->right_attr.relation_name=NULL;
//    // $$->right_attr.attribute_name=$3;
//
//  }
//  |value comOp ID
//  {
//    Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
//    RelAttr right_attr;
//    relation_attr_init(&right_attr, NULL, $3);
//
//    Condition condition;
//    condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
//    CONTEXT->conditions[CONTEXT->condition_length++] = condition;
//
//    // $$=( Condition *)malloc(sizeof( Condition));
//    // $$->left_is_attr = 0;
//    // $$->left_attr.relation_name=NULL;
//    // $$->left_attr.attribute_name=NULL;
//    // $$->left_value = *$1;
//    // $$->comp=CONTEXT->comp;
//
//    // $$->right_is_attr = 1;
//    // $$->right_attr.relation_name=NULL;
//    // $$->right_attr.attribute_name=$3;
//
//  }
//  |ID DOT ID comOp value
//  {
//    RelAttr left_attr;
//    relation_attr_init(&left_attr, $1, $3);
//    Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
//
//    Condition condition;
//    condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
//    CONTEXT->conditions[CONTEXT->condition_length++] = condition;
//
//    // $$=( Condition *)malloc(sizeof( Condition));
//    // $$->left_is_attr = 1;
//    // $$->left_attr.relation_name=$1;
//    // $$->left_attr.attribute_name=$3;
//    // $$->comp=CONTEXT->comp;
//    // $$->right_is_attr = 0;   //属性值
//    // $$->right_attr.relation_name=NULL;
//    // $$->right_attr.attribute_name=NULL;
//    // $$->right_value =*$5;
//
//  }
//  |value comOp ID DOT ID
//  {
//    Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
//
//    RelAttr right_attr;
//    relation_attr_init(&right_attr, $3, $5);
//
//    Condition condition;
//    condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
//    CONTEXT->conditions[CONTEXT->condition_length++] = condition;
//    // $$=( Condition *)malloc(sizeof( Condition));
//    // $$->left_is_attr = 0;//属性值
//    // $$->left_attr.relation_name=NULL;
//    // $$->left_attr.attribute_name=NULL;
//    // $$->left_value = *$1;
//    // $$->comp =CONTEXT->comp;
//    // $$->right_is_attr = 1;//属性
//    // $$->right_attr.relation_name = $3;
//    // $$->right_attr.attribute_name = $5;
//
//  }
//  |ID DOT ID comOp ID DOT ID
//  {
//    RelAttr left_attr;
//    relation_attr_init(&left_attr, $1, $3);
//    RelAttr right_attr;
//    relation_attr_init(&right_attr, $5, $7);
//
//    Condition condition;
//    condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
//    CONTEXT->conditions[CONTEXT->condition_length++] = condition;
//    // $$=( Condition *)malloc(sizeof( Condition));
//    // $$->left_is_attr = 1;		//属性
//    // $$->left_attr.relation_name=$1;
//    // $$->left_attr.attribute_name=$3;
//    // $$->comp =CONTEXT->comp;
//    // $$->right_is_attr = 1;		//属性
//    // $$->right_attr.relation_name=$5;
//    // $$->right_attr.attribute_name=$7;
//  }
//  ;

comOp:
  	  EQ { CONTEXT->comp = EQUAL_TO; }
    | LT { CONTEXT->comp = LESS_THAN; }
    | GT { CONTEXT->comp = GREAT_THAN; }
    | LE { CONTEXT->comp = LESS_EQUAL; }
    | GE { CONTEXT->comp = GREAT_EQUAL; }
    | NE { CONTEXT->comp = NOT_EQUAL; }
    | LIKE { CONTEXT->comp = LIKE_OP; }
    | NOT LIKE { CONTEXT->comp = NOT_LIKE_OP; }
    ;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
