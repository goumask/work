
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

/**
hy340 Phase 3
Eliezer Smaragdis | 4242 | csd4242@csd.uoc.gr
Kostas Goumas | 2746 | goumas@csd.uoc.gr
**/

// ------------------------------- Libraries --------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

// ------------------------------- Defines -----------------------------------------

#define SIZE_HIDDEN_VAR 10
#define SIZE_SYMBOL_TABLE 100
#define SIZE_STACK 1000

#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

// -------------------------------- Enum -------------------------------------------

typedef enum {
    iASSIGN,                   iADD,                    iSUB,
    iMUL,                      iDIV,                    iMOD,
    iUMINUS,                   iAND,                    iOR,
    iNOT,                      iIF_EQ,                  iIF_NOTEQ,
    iIF_LESSEQ,                iIF_GREATEREQ,           iIF_LESS,
    iIF_GREATER,               iCALL,                   iPARAM,
    iRET,                      iGETRETVAL,              iFUNCSTART,
    iFUNCEND,                  iTABLECREATE,            iJUMP,
    iTABLEGETELEM,             iTABLESETELEM
}iopcode;

typedef enum {
    programvar, functionlocal, formalarg
}scopespace_t;

typedef enum {
    var_s, programfunc_s, libraryfunc_s
}symbol_t;

typedef enum enumTypeId {
    enumLOCAL, enumGLOBAL, enumFUNC_ARG, enumFUNC_USER, enumFUNC_LIB
}enumTypeId_t;

typedef enum enumTypeOfValue {
    enumNumber, enumString, enumBoolean, enumNil,
    enumFunctionAddress, enumLibraryFunction, enumTable
}enumTypeOfValue_t;

typedef enum {
    var_e,
    tableitem_e,
    
    programfunc_e,
    libraryfunc_e,
    
    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,
    
    constnum_e,
    constint_e,
    constbool_e,
    conststring_e,
    
    nil_e
}expr_t;

// ------------------------------ Structs ------------------------------------------
struct symbol;

typedef struct expr {
    expr_t             type;
    struct symbol*     sym;
    struct expr*       index;
    double*            numConst;
    int*               intConst;
    unsigned int*      unsIntConst;
    char*              strConst;
    bool*              boolConst;
    struct expr*       PairIndex; // '{' expr ':' expr '}'
    struct expr*       PairValue; // '{' expr ':' expr '}'
    struct expr*       next;
}expr;
/*
typedef struct id {
    // `struct id` is the `struct symbol` 
    char*           name;
    enumTypeId_t    type;           // 0: local, 1: global, 2: function_arg, 3: function_user, 4: function_lib
    int             declare1stLine;
    int             scope;
    int             scopeFuncBlock;
    int             scopeStmtBlock;
    bool            active;

    scopespace_t          space;
    unsigned              offset;
    
    //int             enumNumber;     // serial number of: globals, function_arg, locals
    struct id*      next;
}Id_t;
*/

typedef struct call {
    expr*          elist;
    bool*          method;
    char*          name;
}call;

typedef struct {
    iopcode               op;
    expr*                 result;
    expr*                 arg1;
    expr*                 arg2;
    unsigned              label;
    unsigned              line; // source line
}quad;

typedef struct symbol {
    symbol_t              typeS;  // var_s, programfunc_s, libraryfunc_s
    enumTypeId_t          type;  // 0: local, 1: global, 2: function_arg, 3: function_user, 4: function_lib
    char*                 name; // Name of symbol
    unsigned              iaddress;
    unsigned              totalLocals;
    scopespace_t          space;
    unsigned              offset; // inside scope-space
    unsigned              scope;
    unsigned              scopeFuncBlock;
    unsigned              scopeStmtBlock;
    unsigned              declare1stLine; // first line declaration
    bool                  active;
    struct symbol*        next;
}symbol;

typedef struct stmt {
    int breakList, contList;
    bool breakStmt, contStmt;
    struct stmt* next;
}stmt;

struct forPrefix {
    int test, enter;
};

struct forPREpre {
    int label;
    expr* elist;
};

// ------------------------------- Declare Functions -------------------------------

void yyerror(char* s);
int yylex();

int hash_function(char*);
void insert_symbol_table(char*, enumTypeId_t, int line, int argScope, int argScopeFuncBlock, int argScopeStmtBlock);
bool isLibFunction(char* name);
symbol* lookup_sym(char* name, int argScope);
bool isUserFunction(char* name, int argScope);
char* type2string(enumTypeId_t type);
void hideVariables_sym(int argScope);
void checkOnlyReadValue(const symbol* id);
char* hiddenVarF();

char* iop2string(iopcode op);
int num_of_digits(unsigned int num);
int num_double_digits(double num);


expr* emit_iftableitem(expr* e);
void patchlabel (unsigned quadNo, unsigned label);
unsigned nextquadlabel(void);
void restorecurrscopeoffset(unsigned n);
void resetfunctionlocalsoffset(void);
void resetformalargsoffset(void);
void exitscopespace(void);
void enterscopespace(void);
void incurrscopeoffset(void);
unsigned currscopeoffset(void);
scopespace_t currscopespace(void);
expr* lvalue_expr(symbol* sym);
expr* make_call(expr* lv, expr* elist);


void expand(void);
void emit (
    iopcode      op,
    expr*        arg1,
    expr*        arg2,
    expr*        result,
    unsigned     label,
    unsigned     line
);

void check_arith (expr* e);
unsigned int istempexpr (expr* e);
unsigned int istempname (char* s);
void patchlist (int list, int label);
int mergelist(int l1, int l2);
int newlist(int i);
stmt* make_stmt ();
expr* newexpr_constbool (unsigned int b );
expr* newexpr_conststring(char* s);
expr* newexpr_constnum(unsigned int i);
expr* member_item(expr* lv, char* name);
expr* newexpr(expr_t e_t);
symbol* newsymbol(char* name, symbol_t s_t);

char* newtempname();
void resettemp();
symbol* newtemp();

int pop(int Stack[], int* Top);
void push(int Stack[], int elem, int* Top);

//expr* popElist(expr* Stack[]);
//void pushElist(expr* Stack[], expr* e);

expr* reverse(expr* list);

expr* return_zero_expr(expr* e);
bool isBranch_opcode(iopcode op);


// ------------------------------- Global Variables --------------------------------
extern FILE* yyin;
extern FILE* yyout;
extern int yylineno;

symbol* symbol_table[SIZE_SYMBOL_TABLE] = { NULL };

int hideNameFunction = 0;

int scope = 0;
int scopeStmtBlock = 0;
int scopeFuncBlock = 0;

quad* quads = NULL;
unsigned total = 0;
unsigned int currQuad = 0;

unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;

int tempcounter = 0;

int scopeoffsetStack[SIZE_STACK] = { 0 };
int topOffset = 0;

int loopCounterStack[SIZE_STACK] = { 0 };
int topLoop = 0;

//expr* StackElist[SIZE_STACK] = { 0 };
//int topElist = 0;

int compileErrors = 0;
int loopcounter = 0;
int strErrors[1000] = { 0 };
int indexErrors = 0;

int StackBreak[SIZE_STACK] = { 0 };
int topBreak = 0;

int StackCont[SIZE_STACK] = { 0 };
int topCont = 0;



/* Line 189 of yacc.c  */
#line 352 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     WHILE = 260,
     FOR = 261,
     FUNCTION = 262,
     RETURN = 263,
     BREAK = 264,
     CONTINUE = 265,
     AND = 266,
     NOT = 267,
     OR = 268,
     LOCAL = 269,
     TRUE = 270,
     FALSE = 271,
     NIL = 272,
     EQUAL_EQUAL = 273,
     NOT_EQUAL = 274,
     PLUS_PLUS = 275,
     MINUS_MINUS = 276,
     LESS_EQUAL = 277,
     GREATER_EQUAL = 278,
     COLON_COLON = 279,
     DOT_DOT = 280,
     INT = 281,
     STR = 282,
     REAL = 283,
     ID = 284,
     UMINUS = 285
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define FUNCTION 262
#define RETURN 263
#define BREAK 264
#define CONTINUE 265
#define AND 266
#define NOT 267
#define OR 268
#define LOCAL 269
#define TRUE 270
#define FALSE 271
#define NIL 272
#define EQUAL_EQUAL 273
#define NOT_EQUAL 274
#define PLUS_PLUS 275
#define MINUS_MINUS 276
#define LESS_EQUAL 277
#define GREATER_EQUAL 278
#define COLON_COLON 279
#define DOT_DOT 280
#define INT 281
#define STR 282
#define REAL 283
#define ID 284
#define UMINUS 285




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 301 "parser.y"

    int numInt;
    unsigned unsInt;
    double numReal;
    char* string;
    struct symbol* symbT;
    struct expr* exprT;
    struct call* callS;
    struct forPrefix* forP;
    struct forPREpre* forPP;
    struct stmt* Stm;



/* Line 214 of yacc.c  */
#line 463 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 475 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   890

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNRULES -- Number of states.  */
#define YYNSTATES  226

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    37,     2,     2,
      42,    43,    35,    33,    45,    34,    39,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    44,
      32,    30,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    48,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    10,    13,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    34,    37,    40,
      42,    46,    50,    54,    58,    62,    66,    70,    74,    78,
      82,    86,    90,    94,    96,   100,   103,   106,   109,   112,
     115,   118,   120,   121,   126,   128,   130,   132,   136,   138,
     140,   143,   146,   148,   150,   154,   159,   164,   168,   173,
     177,   180,   187,   193,   195,   197,   201,   204,   210,   215,
     218,   219,   223,   226,   230,   234,   237,   238,   242,   248,
     249,   250,   256,   257,   258,   264,   268,   270,   271,   274,
     275,   280,   282,   284,   286,   288,   290,   292,   294,   295,
     296,   300,   301,   302,   307,   312,   315,   320,   322,   326,
     328,   332,   340,   346,   352,   360,   361,   366,   370,   375,
     378,   379,   380,   384,   388
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    -1,    51,    -1,     1,    -1,    52,    -1,
      51,    52,    -1,    55,    44,    -1,    90,    -1,    93,    -1,
      96,    -1,   105,    -1,    53,    -1,    54,    -1,    73,    -1,
      79,    -1,    44,    -1,     9,    44,    -1,    10,    44,    -1,
      57,    -1,    55,    33,    55,    -1,    55,    34,    55,    -1,
      55,    35,    55,    -1,    55,    36,    55,    -1,    55,    37,
      55,    -1,    55,    31,    55,    -1,    55,    32,    55,    -1,
      55,    23,    55,    -1,    55,    22,    55,    -1,    55,    18,
      55,    -1,    55,    19,    55,    -1,    55,    11,    55,    -1,
      55,    13,    55,    -1,    56,    -1,    42,    55,    43,    -1,
      34,    55,    -1,    12,    55,    -1,    20,    60,    -1,    60,
      20,    -1,    21,    60,    -1,    60,    21,    -1,    59,    -1,
      -1,    60,    58,    30,    55,    -1,    63,    -1,    60,    -1,
      69,    -1,    42,    79,    43,    -1,    85,    -1,    29,    -1,
      14,    29,    -1,    24,    29,    -1,    61,    -1,    62,    -1,
      60,    39,    29,    -1,    60,    40,    55,    41,    -1,    63,
      40,    55,    41,    -1,    63,    39,    29,    -1,    63,    42,
      67,    43,    -1,    63,    42,    43,    -1,    60,    64,    -1,
      42,    79,    43,    42,    67,    43,    -1,    42,    79,    43,
      42,    43,    -1,    65,    -1,    66,    -1,    42,    67,    43,
      -1,    42,    43,    -1,    25,    29,    42,    67,    43,    -1,
      25,    29,    42,    43,    -1,    55,    68,    -1,    -1,    45,
      55,    68,    -1,    40,    41,    -1,    40,    67,    41,    -1,
      40,    70,    41,    -1,    72,    71,    -1,    -1,    45,    72,
      71,    -1,    46,    55,    47,    55,    48,    -1,    -1,    -1,
      46,    74,    50,    75,    48,    -1,    -1,    -1,    46,    77,
      50,    78,    48,    -1,    81,    82,    84,    -1,    29,    -1,
      -1,     7,    80,    -1,    -1,    42,    83,    86,    43,    -1,
      76,    -1,    28,    -1,    26,    -1,    27,    -1,    17,    -1,
      15,    -1,    16,    -1,    -1,    -1,    29,    87,    88,    -1,
      -1,    -1,    45,    29,    89,    88,    -1,    91,    52,    92,
      52,    -1,    91,    52,    -1,     3,    42,    55,    43,    -1,
       4,    -1,    94,    95,   104,    -1,     5,    -1,    42,    55,
      43,    -1,    98,    97,    67,    43,    97,   104,    97,    -1,
     100,    43,    97,   104,    97,    -1,    98,    43,    97,   104,
      97,    -1,   100,    97,    67,    43,    97,   104,    97,    -1,
      -1,    99,    44,    55,    44,    -1,     6,    42,    67,    -1,
     101,    44,    55,    44,    -1,     6,    42,    -1,    -1,    -1,
     102,    52,   103,    -1,     8,    55,    44,    -1,     8,    44,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   331,   331,   334,   338,   347,   355,   370,   377,   384,
     391,   398,   405,   412,   419,   426,   433,   443,   468,   494,
     495,   503,   511,   519,   527,   535,   547,   559,   571,   583,
     595,   607,   616,   625,   636,   642,   651,   660,   681,   702,
     723,   744,   753,   753,   780,   786,   792,   793,   800,   810,
     855,   870,   884,   889,   904,   910,   923,   932,   941,   948,
     954,   976,   984,   995,  1001,  1010,  1034,  1052,  1076,  1104,
    1116,  1127,  1144,  1153,  1171,  1193,  1203,  1210,  1222,  1234,
    1235,  1234,  1240,  1245,  1239,  1259,  1277,  1314,  1323,  1341,
    1341,  1351,  1361,  1377,  1393,  1401,  1407,  1423,  1442,  1443,
    1443,  1467,  1468,  1468,  1500,  1507,  1516,  1527,  1537,  1561,
    1570,  1581,  1604,  1626,  1648,  1674,  1685,  1703,  1720,  1738,
    1754,  1762,  1770,  1778,  1793
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR", "LOCAL", "TRUE",
  "FALSE", "NIL", "EQUAL_EQUAL", "NOT_EQUAL", "PLUS_PLUS", "MINUS_MINUS",
  "LESS_EQUAL", "GREATER_EQUAL", "COLON_COLON", "DOT_DOT", "INT", "STR",
  "REAL", "ID", "'='", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "UMINUS", "'.'", "'['", "']'", "'('", "')'", "';'", "','", "'{'", "':'",
  "'}'", "$accept", "program", "stmts", "stmt", "break", "continue",
  "expr", "term", "assignexpr", "$@1", "primary", "lvalue", "tableitem",
  "member", "call", "callsuffix", "normcall", "methodcall", "elist",
  "elistExtend", "objectdef", "indexed", "indexedExtend", "indexedelem",
  "blockStmt", "$@2", "$@3", "blockFunc", "$@4", "$@5", "funcdef",
  "funcname", "funcprefix", "funcargs", "$@6", "funcbody", "const",
  "idlist", "$@7", "idlistExtend", "$@8", "ifstmt", "ifprefix",
  "elseprefix", "whilestmt", "whilestart", "whilecond", "forstmt", "N",
  "forprefix", "forPREprefix", "forprefixWithoutELIST",
  "forPREprefixWithoutELIST", "loopstart", "loopend", "loopstmt",
  "returnstmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
      61,    62,    60,    43,    45,    42,    47,    37,   285,    46,
      91,    93,    40,    41,    59,    44,   123,    58,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    50,    51,    51,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    53,    54,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    56,    56,    56,    56,    56,    56,
      56,    56,    58,    57,    59,    59,    59,    59,    59,    60,
      60,    60,    60,    60,    61,    61,    62,    62,    63,    63,
      63,    63,    63,    64,    64,    65,    65,    66,    66,    67,
      68,    68,    69,    69,    69,    70,    71,    71,    72,    74,
      75,    73,    77,    78,    76,    79,    80,    80,    81,    83,
      82,    84,    85,    85,    85,    85,    85,    85,    86,    87,
      86,    88,    89,    88,    90,    90,    91,    92,    93,    94,
      95,    96,    96,    96,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   105
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     2,     2,     2,     2,     2,
       2,     1,     0,     4,     1,     1,     1,     3,     1,     1,
       2,     2,     1,     1,     3,     4,     4,     3,     4,     3,
       2,     6,     5,     1,     1,     3,     2,     5,     4,     2,
       0,     3,     2,     3,     3,     2,     0,     3,     5,     0,
       0,     5,     0,     0,     5,     3,     1,     0,     2,     0,
       4,     1,     1,     1,     1,     1,     1,     1,     0,     0,
       3,     0,     0,     4,     4,     2,     4,     1,     3,     1,
       3,     7,     5,     5,     7,     0,     4,     3,     4,     2,
       0,     0,     3,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     4,     0,   109,     0,    87,     0,     0,     0,     0,
       0,    96,    97,    95,     0,     0,     0,    93,    94,    92,
      49,     0,     0,     0,    16,    79,     0,     3,     5,    12,
      13,     0,    33,    19,    41,    45,    52,    53,    44,    46,
      14,    15,     0,    48,     8,     0,     9,     0,    10,   115,
       0,   115,     0,    11,     0,   119,    86,    88,   124,     0,
      17,    18,    36,    50,     0,    37,     0,    39,    51,    35,
      72,     0,    70,     0,     0,    76,     0,     0,     0,     1,
       6,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     7,    38,    40,     0,     0,     0,
       0,     0,    60,    63,    64,     0,     0,     0,    89,     0,
     105,     0,   120,   115,     0,     0,   115,     0,     0,     0,
     117,   123,     0,     0,     0,    69,    73,    74,     0,    75,
      34,    47,    80,    31,    32,    29,    30,    28,    27,    25,
      26,    20,    21,    22,    23,    24,     0,    54,     0,    66,
       0,     0,    57,     0,    59,     0,    98,    82,    91,    85,
     107,     0,     0,     0,   108,   120,     0,     0,   120,     0,
       0,   106,     0,     0,    70,    76,     0,     0,     0,    55,
      65,    43,    56,    58,    99,     0,     0,   104,   110,   121,
     115,   115,   116,   115,   115,   118,     0,    71,    77,    62,
       0,    81,    68,     0,   101,    90,    83,   122,   113,   120,
     112,   120,    78,    61,    67,     0,   100,     0,   115,   115,
     102,    84,   111,   114,   101,   103
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,    28,    29,    30,    72,    32,    33,   101,
      34,    35,    36,    37,    38,   102,   103,   104,    73,   125,
      39,    74,   129,    75,    40,    78,   177,   158,   186,   217,
      41,    57,    42,   109,   156,   159,    43,   185,   204,   216,
     224,    44,    45,   161,    46,    47,   112,    48,   114,    49,
      50,    51,    52,   163,   207,   164,    53
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -155
static const yytype_int16 yypact[] =
{
     222,  -155,   -37,  -155,   -32,   -13,   480,   -19,    -8,   720,
      -5,  -155,  -155,  -155,    -7,    -7,     2,  -155,  -155,  -155,
    -155,   720,   320,    93,  -155,  -155,    39,   264,  -155,  -155,
    -155,   373,  -155,  -155,  -155,   125,  -155,  -155,     1,  -155,
    -155,  -155,    14,  -155,  -155,   264,  -155,    16,  -155,    -1,
      17,    21,    24,  -155,   720,   720,  -155,  -155,  -155,   400,
    -155,  -155,  -155,  -155,    52,   -10,     1,   -10,  -155,  -155,
    -155,   720,   345,    28,    34,    20,   508,    33,   173,  -155,
    -155,   720,   720,   720,   720,   720,   720,   720,   720,   720,
     720,   720,   720,   720,  -155,  -155,  -155,    48,    50,   720,
     592,    64,  -155,  -155,  -155,    51,   720,   624,  -155,    49,
      92,   720,  -155,  -155,   720,   720,  -155,   720,   720,   535,
    -155,  -155,    54,    15,   720,  -155,  -155,  -155,    55,  -155,
    -155,    56,  -155,   833,   826,   853,   853,   366,   366,   366,
     366,    37,    37,  -155,  -155,  -155,    60,  -155,   745,  -155,
      61,   720,  -155,   772,  -155,    73,    74,  -155,  -155,  -155,
    -155,   264,   562,   264,  -155,  -155,    80,   427,  -155,    82,
     454,  -155,    56,   720,   345,    20,   656,    78,   688,  -155,
    -155,   799,  -155,  -155,  -155,    85,   173,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,   294,  -155,  -155,  -155,
      87,  -155,  -155,    89,    94,  -155,  -155,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,   105,  -155,    99,  -155,  -155,
    -155,  -155,  -155,  -155,    94,  -155
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,   -74,  -155,   -25,  -155,  -155,     0,  -155,  -155,  -155,
    -155,    -2,  -155,  -155,     4,  -155,  -155,  -155,   -47,   -26,
    -155,  -155,   -38,    25,  -155,  -155,  -155,  -155,  -155,  -155,
     -20,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,   -82,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,   -50,  -155,
    -155,  -155,  -155,  -155,  -155,  -154,  -155
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -43
static const yytype_int16 yytable[] =
{
      31,   117,    80,    77,   132,    54,    59,    10,   120,    62,
      55,   190,    65,    67,   193,    97,    56,    16,    66,    66,
     110,    69,    20,    76,    63,    60,    81,    31,    82,    98,
      99,    68,   100,    83,    84,    64,    61,    85,    86,    79,
     105,   106,   113,   107,   122,    31,    87,    88,    89,    90,
      91,    92,    93,   150,   119,   218,   108,   219,   111,     5,
     155,   115,   173,   165,   116,   128,   168,   166,   118,   126,
     169,   123,    91,    92,    93,   127,   131,   146,    31,   147,
     152,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   151,   157,   160,   172,   176,   148,
       5,    71,   178,   184,   180,     9,   153,    10,    11,    12,
      13,   162,   206,    14,    15,   167,   183,    16,   170,    17,
      18,    19,    20,   191,   174,   194,   201,    21,   205,   200,
     213,   203,   214,    22,   220,    23,   187,   198,   189,   215,
     208,   209,   225,   210,   211,    95,    96,   221,   197,     0,
      97,   181,     0,   175,     0,   -42,     0,     0,     0,     0,
       0,    31,     0,    31,    98,    99,     0,   100,   222,   223,
       0,     0,     0,   196,     1,     0,     2,     0,     3,     4,
       5,     6,     7,     8,     0,     9,    31,    10,    11,    12,
      13,     0,     0,    14,    15,     0,     0,    16,     0,    17,
      18,    19,    20,     0,     0,     0,     0,    21,     0,     0,
       0,     0,     0,    22,     0,    23,     0,    24,     0,    25,
       0,    -2,    -2,     1,     0,     2,     0,     3,     4,     5,
       6,     7,     8,     0,     9,     0,    10,    11,    12,    13,
       0,     0,    14,    15,     0,     0,    16,     0,    17,    18,
      19,    20,     0,     0,     0,     0,    21,     0,     0,     0,
       0,     0,    22,     0,    23,     0,    24,     2,    25,     3,
       4,     5,     6,     7,     8,     0,     9,     0,    10,    11,
      12,    13,     0,     0,    14,    15,     0,     0,    16,     0,
      17,    18,    19,    20,     0,     0,     0,     0,    21,     0,
       0,     0,     0,     0,    22,    81,    23,    82,    24,     0,
      25,     0,    83,    84,     0,     0,    85,    86,     0,     0,
       0,     0,     0,     0,     0,    87,    88,    89,    90,    91,
      92,    93,     9,     0,    10,    11,    12,    13,     0,     0,
      14,    15,   212,     0,    16,     0,    17,    18,    19,    20,
       0,     0,     0,     0,    21,     0,    81,     0,    82,     0,
      22,    70,    23,    83,    84,     0,    71,    85,    86,     0,
       0,     0,     0,     0,     0,     0,    87,    88,    89,    90,
      91,    92,    93,     0,    81,     0,    82,     0,   -43,   -43,
     124,    83,    84,     0,     0,    85,    86,   -43,   -43,    89,
      90,    91,    92,    93,    87,    88,    89,    90,    91,    92,
      93,    81,     0,    82,     0,     0,     0,    94,    83,    84,
       0,     0,    85,    86,     0,     0,     0,     0,     0,     0,
       0,    87,    88,    89,    90,    91,    92,    93,    81,     0,
      82,     0,     0,     0,   121,    83,    84,     0,     0,    85,
      86,     0,     0,     0,     0,     0,     0,     0,    87,    88,
      89,    90,    91,    92,    93,    81,     0,    82,     0,     0,
       0,   192,    83,    84,     0,     0,    85,    86,     0,     0,
       0,     0,     0,     0,     0,    87,    88,    89,    90,    91,
      92,    93,     9,     0,    10,    11,    12,    13,   195,     0,
      14,    15,     0,     0,    16,     0,    17,    18,    19,    20,
       0,     0,     0,     0,    21,     0,     0,     0,     0,    81,
      22,    82,    23,     0,    58,     0,    83,    84,     0,     0,
      85,    86,     0,     0,     0,     0,     0,     0,     0,    87,
      88,    89,    90,    91,    92,    93,    81,     0,    82,     0,
       0,   130,     0,    83,    84,     0,     0,    85,    86,     0,
       0,     0,     0,     0,     0,     0,    87,    88,    89,    90,
      91,    92,    93,    81,     0,    82,     0,     0,   171,     0,
      83,    84,     0,     0,    85,    86,     0,     0,     0,     0,
       0,     0,     0,    87,    88,    89,    90,    91,    92,    93,
       0,     0,     0,     0,     9,   188,    10,    11,    12,    13,
       0,     0,    14,    15,     0,     0,    16,     0,    17,    18,
      19,    20,     0,     0,     0,     0,    21,     0,     0,     0,
       0,     0,    22,     0,    23,   149,     9,     0,    10,    11,
      12,    13,     0,     0,    14,    15,     0,     0,    16,     0,
      17,    18,    19,    20,     0,     0,     0,     0,    21,     0,
       0,     0,     0,     0,    22,     0,    23,   154,     9,     0,
      10,    11,    12,    13,     0,     0,    14,    15,     0,     0,
      16,     0,    17,    18,    19,    20,     0,     0,     0,     0,
      21,     0,     0,     0,     0,     0,    22,     0,    23,   199,
       9,     0,    10,    11,    12,    13,     0,     0,    14,    15,
       0,     0,    16,     0,    17,    18,    19,    20,     0,     0,
       0,     0,    21,     0,     0,     0,     0,     0,    22,     0,
      23,   202,     9,     0,    10,    11,    12,    13,     0,     0,
      14,    15,     0,     0,    16,     0,    17,    18,    19,    20,
       0,     0,     0,     0,    21,     0,    81,     0,    82,     0,
      22,     0,    23,    83,    84,     0,     0,    85,    86,     0,
       0,     0,     0,     0,     0,     0,    87,    88,    89,    90,
      91,    92,    93,    81,     0,    82,   179,     0,     0,     0,
      83,    84,     0,     0,    85,    86,     0,     0,     0,     0,
       0,     0,     0,    87,    88,    89,    90,    91,    92,    93,
      81,     0,    82,   182,     0,     0,     0,    83,    84,     0,
       0,    85,    86,     0,     0,     0,     0,     0,     0,     0,
      87,    88,    89,    90,    91,    92,    93,    81,     0,     0,
       0,     0,     0,     0,    83,    84,     0,     0,    85,    86,
       0,    83,    84,     0,     0,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    87,    88,    89,    90,    91,    92,
      93,   -43,   -43,     0,     0,    85,    86,     0,     0,     0,
       0,     0,     0,     0,    87,    88,    89,    90,    91,    92,
      93
};

static const yytype_int16 yycheck[] =
{
       0,    51,    27,    23,    78,    42,     6,    14,    55,     9,
      42,   165,    14,    15,   168,    25,    29,    24,    14,    15,
      45,    21,    29,    23,    29,    44,    11,    27,    13,    39,
      40,    29,    42,    18,    19,    42,    44,    22,    23,     0,
      39,    40,    43,    42,    64,    45,    31,    32,    33,    34,
      35,    36,    37,   100,    54,   209,    42,   211,    42,     7,
     107,    44,    47,   113,    43,    45,   116,   114,    44,    41,
     117,    71,    35,    36,    37,    41,    43,    29,    78,    29,
      29,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    30,    46,     4,    43,    42,    99,
       7,    46,    42,    29,    43,    12,   106,    14,    15,    16,
      17,   111,   186,    20,    21,   115,    43,    24,   118,    26,
      27,    28,    29,    43,   124,    43,    48,    34,    43,   176,
      43,   178,    43,    40,    29,    42,   161,   175,   163,    45,
     190,   191,   224,   193,   194,    20,    21,    48,   174,    -1,
      25,   151,    -1,   128,    -1,    30,    -1,    -1,    -1,    -1,
      -1,   161,    -1,   163,    39,    40,    -1,    42,   218,   219,
      -1,    -1,    -1,   173,     1,    -1,     3,    -1,     5,     6,
       7,     8,     9,    10,    -1,    12,   186,    14,    15,    16,
      17,    -1,    -1,    20,    21,    -1,    -1,    24,    -1,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    42,    -1,    44,    -1,    46,
      -1,    48,     0,     1,    -1,     3,    -1,     5,     6,     7,
       8,     9,    10,    -1,    12,    -1,    14,    15,    16,    17,
      -1,    -1,    20,    21,    -1,    -1,    24,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    42,    -1,    44,     3,    46,     5,
       6,     7,     8,     9,    10,    -1,    12,    -1,    14,    15,
      16,    17,    -1,    -1,    20,    21,    -1,    -1,    24,    -1,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    40,    11,    42,    13,    44,    -1,
      46,    -1,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    37,    12,    -1,    14,    15,    16,    17,    -1,    -1,
      20,    21,    48,    -1,    24,    -1,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    34,    -1,    11,    -1,    13,    -1,
      40,    41,    42,    18,    19,    -1,    46,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    37,    -1,    11,    -1,    13,    -1,    22,    23,
      45,    18,    19,    -1,    -1,    22,    23,    31,    32,    33,
      34,    35,    36,    37,    31,    32,    33,    34,    35,    36,
      37,    11,    -1,    13,    -1,    -1,    -1,    44,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    35,    36,    37,    11,    -1,
      13,    -1,    -1,    -1,    44,    18,    19,    -1,    -1,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    36,    37,    11,    -1,    13,    -1,    -1,
      -1,    44,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    37,    12,    -1,    14,    15,    16,    17,    44,    -1,
      20,    21,    -1,    -1,    24,    -1,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    11,
      40,    13,    42,    -1,    44,    -1,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    37,    11,    -1,    13,    -1,
      -1,    43,    -1,    18,    19,    -1,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    37,    11,    -1,    13,    -1,    -1,    43,    -1,
      18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    12,    43,    14,    15,    16,    17,
      -1,    -1,    20,    21,    -1,    -1,    24,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    42,    43,    12,    -1,    14,    15,
      16,    17,    -1,    -1,    20,    21,    -1,    -1,    24,    -1,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    42,    43,    12,    -1,
      14,    15,    16,    17,    -1,    -1,    20,    21,    -1,    -1,
      24,    -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    40,    -1,    42,    43,
      12,    -1,    14,    15,    16,    17,    -1,    -1,    20,    21,
      -1,    -1,    24,    -1,    26,    27,    28,    29,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      42,    43,    12,    -1,    14,    15,    16,    17,    -1,    -1,
      20,    21,    -1,    -1,    24,    -1,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    34,    -1,    11,    -1,    13,    -1,
      40,    -1,    42,    18,    19,    -1,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    37,    11,    -1,    13,    41,    -1,    -1,    -1,
      18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    35,    36,    37,
      11,    -1,    13,    41,    -1,    -1,    -1,    18,    19,    -1,
      -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    35,    36,    37,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    18,    19,    -1,    -1,    22,    23,
      -1,    18,    19,    -1,    -1,    22,    23,    31,    32,    33,
      34,    35,    36,    37,    31,    32,    33,    34,    35,    36,
      37,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     5,     6,     7,     8,     9,    10,    12,
      14,    15,    16,    17,    20,    21,    24,    26,    27,    28,
      29,    34,    40,    42,    44,    46,    50,    51,    52,    53,
      54,    55,    56,    57,    59,    60,    61,    62,    63,    69,
      73,    79,    81,    85,    90,    91,    93,    94,    96,    98,
      99,   100,   101,   105,    42,    42,    29,    80,    44,    55,
      44,    44,    55,    29,    42,    60,    63,    60,    29,    55,
      41,    46,    55,    67,    70,    72,    55,    79,    74,     0,
      52,    11,    13,    18,    19,    22,    23,    31,    32,    33,
      34,    35,    36,    37,    44,    20,    21,    25,    39,    40,
      42,    58,    64,    65,    66,    39,    40,    42,    42,    82,
      52,    42,    95,    43,    97,    44,    43,    97,    44,    55,
      67,    44,    79,    55,    45,    68,    41,    41,    45,    71,
      43,    43,    50,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    29,    29,    55,    43,
      67,    30,    29,    55,    43,    67,    83,    46,    76,    84,
       4,    92,    55,   102,   104,    97,    67,    55,    97,    67,
      55,    43,    43,    47,    55,    72,    42,    75,    42,    41,
      43,    55,    41,    43,    29,    86,    77,    52,    43,    52,
     104,    43,    44,   104,    43,    44,    55,    68,    71,    43,
      67,    48,    43,    67,    87,    43,    50,   103,    97,    97,
      97,    97,    48,    43,    43,    45,    88,    78,   104,   104,
      29,    48,    97,    97,    89,    88
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 331 "parser.y"
    {
        printf("program -> empty\n");
    }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 335 "parser.y"
    {
        printf("program -> stmts\n");
    }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 339 "parser.y"
    {
        printf("\nprogram -> error\n");
        fprintf(stderr, "\nThe program is wrong! See Line: %d\n", yylineno);
        exit(1);
    }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 348 "parser.y"
    {
        printf("stmts -> stmt\n");

        //$$ = $1;

        //printf("stmt ------------------ line %d \n", yylineno);
    }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 356 "parser.y"
    {
        printf("stmts -> stmts stmt\n");

       // printf("stmt ------------------ line %d \n", yylineno);

        //$$ = make_stmt();

        //$$->breakList = mergelist($1->breakList, $2->breakList);
        //$$->contList = mergelist($1->contList, $2->contList);

    }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 371 "parser.y"
    {
        printf("stmt -> expr ';'\n");

        //$$ = make_stmt();
        resettemp();
    }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 378 "parser.y"
    {
        printf("stmt -> ifstmt\n");

        //$$ = make_stmt();
        resettemp();
    }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 385 "parser.y"
    {
        printf("stmt -> whilestmt\n");

        //$$ = make_stmt();
        resettemp();
    }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 392 "parser.y"
    {
        printf("stmt -> forstmt\n");

        //$$ = make_stmt();
        resettemp();
    }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 399 "parser.y"
    {
        printf("stmt -> returnstmt\n");

        //$$ = make_stmt();
        resettemp();
    }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 406 "parser.y"
    {
        printf("stmt -> break\n");

        //$$ = $1;
        resettemp();
    }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 413 "parser.y"
    {
        printf("stmt -> continue\n");

        //$$ = $1;
        resettemp();
    }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 420 "parser.y"
    {
        printf("stmt -> blockStmt\n");

        //$$ = make_stmt();
        resettemp();
    }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 427 "parser.y"
    {
        printf("stmt -> funcdef\n");

        //$$ = make_stmt();
        resettemp();
    }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 434 "parser.y"
    {
        printf("stmt -> ';'\n");

        //$$ = make_stmt();
        resettemp();
    }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 444 "parser.y"
    {
        printf("break -> BREAK ';'\n");

        assert(loopcounter >= 0);

        if (loopcounter == 0) {

            ++compileErrors;
            assert(indexErrors < 1000);
            strErrors[indexErrors] = yylineno;
            ++indexErrors;
        }

        //$$ = make_stmt();
        //$$->breakStmt = true;
        //$$->breakList = newlist(nextquadlabel());

        push(StackBreak, nextquadlabel(), &topBreak);

        emit(iJUMP, NULL, NULL, NULL, 0, yylineno);
    }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 469 "parser.y"
    {
        printf("continue -> CONTINUE ';'\n");

        assert(loopcounter >= 0);


        if (loopcounter == 0) {

            ++compileErrors;
            assert(indexErrors < 1000);
            strErrors[indexErrors] = yylineno;
            ++indexErrors;
        }

        //$$ = make_stmt();
        //$$->contStmt = true;
        //$$->contList = newlist(nextquadlabel());

        push(StackCont, nextquadlabel(), &topCont);

        emit(iJUMP, NULL, NULL, NULL, 0, yylineno);
    }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 494 "parser.y"
    {printf("expr -> assignexpr\n");}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 496 "parser.y"
    {
        printf("expr -> expr '+' expr\n");
        
        (yyval.exprT) = newexpr(arithexpr_e);
        (yyval.exprT)->sym = newtemp();
        emit(iADD, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), (yyval.exprT), 0, yylineno);
    }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 504 "parser.y"
    {
        printf("expr -> expr '-' expr\n");

        (yyval.exprT) = newexpr(arithexpr_e);
        (yyval.exprT)->sym = newtemp();
        emit(iSUB, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), (yyval.exprT), 0, yylineno);    
    }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 512 "parser.y"
    {
        printf("expr -> expr '*' expr\n");

        (yyval.exprT) = newexpr(arithexpr_e);
        (yyval.exprT)->sym = newtemp();
        emit(iMUL, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), (yyval.exprT), 0, yylineno);    
    }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 520 "parser.y"
    {
        printf("expr -> expr '/' expr\n");
        
        (yyval.exprT) = newexpr(arithexpr_e);
        (yyval.exprT)->sym = newtemp();
        emit(iDIV, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), (yyval.exprT), 0, yylineno);
    }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 528 "parser.y"
    {
        printf("expr -> expr '%%' expr\n");
        
        (yyval.exprT) = newexpr(arithexpr_e);
        (yyval.exprT)->sym = newtemp();
        emit(iMOD, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), (yyval.exprT), 0, yylineno);
    }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 536 "parser.y"
    {
        printf("expr -> expr '>' expr\n");

        (yyval.exprT) = newexpr(boolexpr_e);
        (yyval.exprT)->sym = newtemp();

        emit(iIF_GREATER, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, (yyval.exprT), 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, (yyval.exprT), 0, yylineno);    
    }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 548 "parser.y"
    {
        printf("expr -> expr '<' expr\n");
    
        (yyval.exprT) = newexpr(boolexpr_e);
        (yyval.exprT)->sym = newtemp();

        emit(iIF_LESS, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, (yyval.exprT), 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, (yyval.exprT), 0, yylineno);
    }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 560 "parser.y"
    {
        printf("expr -> expr GREATER_EQUAL expr\n");
        
        (yyval.exprT) = newexpr(boolexpr_e);
        (yyval.exprT)->sym = newtemp();

        emit(iIF_GREATEREQ, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, (yyval.exprT), 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, (yyval.exprT), 0, yylineno);
    }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 572 "parser.y"
    {
        printf("expr -> expr LESS_EQUAL expr\n");
        
        (yyval.exprT) = newexpr(boolexpr_e);
        (yyval.exprT)->sym = newtemp();

        emit(iIF_LESSEQ, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, (yyval.exprT), 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, (yyval.exprT), 0, yylineno);
    }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 584 "parser.y"
    {
        printf("expr -> expr EQUAL_EQUAL expr\n");
        
        (yyval.exprT) = newexpr(boolexpr_e);
        (yyval.exprT)->sym = newtemp();

        emit(iIF_EQ, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, (yyval.exprT), 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, (yyval.exprT), 0, yylineno);
    }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 596 "parser.y"
    {
        printf("expr -> expr NOT_EQUAL expr\n");
        
        (yyval.exprT) = newexpr(boolexpr_e);
        (yyval.exprT)->sym = newtemp();

        emit(iIF_NOTEQ, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, (yyval.exprT), 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, (yyval.exprT), 0, yylineno);
    }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 608 "parser.y"
    {
        printf("expr -> expr AND expr\n");

        // total boolean evaluation
        (yyval.exprT) = newexpr(boolexpr_e);
        (yyval.exprT)->sym = newtemp();
        emit(iAND, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), (yyval.exprT), 0, yylineno);
    }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 617 "parser.y"
    {
        printf("expr -> expr OR expr\n");

        // total boolean evaluation
        (yyval.exprT) = newexpr(boolexpr_e);
        (yyval.exprT)->sym = newtemp();
        emit(iOR, (yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].exprT), (yyval.exprT), 0, yylineno);    
    }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 626 "parser.y"
    {
        printf("expr -> term\n");
        
        (yyval.exprT) = (yyvsp[(1) - (1)].exprT);
    }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 637 "parser.y"
    {
        printf("term -> '(' expr ')'\n");

        (yyval.exprT) = (yyvsp[(2) - (3)].exprT);    
    }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 643 "parser.y"
    {
        printf("term -> '-' expr %%prec UMINUS\n");
        
        check_arith((yyvsp[(2) - (2)].exprT));
        (yyval.exprT) = newexpr(arithexpr_e);
        (yyval.exprT)->sym = istempexpr((yyvsp[(2) - (2)].exprT)) ? (yyvsp[(2) - (2)].exprT)->sym : newtemp();
        emit(iUMINUS, (yyvsp[(2) - (2)].exprT), NULL, (yyval.exprT), 0, yylineno);
    }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 652 "parser.y"
    {
        printf("term -> NOT expr\n");
        
        // total boolean evaluation
        (yyval.exprT) = newexpr(boolexpr_e);
        (yyval.exprT)->sym = newtemp();
        emit(iNOT , (yyvsp[(2) - (2)].exprT), NULL, (yyval.exprT), 0, yylineno);
    }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 661 "parser.y"
    {
        printf("term -> PLUS_PLUS lvalue\n");

        checkOnlyReadValue((yyvsp[(2) - (2)].exprT)->sym);

        check_arith((yyvsp[(2) - (2)].exprT));

        if ((yyvsp[(2) - (2)].exprT)->type == tableitem_e) {
            
            (yyval.exprT) = emit_iftableitem((yyvsp[(2) - (2)].exprT));
            emit(iADD, (yyval.exprT), newexpr_constnum(1), (yyval.exprT), 0, yylineno);
            emit(iTABLESETELEM, (yyvsp[(2) - (2)].exprT), (yyvsp[(2) - (2)].exprT)->index, (yyval.exprT), 0, yylineno);
        }
        else {
            emit(iADD, (yyvsp[(2) - (2)].exprT), newexpr_constnum(1), (yyvsp[(2) - (2)].exprT), 0, yylineno);
            (yyval.exprT) = newexpr(arithexpr_e);
            (yyval.exprT)->sym = newtemp();
            emit(iASSIGN, (yyvsp[(2) - (2)].exprT), NULL, (yyval.exprT), 0, yylineno);
        }
    }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 682 "parser.y"
    {
        printf("term -> lvalue PLUS_PLUS\n");

        checkOnlyReadValue((yyvsp[(1) - (2)].exprT)->sym);
        
        check_arith((yyvsp[(1) - (2)].exprT));
        (yyval.exprT) = newexpr(var_e);
        (yyval.exprT)->sym = newtemp();

        if ((yyvsp[(1) - (2)].exprT)->type == tableitem_e) {
            expr* val = emit_iftableitem((yyvsp[(1) - (2)].exprT));
            emit(iASSIGN, val, NULL, (yyval.exprT), 0, yylineno);
            emit(iADD, val, newexpr_constnum(1), val, 0, yylineno);
            emit(iTABLESETELEM, (yyvsp[(1) - (2)].exprT), (yyvsp[(1) - (2)].exprT)->index, val, 0, yylineno);
        }
        else {
            emit(iASSIGN, (yyvsp[(1) - (2)].exprT), NULL, (yyval.exprT), 0, yylineno);
            emit(iADD, (yyvsp[(1) - (2)].exprT), newexpr_constnum(1), (yyvsp[(1) - (2)].exprT), 0, yylineno);
        }
    }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 703 "parser.y"
    {
        printf("term -> MINUS_MINUS lvalue\n");

        checkOnlyReadValue((yyvsp[(2) - (2)].exprT)->sym);        

        check_arith((yyvsp[(2) - (2)].exprT));

        if ((yyvsp[(2) - (2)].exprT)->type == tableitem_e) {
            
            (yyval.exprT) = emit_iftableitem((yyvsp[(2) - (2)].exprT));
            emit(iSUB, (yyval.exprT), newexpr_constnum(1), (yyval.exprT), 0, yylineno);
            emit(iTABLESETELEM, (yyvsp[(2) - (2)].exprT), (yyvsp[(2) - (2)].exprT)->index, (yyval.exprT), 0, yylineno);
        }
        else {
            emit(iSUB, (yyvsp[(2) - (2)].exprT), newexpr_constnum(1), (yyvsp[(2) - (2)].exprT), 0, yylineno);
            (yyval.exprT) = newexpr(arithexpr_e);
            (yyval.exprT)->sym = newtemp();
            emit(iASSIGN, (yyvsp[(2) - (2)].exprT), NULL, (yyval.exprT), 0, yylineno);
        }
    }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 724 "parser.y"
    {
        printf("term -> lvalue MINUS_MINUS\n");

        checkOnlyReadValue((yyvsp[(1) - (2)].exprT)->sym);
        
        check_arith((yyvsp[(1) - (2)].exprT));
        (yyval.exprT) = newexpr(var_e);
        (yyval.exprT)->sym = newtemp();

        if ((yyvsp[(1) - (2)].exprT)->type == tableitem_e) {
            expr* val = emit_iftableitem((yyvsp[(1) - (2)].exprT));
            emit(iASSIGN, val, NULL, (yyval.exprT), 0, yylineno);
            emit(iSUB, val, newexpr_constnum(1), val, 0, yylineno);
            emit(iTABLESETELEM, (yyvsp[(1) - (2)].exprT), (yyvsp[(1) - (2)].exprT)->index, val, 0, yylineno);
        }
        else {
            emit(iASSIGN, (yyvsp[(1) - (2)].exprT), NULL, (yyval.exprT), 0, yylineno);
            emit(iSUB, (yyvsp[(1) - (2)].exprT), newexpr_constnum(1), (yyvsp[(1) - (2)].exprT), 0, yylineno);
        }
    }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 745 "parser.y"
    {
        printf("term -> primary\n");
        
        (yyval.exprT) = (yyvsp[(1) - (1)].exprT);
    }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 753 "parser.y"
    {
        checkOnlyReadValue((yyvsp[(1) - (1)].exprT)->sym);
    }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 757 "parser.y"
    {
        printf("assignexpr -> lvalue '=' expr\n");
    
        if ((yyvsp[(1) - (4)].exprT)->type == tableitem_e) {

            // lvalue[index] = expr;
            emit(iTABLESETELEM, (yyvsp[(1) - (4)].exprT), (yyvsp[(1) - (4)].exprT)->index, (yyvsp[(4) - (4)].exprT), 0, yylineno);

            (yyval.exprT) = emit_iftableitem((yyvsp[(1) - (4)].exprT));
            (yyval.exprT)->type = assignexpr_e;
        }
        else {

            // lvalue = expr;
            emit(iASSIGN, (yyvsp[(4) - (4)].exprT), NULL, (yyvsp[(1) - (4)].exprT), 0, yylineno);
            (yyval.exprT) = newexpr(assignexpr_e);
            (yyval.exprT)->sym = newtemp();
            emit(iASSIGN, (yyvsp[(1) - (4)].exprT), NULL, (yyval.exprT), 0, yylineno);
        }
    }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 781 "parser.y"
    {
        printf("primary -> call\n");
    
        (yyval.exprT) = (yyvsp[(1) - (1)].exprT);
    }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 787 "parser.y"
    {
        printf("primary -> lvalue\n");
    
        (yyval.exprT) = emit_iftableitem((yyvsp[(1) - (1)].exprT));
    }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 792 "parser.y"
    {printf("primary -> objectdef\n");}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 794 "parser.y"
    {
        printf("primary -> '(' funcdef ')'\n");
        
        (yyval.exprT) = newexpr(programfunc_e);
        (yyval.exprT)->sym = (yyvsp[(2) - (3)].symbT);    
    }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 801 "parser.y"
    {
        printf("primary -> const\n");
        
        (yyval.exprT) = (yyvsp[(1) - (1)].exprT);
    }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 811 "parser.y"
    {
        int currScope = scope;
        symbol* foundId = NULL;

        while(currScope >= 0) {

            if((foundId = lookup_sym((yyvsp[(1) - (1)].string), currScope))){
                
                switch(foundId->type) {
                    case enumFUNC_ARG:
                        if(foundId->scopeFuncBlock != scopeFuncBlock) {
                            fprintf(stderr, "ERROR in line %d! Try to access argument [line: %d] of other function while it is active.\n", \
                                        yylineno, foundId->declare1stLine);
                            exit(1);
                        }
                        break;
                    case enumLOCAL:
                        if(foundId->scopeFuncBlock != scopeFuncBlock) {
                            fprintf(stderr, "ERROR in line %d! Try to access local variable [line: %d] of other scope while it is active.\n", \
                                       yylineno, foundId->declare1stLine);
                            exit(1);
                        }
                        break;
                    default:
                        break;
                }

                break;

            }

            --currScope;
        }

        if(foundId == NULL) {
            assert(currScope < 0);
            insert_symbol_table((yyvsp[(1) - (1)].string), (scope != 0) ? enumLOCAL : enumGLOBAL, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
        else {
            assert(!strcmp(foundId->name, (yyvsp[(1) - (1)].string)));    
        }
        (yyval.exprT) = lvalue_expr(newsymbol((yyvsp[(1) - (1)].string), var_s));
        printf("lvalue -> ID: %s\n", (yyvsp[(1) - (1)].string));
    }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 856 "parser.y"
    {
        symbol* foundId = lookup_sym((yyvsp[(2) - (2)].string), scope);

        if(!foundId) {
            if(isLibFunction((yyvsp[(2) - (2)].string))) {
                fprintf(stderr, "ERROR! Try to shadow library function in line %d.\n", yylineno);
                exit(1);
            }
            insert_symbol_table((yyvsp[(2) - (2)].string), (scope != 0) ? enumLOCAL : enumGLOBAL, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }

        (yyval.exprT) = lvalue_expr(newsymbol((yyvsp[(2) - (2)].string), var_s));
        printf("lvalue -> LOCAL ID: %s\n", (yyvsp[(2) - (2)].string));
    }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 871 "parser.y"
    {
        symbol* foundId = lookup_sym((yyvsp[(2) - (2)].string), 0);

        // NEVER insert here!
        if(!foundId) {
            fprintf(stderr, "ERROR! Try to access a not existed global variable or function in line %d.\n", yylineno);
            exit(1);
        }
        
        (yyval.exprT) = lvalue_expr(newsymbol((yyvsp[(2) - (2)].string), var_s));
        
        printf("lvalue -> COLON_COLON ID: %s\n", (yyvsp[(2) - (2)].string));
    }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 885 "parser.y"
    {
        printf("lvalue -> tableitem\n");
        (yyval.exprT) = (yyvsp[(1) - (1)].exprT);
    }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 890 "parser.y"
    {
        symbol* mem = (symbol*) malloc(sizeof(symbol));

        if (mem == NULL) {
            printf("No memory for member\n");
            exit(1);
        }

        (yyval.exprT) = (yyvsp[(1) - (1)].exprT);
        printf("lvalue -> member\n");
    }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 905 "parser.y"
    {
        printf("tableitem -> lvalue '.' ID\n");
    
        (yyval.exprT) = member_item((yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].string));
    }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 911 "parser.y"
    {
        printf("tableitem -> lvalue '[' expr ']'\n");

        (yyvsp[(1) - (4)].exprT) = emit_iftableitem((yyvsp[(1) - (4)].exprT));
        (yyval.exprT) = newexpr(tableitem_e);
        (yyval.exprT)->sym = (yyvsp[(1) - (4)].exprT)->sym;
        (yyval.exprT)->index = (yyvsp[(3) - (4)].exprT);
    }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 924 "parser.y"
    {
        printf("member -> call '[' expr ']'\n");
        
        (yyvsp[(1) - (4)].exprT) = emit_iftableitem((yyvsp[(1) - (4)].exprT));
        (yyval.exprT) = newexpr(tableitem_e);
        (yyval.exprT)->sym = (yyvsp[(1) - (4)].exprT)->sym;
        (yyval.exprT)->index = (yyvsp[(3) - (4)].exprT);
    }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 933 "parser.y"
    {
        printf("member -> call '.' ID\n");

        (yyval.exprT) = member_item((yyvsp[(1) - (3)].exprT), (yyvsp[(3) - (3)].string));    
    }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 942 "parser.y"
    {
        printf("call -> call '(' elist ')'\n");
        

        (yyval.exprT) = make_call((yyvsp[(1) - (4)].exprT), (yyvsp[(3) - (4)].exprT));
    }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 949 "parser.y"
    {
        printf("call -> call '(' ')'\n");
    
        (yyval.exprT) = make_call((yyvsp[(1) - (3)].exprT), NULL);
    }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 955 "parser.y"
    {
        printf("call -> lvalue callsuffix\n");
    
        (yyvsp[(1) - (2)].exprT) = emit_iftableitem((yyvsp[(1) - (2)].exprT));

        if ((yyvsp[(2) - (2)].callS)->method != NULL) {
            
            if (*((yyvsp[(2) - (2)].callS)->method) == true) {
                
                expr* t = (yyvsp[(1) - (2)].exprT);
                (yyvsp[(1) - (2)].exprT) = emit_iftableitem(member_item(t, (yyvsp[(2) - (2)].callS)->name));
                
                if ((yyvsp[(2) - (2)].callS)->elist != NULL) {
                    t->next = (yyvsp[(2) - (2)].callS)->elist->next;
                    free((yyvsp[(2) - (2)].callS)->elist);
                }
                (yyvsp[(2) - (2)].callS)->elist = t;
            }
        }
        (yyval.exprT) = make_call((yyvsp[(1) - (2)].exprT), (yyvsp[(2) - (2)].callS)->elist);
    }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 977 "parser.y"
    {
        printf("call -> '(' funcdef ')' '(' elist ')'\n");

        expr* func = newexpr(programfunc_e);
        func->sym = (yyvsp[(2) - (6)].symbT);
        (yyval.exprT) = make_call(func, (yyvsp[(5) - (6)].exprT));
    }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 985 "parser.y"
    {
        printf("call -> '(' funcdef ')' '(' ')'\n");
        
        expr* func = newexpr(programfunc_e);
        func->sym = (yyvsp[(2) - (5)].symbT);
        (yyval.exprT) = make_call(func, NULL);
    }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 996 "parser.y"
    {
        printf("callsuffix -> normcall\n");
    
        (yyval.callS) = (yyvsp[(1) - (1)].callS);
    }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1002 "parser.y"
    {
        printf("callsuffix -> methodcall\n");
    
        (yyval.callS) = (yyvsp[(1) - (1)].callS);
    }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1011 "parser.y"
    {
        printf("normcall -> '(' elist ')'\n");

        (yyval.callS) = (call*) malloc(sizeof(call));

        if ((yyval.callS) == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.callS)->elist = (yyvsp[(2) - (3)].exprT);

        bool* ptr = (bool*) malloc(sizeof(bool));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.callS)->method = ptr;
        *((yyval.callS)->method) = false;
        (yyval.callS)->name = NULL;
    }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1035 "parser.y"
    {
        printf("normcall -> '(' ')'\n");
        
        (yyval.callS) = (call*) malloc(sizeof(call));

        if ((yyval.callS) == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.callS)->elist = NULL;
        (yyval.callS)->method = NULL;
        (yyval.callS)->name = NULL;
    }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1053 "parser.y"
    {
        printf("methodcall -> DOT_DOT ID '(' elist ')'\n");
    
        (yyval.callS) = (call*) malloc(sizeof(call));

        if ((yyval.callS) == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.callS)->elist = (yyvsp[(4) - (5)].exprT);

        bool* ptr = (bool*) malloc(sizeof(bool));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.callS)->method = ptr;
        *((yyval.callS)->method) = true;
        (yyval.callS)->name = (yyvsp[(2) - (5)].string);
    }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1077 "parser.y"
    {
        printf("methodcall -> DOT_DOT ID '(' ')'\n");
        
        (yyval.callS) = (call*) malloc(sizeof(call));

        if ((yyval.callS) == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.callS)->elist = NULL;

        bool* ptr = (bool*) malloc(sizeof(bool));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.callS)->method = ptr;
        *((yyval.callS)->method) = true;
        (yyval.callS)->name = (yyvsp[(2) - (4)].string);
    }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1105 "parser.y"
    {
        printf("elist -> expr elistExtend\n");
        
        (yyval.exprT) = newexpr(nil_e);
        (yyval.exprT)->sym = NULL;
        (yyval.exprT)->next = (yyvsp[(1) - (2)].exprT);

        (yyvsp[(1) - (2)].exprT)->next = (yyvsp[(2) - (2)].exprT)->next;
    }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1116 "parser.y"
    {
        printf("elistExtend -> emtpy\n");

        (yyval.exprT) = (expr*) malloc(sizeof(expr));

        if ((yyval.exprT) == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }
        (yyval.exprT)->next = NULL;
    }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1128 "parser.y"
    {
        printf("elistExtend -> ',' expr elistExtend\n");
        
        (yyval.exprT) = (expr*) malloc(sizeof(expr));

        if ((yyval.exprT) == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.exprT)->next = (yyvsp[(2) - (3)].exprT);
        (yyvsp[(2) - (3)].exprT)->next = (yyvsp[(3) - (3)].exprT)->next;    
    }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1145 "parser.y"
    {
        printf("objectdef -> '[' ']'\n");
        
        expr* t = newexpr(newtable_e);
        t->sym = newtemp();
        emit(iTABLECREATE, t, NULL, NULL, 0, yylineno);
        (yyval.exprT) = t;
    }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1154 "parser.y"
    {
        printf("objectdef -> '[' elist ']'\n");
    
        expr* t = newexpr(newtable_e);
        t->sym = newtemp();
        emit(iTABLECREATE, t, NULL, NULL, 0, yylineno);

        if ((yyvsp[(2) - (3)].exprT) != NULL) (yyvsp[(2) - (3)].exprT) = (yyvsp[(2) - (3)].exprT)->next;

        unsigned int i = 0;
        while ((yyvsp[(2) - (3)].exprT) != NULL) {
            emit(iTABLESETELEM, t, newexpr_constnum(i), (yyvsp[(2) - (3)].exprT), 0, yylineno);
            ++i;
            (yyvsp[(2) - (3)].exprT) = (yyvsp[(2) - (3)].exprT)->next;
        }
        (yyval.exprT) = t;
    }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1172 "parser.y"
    {
        printf("objectdef -> '[' indexed ']'\n");
        
        expr* t = newexpr(newtable_e);
        t->sym = newtemp();
        emit(iTABLECREATE, t, NULL, NULL, 0, yylineno);

        expr* trace = (yyvsp[(2) - (3)].exprT);

        while (trace != NULL) {
            if (trace->PairIndex != NULL  && trace->PairValue != NULL) {
                emit(iTABLESETELEM, t, trace->PairIndex, trace->PairValue, 0, yylineno);
            }
            trace = trace->next;
        }
        (yyval.exprT) = t;
    }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1194 "parser.y"
    {
        printf("indexed -> indexedelem indexedExtend\n");
        
        (yyval.exprT) = newexpr(var_e);
        (yyval.exprT)->next = (yyvsp[(1) - (2)].exprT);
        (yyvsp[(1) - (2)].exprT)->next = (yyvsp[(2) - (2)].exprT)->next;
    }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1203 "parser.y"
    {
        printf("indexedExtend -> empty\n");

        (yyval.exprT) = newexpr(var_e);

        (yyval.exprT)->next = NULL;
    }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1211 "parser.y"
    {
        printf("indexedExtend -> ',' indexedelem indexedExtend\n");
        
        (yyval.exprT) = newexpr(var_e);

        (yyval.exprT)->next = (yyvsp[(2) - (3)].exprT);
        (yyvsp[(2) - (3)].exprT)->next = (yyvsp[(3) - (3)].exprT)->next;
    }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1223 "parser.y"
    {
        printf("indexedelem -> '{' expr ':' expr '}'\n");
        
        (yyval.exprT) = newexpr(var_e);

        (yyval.exprT)->PairIndex = (yyvsp[(2) - (5)].exprT);
        (yyval.exprT)->PairValue = (yyvsp[(4) - (5)].exprT);
    }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1234 "parser.y"
    { ++scope; ++scopeStmtBlock; }
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 1235 "parser.y"
    { hideVariables_sym(scope); --scope; --scopeStmtBlock; }
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1236 "parser.y"
    {printf("blockStmt -> '{' program '}'\n");}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1240 "parser.y"
    {
        push(loopCounterStack, loopcounter, &topLoop);
        loopcounter = 0;
    }
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1245 "parser.y"
    {
        hideVariables_sym(scope);
        --scope;
        --scopeFuncBlock;
    }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1251 "parser.y"
    {
        printf("blockFunc -> '{' program '}'\n");

        loopcounter = pop(loopCounterStack, &topLoop);        
    }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1260 "parser.y"
    {
        printf("funcdef -> funcprefix funcargs funcbody\n");

        exitscopespace();
        (yyvsp[(1) - (3)].symbT)->totalLocals= (yyvsp[(3) - (3)].unsInt);

        int offset = pop(scopeoffsetStack, &topOffset);
        
        restorecurrscopeoffset(offset);
        (yyval.symbT) = (yyvsp[(1) - (3)].symbT);
        expr* e = newexpr(programfunc_e);
        e->sym = (yyvsp[(1) - (3)].symbT);
        emit(iFUNCEND, e, NULL, NULL, 0, yylineno);
    }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1278 "parser.y"
    { 
        printf("funcname -> ID\n");

        (yyval.string) = (yyvsp[(1) - (1)].string);

        symbol* foundId = lookup_sym((yyvsp[(1) - (1)].string), scope);

        if(isLibFunction((yyvsp[(1) - (1)].string))) {
            fprintf(stderr, "ERROR in line %d! There is already this function name as library function in symbol table.\n", yylineno);
            exit(1);
        }

        if(foundId) {
            fprintf(stderr, "ERROR in line %d! There is already this", yylineno);
            if(foundId->type == enumFUNC_USER) {
                fprintf(stderr, " as user function in symbol table.\n");
            }
            else if(foundId->type == enumGLOBAL) {
                fprintf(stderr, " as global variable in symbol table.\n");
            }
            else if(foundId->type == enumLOCAL) {
                fprintf(stderr, " as local variable in symbol table.\n");
            }
            else if (foundId->type == enumFUNC_ARG) {
                fprintf(stderr, " as function argument in symbol table.\n");
            }
            else {
                assert(0);
            }
            exit(1);
        }
        else {
            insert_symbol_table((yyvsp[(1) - (1)].string), enumFUNC_USER, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
    }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1314 "parser.y"
    {
        printf("funcname -> empty");

        (yyval.string) = hiddenVarF();
        insert_symbol_table((yyval.string), enumFUNC_USER, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
    }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1324 "parser.y"
    {
        printf("funcprefix -> FUNCTION funcname\n");

        (yyval.symbT) = newsymbol((yyvsp[(2) - (2)].string), programfunc_s);
        (yyval.symbT)->iaddress = nextquadlabel();
        
        expr* e = newexpr(programfunc_e);
        e->sym = (yyval.symbT);

        emit(iFUNCSTART, e, NULL, NULL, 0, yylineno);
        push(scopeoffsetStack, currscopeoffset(), &topOffset);
        enterscopespace();
        resetformalargsoffset();
    }
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1341 "parser.y"
    {++scope; ++scopeFuncBlock;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1343 "parser.y"
    {
        printf("funcargs -> '(' idlist ')'\n");
        enterscopespace();
        resetfunctionlocalsoffset();
    }
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1352 "parser.y"
    {
        printf("funcbody -> blockFunc\n");
        (yyval.unsInt) = currscopeoffset();
        exitscopespace();
    }
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1362 "parser.y"
    {
        printf("const -> REAL: %lf\n", (yyvsp[(1) - (1)].numReal));

        (yyval.exprT) = newexpr(constnum_e);

        double* ptr = (double*) malloc(sizeof(double));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.exprT)->numConst = ptr;
        *((yyval.exprT)->numConst) = (yyvsp[(1) - (1)].numReal);
    }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1378 "parser.y"
    {
        printf("const -> INT: %d\n", (yyvsp[(1) - (1)].numInt));
    
        (yyval.exprT) = newexpr(constint_e);

        int* ptr = (int*) malloc(sizeof(int));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }
        
        (yyval.exprT)->intConst = ptr;
        *((yyval.exprT)->intConst) = (yyvsp[(1) - (1)].numInt);
    }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1394 "parser.y"
    {
        printf("const -> STR: %s\n", (yyvsp[(1) - (1)].string));

        (yyval.exprT) = newexpr(conststring_e);
        
        (yyval.exprT)->strConst = (yyvsp[(1) - (1)].string);
    }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1402 "parser.y"
    {
        printf("const -> NIL\n");

        (yyval.exprT) = newexpr(nil_e);
    }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1408 "parser.y"
    {
        printf("const -> TRUE\n");
    
        (yyval.exprT) = newexpr(constbool_e);

        bool* ptr = (bool*) malloc(sizeof(bool));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.exprT)->boolConst = ptr;
        *((yyval.exprT)->boolConst) = true;
    }
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1424 "parser.y"
    {
        printf("const -> FALSE\n");
    
        (yyval.exprT) = newexpr(constbool_e);

        bool* ptr = (bool*) malloc(sizeof(bool));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.exprT)->boolConst = ptr;
        *((yyval.exprT)->boolConst) = false;
    }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1443 "parser.y"
    {
        symbol* foundId = lookup_sym((yyvsp[(1) - (1)].string), scope);

        if(isLibFunction((yyvsp[(1) - (1)].string))) {
            fprintf(stderr, "ERROR in line %d! There is already this library function in symbol table.\n", yylineno);
            fprintf(stderr, "Line Code: %d\n", __LINE__);
            exit(1);
        }
        if(foundId){
            assert(foundId->type != enumFUNC_ARG);
            assert(foundId->type != enumGLOBAL);
            assert(foundId->type != enumLOCAL);
        }
        /*
        if(isUserFunction($1, scope)) {
            fprintf(stderr, "ERROR in line %d! This argument already exists as user function in symbol table.\n", yylineno);
            fprintf(stderr, "Line Code: %d\n", __LINE__);
            exit(1);
        }
        */
        insert_symbol_table((yyvsp[(1) - (1)].string), enumFUNC_ARG, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
    }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1465 "parser.y"
    {printf("idlist -> ID idlistExtend\n");}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1468 "parser.y"
    {
        symbol* foundId = lookup_sym((yyvsp[(2) - (2)].string), scope);

        if(isLibFunction((yyvsp[(2) - (2)].string))) {
            fprintf(stderr, "ERROR in line %d! There is already this library function in symbol table.\n", yylineno);
            fprintf(stderr, "Line Code: %d\n", __LINE__);
            exit(1);
        }

        if(foundId) {
            if(foundId->type == enumFUNC_ARG) {
                fprintf(stderr, "ERROR in line %d! Redeclaration.\n", yylineno);
                fprintf(stderr, "Line Code: %d\n", __LINE__);
            }
            assert(foundId->type != enumFUNC_USER);
            assert(foundId->type != enumGLOBAL);
            assert(foundId->type != enumLOCAL);
            exit(1);
        }
        else {
            if(isUserFunction((yyvsp[(2) - (2)].string), scope)) {
                fprintf(stderr, "ERROR in line %d! This argument already exists as user function in symbol table.\n", yylineno);
                fprintf(stderr, "Line Code: %d\n", __LINE__);
                exit(1);
            }
            insert_symbol_table((yyvsp[(2) - (2)].string), enumFUNC_ARG, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
    }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1496 "parser.y"
    {printf("idlistExtend -> ',' ID idlistExtend\n");}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1501 "parser.y"
    {
        printf("ifstmt -> ifprefix stmt elseprefix stmt\n");
        
        patchlabel((yyvsp[(1) - (4)].unsInt), (yyvsp[(3) - (4)].unsInt) + 1);
        patchlabel((yyvsp[(3) - (4)].unsInt), nextquadlabel());
    }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1508 "parser.y"
    {
        printf("ifstmt -> ifprefix stmt");
        
        patchlabel((yyvsp[(1) - (2)].unsInt), nextquadlabel());
    }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1517 "parser.y"
    {
        printf("ifprefix -> IF '(' expr ')'\n");

        emit(iIF_EQ, (yyvsp[(3) - (4)].exprT), newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
        (yyval.unsInt) = nextquadlabel();
        emit(iJUMP, NULL, NULL, NULL, 0, yylineno);
    }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1528 "parser.y"
    {
        printf("elseprefix -> ELSE\n");

        (yyval.unsInt) = nextquadlabel();
        emit(iJUMP, NULL, NULL, NULL, 0, yylineno);
    }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1538 "parser.y"
    {
        printf("whilestmt -> whilestart whilecond loopstmt\n");

        emit(iJUMP, NULL, NULL, NULL, (yyvsp[(1) - (3)].unsInt), yylineno);
        patchlabel((yyvsp[(2) - (3)].unsInt), nextquadlabel());
        
        for (int i = 0; i < topBreak; ++i) {
            patchlabel(StackBreak[i], nextquadlabel());
        }

        for (int i = 0; i < topCont; ++i) {
            patchlabel(StackCont[i], (yyvsp[(1) - (3)].unsInt));
        }

        topBreak = 0;
        topCont = 0;

        //patchlist($3->breakList, nextquadlabel());
        //patchlist($3->contList, $1);
    }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1562 "parser.y"
    {
        printf("whilestart -> WHILE\n");

        (yyval.unsInt) = nextquadlabel();
    }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1571 "parser.y"
    {
        printf("whilecond -> '(' expr ')'\n");

        emit(iIF_EQ, (yyvsp[(2) - (3)].exprT), newexpr_constbool(1), NULL, nextquadlabel()+2, yylineno);
        (yyval.unsInt) = nextquadlabel();
        emit(iJUMP, NULL, NULL, NULL, 0, yylineno);
    }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1582 "parser.y"
    {
        printf("forstmt -> forprefix N elist ')' N loopstmt N\n");
    
        patchlabel((yyvsp[(1) - (7)].forP)->enter, (yyvsp[(5) - (7)].unsInt) + 1);
        patchlabel((yyvsp[(2) - (7)].unsInt), nextquadlabel());
        patchlabel((yyvsp[(5) - (7)].unsInt), (yyvsp[(1) - (7)].forP)->test);
        patchlabel((yyvsp[(7) - (7)].unsInt), (yyvsp[(2) - (7)].unsInt) + 1);

        for (int i = 0; i < topBreak; ++i) {
            patchlabel(StackBreak[i], nextquadlabel());
        }

        for (int i = 0; i < topCont; ++i) {
            patchlabel(StackCont[i], (yyvsp[(1) - (7)].forP)->test);
        }

        topBreak = 0;
        topCont = 0;

        //patchlist($stmt.breakList, nextquadlabel());
        //patchlist($smst.contlist, $N1+1);
    }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1605 "parser.y"
    {
        printf("forstmt -> forprefixWithoutELIST ')' N stmt N\n");

        patchlabel((yyvsp[(1) - (5)].forP)->enter, (yyvsp[(3) - (5)].unsInt) + 1);
        patchlabel((yyvsp[(3) - (5)].unsInt), nextquadlabel());
        patchlabel((yyvsp[(5) - (5)].unsInt), (yyvsp[(1) - (5)].forP)->test);

        for (int i = 0; i < topBreak; ++i) {
            patchlabel(StackBreak[i], nextquadlabel());
        }

        for (int i = 0; i < topCont; ++i) {
            patchlabel(StackCont[i], (yyvsp[(1) - (5)].forP)->test);
        }

        topBreak = 0;
        topCont = 0;

        //patchlist($stmt.breakList, nextquadlabel());
        //patchlist($smst.contlist, $N1+1);
    }
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1627 "parser.y"
    {
        printf("forstmt -> forprefix ')' N stmt N\n");
        
        patchlabel((yyvsp[(1) - (5)].forP)->enter, (yyvsp[(3) - (5)].unsInt) + 1);
        patchlabel((yyvsp[(3) - (5)].unsInt), nextquadlabel());
        patchlabel((yyvsp[(5) - (5)].unsInt), (yyvsp[(1) - (5)].forP)->test);

        for (int i = 0; i < topBreak; ++i) {
            patchlabel(StackBreak[i], nextquadlabel());
        }

        for (int i = 0; i < topCont; ++i) {
            patchlabel(StackCont[i], (yyvsp[(1) - (5)].forP)->test);
        }

        topBreak = 0;
        topCont = 0;

        //patchlist($stmt.breakList, nextquadlabel());
        //patchlist($stmt.contlist, $N1+1);
    }
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1649 "parser.y"
    {
        printf("forstmt -> forprefixWithoutELIST N elist ')' N stmt N\n");

        patchlabel((yyvsp[(1) - (7)].forP)->enter, (yyvsp[(5) - (7)].unsInt) + 1);
        patchlabel((yyvsp[(2) - (7)].unsInt), nextquadlabel());
        patchlabel((yyvsp[(5) - (7)].unsInt), (yyvsp[(1) - (7)].forP)->test);
        patchlabel((yyvsp[(7) - (7)].unsInt), (yyvsp[(2) - (7)].unsInt) + 1);

        for (int i = 0; i < topBreak; ++i) {
            patchlabel(StackBreak[i], nextquadlabel());
        }

        for (int i = 0; i < topCont; ++i) {
            patchlabel(StackCont[i], (yyvsp[(1) - (7)].forP)->test);
        }

        topBreak = 0;
        topCont = 0;
        
        //patchlist($stmt.breakList, nextquadlabel());
        //patchlist($smst.contlist, $N1+1);
    }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1674 "parser.y"
    {
        printf("N -> empty\n");

        (yyval.unsInt) = nextquadlabel();
        emit(iJUMP, NULL, NULL, NULL, 0, yylineno);
    }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1686 "parser.y"
    {
        printf("forprefix -> forPREprefix ';' expr ';'\n");

        (yyval.forP) = (struct forPrefix*) malloc(sizeof(struct forPrefix));

        if ((yyval.forP) == NULL) {
            printf("No memory... Line Code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.forP)->test = (yyvsp[(1) - (4)].forPP)->label;
        (yyval.forP)->enter = nextquadlabel();
        emit(iIF_EQ, (yyvsp[(3) - (4)].exprT), newexpr_constbool(1), NULL, 0, yylineno);
    }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1704 "parser.y"
    {
        printf("forPREprefix -> FOR '(' elist\n");

        (yyval.forPP) = (struct forPREpre*) malloc(sizeof(struct forPREpre));

        if ((yyval.forPP) == NULL) {
            printf("No memory... Line Code %d:\n", __LINE__);
            exit(1);
        }

        (yyval.forPP)->label = nextquadlabel();
        (yyval.forPP)->elist = (yyvsp[(3) - (3)].exprT);
    }
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1721 "parser.y"
    {
        printf("forprefixWithoutELIST -> forPREprefixWithoutELIST ';' expr ';'\n");

        (yyval.forP) = (struct forPrefix*) malloc(sizeof(struct forPrefix));

        if ((yyval.forP) == NULL) {
            printf("No memory... Line Code: %d\n", __LINE__);
            exit(1);
        }

        (yyval.forP)->test = (yyvsp[(1) - (4)].forPP)->label;
        (yyval.forP)->enter = nextquadlabel();
        emit(iIF_EQ, (yyvsp[(3) - (4)].exprT), newexpr_constbool(1), NULL, 0, yylineno);
    }
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1739 "parser.y"
    {
        printf("forPREprefixWithoutELIST -> FOR '('\n");

        (yyval.forPP) = (struct forPREpre*) malloc(sizeof(struct forPREpre));

        if ((yyval.forPP) == NULL) {
            printf("No memory... Line Code %d:\n", __LINE__);
            exit(1);
        }

        (yyval.forPP)->label = nextquadlabel();
    }
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1754 "parser.y"
    {
        printf("loopstart -> empty\n");

        ++loopcounter;
    }
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1762 "parser.y"
    {
        printf("loopend -> empty\n");

        --loopcounter;
    }
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1771 "parser.y"
    {
        printf("loopstmt -> loopstart stmt loopend\n");
        (yyval.Stm) = (yyvsp[(2) - (3)].Stm);
    }
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1779 "parser.y"
    {
        printf("returnstmt -> RETURN expr ';'\n");

        assert(scopeFuncBlock >= 0);

        if (scopeFuncBlock == 0) {
            ++compileErrors;
            assert(indexErrors < 1000);
            strErrors[indexErrors] = yylineno;
            ++indexErrors;
        }
        
        emit(iRET, (yyvsp[(2) - (3)].exprT), NULL, NULL, 0, yylineno);    
    }
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1794 "parser.y"
    {
        printf("returnstmt -> RETURN ';'\n");

        assert(scopeFuncBlock >= 0);

        if (scopeFuncBlock == 0) {
            ++compileErrors;
            assert(indexErrors < 1000);
            strErrors[indexErrors] = yylineno;
            ++indexErrors;
        }

        emit(iRET, NULL, NULL, NULL, 0, yylineno);
    }
    break;



/* Line 1455 of yacc.c  */
#line 3967 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1811 "parser.y"



void yyerror(char* s)
{
    fprintf(stderr, "Error: %s", s);
    fprintf(stderr, "Line Code: %d\n", __LINE__);
}

int main(int argc, char** argv)
{
    FILE* fOutput;
    int i;
    symbol* trace;

    char cEndProgram = 'a';

    if(argc > 1) {
        if(!(yyin = fopen(argv[1], "r"))) {
            fprintf(stderr, "Error opening input file %s!\n", argv[1]);
            return 1;
        }

        if(argc == 3) {
            /* STDOUT -> FILE* */
            if(! (yyout = fopen(argv[2], "w")) ) {
                fprintf(stderr, "Error opening output file %s!\n", argv[2]);
                return 1;
            }
        } else if (argc > 3) {
            fprintf(stderr, "Too arguments.\n");
            return 1;
        }
        else {
            yyout = stdout;
        }
    }
    else {
        yyin = stdin;
    }

    insert_symbol_table("print", enumFUNC_LIB, 0, 0, 0, 0);
    insert_symbol_table("input", enumFUNC_LIB, 0, 0, 0, 0);
    insert_symbol_table("objectmemberkeys", enumFUNC_LIB, 0, 0, 0, 0);
    insert_symbol_table("objecttotalmembers", enumFUNC_LIB, 0, 0, 0, 0);
    insert_symbol_table("objectcopy", enumFUNC_LIB, 0, 0, 0, 0);
    insert_symbol_table("totalarguments", enumFUNC_LIB, 0, 0, 0, 0);
    insert_symbol_table("argument", enumFUNC_LIB, 0, 0, 0, 0);
    insert_symbol_table("typeof", enumFUNC_LIB, 0, 0, 0, 0);
    insert_symbol_table("strtonum", enumFUNC_LIB, 0, 0, 0, 0);
    insert_symbol_table("sqrt", enumFUNC_LIB, 0, 0, 0, 0);
    insert_symbol_table("cos", enumFUNC_LIB, 0, 0, 0, 0);
    insert_symbol_table("sin", enumFUNC_LIB, 0, 0, 0, 0);

    yyparse();


    for(i = 0; i < SIZE_SYMBOL_TABLE; ++i){

        printf("---------------------------------- Row%d -------------------------------------\n", i);

        if(symbol_table[i] == NULL) {
            continue;
        }
        trace = symbol_table[i];

        while(trace != NULL) {
            printf("name: %s, type: %s, declare1stLine: %d, scope: %d, active: %s\n", \
                 trace->name, type2string(trace->type), trace->declare1stLine, trace->scope, (trace->active)?"yes":"no" \
            );
            trace = trace->next;
        }

    }


    if (compileErrors > 0) {
        printf("Total Compile errors: %d\n", compileErrors);
        printf("Did not produced 'quads.txt'\n");
        
        for (int i = 0; i < indexErrors; ++i) {
            printf("    >>> Compile Error in line %d <<<\n", strErrors[i]);
        }
        
        return 1;
    }
    
    assert(compileErrors == 0);

    if (!(fOutput = fopen("quads.txt", "w"))) {
        fprintf(stderr, "Error opening output file 'quads.txt'!\n");
        return 1;
    }

    // spaces
    int No_to_op = 12;
    int op_to_arg1 = 14;
    int arg1_to_arg2 = 20;
    int arg2_to_result = 20;
    int result_to_label = 20;
    int label_to_line = 12;

    printf("\n\n--- iopcode ---\n\n");
    

    printf("QuadNo");
    for (int i = strlen("QuadNo"); i < No_to_op; ++i) printf(" ");

    printf("op");
    for (int i = strlen("op"); i < op_to_arg1; ++i) printf(" ");

    printf("arg1");
    for (int i = strlen("arg1"); i < arg1_to_arg2; ++i) printf(" ");

    printf("arg2");
    for (int i = strlen("arg2"); i < arg2_to_result; ++i) printf(" ");

    printf("result");
    for (int i = strlen("result"); i < result_to_label; ++i) printf(" ");

    printf("label");
    for (int i = strlen("label"); i < label_to_line; ++i) printf(" ");
    printf("line\n");


    for (int i = 0; i < currQuad; ++i) {
        
        // print QuadNo
        fprintf(fOutput, "%d: ", i);
        printf("%d:", i);
        for (int j = num_of_digits(i) + 1; j < No_to_op; ++j) printf(" ");


        // print op
        fprintf(fOutput, "%s ", iop2string(quads[i].op));
        printf("%s", iop2string(quads[i].op));
        for (int j = strlen(iop2string(quads[i].op)); j < op_to_arg1; ++j) printf(" ");

        // print arg1
        if (quads[i].arg1 != NULL) {
            if (quads[i].arg1->sym != NULL) {
                
                if (quads[i].arg1->sym->name != NULL) {

                    fprintf(fOutput, "%s ", quads[i].arg1->sym->name);
                    printf("%s", quads[i].arg1->sym->name);
                    for (int j = strlen(quads[i].arg1->sym->name); j < arg1_to_arg2; ++j) printf(" ");
                } else {
                    for (int j = 0; j < arg1_to_arg2; ++j) printf(" ");
                }
            }
            else if (quads[i].arg1->intConst != NULL) {
                
                int a = *(quads[i].arg1->intConst);
                fprintf(fOutput, "%d ", a);
                printf("%d", a);
                for (int j = num_of_digits(a); j < arg1_to_arg2; ++j) printf(" ");
            }
            else if (quads[i].arg1->numConst != NULL) {
                
                double a = *(quads[i].arg1->numConst);
                fprintf(fOutput, "%lf ", a);
                printf("%lf", a);
                for (int j = num_double_digits(a) - 1; j < arg1_to_arg2; ++j) printf(" ");
            }
            else if (quads[i].arg1->strConst != NULL) {
                
                char* a = quads[i].arg1->strConst;
                fprintf(fOutput, "\"%s\" ", a);
                printf("\"%s\"", a);
                for (int j = strlen(a) + 2; j < arg1_to_arg2; ++j) printf(" ");
            }
            else if (quads[i].arg1->type == nil_e) {

                fprintf(fOutput, "nil ");
                printf("nil");
                for (int j = strlen("nil"); j < arg1_to_arg2; ++j) printf(" ");
            }
            else if (quads[i].arg1->boolConst != NULL) {
                                
                bool* a = quads[i].arg1->boolConst;
                char* s = (*a) ? "true" : "false";
                fprintf(fOutput, "%s ", s);
                printf("%s", s);
                for (int j = strlen(s); j < arg1_to_arg2; ++j) printf(" ");
            }
            else {
                for (int j = 0; j < arg1_to_arg2; ++j) printf(" ");
            }
        } else {
            for (int j = 0; j < arg1_to_arg2; ++j) printf(" ");
        }

        // print arg2
        if (quads[i].arg2 != NULL) {

            if (quads[i].arg2->sym != NULL) {

                if (quads[i].arg2->sym->name != NULL) {

                    fprintf(fOutput, "%s ", quads[i].arg2->sym->name);
                    printf("%s", quads[i].arg2->sym->name);
                    for (int j = strlen(quads[i].arg2->sym->name); j < arg2_to_result; ++j) printf(" ");
                } else {
                    for (int j = 0; j < arg2_to_result; ++j) printf(" ");
                }
            }
            else if (quads[i].arg2->strConst != NULL) {

                char* s = quads[i].arg2->strConst;
                fprintf(fOutput, "\"%s\" ", s);
                printf("\"%s\"", s);
                for (int j = strlen(s) + 2; j < arg2_to_result; ++j) printf(" ");
            }
            else if (quads[i].arg2->unsIntConst != NULL) {

                unsigned int* unInt = quads[i].arg2->unsIntConst;
                fprintf(fOutput, "%x ", *(unInt));
                printf("%x", *(unInt));
                for (int j = num_of_digits(*(unInt)); j < arg2_to_result; ++j) printf(" ");
            }
            else if (quads[i].arg2->intConst != NULL) {

                int* d = quads[i].arg2->intConst;
                fprintf(fOutput, "%d ", *(d));
                printf("%d", *(d));
                for (int j = num_of_digits(*d); j < arg2_to_result; ++j) printf(" ");
            }
            else if (quads[i].arg2->boolConst != NULL) {

                bool* b = quads[i].arg2->boolConst;
                char* s = (*b == true) ? "true" : "false";
                fprintf(fOutput, "%s ", s);
                printf("%s", s);
                for (int j = strlen(s); j < arg2_to_result; ++j) printf(" ");
            }
            else {
                for (int j = 0; j < arg2_to_result; ++j) printf(" ");
            }
        } else {
            for (int j = 0; j < arg2_to_result; ++j) printf(" ");
        }

        // print result
        if (quads[i].result != NULL) {

            if (quads[i].result->sym != NULL) {

                if (quads[i].result->sym->name != NULL) {

                    fprintf(fOutput, "%s ", quads[i].result->sym->name);
                    printf("%s", quads[i].result->sym->name);
                    for (int j = strlen(quads[i].result->sym->name); j < result_to_label; ++j) printf(" ");
                }
                else {
                    for (int j = 0; j < result_to_label; ++j) printf(" ");
                }
            }
            else if (quads[i].result->numConst != NULL) {

                double* d = quads[i].result->numConst;
                fprintf(fOutput, "%lf ", *d);
                printf("%lf", *d);
                for (int j = num_double_digits(*d) - 1; j < arg2_to_result; ++j) printf(" ");
            }
            else if (quads[i].result->intConst != NULL) {

                int* d = quads[i].result->intConst;
                fprintf(fOutput, "%d ", *d);
                printf("%d", *d);
                for (int j = num_of_digits(*d); j < arg2_to_result; ++j) printf(" ");
            }
            else if (quads[i].result->strConst != NULL) {

                char* s = quads[i].result->strConst;
                fprintf(fOutput, "\"%s\" ", s);
                printf("\"%s\"", s);
                for (int j = strlen(s) + 2; j < arg2_to_result; ++j) printf(" ");
            }
            else if (quads[i].result->boolConst != NULL) {

                bool* b = quads[i].result->boolConst;
                char* s = (*b == true) ? "true" : "false";
                fprintf(fOutput, "%s ", s);
                printf("%s", s);
                for (int j = strlen(s); j < arg2_to_result; ++j) printf(" ");
            }
            else {
                for (int j = 0; j < result_to_label; ++j) printf(" ");
            }
        }
        else {
            for (int j = 0; j < result_to_label; ++j) printf(" ");
        }

        // print label
        if (isBranch_opcode(quads[i].op)) {
            fprintf(fOutput, "%u ", quads[i].label);
            printf("%u", quads[i].label);
            for (int j = num_of_digits(quads[i].label); j < label_to_line; ++j) printf(" ");
        }
        else {
            for (int j = 0; j < label_to_line; ++j) printf(" ");
        }

        // print line
        fprintf(fOutput, "[line %u]\n", quads[i].line);
        printf("%u\n", quads[i].line);
    }
	//print_instructions();
    //printf("\n\nType 'q' to end programm.\n");
    //cEndProgram = getchar();

    fclose(fOutput);
    
    return 0;
}


int hash_function(char* str)
{
    unsigned long long int index = 0;
    int i;

    for(i = 0; i < strlen(str); ++i) {
        index += (int) str[i];
    }

    index = index % SIZE_SYMBOL_TABLE;

    return index;
}


void insert_symbol_table(char* name, enumTypeId_t type, int line, int argScope, int argScopeFuncBlock, int argScopeStmtBlock)
{
    int index = hash_function(name);
    symbol* trace = NULL;


    if (symbol_table[index] == NULL) {
        
        symbol_table[index] = (symbol*) malloc(sizeof(symbol));


        if (symbol_table[index] == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        symbol_table[index]->name = name;
        symbol_table[index]->type = type;
        symbol_table[index]->declare1stLine = line;
        symbol_table[index]->scope = argScope;
        symbol_table[index]->scopeFuncBlock = argScopeFuncBlock;
        symbol_table[index]->scopeStmtBlock = argScopeStmtBlock;
        symbol_table[index]->active = true;
        symbol_table[index]->next = NULL;

        switch (type) {
            case enumLOCAL:
            case enumGLOBAL:
            case enumFUNC_ARG:
                symbol_table[index]->typeS = var_s; break;
            case enumFUNC_LIB:
                symbol_table[index]->typeS = libraryfunc_s; break;
            case enumFUNC_USER: 
                symbol_table[index]->typeS = programfunc_s; break;
            default:
                assert(0);
        }
    }
    else {

        trace = symbol_table[index];

        while(trace->next != NULL) {
            if(
                !strcmp(trace->name, name) &&
                trace->active == true      &&
                trace->scope == argScope
            ) return;
            trace = trace->next;
        }

        /* The end of the chain list */
        if(
            !strcmp(trace->name, name) &&
            trace->active == true      &&
            trace->scope == argScope
        ) return;
        trace->next = (symbol*) malloc(sizeof(symbol));

        if (trace->next == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }
        

        trace->next->name = name;
        trace->next->type = type;
        trace->next->declare1stLine = line;
        trace->next->scope = argScope;
        trace->next->scopeFuncBlock = argScopeFuncBlock;
        trace->next->scopeStmtBlock = argScopeStmtBlock;
        trace->next->active = true;
        trace->next->next = NULL;

        switch (type) {
            case enumLOCAL:
            case enumGLOBAL:
            case enumFUNC_ARG:
                trace->next->typeS = var_s; break;
            case enumFUNC_LIB:
                trace->next->typeS = libraryfunc_s; break;
            case enumFUNC_USER: 
                trace->next->typeS = programfunc_s; break;
            default:
                assert(0);
        }
    }
}

char* hiddenVarF()
{
    char a[SIZE_HIDDEN_VAR] = { '\0' };
    char* str;
    int i;

    ++hideNameFunction;

    sprintf(a, "%d%c", hideNameFunction, '\0');

    str = (char*) malloc(SIZE_HIDDEN_VAR*sizeof(char));

    if (str == NULL) {
        printf("No memory... Line code: %d\n", __LINE__);
        exit(1);
    }

    str[0] = '_';

    for(i = 1; i < SIZE_HIDDEN_VAR; ++i) {
        str[i] = a[i - 1];
    }

    return str;
}

bool isLibFunction(char* name)
{
    if(!strcmp(name, "print")){
    } else if(!strcmp(name, "input")){
    } else if (!strcmp(name, "objectmemberkeys")){
    } else if (!strcmp(name, "objecttotalmembers")){
    } else if (!strcmp(name, "objectcopy")) {
    } else if (!strcmp(name, "totalarguments")) {
    } else if (!strcmp(name, "argument")) {
    } else if (!strcmp(name, "typeof")) {
    } else if (!strcmp(name, "strtonum")) {
    } else if (!strcmp(name, "sqrt")) {
    } else if (!strcmp(name, "cos")) {
    } else if (!strcmp(name, "sin")) {
    } else {
        return false;
    }
        return true;
}

symbol* lookup_sym(char* name, int argScope)
{
    int index = hash_function(name);

    symbol* trace = symbol_table[index];

    while(trace != NULL) {
        if(
            !strcmp(trace->name, name) &&
            trace->active == true      &&
            trace->scope == argScope
        ) return trace;
        trace = trace->next;
    }
    return NULL;
}

bool isUserFunction(char* name, int argScope)
{
    int index = hash_function(name);

    symbol* trace = symbol_table[index];

    while(trace != NULL) {
        if(
            !strcmp(trace->name, name) &&
            trace->active == true      &&
            trace->scope <= argScope   &&
            trace->type == enumFUNC_USER
        ) return true;
        trace = trace->next;
    }
    return false;
}

char* type2string(enumTypeId_t type)
{
    switch(type) {
        case enumLOCAL:
            return "local var";
        case enumGLOBAL:
            return "global var";
        case enumFUNC_USER:
            return "user function";
        case enumFUNC_ARG:
            return "function argument";
        case enumFUNC_LIB:
            return "library function";
        default:
            assert(0);
    }
}

void hideVariables_sym(int argScope)
{
    symbol* trace = NULL;
    int i = 0;

    for(i = 0; i < SIZE_SYMBOL_TABLE; ++i) {

        if(symbol_table[i] != NULL) {

            trace = symbol_table[i];

            while(trace != NULL) {
                if(
                    trace->active == true &&
                    trace->scope == argScope
                ) trace->active = false;
                trace = trace->next;
            }
        }
    }
}


/**
 * If an id is function, it is read only variable.
 * It's not allowed "f=3, ++f, --f, f--, f++" for a function f(){}.
 * @rules:
 *         lvalue '=' expr
 *         PLUS_PLUS lvalue
 *         MINUS_MINUS lvalue
 *         lvalue PLUS_PLUS
 *         lvalue MINUS_MINUS
 *
 *         %type <exprNode> lvalue   ---  struct symbol* exprNode;
**/
void checkOnlyReadValue(const symbol* id)
{
    if(id == NULL) return;

    if(isUserFunction(id->name, scope)) {
        
        int currScope = scope;
        symbol* foundId = NULL;

        while(currScope >= 0) {

            if((foundId = lookup_sym(id->name, currScope))){

                switch(foundId->type) {
                    case enumFUNC_ARG:
                        if(foundId->scopeFuncBlock != scopeFuncBlock) {
                            fprintf(stderr, "ERROR in line %d! Try to access argument [line: %d] of other function while it is active.\n", \
                                        yylineno, foundId->declare1stLine);
                            exit(1);
                        }
                        break;
                    case enumLOCAL:
                        if(foundId->scopeFuncBlock != scopeFuncBlock) {
                            fprintf(stderr, "ERROR in line %d! Try to access local variable [line: %d] of other scope while it is active.\n", \
                                       yylineno, foundId->declare1stLine);
                            exit(1);
                        }
                        break;
                    default:
                        break;
                }

                return;

            }

            --currScope;
        }

        fprintf(stderr, "ERROR! Try to change const value of user Function in line %d.\n", yylineno);
        exit(1);
    }
    else if(isLibFunction(id->name)) {
        fprintf(stderr, "ERROR! Try to change const value of library Function in line %d.\n", yylineno);
        exit(1);
    }
    else {
        //assert(id->type == enumFUNC_ARG || id->type == enumGLOBAL || id->type == enumLOCAL);
    }
}

expr* emit_iftableitem(expr* e)
{
    if (e->type != tableitem_e) {
        return e;
    }
    else {
        expr* result = newexpr(var_e);
        result->sym = newtemp();
        emit(iTABLEGETELEM, e, e->index, result, 0, yylineno);
        return result;
    }
}

scopespace_t currscopespace(void)
{
    if (scopeSpaceCounter == 1) {
        return programvar;
    }
    else if (scopeSpaceCounter % 2 == 0) {
        return formalarg;
    }
    else {
        return functionlocal;
    }
}

unsigned currscopeoffset(void)
{
    switch(currscopespace()) {
        case programvar:       return programVarOffset;
        case functionlocal:    return functionLocalOffset;
        case formalarg:        return formalArgOffset;
        default: assert(0);
    }
}

void incurrscopeoffset(void)
{
    switch(currscopespace()) {
        case programvar:    ++programVarOffset; break;
        case functionlocal: ++functionLocalOffset; break;
        case formalarg:     ++formalArgOffset; break;
        default: assert(0);
    }
}

void enterscopespace(void)
{
    ++scopeSpaceCounter;
}

void exitscopespace(void)
{
    assert(scopeSpaceCounter > 1);
    --scopeSpaceCounter;
}

void resetformalargsoffset(void)
{
    formalArgOffset = 0;
}

void resetfunctionlocalsoffset(void)
{
    functionLocalOffset = 0;
}

void restorecurrscopeoffset(unsigned n)
{
    switch(currscopespace()) {
        case programvar:    programVarOffset = n; break;
        case functionlocal: functionLocalOffset = n; break;
        case formalarg:     formalArgOffset = n; break;
        default: assert(0);
    }
}

unsigned nextquadlabel(void)
{
    return currQuad;
}

void patchlabel (unsigned quadNo, unsigned label)
{
    assert(quadNo < currQuad && !quads[quadNo].label);
    quads[quadNo].label = label;
}

expr* lvalue_expr(symbol* sym)
{
    expr* e = (expr*) malloc(sizeof(expr));

    if (e == NULL) {
        printf("No memory... Line code: %d\n", __LINE__);
        exit(1);
    }

    memset(e, 0, sizeof(expr));

    e->next = NULL;
    e->sym = sym;

    if (sym != NULL) {
        switch (sym->typeS) {
            case var_s:           e->type = var_e; break;
            case programfunc_s:   e->type = programfunc_e; break;
            case libraryfunc_s:   e->type = libraryfunc_e; break;
            default:
                assert(0);
        }
    }
    return e;
}

void expand(void)
{
    assert(total == currQuad);
    quad* p = (quad*) malloc(NEW_SIZE);

    if (p == NULL) {
        printf("No memory... Line code: %d\n", __LINE__);
        exit(1);
    }
    
    if (quads) {
        memcpy(p, quads, CURR_SIZE);
        free(quads);
    }
    quads = p;
    total += EXPAND_SIZE;
}

void emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line)
{
    if (currQuad == total) expand();

    quad* p         = quads + currQuad++;
    p->op           = op;
    p->arg1         = arg1;
    p->arg2         = arg2;
    p->result       = result;
    p->label        = label;
    p->line         = line;
}

void check_arith (expr* e)
{
    if (
        e->type == constbool_e   ||
        e->type == conststring_e ||
        e->type == nil_e         ||
        e->type == newtable_e    ||
        e->type == programfunc_e ||
        e->type == libraryfunc_e ||
        e->type == boolexpr_e
    )
    fprintf(stderr, "Illegal expr used!\n");
}

unsigned int istempname (char* s)
{
    if (s == NULL) return 0;
    if (strlen(s) <= 2) return 0;
    return (*s == '_')&&(s[1] == 't');
}

unsigned int istempexpr (expr* e)
{
    return e->sym && istempname(e->sym->name);
}

expr* newexpr_constbool (unsigned int b )
{
    expr* e = newexpr(constbool_e);

    e->boolConst = (bool*) malloc(sizeof(bool));

    if (e->boolConst == NULL) {
        printf("No memory... Line Code: %d\n", __LINE__);
        exit(1);
    }

    *(e->boolConst) = !!b;
    return e;
}

stmt* make_stmt ()
{
    stmt* s = (stmt*) malloc(sizeof(stmt));

    if (!s) {
        printf("No memory... Line Code: %d\n");
        exit(1);
    }

    s->breakList = 0;
    s->contList = 0;
    s->breakStmt = false;
    s->contStmt = false;
    s->next = NULL;

    return s;
}

int newlist(int i)
{
    assert(i >= 0 && i <= CURR_SIZE);
    quads[i].label = 0;
    return i;
}

int mergelist(int l1, int l2)
{
    if (!l1) return l2;
    else if (!l2) return l1;
    else {
        // l1 != 0 && l2 != 0
        int i = l1;
        while (quads[i].label) i = quads[i].label;
        quads[i].label = l2;
        return l1;
    }
}

void patchlist (int list, int label)
{
    while(list) {
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
}

char* newtempname()
{
    char a[SIZE_HIDDEN_VAR] = { '\0' };
    char* str;
    int i;

    ++tempcounter;

    sprintf(a, "%d%c", tempcounter, '\0');

    str = (char*) malloc(SIZE_HIDDEN_VAR*sizeof(char));

    if (str == NULL) {
        printf("No memory... Line code: %d\n", __LINE__);
        exit(1);
    }

    str[0] = '_';
    str[1] = 't';

    for(i = 2; i < SIZE_HIDDEN_VAR; ++i) {
        str[i] = a[i - 2];
    }

    return str;
}

void resettemp()
{
    tempcounter = 0;
}

symbol* newtemp()
{
    char* name = newtempname();
    symbol* sym = lookup_sym(name, scope);

    if (sym == NULL) {
        insert_symbol_table(name, (scope != 0) ? enumLOCAL : enumGLOBAL, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        sym = newsymbol(name, var_s);
    }
    return sym;
}

expr* newexpr(expr_t e_t)
{
    expr* expression = (expr*) malloc(sizeof(expr));
    expression = return_zero_expr(expression);

    if (expression == NULL) {
        printf("No memory for expression\n");
        exit(1);
    }

    expression->type = e_t;
    expression->sym = NULL;
    return expression;
}

void push(int Stack[], int elem, int* Top)
{
    assert(*Top >= 0 && *Top < SIZE_STACK);
    Stack[*Top] = elem;
    ++(*Top);
}

int pop(int Stack[], int* Top)
{
    return Stack[--(*Top)];
}
/*
expr* popElist(expr* Stack[])
{
    return Stack[--topElist];
}

void pushElist(expr* Stack[], expr* e)
{
    assert(topElist >= 0 && topElist < SIZE_STACK);
    Stack[topElist] = e;
    ++topElist;
}
*/
symbol* newsymbol(char* name, symbol_t s_t)
{
    symbol* sym = (symbol*) malloc(sizeof(symbol));

    if (sym == NULL) {
        printf("No memory for symbol\n");
        exit(1);
    }

    sym->name = name;
    sym->typeS = s_t;
    return sym;
}

char* iop2string(iopcode op)
{
    switch(op) {
        case iASSIGN: return "ASSIGN";
        case iADD: return "ADD";
        case iSUB: return "SUB";
        case iMUL: return "MUL";
        case iDIV: return "DIV";
        case iMOD: return "MOD";
        case iUMINUS: return "UMINUS";
        case iAND: return "AND";
        case iOR: return "OR";
        case iNOT: return "NOT";
        case iIF_EQ: return "IF_EQ";
        case iIF_NOTEQ: return "IF_NOTEQ";
        case iIF_LESSEQ: return "IF_LESSEQ";
        case iIF_GREATEREQ: return "IF_GREATEREQ";
        case iIF_LESS: return "IF_LESS";
        case iIF_GREATER: return "IF_GREATER";
        case iCALL: return "CALL";
        case iPARAM: return "PARAM";
        case iRET: return "RETURN";
        case iGETRETVAL: return "GETRETVAL";
        case iFUNCSTART: return "FUNCSTART";
        case iFUNCEND: return "FUNCEND";
        case iTABLECREATE: return "TABLECREATE";
        case iTABLEGETELEM: return "TABLEGETELEM";
        case iTABLESETELEM: return "TABLESETELEM";
        case iJUMP: return "JUMP";
        default:
            assert(0);
    }
}


int num_of_digits(unsigned int num)
{
    int count = 0;

    do {
        num /= 10;
        ++count;
    } while (num != 0);
    
    return count;
}

expr* member_item(expr* lv, char* name)
{
    lv = emit_iftableitem(lv);
    expr* ti = newexpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name);
    return ti;
}

expr* newexpr_conststring(char* s)
{
    expr* e = newexpr(conststring_e);
    e->strConst = strdup(s);
    return e;
}

int num_double_digits(double num)
{
    // 22342.2234543534 = 16 characters
    int chars = 0;
    char arr[20];

    sprintf(arr, "%lf%c", num, '\0');

    return strlen(arr) + 1;
}

expr* make_call(expr* lv, expr* elist)
{
    expr* reversed_elist = reverse(elist);
    expr* func = emit_iftableitem(lv);

    while (reversed_elist != NULL && reversed_elist->type != nil_e) {
        emit(iPARAM, reversed_elist, NULL, NULL, 0, yylineno);
        reversed_elist = reversed_elist->next;
    }

    emit(iCALL, func, NULL, NULL, 0, yylineno);
    expr* result = newexpr(var_e);
    result->sym = newtemp();
    emit(iGETRETVAL, NULL, NULL, result, 0, yylineno);
    return result;
}


/*
Example:

f(a, b, c, d, e)

elist -> a -> b -> c -> d -> e -> NULL

NULL <- elist <- a <- b <- c <- d <- e

p: prev
m: middle
n: next

1.

p    m    n  
|    |    |
a -> b -> c -> d -> e -> NULL

2.

        p    m    n  
        |    |    |
NULL <- a    b -> c -> d -> e -> NULL


3. while:

(i)
        p    m    n  
        |    |    |
NULL <- a <- b    c -> d -> e -> NULL

(ii)
            p,m    n  
             |    |
NULL <- a <- b    c -> d -> e -> NULL

(iii)
             p   m,n  
             |    |
NULL <- a <- b    c -> d -> e -> NULL

(iv)
             p    m    n  
             |    |    |
NULL <- a <- b    c -> d -> e -> NULL

*/
expr* reverse(expr* list)
{
    expr* prev;
    expr* middle;
    expr* next;

    if (list == NULL || list->next == NULL) {
        return list;
    }
    else {
        // 1.
        prev = list;
        middle = list->next;
        next = list->next->next;

        // 2.
        prev->next = NULL;

        // 3.
        while (next != NULL) {

            middle->next = prev; // (i)
            prev = middle; // (ii)
            middle = next; // (iii)
            next = next->next; // (iv)
        }
        middle->next = prev;
        return middle;
    }
}

expr* newexpr_constnum(unsigned int i)
{
    expr* e = newexpr(constnum_e);
    unsigned int* ptr = (unsigned int*) malloc(sizeof(double));
    
    if (ptr == NULL) {
        printf("No memory... Line Code: %d\n", __LINE__);
        exit(1);
    }

    e->unsIntConst = ptr;
    *(e->unsIntConst) = i;
    return e;
}

expr* return_zero_expr(expr* e)
{
    e->type = nil_e;
    e->sym = NULL;
    e->index = NULL;
    e->numConst = NULL;
    e->intConst = NULL;
    e->unsIntConst = NULL;
    e->strConst = NULL;
    e->boolConst = NULL;
    e->PairIndex = NULL;
    e->PairValue = NULL;
    e->next = NULL;
}

bool isBranch_opcode(iopcode op)
{
    switch(op) {
        case iJUMP: case iIF_EQ: case iIF_NOTEQ:
        case iIF_LESS: case iIF_LESSEQ:
        case iIF_GREATER: case iIF_GREATEREQ:
            return true;
        default:
            return false;
    }
}
