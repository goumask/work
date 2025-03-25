/**
hy340 Phase 4
Kostas Goumas | 2746 | goumas@csd.uoc.gr
**/

#ifndef PHASE4TARGET_H_
#define PHASE4TARGET_H_

#include "structs.h"

void make_operand(expr*, vmarg*);
void make_retvaloperand(vmarg*);

unsigned consts_newstring(char*);
unsigned consts_newnumber(double*);
unsigned consts_newinteger(int*);
unsigned libfuncs_newused(char*);

unsigned nextinstructionlabel();
void expand_strings();
void expand_numbers();
void expand_integers();
void expand_libfuncs();
void expand_instructions();

void generate(vmopcode, quad*);
void generate_ASSIGN(quad*);
void generate_ADD(quad*);
void generate_SUB(quad*);
void generate_MUL(quad*);
void generate_DIV(quad*);
void generate_MOD(quad*);

void generate_NEWTABLE(quad*);
void generate_TABLEGETELEM(quad*);
void generate_TABLESETELEM(quad*);
void generate_NOP();

void generate_relational(vmopcode, quad*);
void generate_JUMP(quad*);
void generate_IF_EQ(quad*);
void generate_IF_NOTEQ(quad*);
void generate_IF_GREATER(quad*);
void generate_IF_GREATEREQ(quad*);
void generate_IF_LESS(quad*);
void generate_IF_LESSEQ(quad*);

void generate_NOT(quad*);
void generate_OR(quad*);
void generate_PARAM(quad*);
void generate_CALL(quad*);
void generate_GETRETVAL(quad*);
void generate_FUNCSTART(quad*);
void generate_RETURN(quad*);
void generate_FUNCEND(quad*);

void reset_operand (vmarg*);
void push_funcstack(symbol);
symbol pop_funcstack();
symbol top_funcstack();
void append_funcstack(instructionNode*, unsigned);

void add_incomplete_jump(unsigned, unsigned);
void patch_incomplete_jumps();

void generateTCode(void);
void generateBinary(FILE*);

typedef void (*generator_func_t)(quad*);

#endif

