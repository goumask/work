#include "structs.h"

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

tempcounter = 0;

int scopeoffsetStack[SIZE_STACK] = { 0 };
int topOffset = 0;

extern int loopCounterStack[SIZE_STACK] = { 0 };
int topLoop = 0;

int compileErrors = 0;
int loopcounter = 0;
int strErrors[1000] = { 0 };
int indexErrors = 0;

int StackBreak[SIZE_STACK] = { 0 };
int topBreak = 0;

int StackCont[SIZE_STACK] = { 0 };
int topCont = 0;

char **consts_strings;
unsigned total_strings = 0;
unsigned current_strings = 0;

double *consts_numbers;
unsigned total_numbers = 0;
unsigned current_numbers = 0;

int *consts_integers;
unsigned total_integers = 0;
unsigned current_integers = 0;

char **libfuncs;
unsigned total_libfuncs = 0;
unsigned current_libfuncs = 0;

userfunction *userfunctions;
unsigned total_userfunctions = 0;
unsigned curr_userfunctions = 0;
funcstack* userfunctionsstack = (funcstack*) 0;

instruction *instructions;
unsigned total_instructions = 0;
unsigned current_instructions = 0;

incomplete_jump* ij_head = (incomplete_jump*) 0;
unsigned ij_total = 0;

unsigned currprocessedquad = 0;
