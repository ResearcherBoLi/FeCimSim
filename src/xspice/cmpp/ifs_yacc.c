/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:339  */


/*============================================================================
FILE  ifs_yacc.y

MEMBER OF process cmpp

Copyright 1991
Georgia Tech Research Corporation
Atlanta, Georgia 30332
All Rights Reserved

PROJECT A-8503

AUTHORS

    9/12/91  Steve Tynor

MODIFICATIONS

    12/31/91  Bill Kuhn  Fix bug in usage of strcmp in check_default_type()

SUMMARY

    This file contains the BNF specification of the language used in
    the ifspec.ifs file together with various support functions,
    and parses the ifspec.ifs file to get the information from it
    and place this information into a data structure
    of type Ifs_Table_t.

INTERFACES

    yyparse()     -    Generated automatically by UNIX 'yacc' utility.

REFERENCED FILES

    ifs_lex.l

NON-STANDARD FEATURES

    None.

============================================================================*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ifs_yacc_y.h"

#define	yymaxdepth ifs_yymaxdepth
#define	yyparse	ifs_yyparse
#define	yylex	ifs_yylex
#define	yyerror	ifs_yyerror
#define	yylval	ifs_yylval
#define	yychar	ifs_yychar
#define	yydebug	ifs_yydebug
#define	yypact	ifs_yypact
#define	yyr1	ifs_yyr1
#define	yyr2	ifs_yyr2
#define	yydef	ifs_yydef
#define	yychk	ifs_yychk
#define	yypgo	ifs_yypgo
#define	yyact	ifs_yyact
#define	yyexca	ifs_yyexca
#define yyerrflag ifs_yyerrflag
#define yynerrs	ifs_yynerrs
#define	yyps	ifs_yyps
#define	yypv	ifs_yypv
#define	yys	ifs_yys
#define	yy_yys	ifs_yyyys
#define	yystate	ifs_yystate
#define	yytmp	ifs_yytmp
#define	yyv	ifs_yyv
#define	yy_yyv	ifs_yyyyv
#define	yyval	ifs_yyval
#define	yylloc	ifs_yylloc
#define yyreds	ifs_yyreds
#define yytoks	ifs_yytoks
#define yylhs	ifs_yyyylhs
#define yylen	ifs_yyyylen
#define yydefred ifs_yyyydefred
#define yydgoto	ifs_yyyydgoto
#define yysindex ifs_yyyysindex
#define yyrindex ifs_yyyyrindex
#define yygindex ifs_yyyygindex
#define yytable	 ifs_yyyytable
#define yycheck	 ifs_yyyycheck
#define yyname   ifs_yyyyname
#define yyrule   ifs_yyyyrule

extern int yylineno;
extern int yyival;
extern double yydval;
extern char *ifs_yytext;
 extern int ifs_yylex(void);

bool parser_just_names;
static bool saw_model_name;
static bool saw_function_name;

static char *dtype_to_str[] = {
   "BOOLEAN", "INTEGER", "REAL", "COMPLEX", "STRING", "POINTER"
   };

static bool did_default_type;
static bool did_allowed_types;

static int num_items;
static int item;
static int item_offset;
static bool num_items_fixed;

Ifs_Table_t *parser_ifs_table;
#define TBL parser_ifs_table

int ifs_num_errors;

static size_t alloced_size [4];

/*
 * !!!!! Make sure these are large enough so that they never get realloced
 * !!!!! since that will cause garbage uninitialized data...
 * !!!!! (FIX THIS!)
 */
#define DEFAULT_SIZE_CONN	100
#define DEFAULT_SIZE_PARAM	100
#define DEFAULT_SIZE_INST_VAR	100
#define GROW_SIZE		10

typedef enum {
   TBL_NAME,
   TBL_PORT,
   TBL_PARAMETER,
   TBL_STATIC_VAR,
} Table_t;

typedef struct {
   Table_t table;
   int record;
} Context_t;

Context_t context;

#define ITEM_BUFFER_SIZE 20	/* number of items that can be put in a table
				 * before requiring a new xxx_TABLE: keyword
				 */
#define FOR_ITEM(i) for (i = item_offset; i < num_items; i++)
#define ITEM_BUF(i) item_buffer[i-item_offset]

#define ASSIGN_BOUNDS(struct_name, i) \
  if (ITEM_BUF(i).range.is_named) {\
    TBL->struct_name[i].has_conn_ref = true;\
    TBL->struct_name[i].conn_ref = find_conn_ref (ITEM_BUF(i).range.u.name);\
  } else {\
    TBL->struct_name[i].has_conn_ref = false;\
    TBL->struct_name[i].has_lower_bound =\
       ITEM_BUF(i).range.u.bounds.lower.has_bound;\
    TBL->struct_name[i].has_upper_bound =\
       ITEM_BUF(i).range.u.bounds.upper.has_bound;\
    if (TBL->struct_name[i].has_lower_bound) {\
      assert (ITEM_BUF(i).range.u.bounds.lower.bound.kind == CMPP_INTEGER);\
       TBL->struct_name[i].lower_bound =\
	ITEM_BUF(i).range.u.bounds.lower.bound.u.ivalue;\
    }\
    if (TBL->struct_name[i].has_upper_bound) {\
       assert (ITEM_BUF(i).range.u.bounds.upper.bound.kind == CMPP_INTEGER);\
       TBL->struct_name[i].upper_bound =\
	  ITEM_BUF(i).range.u.bounds.upper.bound.u.ivalue;\
    }\
  }

/*---------------------------------------------------------------------------*/
static void fatal (char *str)
{
   yyerror (str);
   exit(1);
}

/*---------------------------------------------------------------------------*/
static int
find_conn_ref (char *name)
{
   int i;
   char str[130];
   
   for (i = 0; i < TBL->num_conn; i++) {
      if (strcmp (name, TBL->conn[i].name) == 0) {
	 return i;
      }
   }
   sprintf (str, "Port `%s' not found", name);
   yyerror (str);
   ifs_num_errors++;

   return 0;
}

typedef enum {C_DOUBLE, C_BOOLEAN, C_POINTER, C_UNDEF} Ctype_Class_t;

/*---------------------------------------------------------------------------*/
static Ctype_Class_t get_ctype_class (Port_Type_t type)
{
   switch (type) {
   case USER_DEFINED:
      return C_POINTER;
      break;
   case DIGITAL:
      return C_BOOLEAN;
      break;
   default:
      return C_DOUBLE;
      break;
   }
}

/*---------------------------------------------------------------------------*/
static void check_port_type_direction (Dir_t dir, Port_Type_t port_type)
{
   switch (port_type) {
   case VOLTAGE:
   case DIFF_VOLTAGE:
   case CURRENT:
   case DIFF_CURRENT:
   case DIGITAL:
   case USER_DEFINED:
      /*
       * anything goes
       */
      break;
   case VSOURCE_CURRENT:
      if (dir != CMPP_IN) {
	 yyerror ("Port type `vnam' is only valid for `in' ports");
	 ifs_num_errors++;
      }
      break;
   case CONDUCTANCE:
   case DIFF_CONDUCTANCE:
   case RESISTANCE:
   case DIFF_RESISTANCE:
      if (dir != CMPP_INOUT) {
	 yyerror ("Port types `g', `gd', `h', `hd' are only valid for `inout' ports");
	 ifs_num_errors++;
      }
      break;
   default:
      assert (0);
   }
}

/*---------------------------------------------------------------------------*/
static void check_dtype_not_pointer (Data_Type_t dtype)
{
   if (dtype == CMPP_POINTER) {
      yyerror("Invalid parameter type - POINTER type valid only for STATIC_VARs");
      ifs_num_errors++;
   }
}

/*---------------------------------------------------------------------------*/
static void check_default_type (Conn_Info_t conn)
{
   int i;
   
   for (i = 0; i < conn.num_allowed_types; i++) {
      if (conn.default_port_type == conn.allowed_port_type[i]) {
	 if ((conn.default_port_type != USER_DEFINED) ||
	     (strcmp (conn.default_type, conn.allowed_type[i]) == 0)) {
	    return;
	 }
      }
   }
   yyerror ("Port default type is not an allowed type");
   ifs_num_errors++;
}

/*---------------------------------------------------------------------------*/
static void
assign_ctype_list (Conn_Info_t  *conn, Ctype_List_t *ctype_list )
{
   int i;
   Ctype_List_t *p;
   Ctype_Class_t ctype_class = C_UNDEF;
   
   conn->num_allowed_types = 0;
   for (p = ctype_list; p; p = p->next) {
      conn->num_allowed_types++;
   }
   conn->allowed_type = (char**) calloc ((size_t) conn->num_allowed_types,
					 sizeof (char*));
   conn->allowed_port_type = (Port_Type_t*) calloc ((size_t) conn->num_allowed_types,
						    sizeof (Port_Type_t));
   if (! (conn->allowed_type && conn->allowed_port_type)) {
      fatal ("Could not allocate memory");
   }
   for (i = conn->num_allowed_types-1, p = ctype_list; p; i--, p = p->next) {
      if (ctype_class == C_UNDEF) {
	 ctype_class = get_ctype_class (p->ctype.kind);
      }
      if (ctype_class != get_ctype_class (p->ctype.kind)) {
	 yyerror ("Incompatible port types in `allowed_types' clause");
	 ifs_num_errors++;
      }
      check_port_type_direction (conn->direction, p->ctype.kind);
      
      conn->allowed_port_type[i] = p->ctype.kind;
      conn->allowed_type[i] = p->ctype.id;
   } 
}

/*---------------------------------------------------------------------------*/
static void
assign_value (Data_Type_t type, Value_t *dest_value, My_Value_t src_value)
{
   char str[200];
   if ((type == CMPP_REAL) && (src_value.kind == CMPP_INTEGER)) {
      dest_value->rvalue = src_value.u.ivalue;
      return;
   } else if (type != src_value.kind) {
      sprintf (str, "Invalid parameter type (saw %s - expected %s)",
	       dtype_to_str[src_value.kind],
	       dtype_to_str[type] );
      yyerror (str);
      ifs_num_errors++;
   } 
   switch (type) {
   case CMPP_BOOLEAN:
      dest_value->bvalue = src_value.u.bvalue;
      break;
   case CMPP_INTEGER:
      dest_value->ivalue = src_value.u.ivalue;
      break;
   case CMPP_REAL:
      dest_value->rvalue = src_value.u.rvalue;
      break;
   case CMPP_COMPLEX:
      dest_value->cvalue = src_value.u.cvalue;
      break;
   case CMPP_STRING:
      dest_value->svalue = src_value.u.svalue;
      break;
   default:
      yyerror ("INTERNAL ERROR - unexpected data type in `assign_value'");
      ifs_num_errors++;
   }
}   

/*---------------------------------------------------------------------------*/
static void
assign_limits (Data_Type_t type, Param_Info_t *param, Range_t range)
{
   if (range.is_named) {
      yyerror ("Named range not allowed for limits");
      ifs_num_errors++;
   }
   param->has_lower_limit = range.u.bounds.lower.has_bound;
   if (param->has_lower_limit) {
      assign_value (type, &param->lower_limit, range.u.bounds.lower.bound);
   }
   param->has_upper_limit = range.u.bounds.upper.has_bound;
   if (param->has_upper_limit) {
      assign_value (type, &param->upper_limit, range.u.bounds.upper.bound);
   }
}

/*---------------------------------------------------------------------------*/
static void
check_item_num (void)
{
   if (item-item_offset >= ITEM_BUFFER_SIZE) {
      fatal ("Too many items in table - split into sub-tables");
   }
   if (item > (int) alloced_size [context.table] ) {
      switch (context.table) {
      case TBL_NAME:
	 break;
      case TBL_PORT:
	 alloced_size[context.table] += GROW_SIZE;
	 TBL->conn = (Conn_Info_t*)
	    realloc (TBL->conn,
		     alloced_size [context.table] * sizeof (Conn_Info_t));
	 if (! TBL->conn) {
	    fatal ("Error allocating memory for port definition");
	 }
	 break;
      case TBL_PARAMETER:
	 alloced_size [context.table] += GROW_SIZE;
	 TBL->param = (Param_Info_t*)
	    realloc (TBL->param,
		     alloced_size [context.table] * sizeof (Param_Info_t));
	 if (! TBL->param) {
	    fatal ("Error allocating memory for parameter definition");
	 }
	 break;
      case TBL_STATIC_VAR:
	 alloced_size [context.table] += GROW_SIZE;
	 TBL->inst_var = (Inst_Var_Info_t*)
	    realloc (TBL->inst_var,
		     alloced_size [context.table] * sizeof (Inst_Var_Info_t));
	 if (! TBL->inst_var) {
	    fatal ("Error allocating memory for static variable definition");
	 }
	 break;
      }
   }
   item++;
}

/*---------------------------------------------------------------------------*/
static void
check_end_item_num (void)
{
   if (num_items_fixed) {
      if (item != num_items) {
	 char buf[200];
	 sprintf
	    (buf,
	     "Wrong number of elements in sub-table (saw %d - expected %d)",
	     item - item_offset,
	     num_items - item_offset);
	 fatal (buf);
      }
   } else {
      num_items = item;
      num_items_fixed = true;
      switch (context.table) {
      case TBL_NAME:
	 break;
      case TBL_PORT:
	 TBL->num_conn = num_items;
	 break;
      case TBL_PARAMETER:
	 TBL->num_param = num_items;
	 break;
      case TBL_STATIC_VAR:
	 TBL->num_inst_var = num_items;
	 break;
      }
   }
   item = item_offset;
}

#define INIT(n) item = (n); item_offset = (n); num_items = (n); num_items_fixed = false
#define ITEM check_item_num()
#define END  check_end_item_num()
   

#line 513 "ifs_yacc.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "ifs_yacc.h".  */
#ifndef YY_YY_IFS_YACC_H_INCLUDED
# define YY_YY_IFS_YACC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_ALLOWED_TYPES = 258,
    TOK_ARRAY = 259,
    TOK_ARRAY_BOUNDS = 260,
    TOK_BOOL_NO = 261,
    TOK_BOOL_YES = 262,
    TOK_COMMA = 263,
    TOK_PORT_NAME = 264,
    TOK_PORT_TABLE = 265,
    TOK_CTYPE_D = 266,
    TOK_CTYPE_G = 267,
    TOK_CTYPE_GD = 268,
    TOK_CTYPE_H = 269,
    TOK_CTYPE_HD = 270,
    TOK_CTYPE_I = 271,
    TOK_CTYPE_ID = 272,
    TOK_CTYPE_V = 273,
    TOK_CTYPE_VD = 274,
    TOK_CTYPE_VNAM = 275,
    TOK_C_FUNCTION_NAME = 276,
    TOK_DASH = 277,
    TOK_DATA_TYPE = 278,
    TOK_DEFAULT_TYPE = 279,
    TOK_DEFAULT_VALUE = 280,
    TOK_DESCRIPTION = 281,
    TOK_DIRECTION = 282,
    TOK_DIR_IN = 283,
    TOK_DIR_INOUT = 284,
    TOK_DIR_OUT = 285,
    TOK_DTYPE_BOOLEAN = 286,
    TOK_DTYPE_COMPLEX = 287,
    TOK_DTYPE_INT = 288,
    TOK_DTYPE_POINTER = 289,
    TOK_DTYPE_REAL = 290,
    TOK_DTYPE_STRING = 291,
    TOK_IDENTIFIER = 292,
    TOK_STATIC_VAR_NAME = 293,
    TOK_STATIC_VAR_TABLE = 294,
    TOK_INT_LITERAL = 295,
    TOK_LANGLE = 296,
    TOK_LBRACKET = 297,
    TOK_LIMITS = 298,
    TOK_NAME_TABLE = 299,
    TOK_NULL_ALLOWED = 300,
    TOK_PARAMETER_NAME = 301,
    TOK_PARAMETER_TABLE = 302,
    TOK_RANGLE = 303,
    TOK_RBRACKET = 304,
    TOK_REAL_LITERAL = 305,
    TOK_SPICE_MODEL_NAME = 306,
    TOK_STRING_LITERAL = 307
  };
#endif
/* Tokens.  */
#define TOK_ALLOWED_TYPES 258
#define TOK_ARRAY 259
#define TOK_ARRAY_BOUNDS 260
#define TOK_BOOL_NO 261
#define TOK_BOOL_YES 262
#define TOK_COMMA 263
#define TOK_PORT_NAME 264
#define TOK_PORT_TABLE 265
#define TOK_CTYPE_D 266
#define TOK_CTYPE_G 267
#define TOK_CTYPE_GD 268
#define TOK_CTYPE_H 269
#define TOK_CTYPE_HD 270
#define TOK_CTYPE_I 271
#define TOK_CTYPE_ID 272
#define TOK_CTYPE_V 273
#define TOK_CTYPE_VD 274
#define TOK_CTYPE_VNAM 275
#define TOK_C_FUNCTION_NAME 276
#define TOK_DASH 277
#define TOK_DATA_TYPE 278
#define TOK_DEFAULT_TYPE 279
#define TOK_DEFAULT_VALUE 280
#define TOK_DESCRIPTION 281
#define TOK_DIRECTION 282
#define TOK_DIR_IN 283
#define TOK_DIR_INOUT 284
#define TOK_DIR_OUT 285
#define TOK_DTYPE_BOOLEAN 286
#define TOK_DTYPE_COMPLEX 287
#define TOK_DTYPE_INT 288
#define TOK_DTYPE_POINTER 289
#define TOK_DTYPE_REAL 290
#define TOK_DTYPE_STRING 291
#define TOK_IDENTIFIER 292
#define TOK_STATIC_VAR_NAME 293
#define TOK_STATIC_VAR_TABLE 294
#define TOK_INT_LITERAL 295
#define TOK_LANGLE 296
#define TOK_LBRACKET 297
#define TOK_LIMITS 298
#define TOK_NAME_TABLE 299
#define TOK_NULL_ALLOWED 300
#define TOK_PARAMETER_NAME 301
#define TOK_PARAMETER_TABLE 302
#define TOK_RANGLE 303
#define TOK_RBRACKET 304
#define TOK_REAL_LITERAL 305
#define TOK_SPICE_MODEL_NAME 306
#define TOK_STRING_LITERAL 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 499 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:355  */

   Ctype_List_t 	*ctype_list;
   Dir_t		dir;
   bool			btype;
   Range_t		range;
   Data_Type_t		dtype;
   My_Port_Type_t	ctype;
   My_Value_t		value;
   char			*str;
   Bound_t		bound;
   int			ival;
   double		rval;
   Complex_t		cval;

#line 672 "ifs_yacc.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_IFS_YACC_H_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 529 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:358  */

/*
 * resuse the Yacc union for our buffer:
 */
YYSTYPE item_buffer [ITEM_BUFFER_SIZE];

/*
 * Shorthand for refering to the current element of the item buffer:
 */
#define BUF ITEM_BUF(item-1)


#line 701 "ifs_yacc.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   109

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   544,   544,   544,   573,   574,   578,   577,   581,   580,
     588,   587,   593,   592,   599,   600,   603,   607,   611,   615,
     616,   619,   625,   631,   637,   649,   660,   666,   673,   681,
     682,   685,   691,   697,   704,   716,   724,   730,   736,   744,
     745,   748,   754,   760,   766,   774,   775,   778,   779,   782,
     788,   789,   792,   793,   796,   797,   798,   801,   802,   805,
     806,   809,   810,   811,   812,   813,   814,   815,   816,   817,
     818,   819,   823,   824,   827,   828,   829,   830,   831,   832,
     835,   836,   839,   842,   849,   850,   853,   854,   858,   861,
     868,   869,   873,   874,   877,   878,   881,   884,   887,   890,
     893,   898,   899,   903,   906,   914,   927,   928,   931,   934,
     937,   940,   943,   948,   951
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_ALLOWED_TYPES", "TOK_ARRAY",
  "TOK_ARRAY_BOUNDS", "TOK_BOOL_NO", "TOK_BOOL_YES", "TOK_COMMA",
  "TOK_PORT_NAME", "TOK_PORT_TABLE", "TOK_CTYPE_D", "TOK_CTYPE_G",
  "TOK_CTYPE_GD", "TOK_CTYPE_H", "TOK_CTYPE_HD", "TOK_CTYPE_I",
  "TOK_CTYPE_ID", "TOK_CTYPE_V", "TOK_CTYPE_VD", "TOK_CTYPE_VNAM",
  "TOK_C_FUNCTION_NAME", "TOK_DASH", "TOK_DATA_TYPE", "TOK_DEFAULT_TYPE",
  "TOK_DEFAULT_VALUE", "TOK_DESCRIPTION", "TOK_DIRECTION", "TOK_DIR_IN",
  "TOK_DIR_INOUT", "TOK_DIR_OUT", "TOK_DTYPE_BOOLEAN", "TOK_DTYPE_COMPLEX",
  "TOK_DTYPE_INT", "TOK_DTYPE_POINTER", "TOK_DTYPE_REAL",
  "TOK_DTYPE_STRING", "TOK_IDENTIFIER", "TOK_STATIC_VAR_NAME",
  "TOK_STATIC_VAR_TABLE", "TOK_INT_LITERAL", "TOK_LANGLE", "TOK_LBRACKET",
  "TOK_LIMITS", "TOK_NAME_TABLE", "TOK_NULL_ALLOWED", "TOK_PARAMETER_NAME",
  "TOK_PARAMETER_TABLE", "TOK_RANGLE", "TOK_RBRACKET", "TOK_REAL_LITERAL",
  "TOK_SPICE_MODEL_NAME", "TOK_STRING_LITERAL", "$accept", "ifs_file",
  "$@1", "list_of_tables", "table", "$@2", "$@3", "$@4", "$@5",
  "name_table", "name_table_item", "port_table", "port_table_item",
  "parameter_table", "parameter_table_item", "static_var_table",
  "static_var_table_item", "list_of_ids", "list_of_array_bounds",
  "list_of_strings", "list_of_directions", "direction", "list_of_bool",
  "list_of_ctypes", "ctype", "list_of_dtypes", "dtype", "list_of_ranges",
  "int_range", "maybe_comma", "int_or_dash", "range", "number_or_dash",
  "list_of_values", "value_or_dash", "value", "complex",
  "list_of_ctype_lists", "delimited_ctype_list", "ctype_list", "btype",
  "string", "identifier", "number", "integer_value", "real", "integer", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
};
# endif

#define YYPACT_NINF -101

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-101)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
    -101,    10,    27,  -101,  -101,  -101,  -101,  -101,    27,  -101,
    -101,  -101,  -101,  -101,  -101,     9,     4,    26,    18,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,
    -101,  -101,  -101,   -26,   -32,   -26,  -101,  -101,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,    11,    19,   -13,   -26,
      67,   -32,    72,    19,    19,    57,   -32,   -26,  -101,  -101,
    -101,  -101,  -101,    19,   -13,    57,    -1,   -32,    28,    19,
     -26,    67,  -101,  -101,  -101,  -101,  -101,    33,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,  -101,     7,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,     6,
    -101,  -101,    -4,  -101,    59,  -101,    59,  -101,    59,  -101,
    -101,  -101,    67,    33,     7,     6,  -101,    23,    20,    46,
    -101,  -101,  -101
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     8,    12,     6,    10,     3,     4,
      19,    39,    14,    29,     5,     9,    13,     7,    11,   101,
      57,    47,    45,    59,    50,    52,    57,    20,    57,    72,
      50,    45,    40,     0,     0,     0,    15,    57,    47,    72,
      92,    50,    80,    57,    45,    30,    25,    26,    27,    21,
      24,    22,    23,    28,    44,    43,    42,    41,   109,    16,
     108,    18,    17,    36,    37,    33,    34,    32,    35,    38,
      31,     0,   102,   107,   106,    58,    82,     0,    48,    49,
      46,    70,    66,    67,    68,    69,    64,    65,    61,    62,
      63,    60,    71,    51,    54,    56,    55,    53,    76,    77,
      75,    79,    74,    78,    73,    94,   114,     0,   113,    93,
      95,    98,    97,    96,    99,   111,   110,   112,    88,     0,
      81,   104,    84,    86,    84,    87,    84,    90,    84,    91,
      85,   103,     0,     0,     0,     0,   105,     0,     0,     0,
      83,   100,    89
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -101,  -101,  -101,  -101,    89,  -101,  -101,  -101,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,  -101,   -12,    65,    35,
    -101,  -101,    32,  -101,   -70,    66,  -101,  -101,  -101,   -30,
     -27,  -101,   -28,  -101,  -101,  -101,  -101,  -101,  -101,  -101,
      42,   -18,   -33,    43,   -74,  -100,  -101
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     8,     9,    12,    10,    13,    11,    17,
      36,    15,    27,    18,    45,    16,    32,    49,    48,    51,
      52,    97,    47,    50,    91,    55,   104,    68,    78,   132,
     124,   120,   128,    66,   109,   110,   111,    46,    72,   122,
      75,    93,    80,   129,   115,   116,   117
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,   121,    62,   125,   130,    73,    74,   126,    28,    76,
       3,    58,    19,    20,    21,    79,    61,    92,    22,    57,
      60,   105,    37,    38,    58,    73,    74,    29,   127,    77,
      30,    79,    70,    23,   138,    24,    25,     4,    92,   106,
     107,    39,    31,    40,    41,   131,   106,    33,   113,   108,
     118,    60,    34,    71,    26,   123,   108,   108,    53,   125,
      54,    42,   136,    43,    44,    56,     5,   130,   141,    63,
     119,     6,   140,   106,     7,    69,    67,    35,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    98,    99,
     100,   101,   102,   103,   133,   142,   134,    14,   135,    92,
      94,    95,    96,    64,    58,    65,   137,   139,   112,   114
};

static const yytype_uint8 yycheck[] =
{
      33,    71,    35,    77,     8,     6,     7,   107,     4,    22,
       0,    37,     3,     4,     5,    48,    34,    50,     9,    31,
      52,    22,     4,     5,    37,     6,     7,    23,    22,    42,
      26,    64,    44,    24,   134,    26,    27,    10,    71,    40,
      41,    23,    38,    25,    26,    49,    40,    21,    66,    50,
      22,    52,    26,    42,    45,    22,    50,    50,    26,   133,
      28,    43,   132,    45,    46,    30,    39,     8,    48,    37,
      42,    44,    49,    40,    47,    43,    41,    51,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    31,    32,
      33,    34,    35,    36,   124,    49,   126,     8,   128,   132,
      28,    29,    30,    38,    37,    39,   133,   135,    66,    66
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    54,    55,     0,    10,    39,    44,    47,    56,    57,
      59,    61,    58,    60,    57,    64,    68,    62,    66,     3,
       4,     5,     9,    24,    26,    27,    45,    65,     4,    23,
      26,    38,    69,    21,    26,    51,    63,     4,     5,    23,
      25,    26,    43,    45,    46,    67,    90,    75,    71,    70,
      76,    72,    73,    75,    75,    78,    72,    70,    37,    95,
      52,    94,    95,    75,    71,    78,    86,    72,    80,    75,
      70,    42,    91,     6,     7,    93,    22,    42,    81,    95,
      95,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    77,    95,    94,    28,    29,    30,    74,    31,    32,
      33,    34,    35,    36,    79,    22,    40,    41,    50,    87,
      88,    89,    93,    94,    96,    97,    98,    99,    22,    42,
      84,    77,    92,    22,    83,    97,    98,    22,    85,    96,
       8,    49,    82,    82,    82,    82,    77,    83,    98,    85,
      49,    48,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    55,    54,    56,    56,    58,    57,    59,    57,
      60,    57,    61,    57,    62,    62,    63,    63,    63,    64,
      64,    65,    65,    65,    65,    65,    65,    65,    65,    66,
      66,    67,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    69,    69,    69,    69,    70,    70,    71,    71,    71,
      72,    72,    73,    73,    74,    74,    74,    75,    75,    76,
      76,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    78,    78,    79,    79,    79,    79,    79,    79,
      80,    80,    81,    81,    82,    82,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    87,    88,    88,    88,    88,
      89,    90,    90,    91,    92,    92,    93,    93,    94,    95,
      96,    96,    97,    98,    99
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     2,     2,     2,     2,     0,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     0,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     0,
       2,     2,     2,     2,     2,     0,     2,     0,     2,     2,
       0,     2,     0,     2,     1,     1,     1,     0,     2,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     1,     1,     1,     1,     1,     1,
       0,     2,     1,     5,     0,     1,     1,     1,     1,     5,
       1,     1,     0,     2,     1,     1,     1,     1,     1,     1,
       5,     0,     2,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 544 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {TBL->num_conn = 0;
			   TBL->num_param = 0;
			   TBL->num_inst_var = 0;

			   saw_function_name = false;
			   saw_model_name = false;

			   alloced_size [TBL_PORT] = DEFAULT_SIZE_CONN;
			   alloced_size [TBL_PARAMETER] = DEFAULT_SIZE_PARAM;
			   alloced_size [TBL_STATIC_VAR] = 
			      DEFAULT_SIZE_INST_VAR;

			   TBL->conn = (Conn_Info_t*)
			      calloc (DEFAULT_SIZE_CONN,
				      sizeof (Conn_Info_t));
 		     	   TBL->param = (Param_Info_t*)
			      calloc (DEFAULT_SIZE_PARAM,
				      sizeof (Param_Info_t));
			   TBL->inst_var = (Inst_Var_Info_t*)
			      calloc (DEFAULT_SIZE_INST_VAR,
				      sizeof (Inst_Var_Info_t));
			   if (! (TBL->conn && TBL->param &&
				  TBL->inst_var) ) {
			      fatal ("Could not allocate enough memory");
			   } 
  			  }
#line 1926 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 6:
#line 578 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {context.table = TBL_NAME;}
#line 1932 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 8:
#line 581 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {context.table = TBL_PORT;
			     did_default_type = false;
			     did_allowed_types = false;
			     INIT (TBL->num_conn);}
#line 1941 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 9:
#line 586 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {TBL->num_conn = num_items;}
#line 1947 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 10:
#line 588 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {context.table = TBL_PARAMETER;
			     INIT (TBL->num_param);}
#line 1954 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 11:
#line 591 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {TBL->num_param = num_items;}
#line 1960 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 12:
#line 593 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {context.table = TBL_STATIC_VAR;
			     INIT (TBL->num_inst_var);}
#line 1967 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 13:
#line 596 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {TBL->num_inst_var = num_items;}
#line 1973 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 16:
#line 604 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {TBL->name.c_fcn_name =strdup (ifs_yytext);
 			   saw_function_name = true;
			   if (parser_just_names && saw_model_name) return 0;}
#line 1981 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 17:
#line 608 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {TBL->name.model_name = strdup (ifs_yytext);
 			   saw_model_name = true;
			   if (parser_just_names && saw_function_name) return 0;}
#line 1989 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 18:
#line 612 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {TBL->name.description = strdup (ifs_yytext);}
#line 1995 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 21:
#line 620 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->conn[i].name = ITEM_BUF(i).str;
			   }}
#line 2005 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 22:
#line 626 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->conn[i].description = ITEM_BUF(i).str;
			   }}
#line 2015 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 23:
#line 632 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->conn[i].direction = ITEM_BUF(i).dir;
			   }}
#line 2025 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 24:
#line 638 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   did_default_type = true;
			   FOR_ITEM (i) {
			      TBL->conn[i].default_port_type = 
				 ITEM_BUF(i).ctype.kind;
			      TBL->conn[i].default_type = ITEM_BUF(i).ctype.id;
			      if (did_allowed_types) {
				 check_default_type (TBL->conn[i]);
			      }
			   }}
#line 2041 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 25:
#line 650 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   did_allowed_types = true;
			   FOR_ITEM (i) {
			      assign_ctype_list (&TBL->conn[i],
						 ITEM_BUF(i).ctype_list);
			      if (did_default_type) {
				 check_default_type (TBL->conn[i]);
			      }
			   }}
#line 2056 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 26:
#line 661 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->conn[i].is_array = ITEM_BUF(i).btype;
			   }}
#line 2066 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 27:
#line 667 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      ASSIGN_BOUNDS (conn, i);
			      assert (!TBL->conn[i].has_conn_ref);
			   }}
#line 2077 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 28:
#line 674 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->conn[i].null_allowed = ITEM_BUF(i).btype;
			   }}
#line 2087 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 31:
#line 686 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->param[i].name = ITEM_BUF(i).str;
			   }}
#line 2097 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 32:
#line 692 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->param[i].description = ITEM_BUF(i).str;
			   }}
#line 2107 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 33:
#line 698 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      check_dtype_not_pointer (ITEM_BUF(i).dtype);
			      TBL->param[i].type = ITEM_BUF(i).dtype;
			   }}
#line 2118 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 34:
#line 705 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->param[i].has_default = 
				 ITEM_BUF(i).value.has_value;
			      if (TBL->param[i].has_default) {
   			         assign_value (TBL->param[i].type,
					       &TBL->param[i].default_value,
					       ITEM_BUF(i).value);
			      }
			   }}
#line 2134 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 35:
#line 717 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      assign_limits (TBL->param[i].type, 
					     &TBL->param[i],
					     ITEM_BUF(i).range);
			   }}
#line 2146 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 36:
#line 725 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->param[i].is_array = ITEM_BUF(i).btype;
			   }}
#line 2156 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 37:
#line 731 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      ASSIGN_BOUNDS (param, i);
			   }}
#line 2166 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 38:
#line 737 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->param[i].null_allowed = ITEM_BUF(i).btype;
			   }}
#line 2176 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 41:
#line 749 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->inst_var[i].name = ITEM_BUF(i).str;
			   }}
#line 2186 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 42:
#line 755 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->inst_var[i].description = ITEM_BUF(i).str;
			   }}
#line 2196 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 43:
#line 761 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->inst_var[i].type = ITEM_BUF(i).dtype;
			   }}
#line 2206 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 44:
#line 767 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {int i;
			   END;
			   FOR_ITEM (i) {
			      TBL->inst_var[i].is_array = ITEM_BUF(i).btype;
			   }}
#line 2216 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 46:
#line 775 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {ITEM; BUF.str = (yyvsp[0].str);}
#line 2222 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 48:
#line 780 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {ITEM; 
			    BUF.range = (yyvsp[0].range);}
#line 2229 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 49:
#line 783 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {ITEM; 
			    BUF.range.is_named = true;
			    BUF.range.u.name = (yyvsp[0].str);}
#line 2237 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 51:
#line 789 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {ITEM; BUF.str = (yyvsp[0].str);}
#line 2243 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 53:
#line 793 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {ITEM; BUF.dir = (yyvsp[0].dir);}
#line 2249 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 54:
#line 796 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.dir) = CMPP_IN;}
#line 2255 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 55:
#line 797 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.dir) = CMPP_OUT;}
#line 2261 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 56:
#line 798 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.dir) = CMPP_INOUT;}
#line 2267 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 58:
#line 802 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {ITEM; BUF.btype = (yyvsp[0].btype);}
#line 2273 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 60:
#line 806 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {ITEM; BUF.ctype = (yyvsp[0].ctype);}
#line 2279 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 61:
#line 809 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype).kind = VOLTAGE;}
#line 2285 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 62:
#line 810 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype).kind = DIFF_VOLTAGE;}
#line 2291 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 63:
#line 811 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype).kind = VSOURCE_CURRENT;}
#line 2297 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 64:
#line 812 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype).kind = CURRENT;}
#line 2303 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 65:
#line 813 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype).kind = DIFF_CURRENT;}
#line 2309 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 66:
#line 814 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype).kind = CONDUCTANCE;}
#line 2315 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 67:
#line 815 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype).kind = DIFF_CONDUCTANCE;}
#line 2321 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 68:
#line 816 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype).kind = RESISTANCE;}
#line 2327 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 69:
#line 817 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype).kind = DIFF_RESISTANCE;}
#line 2333 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 70:
#line 818 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype).kind = DIGITAL;}
#line 2339 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 71:
#line 819 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype).kind = USER_DEFINED;
					 (yyval.ctype).id   = (yyvsp[0].str);}
#line 2346 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 73:
#line 824 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {ITEM; BUF.dtype = (yyvsp[0].dtype);}
#line 2352 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 74:
#line 827 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.dtype) = CMPP_REAL;}
#line 2358 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 75:
#line 828 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.dtype) = CMPP_INTEGER;}
#line 2364 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 76:
#line 829 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.dtype) = CMPP_BOOLEAN;}
#line 2370 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 77:
#line 830 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.dtype) = CMPP_COMPLEX;}
#line 2376 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 78:
#line 831 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.dtype) = CMPP_STRING;}
#line 2382 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 79:
#line 832 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.dtype) = CMPP_POINTER;}
#line 2388 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 81:
#line 836 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {ITEM; BUF.range = (yyvsp[0].range);}
#line 2394 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 82:
#line 839 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.range).is_named = false; 
				    (yyval.range).u.bounds.lower.has_bound = false;
				    (yyval.range).u.bounds.upper.has_bound = false;}
#line 2402 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 83:
#line 844 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.range).is_named = false;
			    (yyval.range).u.bounds.lower = (yyvsp[-3].bound);
			    (yyval.range).u.bounds.upper = (yyvsp[-1].bound);}
#line 2410 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 86:
#line 853 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.bound).has_bound = false;}
#line 2416 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 87:
#line 854 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.bound).has_bound = true; 
				           (yyval.bound).bound = (yyvsp[0].value);}
#line 2423 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 88:
#line 858 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.range).is_named = false; 
				    (yyval.range).u.bounds.lower.has_bound = false;
				    (yyval.range).u.bounds.upper.has_bound = false;}
#line 2431 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 89:
#line 863 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.range).is_named = false;
			    (yyval.range).u.bounds.lower = (yyvsp[-3].bound);
			    (yyval.range).u.bounds.upper = (yyvsp[-1].bound);}
#line 2439 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 90:
#line 868 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.bound).has_bound = false;}
#line 2445 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 91:
#line 869 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.bound).has_bound = true; 
				  (yyval.bound).bound = (yyvsp[0].value);}
#line 2452 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 93:
#line 874 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {ITEM; BUF.value = (yyvsp[0].value);}
#line 2458 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 94:
#line 877 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.value).has_value = false;}
#line 2464 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 96:
#line 881 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.value).has_value = true;
					 (yyval.value).kind = CMPP_STRING;
					 (yyval.value).u.svalue = (yyvsp[0].str);}
#line 2472 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 97:
#line 884 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.value).has_value = true;
					 (yyval.value).kind = CMPP_BOOLEAN;
					 (yyval.value).u.bvalue = (yyvsp[0].btype);}
#line 2480 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 98:
#line 887 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.value).has_value = true;
					 (yyval.value).kind = CMPP_COMPLEX;
					 (yyval.value).u.cvalue = (yyvsp[0].cval);}
#line 2488 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 100:
#line 894 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.cval).real = (yyvsp[-3].rval);
			   (yyval.cval).imag = (yyvsp[-1].rval);}
#line 2495 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 102:
#line 900 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {ITEM; BUF.ctype_list = (yyvsp[0].ctype_list);}
#line 2501 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 103:
#line 903 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype_list) = (yyvsp[-1].ctype_list);}
#line 2507 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 104:
#line 907 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype_list) = (Ctype_List_t*)calloc (1,
							sizeof (Ctype_List_t));
			    if (!(yyval.ctype_list)) {
			       fatal ("Error allocating memory");
			    }
			    (yyval.ctype_list)->ctype = (yyvsp[0].ctype);
			    (yyval.ctype_list)->next = (Ctype_List_t*)0;}
#line 2519 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 105:
#line 915 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ctype_list) = (Ctype_List_t*)calloc (1, 
							sizeof (Ctype_List_t));
			    if (!(yyval.ctype_list)) {
			       fatal ("Error allocating memory");
			    }
			    (yyval.ctype_list)->ctype = (yyvsp[0].ctype);
			    (yyval.ctype_list)->next = (yyvsp[-2].ctype_list);
			    /*$$->next = (Ctype_List_t*)0;
			    assert ($1);
			    $1->next = $$;*/}
#line 2534 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 106:
#line 927 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.btype) = true;}
#line 2540 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 107:
#line 928 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.btype) = false;}
#line 2546 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 108:
#line 931 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.str) = strdup(ifs_yytext);}
#line 2552 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 109:
#line 934 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.str) = strdup(ifs_yytext);}
#line 2558 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 110:
#line 937 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.value).has_value = true;
				 (yyval.value).kind = CMPP_REAL;
				 (yyval.value).u.rvalue = (yyvsp[0].rval);}
#line 2566 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 112:
#line 943 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.value).has_value = true;
					 (yyval.value).kind = CMPP_INTEGER;
					 (yyval.value).u.ivalue = (yyvsp[0].ival);}
#line 2574 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 113:
#line 948 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.rval) = yydval;}
#line 2580 "ifs_yacc.c" /* yacc.c:1646  */
    break;

  case 114:
#line 951 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1646  */
    {(yyval.ival) = yyival;}
#line 2586 "ifs_yacc.c" /* yacc.c:1646  */
    break;


#line 2590 "ifs_yacc.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 954 "../../../../src/xspice/cmpp/ifs_yacc.y" /* yacc.c:1906  */

