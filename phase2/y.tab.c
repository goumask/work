
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

void yyerror(char* s);
int yylex();
extern FILE* yyin;
extern int yylineno;

#define SIZE_HIDDEN_VAR 10
#define SIZE_SYMBOL_TABLE 100

typedef enum enumTypeId {
    enumLOCAL, enumGLOBAL, enumFUNC_ARG, enumFUNC_USER, enumFUNC_LIB
}enumTypeId_t;

typedef struct id {
    char*           name;
    enumTypeId_t    type;           /* 0: local, 1: global, 2: function_arg, 3: function_user, 4: function_lib */
    int             declare1stLine;
    int             scope;
    int             scopeFuncBlock;
    int             scopeStmtBlock;
    bool            active;
    //int             enumNumber;     /* serial number of: globals, function_arg, locals */
    struct id*      next;
}Id_t;



Id_t* symbol_table[SIZE_SYMBOL_TABLE] = { NULL };

int hash_function(char*);
void insert_symbol_table(char*, enumTypeId_t, int line, int argScope, int argScopeFuncBlock, int argScopeStmtBlock);
bool isLibFunction(char* name);
Id_t* lookup_sym(char* name, int argScope);
bool isUserFunction(char* name, int argScope);
char* type2string(enumTypeId_t type);
void hideVariables_sym(int argScope);
void checkOnlyReadValue(const Id_t* id);

int hideNameFunction = 0;
char* hiddenVarF();



int scope = 0;
int scopeStmtBlock = 0;
int scopeFuncBlock = 0;



/* Line 189 of yacc.c  */
#line 129 "y.tab.c"

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
#line 69 "parser.y"

    int numInt;
    double numReal;
    char* string;
    struct id* exprNode; // Compiler says: unknown type name 'Id_t'



/* Line 214 of yacc.c  */
#line 234 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 246 "y.tab.c"

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
#define YYFINAL  68
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   684

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNRULES -- Number of states.  */
#define YYNSTATES  178

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
       0,     0,     3,     4,     7,     9,    12,    14,    16,    18,
      20,    23,    26,    28,    30,    32,    34,    38,    40,    42,
      44,    46,    48,    50,    52,    54,    56,    58,    60,    62,
      64,    66,    70,    73,    76,    79,    82,    85,    88,    90,
      91,    96,    98,   100,   102,   106,   108,   110,   113,   116,
     118,   122,   127,   132,   136,   141,   144,   151,   153,   155,
     159,   165,   166,   168,   171,   172,   176,   180,   184,   185,
     188,   189,   193,   199,   200,   201,   207,   208,   213,   214,
     215,   224,   225,   226,   234,   236,   238,   240,   242,   244,
     246,   247,   248,   252,   253,   254,   259,   266,   267,   270,
     276,   286,   290
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    -1,    51,    50,    -1,     1,    -1,    52,
      44,    -1,    85,    -1,    87,    -1,    88,    -1,    89,    -1,
       9,    44,    -1,    10,    44,    -1,    70,    -1,    75,    -1,
      44,    -1,    55,    -1,    52,    53,    52,    -1,    54,    -1,
      33,    -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,
      31,    -1,    23,    -1,    32,    -1,    22,    -1,    18,    -1,
      19,    -1,    11,    -1,    13,    -1,    42,    52,    43,    -1,
      34,    52,    -1,    12,    52,    -1,    20,    58,    -1,    58,
      20,    -1,    21,    58,    -1,    58,    21,    -1,    57,    -1,
      -1,    58,    56,    30,    52,    -1,    60,    -1,    58,    -1,
      66,    -1,    42,    75,    43,    -1,    80,    -1,    29,    -1,
      14,    29,    -1,    24,    29,    -1,    59,    -1,    58,    39,
      29,    -1,    58,    40,    52,    41,    -1,    60,    40,    52,
      41,    -1,    60,    39,    29,    -1,    60,    42,    64,    43,
      -1,    58,    61,    -1,    42,    75,    43,    42,    64,    43,
      -1,    62,    -1,    63,    -1,    42,    64,    43,    -1,    25,
      29,    42,    64,    43,    -1,    -1,    52,    -1,    52,    65,
      -1,    -1,    45,    52,    65,    -1,    40,    64,    41,    -1,
      40,    67,    41,    -1,    -1,    69,    68,    -1,    -1,    45,
      69,    68,    -1,    46,    52,    47,    52,    48,    -1,    -1,
      -1,    46,    71,    50,    72,    48,    -1,    -1,    46,    50,
      74,    48,    -1,    -1,    -1,     7,    29,    76,    42,    77,
      81,    43,    73,    -1,    -1,    -1,     7,    78,    42,    79,
      81,    43,    73,    -1,    28,    -1,    26,    -1,    27,    -1,
      17,    -1,    15,    -1,    16,    -1,    -1,    -1,    29,    82,
      83,    -1,    -1,    -1,    45,    29,    84,    83,    -1,     3,
      42,    52,    43,    51,    86,    -1,    -1,     4,    51,    -1,
       5,    42,    52,    43,    51,    -1,     6,    42,    64,    44,
      52,    44,    64,    43,    51,    -1,     8,    52,    44,    -1,
       8,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    94,    94,    95,    96,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   116,   117,   118,   122,   122,
     122,   122,   122,   122,   122,   123,   123,   123,   123,   123,
     123,   127,   128,   129,   130,   131,   132,   133,   134,   138,
     138,   145,   146,   147,   148,   149,   153,   194,   206,   216,
     220,   221,   222,   223,   227,   228,   229,   233,   234,   238,
     242,   246,   247,   248,   250,   251,   255,   256,   260,   261,
     263,   264,   268,   272,   273,   272,   277,   277,   282,   310,
     282,   313,   314,   313,   319,   319,   319,   319,   319,   319,
     323,   324,   324,   345,   346,   346,   375,   377,   378,   382,
     386,   390,   391
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
  "'}'", "$accept", "program", "stmt", "expr", "op", "term", "assignexpr",
  "$@1", "primary", "lvalue", "member", "call", "callsuffix", "normcall",
  "methodcall", "elist", "elistExtend", "objectdef", "indexed",
  "indexedExtend", "indexedelem", "blockStmt", "$@2", "$@3", "blockFunc",
  "$@4", "funcdef", "$@5", "$@6", "$@7", "$@8", "const", "idlist", "$@9",
  "idlistExtend", "$@10", "ifstmt", "ifstmtExtend", "whilestmt", "forstmt",
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
       0,    49,    50,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    52,    52,    52,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    54,    54,    54,    54,    54,    54,    54,    54,    56,
      55,    57,    57,    57,    57,    57,    58,    58,    58,    58,
      59,    59,    59,    59,    60,    60,    60,    61,    61,    62,
      63,    64,    64,    64,    65,    65,    66,    66,    67,    67,
      68,    68,    69,    71,    72,    70,    74,    73,    76,    77,
      75,    78,    79,    75,    80,    80,    80,    80,    80,    80,
      81,    82,    81,    83,    84,    83,    85,    86,    86,    87,
      88,    89,    89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     2,     2,     2,     2,     2,     1,     0,
       4,     1,     1,     1,     3,     1,     1,     2,     2,     1,
       3,     4,     4,     3,     4,     2,     6,     1,     1,     3,
       5,     0,     1,     2,     0,     3,     3,     3,     0,     2,
       0,     3,     5,     0,     0,     5,     0,     4,     0,     0,
       8,     0,     0,     7,     1,     1,     1,     1,     1,     1,
       0,     0,     3,     0,     0,     4,     6,     0,     2,     5,
       9,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     4,     0,     0,     0,    81,     0,     0,     0,     0,
       0,    88,    89,    87,     0,     0,     0,    85,    86,    84,
      46,     0,    61,     0,    14,    73,     0,     0,     0,    17,
      15,    38,    42,    49,    41,    43,    12,    13,    45,     6,
       7,     8,     9,     0,     0,    61,    78,     0,   102,     0,
      10,    11,    33,    47,     0,    34,     0,    36,    48,    32,
       0,    62,     0,     0,    70,     0,     0,     0,     1,     3,
      29,    30,    27,    28,    26,    24,    23,    25,    18,    19,
      20,    21,    22,     5,     0,    35,    37,     0,     0,     0,
      61,     0,    55,    57,    58,     0,     0,    61,     0,     0,
       0,     0,    82,   101,     0,     0,     0,    63,    66,    67,
       0,    69,    31,    44,    74,    16,     0,    50,     0,     0,
       0,    53,     0,     0,     0,     0,     0,    79,    90,     0,
       0,    64,    70,    61,     0,    61,    51,    59,    40,    52,
      54,    97,    99,     0,    90,    91,     0,     0,    65,    71,
       0,    75,     0,     0,    96,    61,     0,    93,     0,    72,
      56,    60,    98,     0,     0,     0,    92,     0,    83,     0,
      80,    94,    76,   100,    93,     0,    95,    77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,    28,    84,    29,    30,    91,    31,    32,
      33,    34,    92,    93,    94,    62,   107,    35,    63,   111,
      64,    36,    67,   134,   168,   175,    37,   101,   144,    47,
     128,    38,   146,   157,   166,   174,    39,   154,    40,    41,
      42
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -119
static const yytype_int16 yypact[] =
{
     223,  -119,   -34,   -30,   -24,   -27,   456,   -21,   -19,   568,
      -1,  -119,  -119,  -119,   -10,   -10,     2,  -119,  -119,  -119,
    -119,   568,   323,    46,  -119,  -119,    36,   130,   376,  -119,
    -119,  -119,    77,  -119,   -29,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,   568,   568,   568,  -119,     7,  -119,   403,
    -119,  -119,  -119,  -119,    45,    64,   -29,    64,  -119,  -119,
     568,   348,    14,    15,    19,   484,    22,   174,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,   568,  -119,  -119,    39,    40,   568,
     568,    41,  -119,  -119,  -119,    47,   568,   568,   511,   538,
      33,    37,  -119,  -119,    38,   295,   568,  -119,  -119,  -119,
      48,  -119,  -119,    43,  -119,   647,    50,  -119,   593,    44,
     568,  -119,   620,    53,   265,   265,   568,  -119,    70,    43,
     568,   348,    19,   568,    34,   568,  -119,  -119,   647,  -119,
    -119,    97,  -119,   430,    70,  -119,    62,    11,  -119,  -119,
      65,  -119,    66,   265,  -119,   568,    67,    68,    72,  -119,
    -119,  -119,  -119,    69,    72,    82,  -119,   174,  -119,   265,
    -119,  -119,  -119,  -119,    68,    73,  -119,  -119
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -119,   -26,  -118,    -6,  -119,  -119,  -119,  -119,  -119,     6,
    -119,    12,  -119,  -119,  -119,   -40,    -9,  -119,  -119,    -7,
      13,  -119,  -119,  -119,   -38,  -119,   -14,  -119,  -119,  -119,
    -119,  -119,   -16,  -119,   -42,  -119,  -119,  -119,  -119,  -119,
    -119
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -40
static const yytype_int16 yytable[] =
{
      49,    69,    46,    52,    10,   100,   141,   142,    43,    66,
      95,    96,    44,    97,    16,    59,    61,    65,    45,    20,
      55,    57,    70,    50,    71,    51,    56,    56,    53,    72,
      73,    58,    54,    74,    75,   162,    68,    98,    99,    61,
     104,   114,    76,    77,    78,    79,    80,    81,    82,   102,
     119,   173,     5,     5,   105,   108,   109,   123,     9,   159,
      10,    11,    12,    13,   110,   113,    14,    15,   116,   117,
      16,   120,    17,    18,    19,    20,   121,   126,   115,   127,
      21,   129,   151,   118,    61,   133,    22,   137,    23,    87,
     122,    61,   135,   150,    60,   152,   140,    85,    86,   145,
     131,   153,    87,    88,    89,   158,    90,   -39,   160,   161,
     164,   171,   169,   165,   138,   163,    88,    89,   167,    90,
     143,   177,   148,   132,   147,   149,   170,    61,   156,    61,
      -2,     1,   176,     2,     0,     3,     4,     5,     6,     7,
       8,   172,     9,     0,    10,    11,    12,    13,     0,    61,
      14,    15,     0,     0,    16,     0,    17,    18,    19,    20,
       0,     0,     0,     0,    21,     0,     0,     0,     0,     0,
      22,     0,    23,     0,    24,     1,    25,     2,    -2,     3,
       4,     5,     6,     7,     8,     0,     9,     0,    10,    11,
      12,    13,     0,     0,    14,    15,     0,     0,    16,     0,
      17,    18,    19,    20,     0,     0,     0,     0,    21,     0,
       0,     0,     0,     0,    22,     0,    23,     0,    24,     0,
      25,     0,    -2,    -2,     1,     0,     2,     0,     3,     4,
       5,     6,     7,     8,     0,     9,     0,    10,    11,    12,
      13,     0,     0,    14,    15,     0,     0,    16,     0,    17,
      18,    19,    20,     0,     0,     0,     0,    21,     0,     0,
       0,     0,     0,    22,     0,    23,     0,    24,     2,    25,
       3,     4,     5,     6,     7,     8,     0,     9,     0,    10,
      11,    12,    13,     0,     0,    14,    15,     0,     0,    16,
       0,    17,    18,    19,    20,     0,     0,     0,     0,    21,
       0,     0,     0,     0,     0,    22,    70,    23,    71,    24,
       0,    25,     0,    72,    73,     0,     0,    74,    75,     0,
       0,     0,     0,     0,     0,     0,    76,    77,    78,    79,
      80,    81,    82,     0,     0,     9,     0,    10,    11,    12,
      13,     0,   130,    14,    15,     0,     0,    16,     0,    17,
      18,    19,    20,     0,     0,     0,     0,    21,     0,    70,
       0,    71,     0,    22,     0,    23,    72,    73,     0,    60,
      74,    75,     0,     0,     0,     0,     0,     0,     0,    76,
      77,    78,    79,    80,    81,    82,     0,    70,     0,    71,
       0,     0,     0,   106,    72,    73,     0,     0,    74,    75,
       0,     0,     0,     0,     0,     0,     0,    76,    77,    78,
      79,    80,    81,    82,    70,     0,    71,     0,     0,     0,
      83,    72,    73,     0,     0,    74,    75,     0,     0,     0,
       0,     0,     0,     0,    76,    77,    78,    79,    80,    81,
      82,    70,     0,    71,     0,     0,     0,   103,    72,    73,
       0,     0,    74,    75,     0,     0,     0,     0,     0,     0,
       0,    76,    77,    78,    79,    80,    81,    82,     9,     0,
      10,    11,    12,    13,   155,     0,    14,    15,     0,     0,
      16,     0,    17,    18,    19,    20,     0,     0,     0,     0,
      21,     0,     0,     0,     0,    70,    22,    71,    23,     0,
      48,     0,    72,    73,     0,     0,    74,    75,     0,     0,
       0,     0,     0,     0,     0,    76,    77,    78,    79,    80,
      81,    82,    70,     0,    71,     0,     0,   112,     0,    72,
      73,     0,     0,    74,    75,     0,     0,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,    81,    82,    70,
       0,    71,     0,     0,   124,     0,    72,    73,     0,     0,
      74,    75,     0,     0,     0,     0,     0,     0,     0,    76,
      77,    78,    79,    80,    81,    82,     0,     0,     0,     0,
       9,   125,    10,    11,    12,    13,     0,     0,    14,    15,
       0,     0,    16,     0,    17,    18,    19,    20,     0,     0,
       0,     0,    21,     0,    70,     0,    71,     0,    22,     0,
      23,    72,    73,     0,     0,    74,    75,     0,     0,     0,
       0,     0,     0,     0,    76,    77,    78,    79,    80,    81,
      82,    70,     0,    71,   136,     0,     0,     0,    72,    73,
       0,     0,    74,    75,     0,     0,     0,     0,     0,     0,
       0,    76,    77,    78,    79,    80,    81,    82,    70,     0,
      71,   139,     0,     0,     0,    72,    73,     0,     0,    74,
      75,     0,     0,     0,     0,     0,     0,     0,    76,    77,
      78,    79,    80,    81,    82
};

static const yytype_int16 yycheck[] =
{
       6,    27,    29,     9,    14,    45,   124,   125,    42,    23,
      39,    40,    42,    42,    24,    21,    22,    23,    42,    29,
      14,    15,    11,    44,    13,    44,    14,    15,    29,    18,
      19,    29,    42,    22,    23,   153,     0,    43,    44,    45,
      54,    67,    31,    32,    33,    34,    35,    36,    37,    42,
      90,   169,     7,     7,    60,    41,    41,    97,    12,    48,
      14,    15,    16,    17,    45,    43,    20,    21,    29,    29,
      24,    30,    26,    27,    28,    29,    29,    44,    84,    42,
      34,    43,    48,    89,    90,    42,    40,    43,    42,    25,
      96,    97,    42,   133,    46,   135,    43,    20,    21,    29,
     106,     4,    25,    39,    40,    43,    42,    30,    43,    43,
      43,    29,    43,    45,   120,   155,    39,    40,    46,    42,
     126,    48,   131,   110,   130,   132,   164,   133,   144,   135,
       0,     1,   174,     3,    -1,     5,     6,     7,     8,     9,
      10,   167,    12,    -1,    14,    15,    16,    17,    -1,   155,
      20,    21,    -1,    -1,    24,    -1,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    42,    -1,    44,     1,    46,     3,    48,     5,
       6,     7,     8,     9,    10,    -1,    12,    -1,    14,    15,
      16,    17,    -1,    -1,    20,    21,    -1,    -1,    24,    -1,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    42,    -1,    44,    -1,
      46,    -1,    48,     0,     1,    -1,     3,    -1,     5,     6,
       7,     8,     9,    10,    -1,    12,    -1,    14,    15,    16,
      17,    -1,    -1,    20,    21,    -1,    -1,    24,    -1,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    42,    -1,    44,     3,    46,
       5,     6,     7,     8,     9,    10,    -1,    12,    -1,    14,
      15,    16,    17,    -1,    -1,    20,    21,    -1,    -1,    24,
      -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    40,    11,    42,    13,    44,
      -1,    46,    -1,    18,    19,    -1,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    12,    -1,    14,    15,    16,
      17,    -1,    47,    20,    21,    -1,    -1,    24,    -1,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    34,    -1,    11,
      -1,    13,    -1,    40,    -1,    42,    18,    19,    -1,    46,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    37,    -1,    11,    -1,    13,
      -1,    -1,    -1,    45,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    37,    11,    -1,    13,    -1,    -1,    -1,
      44,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      37,    11,    -1,    13,    -1,    -1,    -1,    44,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    35,    36,    37,    12,    -1,
      14,    15,    16,    17,    44,    -1,    20,    21,    -1,    -1,
      24,    -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    11,    40,    13,    42,    -1,
      44,    -1,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    37,    11,    -1,    13,    -1,    -1,    43,    -1,    18,
      19,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    11,
      -1,    13,    -1,    -1,    43,    -1,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      12,    43,    14,    15,    16,    17,    -1,    -1,    20,    21,
      -1,    -1,    24,    -1,    26,    27,    28,    29,    -1,    -1,
      -1,    -1,    34,    -1,    11,    -1,    13,    -1,    40,    -1,
      42,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      37,    11,    -1,    13,    41,    -1,    -1,    -1,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    35,    36,    37,    11,    -1,
      13,    41,    -1,    -1,    -1,    18,    19,    -1,    -1,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     5,     6,     7,     8,     9,    10,    12,
      14,    15,    16,    17,    20,    21,    24,    26,    27,    28,
      29,    34,    40,    42,    44,    46,    50,    51,    52,    54,
      55,    57,    58,    59,    60,    66,    70,    75,    80,    85,
      87,    88,    89,    42,    42,    42,    29,    78,    44,    52,
      44,    44,    52,    29,    42,    58,    60,    58,    29,    52,
      46,    52,    64,    67,    69,    52,    75,    71,     0,    50,
      11,    13,    18,    19,    22,    23,    31,    32,    33,    34,
      35,    36,    37,    44,    53,    20,    21,    25,    39,    40,
      42,    56,    61,    62,    63,    39,    40,    42,    52,    52,
      64,    76,    42,    44,    75,    52,    45,    65,    41,    41,
      45,    68,    43,    43,    50,    52,    29,    29,    52,    64,
      30,    29,    52,    64,    43,    43,    44,    42,    79,    43,
      47,    52,    69,    42,    72,    42,    41,    43,    52,    41,
      43,    51,    51,    52,    77,    29,    81,    52,    65,    68,
      64,    48,    64,     4,    86,    44,    81,    82,    43,    48,
      43,    43,    51,    64,    43,    45,    83,    46,    73,    43,
      73,    29,    50,    51,    84,    74,    83,    48
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
        case 4:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    { 
        fprintf(stderr, "\nThe program is wrong! See Line: %d\n", yylineno);
        exit(1);
    }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    { checkOnlyReadValue((yyvsp[(2) - (2)].exprNode)); }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    { checkOnlyReadValue((yyvsp[(1) - (2)].exprNode)); }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 132 "parser.y"
    { checkOnlyReadValue((yyvsp[(2) - (2)].exprNode)); }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 133 "parser.y"
    { checkOnlyReadValue((yyvsp[(1) - (2)].exprNode)); }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 138 "parser.y"
    {
        checkOnlyReadValue((yyvsp[(1) - (1)].exprNode));
    }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    {
        int currScope = scope;
        Id_t* foundId = NULL;

        while(currScope >= 0) {

            if((foundId = lookup_sym((yyvsp[(1) - (1)].string), currScope))){
                
                switch(foundId->type) {
                    case enumFUNC_ARG:
                        if(foundId->scopeFuncBlock != scopeFuncBlock) {
                            fprintf(stderr, "ERROR! Try to access argument of other function in line %d.\n", yylineno);
                            exit(1);
                        }
                        break;
                    case enumLOCAL:
                        if(foundId->scopeFuncBlock != scopeFuncBlock) {
                            fprintf(stderr, "ERROR! Try to access local variable of other function in line %d.\n", yylineno);
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
        (yyval.exprNode) = foundId;
    }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 194 "parser.y"
    {
        Id_t* foundId = lookup_sym((yyvsp[(2) - (2)].string), scope);

        if(!foundId) {
            if(isLibFunction((yyvsp[(2) - (2)].string))) {
                fprintf(stderr, "ERROR! Try to shadow library function in line %d.\n", yylineno);
                exit(1);
            }
            insert_symbol_table((yyvsp[(2) - (2)].string), (scope != 0) ? enumLOCAL : enumGLOBAL, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
        (yyval.exprNode) = foundId;
    }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 206 "parser.y"
    {
        Id_t* foundId = lookup_sym((yyvsp[(2) - (2)].string), 0);

        // NEVER insert here!
        if(!foundId) {
            fprintf(stderr, "ERROR! Try to access a not existed global variable or function in line %d.\n", yylineno);
            exit(1);
        }
        (yyval.exprNode) = foundId;
    }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 272 "parser.y"
    { ++scope; ++scopeStmtBlock; }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 273 "parser.y"
    { hideVariables_sym(scope); --scope; --scopeStmtBlock; }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 277 "parser.y"
    { hideVariables_sym(scope); --scope; --scopeFuncBlock; }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 282 "parser.y"
    {
        Id_t* foundId = lookup_sym((yyvsp[(2) - (2)].string), scope);

        if(isLibFunction((yyvsp[(2) - (2)].string))) {
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
            else {
                assert(foundId->type != enumFUNC_ARG);
            }
            exit(1);
        }
        else {
            insert_symbol_table((yyvsp[(2) - (2)].string), enumFUNC_USER, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
    }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 310 "parser.y"
    { ++scope; ++scopeFuncBlock;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 313 "parser.y"
    { insert_symbol_table(hiddenVarF(), enumFUNC_USER, yylineno, scope, scopeFuncBlock, scopeStmtBlock); }
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 314 "parser.y"
    { ++scope; ++scopeFuncBlock;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 324 "parser.y"
    {
        Id_t* foundId = lookup_sym((yyvsp[(1) - (1)].string), scope);

        if(isLibFunction((yyvsp[(1) - (1)].string))) {
            fprintf(stderr, "ERROR in line %d! There is already this library function in symbol table.\n", yylineno);
            exit(1);
        }
        if(foundId){
            assert(foundId->type != enumFUNC_ARG);
            assert(foundId->type != enumGLOBAL);
            assert(foundId->type != enumLOCAL);
        }
        
        if(isUserFunction((yyvsp[(1) - (1)].string), scope)) {
            fprintf(stderr, "ERROR in line %d! This argument already exists as user function in symbol table.\n", yylineno);
            exit(1);
        }
        insert_symbol_table((yyvsp[(1) - (1)].string), enumFUNC_ARG, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
    }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 346 "parser.y"
    {
        Id_t* foundId = lookup_sym((yyvsp[(2) - (2)].string), scope);

        if(isLibFunction((yyvsp[(2) - (2)].string))) {
            fprintf(stderr, "ERROR in line %d! There is already this library function in symbol table.\n", yylineno);
            exit(1);
        }

        if(foundId) {
            if(foundId->type == enumFUNC_ARG) {
                fprintf(stderr, "ERROR in line %d! Redeclaration.\n", yylineno);
            }
            assert(foundId->type != enumFUNC_USER);
            assert(foundId->type != enumGLOBAL);
            assert(foundId->type != enumLOCAL);
            exit(1);
        }
        else {
            if(isUserFunction((yyvsp[(2) - (2)].string), scope)) {
                fprintf(stderr, "ERROR in line %d! This argument already exists as user function in symbol table.\n", yylineno);
                exit(1);
            }
            insert_symbol_table((yyvsp[(2) - (2)].string), enumFUNC_ARG, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
    }
    break;



/* Line 1455 of yacc.c  */
#line 1965 "y.tab.c"
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
#line 395 "parser.y"



void yyerror(char* s)
{
    fprintf(stderr, "Error: %s", s);
}

int main(int argc, char** argv)
{
    FILE* fOutput;
    int i;
    Id_t* trace;

    char cEndProgram = 'a';

    if(argc > 1) {
        if(!(yyin = fopen(argv[1], "r"))) {
            fprintf(stderr, "Error opening input file %s!\n", argv[1]);
            return 1;
        }
        if(argc == 3) {
            /* STDOUT -> FILE* */
            if(! (fOutput = fopen(argv[2], "w")) ) {
                fprintf(stderr, "Error opening output file %s!\n", argv[2]);
                return 1;
            }
        } else if (argc > 3) {
            fprintf(stderr, "Too arguments.\n");
            return 1;
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

    printf("\n\nType 'q' to end programm.\n");
    cEndProgram = getchar();

    
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
    Id_t* trace = NULL;


    if (symbol_table[index] == NULL) {
        
        symbol_table[index] = (Id_t*) malloc(sizeof(Id_t));

        symbol_table[index]->name = name;
        symbol_table[index]->type = type;
        symbol_table[index]->declare1stLine = line;
        symbol_table[index]->scope = argScope;
        symbol_table[index]->scopeFuncBlock = argScopeFuncBlock;
        symbol_table[index]->scopeStmtBlock = argScopeStmtBlock;
        symbol_table[index]->active = true;
        symbol_table[index]->next = NULL;
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
        trace->next = (Id_t*) malloc(sizeof(Id_t));

        trace->next->name = name;
        trace->next->type = type;
        trace->next->declare1stLine = line;
        trace->next->scope = argScope;
        trace->next->scopeFuncBlock = argScopeFuncBlock;
        trace->next->scopeStmtBlock = argScopeStmtBlock;
        trace->next->active = true;
        trace->next->next = NULL;
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

Id_t* lookup_sym(char* name, int argScope)
{
    int index = hash_function(name);

    Id_t* trace = symbol_table[index];

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

    Id_t* trace = symbol_table[index];

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
            return "gloabl var";
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
    Id_t* trace = NULL;
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

void checkOnlyReadValue(const Id_t* id)
{
    if(id == NULL) return;

    if(isUserFunction(id->name, scope)) {
        fprintf(stderr, "ERROR! Try to change const value of user Function in line %d.\n", yylineno);
        exit(1);
    }
    else if(isLibFunction(id->name)) {
        fprintf(stderr, "ERROR! Try to change const value of library Function in line %d.\n", yylineno);
        exit(1);
    }
    else {
        assert(id->type == enumFUNC_ARG || id->type == enumGLOBAL || id->type == enumLOCAL);
    }
}
