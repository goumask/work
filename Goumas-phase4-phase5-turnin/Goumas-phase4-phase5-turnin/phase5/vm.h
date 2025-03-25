/**
hy340 Phase 5
Kostas Goumas | 2746 | goumas@csd.uoc.gr
**/

#ifndef VM_H_
#define VM_H_

#include <stdio.h>
#include <assert.h>

#define AVM_TABLE_HASHSIZE 211
#define AVM_STACKENV_SIZE	4
#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))

#define AVM_ENDING_PC codeSize
#define AVM_MAX_INSTRUCTIONS 100

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1

// 					#### Enums ####

typedef enum {
    assign_v,	add_v,		sub_v,			mul_v,
	div_v,		mod_v,		jump_v,			jeq_v,
	jne_v,		jle_v,		jge_v,			jlt_v,
	jgt_v,		call_v,		pusharg_v,		funcenter_v,
	funcexit_v,	newtable_v,	tablegetelem_v,	tablesetelem_v,
	nop_v
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

typedef enum avm_memcell_t {
	number_m	= 0,
	string_m	= 1,
	bool_m		= 2,
	table_m 	= 3,
	userfunc_m	= 4,
	libfunc_m	= 5,
	nil_m		= 6,
	undef_m		= 7,
}avm_memcell_t;


// 					#### Structs ####

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

typedef struct avm_memcell {
	
	avm_memcell_t type;
	union{
		double					numVal;
		char*					strVal;
		unsigned char 			boolVal;
		struct avm_table* 		tableVal;
		unsigned				funcVal;
		char*					libfuncVal;
	}data;
}avm_memcell;

avm_memcell stack[AVM_STACKSIZE];
avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top, topsp;

typedef struct avm_table_bucket {
	avm_memcell key;
	avm_memcell value;
	struct avm_table_bucket* next;
}avm_table_bucket;

typedef struct avm_table {

	unsigned ref_counter;
	avm_table_bucket* str_indexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket* num_indexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket* lib_indexed[AVM_TABLE_HASHSIZE];
	unsigned id;
	unsigned total;
}avm_table;

typedef struct userfunc {
	unsigned	address;
	unsigned	localSize;
	char*		id;
}userfunc;


// 					#### Functions ####

typedef void (*library_func_t)(void);
library_func_t avm_getlibraryfunc(char *id);

void libfunc_print(void);
void libfunc_typeof(void);
void libfunc_totalarguments(void);
void libfunc_argument(void);

void execute_assign(instruction*);
void execute_add(instruction*);
void execute_arithmetic(instruction*);
void execute_jump(instruction*);
void execute_jeq(instruction*);
void execute_jne(instruction*);
void execute_jle(instruction*);
void execute_jge(instruction*);
void execute_jlt(instruction*);
void execute_jgt(instruction*);
void execute_call(instruction *instr);
void execute_funcexit(instruction*);
void execute_pusharg(instruction*);
void execute_funcenter(instruction*);
void execute_newtable(instruction*);
void execute_tablegetelem(instruction*);
void execute_tablesetelem(instruction*);
void execute_nop(instruction*);

avm_table *avm_tablenew(void);
void avm_tablebucketsinit(avm_table_bucket**);
avm_memcell *avm_tablegetelem(avm_table*, avm_memcell*);
void avm_tablesetelem(avm_table*, avm_memcell*, avm_memcell*);

typedef void (*execute_func_t)(instruction *);

userfunc* avm_getfuncinfo(unsigned);

typedef unsigned char (*tobool_func_t)(avm_memcell*);
unsigned char number_tobool(avm_memcell* m) {return m->data.numVal != 0;}
unsigned char string_tobool(avm_memcell* m) {return m->data.strVal[0] != 0;}
unsigned char bool_tobool(avm_memcell* m){return m->data.boolVal;}
unsigned char table_tobool(avm_memcell* m){return 1;}
unsigned char userfunc_tobool(avm_memcell* m){return 1;}
unsigned char libfunc_tobool(avm_memcell* m){return 1;}
unsigned char nil_tobool(avm_memcell* m){return 0;}
unsigned char undef_tobool(avm_memcell* m){assert(0); return 0;}

unsigned char avm_tobool(avm_memcell*);

typedef double (*arithmetic_func_t)(double x, double y);
double add_impl(double x, double y);
double sub_impl(double x, double y);
double mul_impl(double x, double y);
double div_impl(double x, double y);
double mod_impl(double x, double y);

typedef void (*memclear_func_t) (avm_memcell*);
void memclear_string(avm_memcell*);
void memclear_table(avm_memcell*);

void avm_assign(avm_memcell*, avm_memcell*);

void read_binary(FILE*);
void avm_initialize(void);
static void avm_initstack(void);
avm_memcell* avm_translate_operand(vmarg*, avm_memcell*);
void execute_cycle(void);

void avm_error(char*);
void avm_warning(char*);
void avm_memcellclear(avm_memcell*);
void avm_tableincrefcounter(avm_table*);
void avm_tabledecrefcounter(avm_table*);
void avm_tablebucketsdestroy(avm_table_bucket**);
void avm_tabledestroy(avm_table*);

void avm_dec_top(void);
void avm_push_envvalue(unsigned);
void avm_callsaveenvironment(void);
avm_memcell* avm_getactual(unsigned);
unsigned avm_totalactuals(void);
unsigned avm_get_envvalue(unsigned);

typedef char* (*tostring_func_t)(avm_memcell*);
extern char* number_tostring(avm_memcell*);
extern char* string_tostring(avm_memcell*);
extern char* bool_tostring(avm_memcell*);
extern char* table_tostring(avm_memcell*);
extern char* userfunc_tostring(avm_memcell*);
extern char* libfunc_tostring(avm_memcell*);
extern char* nil_tostring(avm_memcell*);
extern char* undef_tostring(avm_memcell*);

char *avm_tostring(avm_memcell*);
library_func_t avm_getlibraryfunc(char*);
void avm_calllibfunc(char*);

double consts_getnumber(unsigned);
char* consts_getstring(unsigned);
char* libfuncs_getused(unsigned);

// 					#### Variables ####

execute_func_t executeFuncs[] = {
 
	execute_assign,
	execute_add,
	execute_sub,
	execute_mul,
	execute_div,
	execute_mod,
	execute_jump,
	execute_jeq,
	execute_jne,
	execute_jle,
	execute_jge,
	execute_jlt,
	execute_jgt,
	execute_call,
	execute_pusharg,
	execute_funcenter,
	execute_funcexit,
	execute_newtable,
	execute_tablegetelem,
	execute_tablesetelem,
	execute_nop
};

char *typeStrings[] = {
	"number",
	"string",
	"bool",
	"table",
	"userfunc",
	"libfunc",
	"nil",
	"undef"
};

tobool_func_t toboolFuncs[] = {	
	number_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool
};

arithmetic_func_t arithmeticFuncs[] = {

	add_impl,
	sub_impl,
	mul_impl,
	div_impl,
	mod_impl
};

memclear_func_t memclearFuncs[] = {
	0, /* number */
	memclear_string,
	0, /* bool */
	memclear_table,
	0, /* userfunc */
	0, /* libfunc */
	0, /* nil */
	0  /* undef */
};

tostring_func_t tostringFuncs[] = {
	number_tostring,
	string_tostring,
	bool_tostring,
	table_tostring,
	userfunc_tostring,
	libfunc_tostring,
	nil_tostring,
	undef_tostring
};

unsigned total_globals = 0;

double *consts_numbers;
unsigned current_numbers;

int *consts_integers;
unsigned current_integers;

char **consts_strings;
unsigned current_strings;

char **libfuncs;
unsigned current_libfuncs;

userfunc* userfuncs;
unsigned curr_userfuncs;

instruction *instructions;
unsigned current_instructions;

unsigned executionFinished = 0;
unsigned pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;
instruction* code = (instruction*) 0;

unsigned totalActuals = 0;
#endif