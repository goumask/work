/**
hy340 Phase 5
Kostas Goumas | 2746 | goumas@csd.uoc.gr
**/

#include "vm.h"

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){

	//printf("arg->type %d\n", arg->type);
	if(arg->type == -1 || arg->type > 12)
		return reg;

	switch(arg->type){
		
		/* Variables */
		case global_a :	return &stack[AVM_STACKSIZE - 1 - arg->val];
		case local_a  :	return &stack[topsp - arg->val];
		case formal_a :	return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];

		case retval_a:	return &retval;

		case number_a:	{
							reg->type = number_m;
							reg->data.numVal = consts_getnumber(arg->val);
							return reg;
						}

		case string_a:	{
							reg->type = string_m;
							reg->data.strVal = strdup(consts_getstring(arg->val));
							return reg;
						}

		case bool_a:	{
							//printf("#\n");
							reg->type = bool_m;
							//printf("##\n");
							reg->data.boolVal = arg->val;
							//printf("##\n");
							return reg;
						}

		case nil_a:		reg->type = nil_m; return reg;

		case userfunc_a:	{

								reg->type = userfunc_m;
								// Stelnontai sto arg, oxi se pinaka
								reg->data.funcVal = arg->val;
								return reg;
							}

		case libfunc_a:		{
								reg->type = libfunc_m;
								reg->data.libfuncVal = libfuncs_getused(arg->val);
								return reg;
							}

		default:			assert(0);

	}
}

double consts_getnumber(unsigned index){

	//printf("Index: %d, current_numbers: %d\n", index, current_numbers);
	assert(index >= 0 && index < current_numbers);
	return (double) consts_numbers[index];

}

char* consts_getstring(unsigned index){

	assert(index >= 0 && index < current_strings);
	return consts_strings[index];
}

char* libfuncs_getused(unsigned index){

	assert(index >= 0 && index < current_libfuncs);
	return libfuncs[index];

}

void avm_error(char* msg) {
	
	printf("Error: %s\n", msg);
}

void avm_warning(char* msg) {
	
	printf("Warning: %s\n", msg);
}

void memclear_string(avm_memcell* m)
{

	assert(m->data.strVal);
	free(m->data.strVal);
}

void memclear_table(avm_memcell* m) {

	assert(m->data.tableVal);
	avm_tabledecrefcounter(m->data.tableVal);
}

void avm_memcellclear(avm_memcell* m) {

	if (m->type != undef_m)	{
		
		memclear_func_t f = memclearFuncs[m->type];
		if (f)
			(*f)(m);
		m->type = undef_m;
	}
}

void avm_tableincrefcounter(avm_table *t) {

	++t->ref_counter;
}

void avm_tabledecrefcounter(avm_table *t) {

	assert(t->ref_counter > 0);

	if (!--t->ref_counter)
		avm_tabledestroy(t);
}

void avm_tablebucketsdestroy(avm_table_bucket** p)
{

	for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p) {

		for (avm_table_bucket* b = *p; b;) {
			avm_table_bucket *del = b;
			b = b->next;
			avm_memcellclear(&del->key);
			avm_memcellclear(&del->value);
			free(del);
		}
		p[i] = (avm_table_bucket*) 0;
	}
}

void avm_tabledestroy(avm_table* t)
{

	avm_tablebucketsdestroy(t->str_indexed);
	avm_tablebucketsdestroy(t->num_indexed);
	free(t);
}

void avm_assign(avm_memcell *lv, avm_memcell *rv)
{

	if (lv == rv)
		return;

	if (lv->type == table_m &&
		rv->type == table_m &&
		lv->data.tableVal == rv->data.tableVal)
		return;

	if (rv->type == undef_m)
		avm_warning("assigning from 'undef' content !");

	avm_memcellclear(lv);
	memcpy(lv, rv, sizeof(avm_memcell));
	printf("Assign operation with result: %lf\n", lv->data.numVal);
	
	if (lv->type == string_m)
		lv->data.strVal = strdup(rv->data.strVal);
	else
		if (lv->type == table_m)
			avm_tableincrefcounter(lv->data.tableVal);
}

void avm_dec_top(void) {

	if (!top)
	{
		
		avm_error("stack overflow!\n");
		executionFinished = 1;
	}
	else
		--top;
}

void avm_push_envvalue(unsigned value) {

	stack[top].type = number_m;
	stack[top].data.numVal = value;
	avm_dec_top();
}

void avm_callsaveenvironment(void) {

	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc + 1);
	avm_push_envvalue(top + totalActuals + 2);
	avm_push_envvalue(topsp);
}

avm_memcell* avm_getactual(unsigned i) {

	assert(i < avm_totalactuals());
	return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

unsigned avm_totalactuals(void) {

	return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

unsigned avm_get_envvalue(unsigned i) {

	assert(stack[i].type == number_m);
	unsigned val = (unsigned) stack[i].data.numVal;
	assert(stack[i].data.numVal == (double)val);
	return val;
}

userfunc *avm_getfuncinfo(unsigned int address)
{

	assert(address >= 0 && address < curr_userfuncs);
	return &userfuncs[address];
}

char *number_tostring(avm_memcell *mc) {

	assert(mc->type == number_m);

	char *str = NULL;
	double dec, zero = 0;

	dec = modf(mc->data.numVal, &dec);

	if (zero == dec) {
		
		asprintf(&str, "%d", (int)mc->data.numVal);
	}
	else {
		
		asprintf(&str, "%lf", mc->data.numVal);
	}

	return str;
}

char *string_tostring(avm_memcell *mc) {

	assert(mc->type == string_m);
	return mc->data.strVal;
}

char *bool_tostring(avm_memcell *mc) 
{
	
	assert(mc->type == bool_m);
	if (mc->data.boolVal == '0')
		return "false";
	else
		return "true";
}

char *table_tostring(avm_memcell *mc){

	assert(mc->type == table_m);
	return "";
}

char *userfunc_tostring(avm_memcell *mc) {

	assert(mc->type == userfunc_m);
	char *str = "userfunc";
	return str;
}

char *libfunc_tostring(avm_memcell *mc) {

	char *str = "libfunc";
	return str;
}

char *nil_tostring(avm_memcell *mc) {

	char *str = "nil";
	return str;
}

char *undef_tostring(avm_memcell *mc) {

	char *str = "undef";
	return str;
}

char *avm_tostring(avm_memcell *mc) {

	assert(mc->type >= 0 && mc->type <= undef_m);
	return (*tostringFuncs[mc->type])(mc);
}

library_func_t avm_getlibraryfunc(char *id) {

	if (strcmp("print", id) == 0) {
		
		return libfunc_print;
	}
	else if (strcmp("totalarguments", id) == 0)	{
		
		return libfunc_totalarguments;
	}
	else if (strcmp("argument", id) == 0) {
		
		return libfunc_argument;
	}
	else if (strcmp("typeof", id) == 0)	{
		
		return libfunc_typeof;
	}
	else {
		return 0;
	}
}

void libfunc_print(void) {

	unsigned n = avm_totalactuals();
	for (unsigned i = 0; i < n; ++i) {

		char* s = avm_tostring(avm_getactual(i));
		puts(s);
		free(s);
	} 
}

void libfunc_typeof(void) {

	unsigned n = avm_totalactuals();

	if (n != 1)	{
		
		char* msg = (char*) malloc(100 * sizeof(char));
		msg = sprintf(msg, "one argument (not %d) expected in 'typeof'!", n);
		avm_error(msg);
		executionFinished = 1;
	}
	else {
		
		avm_memcellclear(&retval);
		retval.type = string_m;
		retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
	}
}

void libfunc_totalarguments(void) {

	unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);

	if (!p_topsp) {
		
		avm_error("'totalarguments' called outside a function!");
		retval.type = nil_m;
		executionFinished = 1;
	}
	else {
		
		retval.type = number_m;
		retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
	}
}

void libfunc_argument(void) {
	
	avm_memcellclear(&retval);
	memcpy(&retval, avm_getactual(0), sizeof(avm_memcell));
}

void avm_calllibfunc(char *id) {

	library_func_t f = avm_getlibraryfunc(id);
	if (!f)	{
		
		char* msg = (char*) malloc(100 * sizeof(char));
		msg = sprintf(msg, "unsupported libfunc '%s' called!", id);
		avm_error(msg);
		executionFinished = 1;
	}
	else {
		
		avm_callsaveenvironment();
		topsp = top;
		totalActuals = 0;
		(*f)();
		if (!executionFinished)
			execute_funcexit((instruction*) 0);
	}
}

double add_impl(double x, double y) { return x + y; }
double sub_impl(double x, double y) { return x - y; }
double mul_impl(double x, double y) { return x * y; }
double div_impl(double x, double y) {

	if (y != 0) {
		return x / y;
	}
	avm_error("Division by 0");
	executionFinished = 1;
	return -1;
}

double mod_impl(double x, double y) {

	if (y != 0) {
		return ((unsigned int) x) % ((unsigned int) y);
	}
	avm_error("Modulo by 0");
	executionFinished = 1;
	return -1;
}

// 			####	Start of Execute Functions	####

void execute_assign(instruction *instr)
{
	//avm_memcell* dummy = (avm_memcell*) malloc(sizeof(avm_memcell));
	//avm_memcell *lv = avm_translate_operand(&instr->result, dummy);
	avm_memcell* lv = avm_translate_operand(&instr->result, (instruction*) 0);
	avm_memcell* rv = avm_translate_operand(&instr->arg1, &ax);
	(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
	assert(rv);
	avm_assign(lv, rv);
}

void execute_arithmetic(instruction *instr)
{
	//avm_memcell* dummy = (avm_memcell*) malloc(sizeof(avm_memcell));
	//avm_memcell *lv = avm_translate_operand(&instr->result, dummy);
	avm_memcell* lv = avm_translate_operand(&instr->result, (instruction*) 0);
	avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

	//assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
	assert(rv1 && rv2);

	if (rv1->type != number_m || rv2->type != number_m)	{
		
		avm_error("not a number in arithmetic!");
		executionFinished = 1;
		exit(0);
	}
	else
	{

		arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
		avm_memcellclear(lv);
		lv->type = number_m;
		lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
		printf("Arithmetic operation with result: %lf\n", lv->data.numVal);
	}
}

void execute_jump(instruction* instr)
{

	if (!executionFinished)
		pc = instr -> result.val;
}

void execute_jeq(instruction *instr) {

	assert(instr->result.type == label_a);

	avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

	unsigned char result = 0;

	if (rv1->type == undef_m || rv2->type == undef_m) {
		
		avm_error("'undef' involved in equality");
		executionFinished = 1;
	}
	else if (rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else if (rv1->type != rv2->type) {
		
		char* msg = (char*) malloc(100 * sizeof(char));
		msg = sprintf(msg, "%s == %s is illegal", typeStrings[rv1->type], typeStrings[rv2->type]);
		avm_error(msg);
		executionFinished = 1;
	}
	else {
		
		if (rv1->type == number_m)
			result = rv1->data.numVal == rv2->data.numVal;
		else if (rv1->type == string_m)
			result = !strcmp(rv1->data.strVal, rv2->data.strVal);
		else
			result = (avm_tobool(rv1) == avm_tobool(rv2));
	}

	if (!executionFinished && result)
		pc = instr->result.val;
}

void execute_jne(instruction *instr){
	
	assert(instr->result.type == label_a);

	avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

	unsigned char result = 0;

	if (rv1->type == undef_m || rv2->type == undef_m)
	{
		avm_error("'undef' involved in equality");
		executionFinished = 1;
	}
	else if (rv1->type == nil_m || rv2->type == nil_m)
		result = (rv1->type == nil_m) && (rv2->type == nil_m);
	else if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else if (rv1->type != rv2->type) {
		
		char* msg = (char*) malloc(100 * sizeof(char));
		msg = sprintf(msg, "%s != %s is illegal", typeStrings[rv1->type], typeStrings[rv2->type]);
		avm_error(msg);
		executionFinished = 1;
	}
	else {
		
		if (rv1->type == number_m)			
			result = rv1->data.numVal == rv2->data.numVal;
		else if (rv1->type == string_m)
			result = !strcmp(rv1->data.strVal, rv2->data.strVal);
		else
			result = (avm_tobool(rv1) == avm_tobool(rv2));
	}

	if (!executionFinished && !result)
		pc = instr->result.val;
}

void execute_jle(instruction* instr) {
	
	avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

	unsigned char result = 0;

	if (rv1->type != number_m || rv2->type != number_m)
	{
		avm_error("only numbers allowed in comparison");
		executionFinished = 1;
	}
	else {

		result = (rv1->data.numVal <= rv2->data.numVal);
		if (!executionFinished && result) {
			
			pc = instr->result.val;
		}
	}
}

void execute_jge(instruction* instr) {
	
	avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

	unsigned char result = 0;

	if (rv1->type != number_m || rv2->type != number_m)
	{
		avm_error("only numbers allowed in comparison");
		executionFinished = 1;
	}
	else {

		result = (rv1->data.numVal >= rv2->data.numVal);
		if (!executionFinished && result) {
			
			pc = instr->result.val;
		}
	}
}

void execute_jlt(instruction* instr) {
	
	avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

	unsigned char result = 0;

	if (rv1->type != number_m || rv2->type != number_m)
	{
		avm_error("only numbers allowed in comparison");
		executionFinished = 1;
	}
	else {

		result = (rv1->data.numVal < rv2->data.numVal);
		if (!executionFinished && result) {
			
			pc = instr->result.val;
		}
	}
}

void execute_jgt(instruction* instr) {
	
	avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

	unsigned char result = 0;

	if (rv1->type != number_m || rv2->type != number_m)
	{
		avm_error("only numbers allowed in comparison");
		executionFinished = 1;
	}
	else {

		result = (rv1->data.numVal > rv2->data.numVal);
		if (!executionFinished && result) {
			
			pc = instr->result.val;
		}
	}
}

void execute_call(instruction *instr) {

	avm_memcell* func = avm_translate_operand(&instr->result, &ax);
	assert(func);
	switch (func->type)	{
		case userfunc_m: {
			avm_callsaveenvironment();
			pc = func->data.funcVal;
			assert(pc < AVM_ENDING_PC);
			assert(code[pc].opcode == funcenter_v);
			break;
		}

		case string_m: 	avm_calllibfunc(func->data.strVal);			break;
		case libfunc_m:	avm_calllibfunc(func->data.libfuncVal);		break;
		
		default: {
			char *s = avm_tostring(func);
			char* msg = (char*) malloc(100 * sizeof(char));
			msg = sprintf(msg, "call: cannot bind %s to function!", s);
			avm_error(msg);
			free(s);
			executionFinished = 1;
		}
	}
}

void execute_pusharg(instruction* instr) {

	avm_memcell *arg = avm_translate_operand(&instr->arg1, &ax);
	assert(arg);

	avm_assign(&stack[top], arg);
	++totalActuals;
	avm_dec_top();
}

void execute_funcenter(instruction *instr) {

	avm_memcell* func = avm_translate_operand(&instr->result, &ax);
	assert(func);
	assert(pc == func->data.funcVal);

	totalActuals = 0;
	userfunc* funcInfo = avm_getfuncinfo(pc);
	topsp = top;
	top = top - funcInfo->localSize;
}

void execute_funcexit(instruction *instr) {

	unsigned oldTop = top;
	top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
	pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
	topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

	while (++oldTop <= top)
		avm_memcellclear(&stack[oldTop]);
}

void execute_newtable(instruction* instr) {

	avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
	assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv == &retval));
	avm_memcellclear(lv);
	lv->type = table_m;
	lv->data.tableVal = avm_tablenew();
	avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(instruction* instr) {

	avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
	avm_memcell *t = avm_translate_operand(&instr->arg1, (avm_memcell*) 0);
	avm_memcell *i = avm_translate_operand(&instr->arg2, &ax);

	assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv == &retval));
	assert(t && &stack[0] <= t && &stack[top] > t);
	assert(i);

	avm_memcellclear(lv);
	lv->type = nil_m;
	
	if (t->type != table_m)	{

		char* msg = (char*) malloc(100 * sizeof(char));
		msg = sprintf(msg, "illegal use of type %s as table!", typeStrings[t->type]);
		avm_error(msg);
		executionFinished = 1;
	}
	else {

		char *ts = avm_tostring(t);
		char *is = avm_tostring(i);
		char* msg = (char*) malloc(100 * sizeof(char));
		msg = sprintf(msg, "%s[%s] not found!", ts, is);
		avm_warning(msg);
		free(ts);
		free(is);
	}
}

void execute_tablesetelem(instruction *instr) {

	avm_memcell* t = avm_translate_operand(&instr->result, (avm_memcell*) 0);
	avm_memcell *i = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell *c = avm_translate_operand(&instr->arg2, &bx);

	assert(t && (&stack[0] <= t && &stack[top] > t));
	assert(i && c);

	if (t->type != table_m) {
		
		char* msg = (char*) malloc(100 * sizeof(char));
		msg = sprintf(msg, "illegal use of type %s as table!", typeStrings[t->type]);
		avm_error(msg);
		executionFinished = 1;
	}
}

void execute_nop(instruction* instr) {

	executionFinished = 1;
}

// 			####	End of Execute Functions	####

avm_table *avm_tablenew(void) {

	avm_table *newt = (avm_table*) malloc(sizeof(avm_table));
	AVM_WIPEOUT(*newt);

	newt->ref_counter = 0;
	newt->total = 0;
	avm_tablebucketsinit(newt->num_indexed);
	avm_tablebucketsinit(newt->str_indexed);

	return newt;
}

void avm_tablebucketsinit(avm_table_bucket **tb) {

	unsigned i = 0;
	for (i = 0; i < AVM_TABLE_HASHSIZE; ++i)
	{
		tb[i] = (avm_table_bucket*) 0;
	}
}

unsigned char avm_tobool(avm_memcell *m) {

	assert(m->type >= 0 && m->type < undef_m);
	return (*toboolFuncs[m->type])(m);
}

void read_binary(FILE* fBinary) {
	
	unsigned i;
	unsigned magicNumber;
	fread(&magicNumber, sizeof(unsigned), 1, fBinary);
	assert(magicNumber == 12365487);
	
	/*fread(&current_integers, sizeof(unsigned), 1, fBinary);
	if(current_integers) {
		
		//int** consts_integer = (int*) malloc(current_integers * sizeof(int));
		consts_integers = (int*) malloc(current_integers * sizeof(int));
		for (i = 0; i < current_integers; ++i) {
	
			//fread(&consts_integers[i], sizeof(int), 1, fBinary);
			//printf("Reading\n");
			fread(&consts_integers[i], sizeof(int), 1, fBinary);
			//printf("Read\n");
			printf("%d\n", consts_integers[i]);
		}
	}*/
	
	fread(&current_numbers, sizeof(unsigned), 1, fBinary);
	if(current_numbers) {
		
		consts_numbers = (double*) malloc(current_numbers * sizeof(double));
		for (i = 0; i < current_numbers; ++i) {
	
			fread(&consts_numbers[i], sizeof(double), 1, fBinary);
			printf("%lf\n", consts_numbers[i]);
		}
	}
	unsigned stringSize;
	fread(&current_strings, sizeof(unsigned), 1, fBinary);
	for(i = 0; i < current_strings; ++i) {
	
		fread(&stringSize, sizeof(unsigned), 1, fBinary);
		//consts_strings[i] = (char*) malloc(stringSize * sizeof(char));
		fread(consts_strings[i], sizeof(char), stringSize, fBinary);
	}
	fread(&current_libfuncs, sizeof(unsigned), 1, fBinary);
	for(i = 0; i < current_libfuncs; ++i){

		fread(&stringSize, sizeof(unsigned), 1, fBinary);
		fread(libfuncs[i], sizeof(char), stringSize, fBinary);
	}
	fread(&current_instructions, sizeof(unsigned), 1, fBinary);
	codeSize = current_instructions;
	if(current_instructions) {
		
		instructions = (instruction*) malloc(current_instructions * sizeof(instruction));
		for (i = 0; i < current_instructions; ++i) {
	
			fread(&instructions[i], sizeof(instruction), 1, fBinary);
		}
	}
}

void avm_initialize(void) {
	
	avm_initstack();
	top = AVM_STACKSIZE - 1 - total_globals;
	topsp = top;	
}

static void avm_initstack(void) {
	
	for (unsigned i = 0; i < AVM_STACKSIZE; ++i ) {
		
		(AVM_WIPEOUT(stack[i])); stack[i].type = undef_m; }
}

void execute_cycle() {
	
	if (executionFinished)
		return;
	else
		if (pc == AVM_ENDING_PC) {
			
			executionFinished = 1;
			return;
		}
		else {
			
			assert(pc < AVM_ENDING_PC);
			instruction* instr = instructions + pc;
			assert (
				instr->opcode >= 0 &&
				instr->opcode <= AVM_MAX_INSTRUCTIONS
			);
			if(instr->srcLine)
				currLine = instr->srcLine;
			unsigned oldPC = pc;
			printf("Executing Instruction %d with vmopcode: %d\n", pc, instr->opcode);
			(*executeFuncs[instr->opcode])(instr);
			if(pc == oldPC)
				++pc;
		}
}

int main(int argc, char** argv) {
	
	FILE* fBinary;
	if(!(fBinary = fopen(argv[1], "rb"))) {
            fprintf(stderr, "Error opening input file %s!\n", argv[1]);
            return 1;
    }
	
	read_binary(fBinary);
	printf("read_binary finished...\n");
	print_number_consts();
	print_instruction_codes();
	avm_initialize();
	printf("avm_initialize finished...\n");
	while (pc < AVM_ENDING_PC)
		execute_cycle();
	printf("execute_cycles finished...\n");
	
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