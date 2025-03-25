/**
hy340 Phase 4
Kostas Goumas | 2746 | goumas@csd.uoc.gr
**/

#include "phase4Target.h"
 
void make_operand(expr* e, vmarg* arg) {
	
	if(e == NULL) {

		arg->val = -1;
		arg->type = nil_a;
	}
	else {
		//printf("expr: %d\n", e->type);
		switch (e->type) {
			
			case var_e:
			case tableitem_e:
			case arithexpr_e:
			case boolexpr_e:
			case assignexpr_e:
			
			case newtable_e: {
				
				arg->val = e->sym->offset;
				
				switch (e->sym->space) {
					case programvar:	arg->type = global_a;	break;
					case functionlocal:	arg->type = local_a;	break;
					case formalarg:		arg->type = formal_a;	break;
					default:	assert(0);
				}
				break;
			}
			
			/* Constants */
			case constbool_e:	{
				arg->val = e->boolConst;
				arg->type = bool_a;		break;
			}
			
			case conststring_e: {
				printf("String!!\n");
				arg->val = consts_newstring(e->strConst);
				arg->type = string_a;	break;
			}
			
			case constnum_e:	{
				
				arg->val = consts_newnumber(e->numConst);
				//printf("*\n");
				arg->type = number_a;	break;
			}
			
			/*case constint_e:	{
				printf("*\n");
				arg->val = consts_newinteger(e->intConst);
				printf("*\n");
				arg->type = integer_a; printf("*\n");	break;
			}*/
			
			case nil_e:	arg->type = nil_a;	break;
			
			/* Functions */
			case programfunc_e: {
				
				arg->type = userfunc_a; 
				arg->val = e->sym->taddress;
				break;
			}
			
			case libraryfunc_e: {
				
				printf("lf\n");
				arg->type = libfunc_a;
				arg->val = libfuncs_newused(e->sym->name);
				break;
			}
			
			default: assert(0);
		}
	}
}

void make_retvaloperand(vmarg* arg) {

	arg->type = retval_a;
}

void reset_operand (vmarg* arg) {
	
	memset(arg, 0, sizeof(vmarg));
}

unsigned consts_newstring(char* newstring) {
	
	int i;
	for (i = 0; i < total_strings; i++)	{
		
		if (strcmp(consts_strings[i], newstring) == 0) {
			return i;
		}
	}

	if (total_strings <= current_strings) expand_strings();
	consts_strings[current_strings++] = (char *)strdup(newstring);
	return current_strings - 1;
}

unsigned consts_newnumber(double* newnumber) {
	
	int i;

	for(i = 0; i < total_numbers; i++) {

		if (consts_numbers[i] == *newnumber){
			 return i;
		}
	}
	
	if (total_numbers <= current_numbers) expand_numbers();
	
	consts_numbers[current_numbers++] = *newnumber;
	return current_numbers - 1;
}

unsigned consts_newinteger(int* newinteger) {
	
	int i;

	for(i = 0; i < total_integers; i++) {

		if (consts_integers[i] == *newinteger){
			 return i;
		}
	}
	
	if (total_integers <= current_integers) expand_integers();
	
	consts_integers[current_integers++] = *newinteger;
	return current_integers - 1;
}

unsigned libfuncs_newused(char* newfunction) {
	
	int i;
	for (i = 0; i < total_libfuncs; i++)	{
		
		if (strcmp(libfuncs[i], newfunction) == 0)
		{
			return i;
		}
	}

	if (total_libfuncs <= current_libfuncs)	expand_libfuncs();
	libfuncs[current_libfuncs++] = (char *)strdup(newfunction);
	return current_libfuncs - 1;	
}

unsigned nextinstructionlabel() {
	
	return current_instructions;
}

void expand_strings() {
	
	char **expanded = (char **) malloc(NEW_SIZE_STRINGS);
	if (consts_strings != NULL)	{
		
		memcpy(expanded, consts_strings, CURR_SIZE_STRINGS);
		free(consts_strings);
	}
	consts_strings = expanded;
	total_strings += EXPAND_SIZE;
}

void expand_numbers() {
	
	double *expanded = (double *) malloc(NEW_SIZE_NUMBERS);
	if (consts_numbers != NULL)
	{
		memcpy(expanded, consts_numbers, CURR_SIZE_NUMBERS);
		free(consts_numbers);
	}
	consts_numbers = expanded;
	total_numbers += EXPAND_SIZE;
}

void expand_integers() {
	
	int *expanded = (int *) malloc(NEW_SIZE_INTEGERS);
	if (consts_integers != NULL)
	{
		memcpy(expanded, consts_integers, CURR_SIZE_INTEGERS);
		free(consts_integers);
	}
	consts_integers = expanded;
	total_integers += EXPAND_SIZE;
}

void expand_libfuncs() {
	
	char **expanded = (char **) malloc(NEW_SIZE_LIBFUNCS);
	if (libfuncs != NULL)
	{
		memcpy(expanded, libfuncs, CURR_SIZE_LIBFUNCS);
		free(libfuncs);
	}
	libfuncs = expanded;
	total_libfuncs += EXPAND_SIZE;	
}

void expand_instructions() {
	
	instruction *expanded = (instruction *) malloc(NEW_SIZE_INSTRUCTIONS);
	if (instructions != NULL)
	{
		memcpy(expanded, instructions, CURR_SIZE_INSTRUCTIONS);
		free(instructions);
	}
	instructions = expanded;
	total_instructions += EXPAND_SIZE;	
}


void emit_target (instruction t){
	
	if (current_instructions == total_instructions) expand_instructions();

	instruction* i = instructions + current_instructions++;
	i->opcode 	= t.opcode;
	i->arg1 	= t.arg1;
	i->arg2 	= t.arg2;
	i->result 	= t.result;
	i->srcLine	= t.srcLine;
}

void generate(vmopcode op, quad *quad) {

	instruction t;
	t.opcode = op;
	t.srcLine = nextinstructionlabel();
	make_operand(quad->arg1, &t.arg1);
	make_operand(quad->arg2, &t.arg2);
	make_operand(quad->result, &t.result);
	quad->taddress = nextinstructionlabel();
	emit_target(t);
}
void generate_ASSIGN(quad *quad) {generate(assign, quad);}
void generate_ADD(quad *quad) {generate(add, quad);}
void generate_SUB(quad *quad) {generate(sub, quad);}
void generate_MUL(quad *quad) {generate(mul, quad);}
void generate_DIV(quad *quad) {generate(DIV, quad);}
void generate_MOD(quad *quad) {generate(MOD, quad);}

void generate_NEWTABLE(quad* quad)		{generate(newtable, quad);}
void generate_TABLEGETELEM(quad* quad) 	{generate(tablegetelem, quad);}
void generate_TABLESETELEM(quad* quad) 	{generate(tablesetelem, quad);}
void generate_NOP()						{instruction t; t.opcode = nop; emit_target(t);}

void generate_relational(vmopcode op, quad* quad) {
	
	instruction t;
	t.opcode = op;
	t.srcLine = nextinstructionlabel();
	make_operand(quad->arg1, &t.arg1);
	make_operand(quad->arg2, &t.arg2);
	t.result.type = label_a;
	if (quad->label < currprocessedquad) 
		t.result.val = quads[quad->label].taddress;
	else
		add_incomplete_jump(nextinstructionlabel(), quad->label);
	
	quad->taddress = nextinstructionlabel();
	emit_target(t);
	
}

void generate_JUMP(quad* quad) 		{generate_relational(jump, quad);}
void generate_IF_EQ(quad* quad)		{generate_relational(jeq, quad);}
void generate_IF_NOTEQ(quad* quad)		{generate_relational(jne, quad);}
void generate_IF_GREATER(quad* quad)	{generate_relational(jgt, quad);}
void generate_IF_GREATEREQ(quad* quad)	{generate_relational(jge, quad);}
void generate_IF_LESS(quad* quad)		{generate_relational(jlt, quad);}
void generate_IF_LESSEQ(quad* quad)	{generate_relational(jle, quad);}

void generate_PARAM(quad* quad) {
	
	quad->taddress = nextinstructionlabel();
	instruction t;
	t.opcode = pusharg;
	t.srcLine = nextinstructionlabel();
	make_operand(quad->arg1, &t.arg1); //****
	emit_target(t);
}

void generate_CALL(quad* quad) {
	
	quad->taddress = nextinstructionlabel();
	instruction t;
	t.opcode = callfunc;
	t.srcLine = nextinstructionlabel();
	make_operand(quad->arg1, &t.arg1); //***
	emit_target(t);
}

void generate_GETRETVAL(quad* quad) {
	
	quad->taddress = nextinstructionlabel();
	instruction t;
	t.opcode = assign;
	t.srcLine = nextinstructionlabel();
	make_operand(quad->result, &t.result);
	make_retvaloperand(&t.arg1);
	emit_target(t);
}
void generate_FUNCSTART(quad* quad) {
	
	symbol* f;
	if (quad->result == NULL)
		f = (symbol*) malloc(sizeof(symbol));
	else
		f = quad->result->sym;
	
	f->taddress = nextinstructionlabel();
	f->returnList = NULL;
	quad->taddress = nextinstructionlabel();

	// userfunctions populated at make_operand
	push_funcstack(*f);
	
	instruction t;
	t.opcode = enterfunc;
	t.srcLine = nextinstructionlabel();
	make_operand(quad->result, &t.result);
	emit_target(t);
}

void generate_RETURN(quad* quad) {
	
	if (userfunctionsstack == NULL) {printf("genreNULL\n");}
	quad->taddress = nextinstructionlabel();
	instruction t;
	t.opcode = assign;
	t.srcLine = nextinstructionlabel();
	
	make_retvaloperand(&t.result);
	
	make_operand(quad->arg1, &t.arg1); //***
	
	emit_target(t);
	symbol f = top_funcstack();
	append_funcstack(f.returnList, nextinstructionlabel());
	
	t.srcLine = nextinstructionlabel();
	t.opcode = jump;
	reset_operand(&t.arg1);
	reset_operand(&t.arg2);
	t.result.type = label_a;
	emit_target(t);
}

void generate_FUNCEND(quad* quad) {
	
	symbol f = pop_funcstack();
	printf("fe\n");
	/* Backpatch */
	instructionNode* rl = f.returnList;
	printf("fe*\n");
	while (rl != NULL)
	{
		instructions[rl->instructionlabel].result.val = nextinstructionlabel();
		rl = rl->next;
	}

	quad->taddress = nextinstructionlabel();
	instruction t;
	t.opcode = exitfunc;
	t.srcLine = nextinstructionlabel();
	make_operand(quad->result, &t.result);
	emit_target(t);
}

void push_funcstack(symbol symbol) {
	
	funcstack* node;
	if (userfunctionsstack == NULL) {
		
		node = (funcstack*) malloc(sizeof(funcstack));
		node->symbol = symbol;
		node->next = NULL;
		userfunctionsstack = node;
	}
	else {

		node = (funcstack*) malloc(sizeof(funcstack));
		node->symbol = symbol;
		node->next = userfunctionsstack;
		userfunctionsstack = node;
	}
}

symbol pop_funcstack() {
	
	funcstack* head = userfunctionsstack;
	symbol s = head->symbol;
	userfunctionsstack = userfunctionsstack->next;
	head->next = NULL;
	free(head);
	return s;
}

symbol top_funcstack() {
	
	
	funcstack* head = userfunctionsstack;
	symbol s = head->symbol;
	return s;
}

void append_funcstack(instructionNode* returnList, unsigned instructionlabel) {
	
	instructionNode* node = (instructionNode*) malloc(sizeof(instructionNode));
	node->instructionlabel = instructionlabel;
	node->next = NULL;
	if (returnList == NULL) {
		returnList = node;
	}
	else {
		
		instructionNode* iterator = returnList;
		while (iterator->next != NULL) {
	
			iterator = iterator->next;
		}
		iterator->next = node;
	}
	
}

void add_incomplete_jump(unsigned instrNo, unsigned iaddress) {
	
	incomplete_jump *new = (incomplete_jump *) malloc(sizeof(incomplete_jump));
	
	new->instrNo = instrNo;
	new->iaddress = iaddress;
	
	if( ij_head == NULL )
        new->next = NULL;
    else
        new->next = ij_head;
    ij_head = new;
	ij_total++;
}

void patch_incomplete_jumps() {
	
	incomplete_jump *iterator;
    iterator = ij_head;

    while(iterator != NULL) {
		
        if (iterator->iaddress == total) {
			
            instructions[iterator->instrNo].result.val = nextinstructionlabel();
        }
        else {
            instructions[iterator->instrNo].result.val = quads[iterator->iaddress].taddress;
        }
        iterator = iterator->next;
    }
	
}

generator_func_t generators[] = {
	generate_ASSIGN,
	generate_ADD,
	generate_SUB,
	generate_MUL,
	generate_DIV,
	generate_MOD,
	generate_JUMP,
	generate_IF_EQ,
	generate_IF_NOTEQ,
	generate_IF_LESSEQ,
	generate_IF_GREATEREQ,
	generate_IF_LESS,
	generate_IF_GREATER,
	generate_CALL,
	generate_PARAM,
	generate_FUNCSTART,
	generate_FUNCEND,
	generate_NEWTABLE,
	generate_TABLEGETELEM,
	generate_TABLESETELEM,
	generate_GETRETVAL,
	generate_NOP,
	generate_RETURN
};

void generateTCode(void) {

	for (unsigned i = 0; i < currQuad; ++i){
		//printf("* %d\n", quads[i].op);
		currprocessedquad = i;
		(*generators[quads[i].op])(quads+i);
	}
	patch_incomplete_jumps();
	
	print_instruction_codes();
	print_number_consts(); printf("\n");
	print_string_consts(); printf("\n");
	print_libfuncs(); printf("\n");
}

void generateBinary(FILE* fBinary) {
	
	int i;
	unsigned magicNumber    = 12365487;
    fwrite(&magicNumber, sizeof(unsigned), 1, fBinary);
	
	fwrite(&current_numbers, sizeof(unsigned), 1, fBinary);
	for (i = 0; i < current_numbers; ++i) {
	
		fwrite(&consts_numbers[i], sizeof(double), 1, fBinary);
	}
	
	unsigned stringSize;
	fwrite(&current_strings, sizeof(unsigned), 1, fBinary);
	for(i = 0; i < current_strings; ++i){
	
		stringSize = strlen(consts_strings[i]);
		fwrite(&stringSize, sizeof(unsigned), 1, fBinary);
		fwrite(&consts_strings[i], sizeof(char), stringSize, fBinary);
	}
	
	fwrite(&current_libfuncs, sizeof(unsigned), 1, fBinary);
	for(i = 0; i < current_libfuncs; ++i){

		stringSize = strlen(libfuncs[i]);
		fwrite(&stringSize, sizeof(unsigned), 1, fBinary);
		fwrite(libfuncs[i], sizeof(char), stringSize, fBinary);
	}
	
	fwrite(&current_instructions, sizeof(unsigned), 1, fBinary);
	for (i = 0; i < current_instructions; ++i) {
	
		fwrite(&instructions[i], sizeof(instruction), 1, fBinary);
	}
}

void print_instruction_codes(void) {

	printf("Instruction Vmopcodes\n");
	for (unsigned i = 0; i < current_instructions; i++) {
		
		printf("Instruction vmopcode: %d, srcLine: %d\n", instructions[i].opcode, instructions[i].srcLine);
	}
	printf("\n");
}

void print_number_consts(void) {

	printf("Number consts table\n");
	for (unsigned i = 0; i < current_numbers; i++) {
		
		printf("%d	%lf\n", i, consts_numbers[i]);
	}
	printf("\n");
}

void print_string_consts(void) {

	printf("String consts table\n");
	for (unsigned i = 0; i < current_strings; i++) {
		
		printf("%d	%s\n", i, consts_strings[i]);
	}
	printf("\n");
}

void print_libfuncs(void) {

	printf("Libfuncs table\n");

	for (unsigned i = 0; i < current_libfuncs; i++) {
		
		printf("%d	%s\n", i, libfuncs[i]);
	}
	printf("\n");
}