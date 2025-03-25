/**
hy340 Phase 4
Kostas Goumas | 2746 | goumas@csd.uoc.gr
**/

#ifndef STRUCTS_H_
#define STRUCTS_H_

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
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)

#define CURR_SIZE_NUMBERS (total_numbers * sizeof(double))
#define NEW_SIZE_NUMBERS (EXPAND_SIZE * sizeof(double) + CURR_SIZE_NUMBERS)

#define CURR_SIZE_INTEGERS (total_integers * sizeof(int))
#define NEW_SIZE_INTEGERS (EXPAND_SIZE * sizeof(int) + CURR_SIZE_INTEGERS)

#define CURR_SIZE_STRINGS (total_strings * sizeof(char *))
#define NEW_SIZE_STRINGS (EXPAND_SIZE * sizeof(char *) + CURR_SIZE_STRINGS)

#define CURR_SIZE_LIBFUNCS (total_libfuncs * sizeof(char *))
#define NEW_SIZE_LIBFUNCS (EXPAND_SIZE * sizeof(char *) + CURR_SIZE_LIBFUNCS)

#define CURR_SIZE_INSTRUCTIONS (total_instructions * sizeof(instruction))
#define NEW_SIZE_INSTRUCTIONS (EXPAND_SIZE * sizeof(instruction) + CURR_SIZE_INSTRUCTIONS)

// -------------------------------- Enum -------------------------------------------

typedef enum {
    iASSIGN,                   	iADD,                   iSUB,
    iMUL,                      	iDIV,                   iMOD,
    iJUMP,						iIF_EQ,                 iIF_NOTEQ,                  
    iIF_LESSEQ,                	iIF_GREATEREQ,          iIF_LESS,
    iIF_GREATER,               	iCALL,                  iPARAM,
    iFUNCSTART,					iFUNCEND,				iTABLECREATE,                               	            
    iTABLEGETELEM,             	iTABLESETELEM, 			iGETRETVAL,
	iNOP,						iRET,					iUMINUS,
	iAND,                    	iOR, 					iNOT
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
	userfunc_e,
    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,
    constnum_e,
    //constint_e,
    constbool_e,
    conststring_e,
    nil_e
}expr_t;

typedef enum {
		assign,		add,			sub,  			mul,	DIV,	MOD,
		newtable,	tablegetelem,	tablesetelem,	nop,	jump,	jeq,
		jne,		jgt,			jge,			jlt,	jle,	pusharg,
		callfunc,	enterfunc,		exitfunc
}vmopcode;

typedef enum vmarg_t
{
	label_a = 0,
   	global_a = 1,
   	formal_a = 2,
   	local_a = 3,
   	integer_a = 4,
   	double_a = 5,
   	string_a = 6,
   	bool_a = 7,
   	nil_a = 8,
   	userfunc_a = 9,
   	libfunc_a = 10,
   	retval_a = 11,
	number_a = 12 
}vmarg_t;

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
	unsigned 			  taddress;
}quad;

typedef struct instructionNode {
	
	unsigned instructionlabel;
	struct instructionNode* next;
}instructionNode;

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
	unsigned 			  taddress;
    struct symbol*        next;
	instructionNode* 	  returnList;
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

typedef struct vmarg
{
	vmarg_t type;
	unsigned val;
}vmarg;

typedef struct instruction
{
	vmopcode opcode;
	vmarg result;
	vmarg arg1;
	vmarg arg2;
	unsigned srcLine;
}instruction;

typedef struct incomplete_jump {
	unsigned instrNo;
	unsigned iaddress;
	struct incomplete_jump* next;
}incomplete_jump;

typedef struct userfunction {
	unsigned	address;
	unsigned	localSize;
	char*		id;
}userfunction;

typedef struct functionstack funcstack;

typedef struct functionstack
{
	symbol symbol;
	struct functionstack *next;
};

// ------------------------------- Global Variables --------------------------------
extern FILE* yyin;
extern FILE* yyout;
extern int yylineno;

extern symbol* symbol_table[];

extern int hideNameFunction;

extern int scope;
extern int scopeStmtBlock;
extern int scopeFuncBlock;

extern quad* quads;
extern unsigned total;
extern unsigned int currQuad;

extern unsigned programVarOffset;
extern unsigned functionLocalOffset;
extern unsigned formalArgOffset;
extern unsigned scopeSpaceCounter;

extern int tempcounter;

extern int scopeoffsetStack[];
extern int topOffset;

extern int loopCounterStack[];
extern int topLoop;

extern int compileErrors;
extern int loopcounter;
extern int strErrors[];
extern int indexErrors;

extern int StackBreak[];
extern int topBreak;

extern int StackCont[];
extern int topCont;

extern char **consts_strings;
extern unsigned total_strings;
extern unsigned current_strings;

extern double *consts_numbers;
extern unsigned total_numbers;
extern unsigned current_numbers;

extern int *consts_integers;
extern unsigned total_integers;
extern unsigned current_integers;

extern char **libfuncs;
extern unsigned total_libfuncs;
extern unsigned current_libfuncs;

extern userfunction *userfunctions;
extern unsigned	total_userfunctions;
extern unsigned	curr_userfunctions;
extern funcstack* userfunctionsstack;

extern instruction *instructions;
extern unsigned total_instructions;
extern unsigned current_instructions;

extern incomplete_jump* ij_head;
extern unsigned ij_total;

extern unsigned currprocessedquad;

#endif