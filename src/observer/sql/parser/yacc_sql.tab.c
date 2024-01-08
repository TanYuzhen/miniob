/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 128 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_DESC = 10,                      /* DESC  */
  YYSYMBOL_SHOW = 11,                      /* SHOW  */
  YYSYMBOL_SYNC = 12,                      /* SYNC  */
  YYSYMBOL_INSERT = 13,                    /* INSERT  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_UPDATE = 15,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 16,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 17,                    /* RBRACE  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 19,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 20,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 21,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 22,                     /* INT_T  */
  YYSYMBOL_STRING_T = 23,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 24,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 25,                    /* DATE_T  */
  YYSYMBOL_HELP = 26,                      /* HELP  */
  YYSYMBOL_EXIT = 27,                      /* EXIT  */
  YYSYMBOL_DOT = 28,                       /* DOT  */
  YYSYMBOL_INTO = 29,                      /* INTO  */
  YYSYMBOL_VALUES = 30,                    /* VALUES  */
  YYSYMBOL_FROM = 31,                      /* FROM  */
  YYSYMBOL_WHERE = 32,                     /* WHERE  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_SET = 34,                       /* SET  */
  YYSYMBOL_INNER = 35,                     /* INNER  */
  YYSYMBOL_JOIN = 36,                      /* JOIN  */
  YYSYMBOL_ON = 37,                        /* ON  */
  YYSYMBOL_LOAD = 38,                      /* LOAD  */
  YYSYMBOL_DATA = 39,                      /* DATA  */
  YYSYMBOL_INFILE = 40,                    /* INFILE  */
  YYSYMBOL_EQ = 41,                        /* EQ  */
  YYSYMBOL_LT = 42,                        /* LT  */
  YYSYMBOL_GT = 43,                        /* GT  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_GE = 45,                        /* GE  */
  YYSYMBOL_NE = 46,                        /* NE  */
  YYSYMBOL_ADD = 47,                       /* ADD  */
  YYSYMBOL_SUB = 48,                       /* SUB  */
  YYSYMBOL_DIV = 49,                       /* DIV  */
  YYSYMBOL_NOT = 50,                       /* NOT  */
  YYSYMBOL_LIKE = 51,                      /* LIKE  */
  YYSYMBOL_UNIQUE = 52,                    /* UNIQUE  */
  YYSYMBOL_NUMBER = 53,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 54,                     /* FLOAT  */
  YYSYMBOL_ID = 55,                        /* ID  */
  YYSYMBOL_PATH = 56,                      /* PATH  */
  YYSYMBOL_SSS = 57,                       /* SSS  */
  YYSYMBOL_STAR = 58,                      /* STAR  */
  YYSYMBOL_STRING_V = 59,                  /* STRING_V  */
  YYSYMBOL_DATE_STR = 60,                  /* DATE_STR  */
  YYSYMBOL_YYACCEPT = 61,                  /* $accept  */
  YYSYMBOL_commands = 62,                  /* commands  */
  YYSYMBOL_command = 63,                   /* command  */
  YYSYMBOL_exit = 64,                      /* exit  */
  YYSYMBOL_help = 65,                      /* help  */
  YYSYMBOL_sync = 66,                      /* sync  */
  YYSYMBOL_begin = 67,                     /* begin  */
  YYSYMBOL_commit = 68,                    /* commit  */
  YYSYMBOL_rollback = 69,                  /* rollback  */
  YYSYMBOL_drop_table = 70,                /* drop_table  */
  YYSYMBOL_show_tables = 71,               /* show_tables  */
  YYSYMBOL_desc_table = 72,                /* desc_table  */
  YYSYMBOL_create_index = 73,              /* create_index  */
  YYSYMBOL_ix = 74,                        /* ix  */
  YYSYMBOL_ix_list = 75,                   /* ix_list  */
  YYSYMBOL_show_index = 76,                /* show_index  */
  YYSYMBOL_drop_index = 77,                /* drop_index  */
  YYSYMBOL_create_table = 78,              /* create_table  */
  YYSYMBOL_attr_def_list = 79,             /* attr_def_list  */
  YYSYMBOL_attr_def = 80,                  /* attr_def  */
  YYSYMBOL_number = 81,                    /* number  */
  YYSYMBOL_type = 82,                      /* type  */
  YYSYMBOL_ID_get = 83,                    /* ID_get  */
  YYSYMBOL_insert = 84,                    /* insert  */
  YYSYMBOL_row_values_list = 85,           /* row_values_list  */
  YYSYMBOL_row_values = 86,                /* row_values  */
  YYSYMBOL_value_list = 87,                /* value_list  */
  YYSYMBOL_unary_expr = 88,                /* unary_expr  */
  YYSYMBOL_mul_expr = 89,                  /* mul_expr  */
  YYSYMBOL_add_expr = 90,                  /* add_expr  */
  YYSYMBOL_condition = 91,                 /* condition  */
  YYSYMBOL_value = 92,                     /* value  */
  YYSYMBOL_delete = 93,                    /* delete  */
  YYSYMBOL_update = 94,                    /* update  */
  YYSYMBOL_select = 95,                    /* select  */
  YYSYMBOL_select_attr = 96,               /* select_attr  */
  YYSYMBOL_attr_list = 97,                 /* attr_list  */
  YYSYMBOL_rel_list = 98,                  /* rel_list  */
  YYSYMBOL_inner_join_condition_lists = 99, /* inner_join_condition_lists  */
  YYSYMBOL_where = 100,                    /* where  */
  YYSYMBOL_condition_list = 101,           /* condition_list  */
  YYSYMBOL_comOp = 102,                    /* comOp  */
  YYSYMBOL_load_data = 103                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   208

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  215

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   315


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   148,   148,   150,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   175,   180,   185,   191,   197,   203,   209,   215,
     221,   228,   232,   239,   245,   245,   252,   260,   267,   276,
     278,   282,   293,   306,   309,   310,   311,   312,   315,   324,
     338,   339,   345,   353,   355,   361,   368,   377,   386,   393,
     396,   411,   418,   428,   429,   436,   446,   454,   457,   460,
     463,   466,   470,   478,   488,   498,   517,   522,   527,   534,
     536,   541,   546,   553,   555,   558,   562,   563,   567,   569,
     573,   575,   727,   728,   729,   730,   731,   732,   733,   734,
     738
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "INNER", "JOIN", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE",
  "GE", "NE", "ADD", "SUB", "DIV", "NOT", "LIKE", "UNIQUE", "NUMBER",
  "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "DATE_STR", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "ix", "ix_list", "show_index", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "insert",
  "row_values_list", "row_values", "value_list", "unary_expr", "mul_expr",
  "add_expr", "condition", "value", "delete", "update", "select",
  "select_attr", "attr_list", "rel_list", "inner_join_condition_lists",
  "where", "condition_list", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-183)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -183,    97,  -183,    -4,     7,     5,     9,    28,    21,    40,
      45,    25,    92,   102,   110,   118,   119,    61,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,  -183,  -183,    70,    71,   130,
      84,    85,   -10,    24,  -183,  -183,   113,  -183,   124,  -183,
    -183,   -31,    56,  -183,   112,   141,   142,   115,  -183,    93,
      94,   116,  -183,  -183,  -183,  -183,  -183,   107,   135,   117,
      98,   149,   152,   128,    -6,    29,  -183,  -183,  -183,   -27,
      13,  -183,    39,    39,   -10,   -10,  -183,   103,  -183,  -183,
     105,   127,   129,   108,   109,   114,   120,   125,  -183,  -183,
     121,  -183,  -183,  -183,  -183,   124,   136,   124,    56,  -183,
    -183,   -31,   -31,    -1,   162,   151,   -10,   165,   131,   144,
    -183,   153,    66,   154,   122,  -183,   -25,  -183,  -183,   123,
     138,   129,  -183,   -34,   161,    86,   147,  -183,   -34,   175,
     114,   166,  -183,  -183,  -183,  -183,   168,   132,   169,   124,
      -1,   133,   179,   171,   151,   183,  -183,  -183,  -183,  -183,
    -183,  -183,   139,  -183,   -10,   -10,  -183,   129,   137,   153,
     188,   140,  -183,   176,   132,  -183,  -183,   158,  -183,   -34,
     180,   161,  -183,  -183,    67,   147,   193,   195,  -183,  -183,
    -183,   182,   132,   184,   176,   -10,    -1,   171,  -183,  -183,
    -183,  -183,  -183,  -183,   176,   197,   185,   147,  -183,  -183,
    -183,  -183,   200,  -183,  -183
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,    19,     0,     0,     0,
       0,     0,     0,     0,    67,    69,    56,    71,    79,    72,
      59,    63,    79,    55,     0,     0,     0,     0,    24,     0,
       0,     0,    25,    26,    27,    23,    22,     0,     0,     0,
       0,     0,     0,    56,     0,     0,    67,    69,    60,     0,
       0,    76,     0,     0,     0,     0,    78,     0,    30,    29,
       0,     0,    88,     0,     0,     0,     0,     0,    28,    37,
       0,    58,    68,    70,    57,    79,    56,    79,    79,    62,
      61,    64,    65,    83,     0,     0,     0,     0,     0,     0,
      48,    39,     0,     0,     0,    77,     0,    80,    82,     0,
       0,    88,    36,     0,    50,     0,    90,    73,     0,     0,
       0,     0,    44,    45,    46,    47,    42,     0,     0,    79,
      83,     0,     0,    53,     0,     0,    92,    93,    94,    95,
      96,    97,     0,    98,     0,     0,    89,    88,     0,    39,
       0,     0,    33,    34,     0,    81,    84,    86,    75,     0,
       0,    50,    49,    99,    66,    90,     0,     0,    40,    38,
      43,     0,     0,     0,    34,     0,    83,    53,    52,    51,
      91,    74,   100,    41,    34,     0,     0,    90,    85,    54,
      35,    31,     0,    87,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,  -167,  -182,  -183,  -183,  -183,    36,    64,
    -183,  -183,  -183,  -183,    26,    52,    11,     3,    35,    -5,
    -156,  -130,  -183,  -183,  -183,  -183,   -51,  -145,  -183,  -115,
    -175,  -183,  -183
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   173,   193,    29,    30,    31,   141,   121,
     191,   146,   122,    32,   155,   134,   180,    50,    51,   135,
     136,    53,    33,    34,    35,    54,    81,   131,   196,   117,
     166,   164,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      52,    86,    37,   153,    38,   176,    42,   194,   167,   185,
     200,   101,   206,    40,    75,    41,   152,   129,    82,    44,
      45,    42,   210,    47,    58,   204,    49,    83,   104,    42,
     104,   105,   213,   149,   130,    56,    57,    74,    43,   207,
      42,    84,    85,    44,    45,    73,    78,    47,    39,   197,
      49,   208,   186,    43,   125,    42,   127,   128,    44,    45,
      46,    43,    47,    48,    55,    49,    44,    45,   106,    59,
      47,   107,    75,    49,    80,   108,    60,    76,    77,    73,
      61,    47,   102,   103,    49,   109,   110,    75,   142,   143,
     144,   145,    44,    45,    73,    62,    47,     2,   175,    49,
      67,     3,     4,    84,    85,    63,     5,     6,     7,     8,
       9,    10,    11,    64,    84,    85,    12,    13,    14,   111,
     112,    65,    66,    15,    16,    68,    69,   156,   157,   158,
     159,   160,   161,    84,    85,    17,   162,   163,    70,    71,
      72,    79,    80,    87,    88,    89,    90,    94,    91,    92,
      93,    95,    98,    97,    96,    99,   100,   115,   113,   184,
     114,   116,   124,   118,   126,   132,   119,   133,   137,   120,
     147,   140,   138,   139,   151,   123,   104,   148,   150,   154,
     165,   168,   178,   170,   171,   174,   182,   172,   177,   179,
     183,   189,   187,   190,   192,   195,   201,   198,   202,   203,
     211,   205,   212,   214,   169,   188,   181,   199,   209
};

static const yytype_uint8 yycheck[] =
{
       5,    52,     6,   133,     8,   150,    16,   174,   138,   165,
     185,    17,   194,     6,    48,     8,   131,    18,    49,    53,
      54,    16,   204,    57,     3,   192,    60,    58,    55,    16,
      55,    58,   207,    58,    35,     7,     8,    42,    48,   195,
      16,    47,    48,    53,    54,    55,    43,    57,    52,   179,
      60,   196,   167,    48,   105,    16,   107,   108,    53,    54,
      55,    48,    57,    58,    55,    60,    53,    54,    55,    29,
      57,    58,    48,    60,    18,    80,    31,    53,    54,    55,
      55,    57,    53,    54,    60,    82,    83,    48,    22,    23,
      24,    25,    53,    54,    55,     3,    57,     0,   149,    60,
      39,     4,     5,    47,    48,     3,     9,    10,    11,    12,
      13,    14,    15,     3,    47,    48,    19,    20,    21,    84,
      85,     3,     3,    26,    27,    55,    55,    41,    42,    43,
      44,    45,    46,    47,    48,    38,    50,    51,     8,    55,
      55,    28,    18,    31,     3,     3,    31,    40,    55,    55,
      34,    16,     3,    55,    37,     3,    28,    30,    55,   164,
      55,    32,    37,    55,    28,     3,    57,    16,     3,    55,
      16,    18,    41,    29,    36,    55,    55,    55,    55,    18,
      33,     6,     3,    17,    16,    16,     3,    55,    55,    18,
      51,     3,    55,    53,    18,    37,     3,    17,     3,    17,
       3,    17,    17,     3,   140,   169,   154,   181,   197
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    62,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    38,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    76,
      77,    78,    84,    93,    94,    95,   103,     6,     8,    52,
       6,     8,    16,    48,    53,    54,    55,    57,    58,    60,
      88,    89,    90,    92,    96,    55,     7,     8,     3,    29,
      31,    55,     3,     3,     3,     3,     3,    39,    55,    55,
       8,    55,    55,    55,    90,    48,    53,    54,    88,    28,
      18,    97,    49,    58,    47,    48,    97,    31,     3,     3,
      31,    55,    55,    34,    40,    16,    37,    55,     3,     3,
      28,    17,    53,    54,    55,    58,    55,    58,    90,    88,
      88,    89,    89,    55,    55,    30,    32,   100,    55,    57,
      55,    80,    83,    55,    37,    97,    28,    97,    97,    18,
      35,    98,     3,    16,    86,    90,    91,     3,    41,    29,
      18,    79,    22,    23,    24,    25,    82,    16,    55,    58,
      55,    36,   100,    92,    18,    85,    41,    42,    43,    44,
      45,    46,    50,    51,   102,    33,   101,    92,     6,    80,
      17,    16,    55,    74,    16,    97,    98,    55,     3,    18,
      87,    86,     3,    51,    90,    91,   100,    55,    79,     3,
      53,    81,    18,    75,    74,    37,    99,    92,    17,    85,
     101,     3,     3,    17,    74,    17,    75,    91,    98,    87,
      75,     3,    17,   101,     3
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    61,    62,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    73,    74,    75,    75,    76,    77,    78,    79,
      79,    80,    80,    81,    82,    82,    82,    82,    83,    84,
      85,    85,    86,    87,    87,    88,    88,    88,    88,    89,
      89,    89,    89,    90,    90,    90,    91,    92,    92,    92,
      92,    92,    92,    93,    94,    95,    96,    96,    96,    97,
      97,    97,    97,    98,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   102,   102,   102,   102,   102,   102,
     103
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,    10,    11,     1,     0,     3,     5,     4,     8,     0,
       3,     5,     2,     1,     1,     1,     1,     1,     1,     7,
       0,     3,     4,     0,     3,     1,     1,     3,     3,     1,
       2,     3,     3,     1,     3,     3,     3,     1,     2,     1,
       2,     1,     1,     5,     8,     7,     2,     4,     2,     0,
       3,     5,     3,     0,     3,     5,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     2,
       8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 22: /* exit: EXIT SEMICOLON  */
#line 175 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1375 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 180 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1383 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 185 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1391 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 191 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1399 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 197 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1407 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 203 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1415 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 209 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1424 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 215 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1432 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 221 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1441 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE ix ix_list RBRACE SEMICOLON  */
#line 228 "yacc_sql.y"
                                                             {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, false, (yyvsp[-7].string), (yyvsp[-5].string));
		}
#line 1450 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ix ix_list RBRACE SEMICOLON  */
#line 233 "yacc_sql.y"
            {
	        CONTEXT->ssql->flag = SCF_CREATE_INDEX;
	        create_index_init(&CONTEXT->ssql->sstr.create_index, true, (yyvsp[-7].string), (yyvsp[-5].string));
	    }
#line 1459 "yacc_sql.tab.c"
    break;

  case 33: /* ix: ID  */
#line 240 "yacc_sql.y"
    {
        create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
    }
#line 1467 "yacc_sql.tab.c"
    break;

  case 35: /* ix_list: COMMA ix ix_list  */
#line 246 "yacc_sql.y"
    {

    }
#line 1475 "yacc_sql.tab.c"
    break;

  case 36: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 253 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_SHOW_INDEX;
            desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
        }
#line 1484 "yacc_sql.tab.c"
    break;

  case 37: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 261 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1493 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 268 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1505 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 278 "yacc_sql.y"
                                   {    }
#line 1511 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 283 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1526 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type  */
#line 294 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1541 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 306 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1547 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 309 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1553 "yacc_sql.tab.c"
    break;

  case 45: /* type: STRING_T  */
#line 310 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1559 "yacc_sql.tab.c"
    break;

  case 46: /* type: FLOAT_T  */
#line 311 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1565 "yacc_sql.tab.c"
    break;

  case 47: /* type: DATE_T  */
#line 312 "yacc_sql.y"
                { (yyval.number)=DATE; }
#line 1571 "yacc_sql.tab.c"
    break;

  case 48: /* ID_get: ID  */
#line 316 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1580 "yacc_sql.tab.c"
    break;

  case 49: /* insert: INSERT INTO ID VALUES row_values row_values_list SEMICOLON  */
#line 325 "yacc_sql.y"
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			//inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->values, CONTEXT->value_length);
            inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 1597 "yacc_sql.tab.c"
    break;

  case 51: /* row_values_list: COMMA row_values row_values_list  */
#line 340 "yacc_sql.y"
            {
            //Nothing to do here
     }
#line 1605 "yacc_sql.tab.c"
    break;

  case 52: /* row_values: LBRACE value value_list RBRACE  */
#line 346 "yacc_sql.y"
        {
            inserts_data_init(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
            memset(CONTEXT->values, 0, sizeof(CONTEXT->values));
            //临时变量清零
            CONTEXT->value_length=0;
     }
#line 1616 "yacc_sql.tab.c"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 355 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1624 "yacc_sql.tab.c"
    break;

  case 55: /* unary_expr: value  */
#line 361 "yacc_sql.y"
          {
        Expr *expr = malloc(sizeof(Expr));
        UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
        unary_expr_init_value(u_expr, &CONTEXT->values[CONTEXT->value_length-1]);
        expr_init_unary(expr, u_expr);
        (yyval.exp1) = expr;
    }
#line 1636 "yacc_sql.tab.c"
    break;

  case 56: /* unary_expr: ID  */
#line 368 "yacc_sql.y"
         {
    	Expr *expr = malloc(sizeof(Expr));
        RelAttr* attr = malloc(sizeof(RelAttr));
        relation_attr_init(attr, NULL, (yyvsp[0].string));
        UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
        unary_expr_init_attr(u_expr, attr);
        expr_init_unary(expr, u_expr);
        (yyval.exp1) = expr;
    }
#line 1650 "yacc_sql.tab.c"
    break;

  case 57: /* unary_expr: ID DOT ID  */
#line 377 "yacc_sql.y"
                {
    	Expr *expr = malloc(sizeof(Expr));
        RelAttr* attr = malloc(sizeof(RelAttr));
        relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
        UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
        unary_expr_init_attr(u_expr, &attr);
        expr_init_unary(expr, u_expr);
        (yyval.exp1) = expr;
    }
#line 1664 "yacc_sql.tab.c"
    break;

  case 58: /* unary_expr: LBRACE add_expr RBRACE  */
#line 386 "yacc_sql.y"
                             {
        expr_set_with_brace((yyvsp[-1].exp3));
        (yyval.exp1) = (yyvsp[-1].exp3);
    }
#line 1673 "yacc_sql.tab.c"
    break;

  case 59: /* mul_expr: unary_expr  */
#line 393 "yacc_sql.y"
               {
        (yyval.exp2) = (yyvsp[0].exp1);
    }
#line 1681 "yacc_sql.tab.c"
    break;

  case 60: /* mul_expr: SUB unary_expr  */
#line 396 "yacc_sql.y"
                     {
        Value * tmp_val = malloc(sizeof(Value));
        value_init_integer(tmp_val, -1);
        UnaryExpr * tmp_uexpr = malloc(sizeof(UnaryExpr));
        unary_expr_init_value(tmp_uexpr, tmp_val);
        Expr * tmp_expr = malloc(sizeof(Expr));
        expr_init_unary(tmp_expr, tmp_uexpr);

        Expr * expr = malloc(sizeof(Expr));
        BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
        binary_expr_init(b_expr, MUL_OP, tmp_expr, (yyvsp[0].exp1));
        binary_expr_set_minus(b_expr);
        expr_init_binary(expr, b_expr);
        (yyval.exp2) = expr;
    }
#line 1701 "yacc_sql.tab.c"
    break;

  case 61: /* mul_expr: mul_expr STAR unary_expr  */
#line 411 "yacc_sql.y"
                               {
        Expr * expr = malloc(sizeof(Expr));
        BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
        binary_expr_init(b_expr, MUL_OP, (yyvsp[-2].exp2), (yyvsp[0].exp1));
        expr_init_binary(expr, b_expr);
        (yyval.exp2) = expr;
    }
#line 1713 "yacc_sql.tab.c"
    break;

  case 62: /* mul_expr: mul_expr DIV unary_expr  */
#line 418 "yacc_sql.y"
                              {
    	Expr * expr = malloc(sizeof(Expr));
        BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
        binary_expr_init(b_expr, DIV_OP, (yyvsp[-2].exp2), (yyvsp[0].exp1));
        expr_init_binary(expr, b_expr);
        (yyval.exp2) = expr;
    }
#line 1725 "yacc_sql.tab.c"
    break;

  case 63: /* add_expr: mul_expr  */
#line 428 "yacc_sql.y"
             { (yyval.exp3) = (yyvsp[0].exp2); }
#line 1731 "yacc_sql.tab.c"
    break;

  case 64: /* add_expr: add_expr ADD mul_expr  */
#line 429 "yacc_sql.y"
                            {
    	Expr * expr = malloc(sizeof(Expr));
        BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
        binary_expr_init(b_expr, ADD_OP, (yyvsp[-2].exp3), (yyvsp[0].exp2));
        expr_init_binary(expr, b_expr);
        (yyval.exp3) = expr;
    }
#line 1743 "yacc_sql.tab.c"
    break;

  case 65: /* add_expr: add_expr SUB mul_expr  */
#line 436 "yacc_sql.y"
                            {
    	Expr * expr = malloc(sizeof(Expr));
        BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
        binary_expr_init(b_expr, SUB_OP, (yyvsp[-2].exp3), (yyvsp[0].exp2));
        expr_init_binary(expr, b_expr);
        (yyval.exp3) = expr;
    }
#line 1755 "yacc_sql.tab.c"
    break;

  case 66: /* condition: add_expr comOp add_expr  */
#line 446 "yacc_sql.y"
                           {
        Condition* expr = malloc(sizeof(Condition));
        condition_init(expr, CONTEXT->comp, (yyvsp[-2].exp3), (yyvsp[0].exp3));
        CONTEXT->conditions[CONTEXT->condition_length++] = *expr;
    }
#line 1765 "yacc_sql.tab.c"
    break;

  case 67: /* value: NUMBER  */
#line 454 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1773 "yacc_sql.tab.c"
    break;

  case 68: /* value: SUB NUMBER  */
#line 457 "yacc_sql.y"
                   {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].number)));
    	}
#line 1781 "yacc_sql.tab.c"
    break;

  case 69: /* value: FLOAT  */
#line 460 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1789 "yacc_sql.tab.c"
    break;

  case 70: /* value: SUB FLOAT  */
#line 463 "yacc_sql.y"
                  {
        value_init_float(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].floats)));
        }
#line 1797 "yacc_sql.tab.c"
    break;

  case 71: /* value: SSS  */
#line 466 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1806 "yacc_sql.tab.c"
    break;

  case 72: /* value: DATE_STR  */
#line 470 "yacc_sql.y"
                 {
	        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
	    if(0 != value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string)))
	        return -1;
	}
#line 1816 "yacc_sql.tab.c"
    break;

  case 73: /* delete: DELETE FROM ID where SEMICOLON  */
#line 479 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1828 "yacc_sql.tab.c"
    break;

  case 74: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 489 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1840 "yacc_sql.tab.c"
    break;

  case 75: /* select: SELECT select_attr FROM ID rel_list where SEMICOLON  */
#line 499 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1860 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr: STAR attr_list  */
#line 517 "yacc_sql.y"
                   {
        ProjectCol project_col;
        project_init_star(&project_col, NULL);
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
#line 1870 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: ID DOT STAR attr_list  */
#line 522 "yacc_sql.y"
                           {
        ProjectCol project_col;
        project_init_star(&project_col, (yyvsp[-3].string));
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
#line 1880 "yacc_sql.tab.c"
    break;

  case 78: /* select_attr: add_expr attr_list  */
#line 527 "yacc_sql.y"
                        {
        ProjectCol project_col;
        project_init_expr(&project_col, (yyvsp[-1].exp3));
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
#line 1890 "yacc_sql.tab.c"
    break;

  case 80: /* attr_list: COMMA STAR attr_list  */
#line 536 "yacc_sql.y"
                          {
        ProjectCol project_col;
        project_init_star(&project_col, NULL);
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
#line 1900 "yacc_sql.tab.c"
    break;

  case 81: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 541 "yacc_sql.y"
                                 {
        ProjectCol project_col;
        project_init_star(&project_col, (yyvsp[-3].string));
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
#line 1910 "yacc_sql.tab.c"
    break;

  case 82: /* attr_list: COMMA add_expr attr_list  */
#line 546 "yacc_sql.y"
                              {
        ProjectCol project_col;
        project_init_expr(&project_col, (yyvsp[-1].exp3));
        selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
#line 1920 "yacc_sql.tab.c"
    break;

  case 84: /* rel_list: COMMA ID rel_list  */
#line 555 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 1928 "yacc_sql.tab.c"
    break;

  case 85: /* rel_list: INNER JOIN ID inner_join_condition_lists rel_list  */
#line 558 "yacc_sql.y"
                                                        {
                selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
          }
#line 1936 "yacc_sql.tab.c"
    break;

  case 87: /* inner_join_condition_lists: ON condition condition_list  */
#line 563 "yacc_sql.y"
                                  {

         }
#line 1944 "yacc_sql.tab.c"
    break;

  case 89: /* where: WHERE condition condition_list  */
#line 569 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1952 "yacc_sql.tab.c"
    break;

  case 91: /* condition_list: AND condition condition_list  */
#line 575 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1960 "yacc_sql.tab.c"
    break;

  case 92: /* comOp: EQ  */
#line 727 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 1966 "yacc_sql.tab.c"
    break;

  case 93: /* comOp: LT  */
#line 728 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 1972 "yacc_sql.tab.c"
    break;

  case 94: /* comOp: GT  */
#line 729 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 1978 "yacc_sql.tab.c"
    break;

  case 95: /* comOp: LE  */
#line 730 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 1984 "yacc_sql.tab.c"
    break;

  case 96: /* comOp: GE  */
#line 731 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 1990 "yacc_sql.tab.c"
    break;

  case 97: /* comOp: NE  */
#line 732 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 1996 "yacc_sql.tab.c"
    break;

  case 98: /* comOp: LIKE  */
#line 733 "yacc_sql.y"
           { CONTEXT->comp = LIKE_OP; }
#line 2002 "yacc_sql.tab.c"
    break;

  case 99: /* comOp: NOT LIKE  */
#line 734 "yacc_sql.y"
               { CONTEXT->comp = NOT_LIKE_OP; }
#line 2008 "yacc_sql.tab.c"
    break;

  case 100: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 739 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2017 "yacc_sql.tab.c"
    break;


#line 2021 "yacc_sql.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 744 "yacc_sql.y"

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
