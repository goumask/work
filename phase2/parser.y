%{
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

%}

%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE
%token AND NOT OR LOCAL TRUE FALSE NIL
%token EQUAL_EQUAL NOT_EQUAL PLUS_PLUS MINUS_MINUS
%token LESS_EQUAL GREATER_EQUAL COLON_COLON DOT_DOT

%token INT STR REAL ID

%type <numInt> INT
%type <string> STR ID
%type <numReal> REAL
%type <exprNode> lvalue


%union{
    int numInt;
    double numReal;
    char* string;
    struct id* exprNode; // Compiler says: unknown type name 'Id_t'
}



%right          '='
%left           OR
%left           AND
%nonassoc       EQUAL_EQUAL NOT_EQUAL
%nonassoc       '>' GREATER_EQUAL '<' LESS_EQUAL
%left           '+' '-'
%left           '*' '/' '%'
%right          NOT PLUS_PLUS MINUS_MINUS UMINUS
%left           '.' DOT_DOT
%left           '[' ']'
%left           '(' ')'



%%

program:
    | stmt program
    | error     { 
        fprintf(stderr, "\nThe program is wrong! See Line: %d\n", yylineno);
        exit(1);
    }
;

stmt:
    expr ';'
    | ifstmt
    | whilestmt
    | forstmt
    | returnstmt
    | BREAK ';'
    | CONTINUE ';'
    | blockStmt
    | funcdef
    | ';'
;

expr:
    assignexpr
    | expr op expr
    | term
;

op:
    '+' | '-' | '*' | '/'  | '%' | '>' | GREATER_EQUAL
    | '<' | LESS_EQUAL | EQUAL_EQUAL | NOT_EQUAL | AND | OR
;

term:
    '(' expr ')'
    | '-' expr %prec UMINUS
    | NOT expr
    | PLUS_PLUS lvalue { checkOnlyReadValue($2); }
    | lvalue PLUS_PLUS { checkOnlyReadValue($1); }
    | MINUS_MINUS lvalue { checkOnlyReadValue($2); }
    | lvalue MINUS_MINUS { checkOnlyReadValue($1); }
    | primary
;

assignexpr:
    lvalue {
        checkOnlyReadValue($1);
    }
    '=' expr
;

primary:
    call
    | lvalue
    | objectdef
    | '(' funcdef ')'
    | const
;

lvalue:
    ID                          {
        int currScope = scope;
        Id_t* foundId = NULL;

        while(currScope >= 0) {

            if((foundId = lookup_sym($1, currScope))){
                
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
            insert_symbol_table($1, (scope != 0) ? enumLOCAL : enumGLOBAL, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
        else {
            assert(!strcmp(foundId->name, $1));    
        }
        $$ = foundId;
    }
    | LOCAL ID                  {
        Id_t* foundId = lookup_sym($2, scope);

        if(!foundId) {
            if(isLibFunction($2)) {
                fprintf(stderr, "ERROR! Try to shadow library function in line %d.\n", yylineno);
                exit(1);
            }
            insert_symbol_table($2, (scope != 0) ? enumLOCAL : enumGLOBAL, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
        $$ = foundId;
    }
    | COLON_COLON ID            {
        Id_t* foundId = lookup_sym($2, 0);

        // NEVER insert here!
        if(!foundId) {
            fprintf(stderr, "ERROR! Try to access a not existed global variable or function in line %d.\n", yylineno);
            exit(1);
        }
        $$ = foundId;
    }
    | member
;

member:
    lvalue '.' ID
    | lvalue '[' expr ']'
    | call '[' expr ']'
    | call '.' ID
;

call:
    call '(' elist ')'
    | lvalue callsuffix
    | '(' funcdef ')' '(' elist ')'
;

callsuffix:
    normcall
    | methodcall
;

normcall:
    '(' elist ')'
;

methodcall:
    DOT_DOT ID '(' elist ')'
;


elist:
    | expr
    | expr elistExtend
;
elistExtend:
    | ',' expr elistExtend
;

objectdef:
    '[' elist ']'
    | '[' indexed ']'
;


indexed:
    | indexedelem indexedExtend
;
indexedExtend:
    | ',' indexedelem indexedExtend
;

indexedelem:
    '{' expr ':' expr '}'
;

blockStmt:
    '{'            { ++scope; ++scopeStmtBlock; }
        program   { hideVariables_sym(scope); --scope; --scopeStmtBlock; }
        '}'
;
blockFunc:
    '{' program  { hideVariables_sym(scope); --scope; --scopeFuncBlock; } 
        '}'
;

funcdef:
    FUNCTION ID {
        Id_t* foundId = lookup_sym($2, scope);

        if(isLibFunction($2)) {
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
            insert_symbol_table($2, enumFUNC_USER, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
    }
    '(' { ++scope; ++scopeFuncBlock;}
     idlist ')' blockFunc

    | FUNCTION  { insert_symbol_table(hiddenVarF(), enumFUNC_USER, yylineno, scope, scopeFuncBlock, scopeStmtBlock); }
    '(' { ++scope; ++scopeFuncBlock;}
     idlist ')' blockFunc
;

const:
    REAL | INT | STR | NIL | TRUE | FALSE
;


idlist:
    | ID {
        Id_t* foundId = lookup_sym($1, scope);

        if(isLibFunction($1)) {
            fprintf(stderr, "ERROR in line %d! There is already this library function in symbol table.\n", yylineno);
            exit(1);
        }
        if(foundId){
            assert(foundId->type != enumFUNC_ARG);
            assert(foundId->type != enumGLOBAL);
            assert(foundId->type != enumLOCAL);
        }
        
        if(isUserFunction($1, scope)) {
            fprintf(stderr, "ERROR in line %d! This argument already exists as user function in symbol table.\n", yylineno);
            exit(1);
        }
        insert_symbol_table($1, enumFUNC_ARG, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
    }
    idlistExtend
;
idlistExtend:
    | ',' ID {
        Id_t* foundId = lookup_sym($2, scope);

        if(isLibFunction($2)) {
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
            if(isUserFunction($2, scope)) {
                fprintf(stderr, "ERROR in line %d! This argument already exists as user function in symbol table.\n", yylineno);
                exit(1);
            }
            insert_symbol_table($2, enumFUNC_ARG, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
    }
    idlistExtend
;

ifstmt:
    IF '(' expr ')' stmt ifstmtExtend
;
ifstmtExtend:
    | ELSE stmt
;

whilestmt:
    WHILE '(' expr ')' stmt
;

forstmt:
    FOR '(' elist ';' expr ';' elist ')' stmt
;

returnstmt:
    RETURN expr ';'
    | RETURN ';'
;


%%


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