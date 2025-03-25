%{
/**
hy340 Phase 3
Kostas Goumas | 2746 | goumas@csd.uoc.gr
**/

// ------------------------------- Libraries --------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "structs.h"
//#include "variables.c"





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
expr* newexpr_constnum(double i);
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



%}

%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE
%token AND NOT OR LOCAL TRUE FALSE NIL
%token EQUAL_EQUAL NOT_EQUAL PLUS_PLUS MINUS_MINUS
%token LESS_EQUAL GREATER_EQUAL COLON_COLON DOT_DOT

%token INT STR REAL ID

%type <numInt> INT
%type <unsInt> funcbody ifprefix elseprefix
%type <unsInt> whilestart whilecond N
%type <string> STR ID funcname
%type <numReal> REAL
%type <symbT> funcprefix funcdef
%type <exprT> lvalue member primary assignexpr
%type <exprT> call term objectdef const
%type <exprT> tableitem expr elist elistExtend
%type <exprT> indexed indexedelem indexedExtend
%type <callS> callsuffix normcall methodcall
%type <forP> forprefix forprefixWithoutELIST
%type <forPP> forPREprefix forPREprefixWithoutELIST
%type <Stm> loopstmt stmts stmt break continue

%union {
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
    {
        printf("program -> empty\n");
    }
    | stmts
    {
        printf("program -> stmts\n");
    }
    | error
    {
        printf("\nprogram -> error\n");
        fprintf(stderr, "\nThe program is wrong! See Line: %d\n", yylineno);
        exit(1);
    }
;

stmts:
    stmt
    {
        printf("stmts -> stmt\n");

        //$$ = $1;

        //printf("stmt ------------------ line %d \n", yylineno);
    }
    | stmts stmt
    {
        printf("stmts -> stmts stmt\n");

       // printf("stmt ------------------ line %d \n", yylineno);

        //$$ = make_stmt();

        //$$->breakList = mergelist($1->breakList, $2->breakList);
        //$$->contList = mergelist($1->contList, $2->contList);

    }
;

stmt:
    expr ';'
    {
        printf("stmt -> expr ';'\n");

        //$$ = make_stmt();
        resettemp();
    }
    | ifstmt
    {
        printf("stmt -> ifstmt\n");

        //$$ = make_stmt();
        resettemp();
    }
    | whilestmt
    {
        printf("stmt -> whilestmt\n");

        //$$ = make_stmt();
        resettemp();
    }
    | forstmt
    {
        printf("stmt -> forstmt\n");

        //$$ = make_stmt();
        resettemp();
    }
    | returnstmt
    {
        printf("stmt -> returnstmt\n");

        //$$ = make_stmt();
        resettemp();
    }
    | break
    {
        printf("stmt -> break\n");

        //$$ = $1;
        resettemp();
    }
    | continue
    {
        printf("stmt -> continue\n");

        //$$ = $1;
        resettemp();
    }
    | blockStmt
    {
        printf("stmt -> blockStmt\n");

        //$$ = make_stmt();
        resettemp();
    }
    | funcdef
    {
        printf("stmt -> funcdef\n");

        //$$ = make_stmt();
        resettemp();
    }
    | ';'
    {
        printf("stmt -> ';'\n");

        //$$ = make_stmt();
        resettemp();
    }
;

break:
    BREAK ';'
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
;

continue:
    CONTINUE ';'
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
;

expr:
    assignexpr                  {printf("expr -> assignexpr\n");}
    | expr '+' expr
    {
        printf("expr -> expr '+' expr\n");
        
        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp();
        emit(iADD, $1, $3, $$, 0, yylineno);
    }
    | expr '-' expr
    {
        printf("expr -> expr '-' expr\n");

        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp();
        emit(iSUB, $1, $3, $$, 0, yylineno);    
    }
    | expr '*' expr
    {
        printf("expr -> expr '*' expr\n");

        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp();
        emit(iMUL, $1, $3, $$, 0, yylineno);    
    }
    | expr '/' expr
    {
        printf("expr -> expr '/' expr\n");
        
        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp();
        emit(iDIV, $1, $3, $$, 0, yylineno);
    }
    | expr '%' expr
    {
        printf("expr -> expr '%%' expr\n");
        
        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp();
        emit(iMOD, $1, $3, $$, 0, yylineno);
    }
    | expr '>' expr
    {
        printf("expr -> expr '>' expr\n");

        $$ = newexpr(boolexpr_e);
        $$->sym = newtemp();

        emit(iIF_GREATER, $1, $3, NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, $$, 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, $$, 0, yylineno);    
    }
    | expr '<' expr
    {
        printf("expr -> expr '<' expr\n");
    
        $$ = newexpr(boolexpr_e);
        $$->sym = newtemp();

        emit(iIF_LESS, $1, $3, NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, $$, 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, $$, 0, yylineno);
    }
    | expr GREATER_EQUAL expr
    {
        printf("expr -> expr GREATER_EQUAL expr\n");
        
        $$ = newexpr(boolexpr_e);
        $$->sym = newtemp();

        emit(iIF_GREATEREQ, $1, $3, NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, $$, 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, $$, 0, yylineno);
    }
    | expr LESS_EQUAL expr
    {
        printf("expr -> expr LESS_EQUAL expr\n");
        
        $$ = newexpr(boolexpr_e);
        $$->sym = newtemp();

        emit(iIF_LESSEQ, $1, $3, NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, $$, 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, $$, 0, yylineno);
    }
    | expr EQUAL_EQUAL expr
    {
        printf("expr -> expr EQUAL_EQUAL expr\n");
        
        $$ = newexpr(boolexpr_e);
        $$->sym = newtemp();

        emit(iIF_EQ, $1, $3, NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, $$, 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, $$, 0, yylineno);
    }
    | expr NOT_EQUAL expr
    {
        printf("expr -> expr NOT_EQUAL expr\n");
        
        $$ = newexpr(boolexpr_e);
        $$->sym = newtemp();

        emit(iIF_NOTEQ, $1, $3, NULL, nextquadlabel() + 3, yylineno);
        emit(iASSIGN, newexpr_constbool(0), NULL, $$, 0, yylineno);
        emit(iJUMP, NULL, NULL, NULL, nextquadlabel()+2, yylineno);
        emit(iASSIGN, newexpr_constbool(1), NULL, $$, 0, yylineno);
    }
    | expr AND expr
    {
        printf("expr -> expr AND expr\n");

        // total boolean evaluation
        $$ = newexpr(boolexpr_e);
        $$->sym = newtemp();
        emit(iAND, $1, $3, $$, 0, yylineno);
    }
    | expr OR expr
    {
        printf("expr -> expr OR expr\n");

        // total boolean evaluation
        $$ = newexpr(boolexpr_e);
        $$->sym = newtemp();
        emit(iOR, $1, $3, $$, 0, yylineno);    
    }
    | term
    {
        printf("expr -> term\n");
        
        $$ = $1;
    }
;



term:
    '(' expr ')'
    {
        printf("term -> '(' expr ')'\n");

        $$ = $2;    
    }
    | '-' expr %prec UMINUS
    {
        printf("term -> '-' expr %%prec UMINUS\n");
        
        check_arith($2);
        $$ = newexpr(arithexpr_e);
        $$->sym = istempexpr($2) ? $2->sym : newtemp();
        emit(iMUL, $2, newexpr_constnum(-1), $$, 0, yylineno);
    }
    | NOT expr
    {
        printf("term -> NOT expr\n");
        
        // total boolean evaluation
        $$ = newexpr(boolexpr_e);
        $$->sym = newtemp();
        emit(iNOT , $2, NULL, $$, 0, yylineno);
    }
    | PLUS_PLUS lvalue
    {
        printf("term -> PLUS_PLUS lvalue\n");

        checkOnlyReadValue($2->sym);

        check_arith($2);

        if ($2->type == tableitem_e) {
            
            $$ = emit_iftableitem($2);
            emit(iADD, $$, newexpr_constnum(1), $$, 0, yylineno);
            emit(iTABLESETELEM, $2, $2->index, $$, 0, yylineno);
        }
        else {
            emit(iADD, $2, newexpr_constnum(1), $2, 0, yylineno);
            $$ = newexpr(arithexpr_e);
            $$->sym = newtemp();
            emit(iASSIGN, $2, NULL, $$, 0, yylineno);
        }
    }
    | lvalue PLUS_PLUS
    {
        printf("term -> lvalue PLUS_PLUS\n");

        checkOnlyReadValue($1->sym);
        
        check_arith($1);
        $$ = newexpr(var_e);
        $$->sym = newtemp();

        if ($1->type == tableitem_e) {
            expr* val = emit_iftableitem($1);
            emit(iASSIGN, val, NULL, $$, 0, yylineno);
            emit(iADD, val, newexpr_constnum(1), val, 0, yylineno);
            emit(iTABLESETELEM, $1, $1->index, val, 0, yylineno);
        }
        else {
            emit(iASSIGN, $1, NULL, $$, 0, yylineno);
            emit(iADD, $1, newexpr_constnum(1), $1, 0, yylineno);
        }
    }
    | MINUS_MINUS lvalue
    {
        printf("term -> MINUS_MINUS lvalue\n");

        checkOnlyReadValue($2->sym);        

        check_arith($2);

        if ($2->type == tableitem_e) {
            
            $$ = emit_iftableitem($2);
            emit(iSUB, $$, newexpr_constnum(1), $$, 0, yylineno);
            emit(iTABLESETELEM, $2, $2->index, $$, 0, yylineno);
        }
        else {
            emit(iSUB, $2, newexpr_constnum(1), $2, 0, yylineno);
            $$ = newexpr(arithexpr_e);
            $$->sym = newtemp();
            emit(iASSIGN, $2, NULL, $$, 0, yylineno);
        }
    }
    | lvalue MINUS_MINUS
    {
        printf("term -> lvalue MINUS_MINUS\n");

        checkOnlyReadValue($1->sym);
        
        check_arith($1);
        $$ = newexpr(var_e);
        $$->sym = newtemp();

        if ($1->type == tableitem_e) {
            expr* val = emit_iftableitem($1);
            emit(iASSIGN, val, NULL, $$, 0, yylineno);
            emit(iSUB, val, newexpr_constnum(1), val, 0, yylineno);
            emit(iTABLESETELEM, $1, $1->index, val, 0, yylineno);
        }
        else {
            emit(iASSIGN, $1, NULL, $$, 0, yylineno);
            emit(iSUB, $1, newexpr_constnum(1), $1, 0, yylineno);
        }
    }
    | primary
    {
        printf("term -> primary\n");
        
        $$ = $1;
    }
;

assignexpr:
    lvalue {
        checkOnlyReadValue($1->sym);
    }
    '=' expr
    {
        printf("assignexpr -> lvalue '=' expr\n");
    
        if ($1->type == tableitem_e) {

            // lvalue[index] = expr;
            emit(iTABLESETELEM, $1, $1->index, $4, 0, yylineno);

            $$ = emit_iftableitem($1);
            $$->type = assignexpr_e;
        }
        else {

            // lvalue = expr;
            emit(iASSIGN, $4, NULL, $1, 0, yylineno);
            $$ = newexpr(assignexpr_e);
            $$->sym = newtemp();
            emit(iASSIGN, $1, NULL, $$, 0, yylineno);
        }
    }
;

primary:
    call
    {
        printf("primary -> call\n");
    
        $$ = $1;
    }
    | lvalue
    {
        printf("primary -> lvalue\n");
    
        $$ = emit_iftableitem($1);
    }
    | objectdef                        {printf("primary -> objectdef\n");}
    | '(' funcdef ')'
    {
        printf("primary -> '(' funcdef ')'\n");
        
        $$ = newexpr(programfunc_e);
        $$->sym = $2;    
    }
    | const
    {
        printf("primary -> const\n");
        
        $$ = $1;
    }

;

lvalue:
    ID
    {
        int currScope = scope;
        symbol* foundId = NULL;

        while(currScope >= 0) {

            if((foundId = lookup_sym($1, currScope))){
                
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
            insert_symbol_table($1, (scope != 0) ? enumLOCAL : enumGLOBAL, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
        else {
            assert(!strcmp(foundId->name, $1));    
        }
        $$ = lvalue_expr(newsymbol($1, var_s));
        printf("lvalue -> ID: %s\n", $1);
    }
    | LOCAL ID
    {
        symbol* foundId = lookup_sym($2, scope);

        if(!foundId) {
            if(isLibFunction($2)) {
                fprintf(stderr, "ERROR! Try to shadow library function in line %d.\n", yylineno);
                exit(1);
            }
            insert_symbol_table($2, (scope != 0) ? enumLOCAL : enumGLOBAL, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }

        $$ = lvalue_expr(newsymbol($2, var_s));
        printf("lvalue -> LOCAL ID: %s\n", $2);
    }
    | COLON_COLON ID 
    {
        symbol* foundId = lookup_sym($2, 0);

        // NEVER insert here!
        if(!foundId) {
            fprintf(stderr, "ERROR! Try to access a not existed global variable or function in line %d.\n", yylineno);
            exit(1);
        }
        
        $$ = lvalue_expr(newsymbol($2, var_s));
        
        printf("lvalue -> COLON_COLON ID: %s\n", $2);
    }
    | tableitem
    {
        printf("lvalue -> tableitem\n");
        $$ = $1;
    }    
    | member
    {
        symbol* mem = (symbol*) malloc(sizeof(symbol));

        if (mem == NULL) {
            printf("No memory for member\n");
            exit(1);
        }

        $$ = $1;
        printf("lvalue -> member\n");
    }
;

tableitem:
    lvalue '.' ID
    {
        printf("tableitem -> lvalue '.' ID\n");
    
        $$ = member_item($1, $3);
    }
    | lvalue '[' expr ']'
    {
        printf("tableitem -> lvalue '[' expr ']'\n");

        $1 = emit_iftableitem($1);
        $$ = newexpr(tableitem_e);
        $$->sym = $1->sym;
        $$->index = $3;
    }
    
;

member:
    call '[' expr ']'
    {
        printf("member -> call '[' expr ']'\n");
        
        $1 = emit_iftableitem($1);
        $$ = newexpr(tableitem_e);
        $$->sym = $1->sym;
        $$->index = $3;
    }
    | call '.' ID
    {
        printf("member -> call '.' ID\n");

        $$ = member_item($1, $3);    
    }
;

call:
    call '(' elist ')'
    {
        printf("call -> call '(' elist ')'\n");
        

        $$ = make_call($1, $3);
    }
    | call '(' ')'
    {
        printf("call -> call '(' ')'\n");
    
        $$ = make_call($1, NULL);
    }
    | lvalue callsuffix
    {
        printf("call -> lvalue callsuffix\n");
    
        $1 = emit_iftableitem($1);

        if ($2->method != NULL) {
            
            if (*($2->method) == true) {
                
                expr* t = $1;
                $1 = emit_iftableitem(member_item(t, $2->name));
                
                if ($2->elist != NULL) {
                    t->next = $2->elist->next;
                    free($2->elist);
                }
                $2->elist = t;
            }
        }
        $$ = make_call($1, $2->elist);
    }
    | '(' funcdef ')' '(' elist ')'
    {
        printf("call -> '(' funcdef ')' '(' elist ')'\n");

        expr* func = newexpr(programfunc_e);
        func->sym = $2;
        $$ = make_call(func, $5);
    }
    | '(' funcdef ')' '(' ')'
    {
        printf("call -> '(' funcdef ')' '(' ')'\n");
        
        expr* func = newexpr(programfunc_e);
        func->sym = $2;
        $$ = make_call(func, NULL);
    }
;

callsuffix:
    normcall
    {
        printf("callsuffix -> normcall\n");
    
        $$ = $1;
    }
    | methodcall
    {
        printf("callsuffix -> methodcall\n");
    
        $$ = $1;
    }
;

normcall:
    '(' elist ')'
    {
        printf("normcall -> '(' elist ')'\n");

        $$ = (call*) malloc(sizeof(call));

        if ($$ == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        $$->elist = $2;

        bool* ptr = (bool*) malloc(sizeof(bool));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        $$->method = ptr;
        *($$->method) = false;
        $$->name = NULL;
    }
    | '(' ')'
    {
        printf("normcall -> '(' ')'\n");
        
        $$ = (call*) malloc(sizeof(call));

        if ($$ == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        $$->elist = NULL;
        $$->method = NULL;
        $$->name = NULL;
    }
;

methodcall:
    DOT_DOT ID '(' elist ')'
    {
        printf("methodcall -> DOT_DOT ID '(' elist ')'\n");
    
        $$ = (call*) malloc(sizeof(call));

        if ($$ == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        $$->elist = $4;

        bool* ptr = (bool*) malloc(sizeof(bool));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        $$->method = ptr;
        *($$->method) = true;
        $$->name = $2;
    }
    | DOT_DOT ID '(' ')'
    {
        printf("methodcall -> DOT_DOT ID '(' ')'\n");
        
        $$ = (call*) malloc(sizeof(call));

        if ($$ == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        $$->elist = NULL;

        bool* ptr = (bool*) malloc(sizeof(bool));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        $$->method = ptr;
        *($$->method) = true;
        $$->name = $2;
    }
;


elist:
    expr elistExtend
    {
        printf("elist -> expr elistExtend\n");
        
        $$ = newexpr(nil_e);
        $$->sym = NULL;
        $$->next = $1;

        $1->next = $2->next;
    }
;
elistExtend:
    {
        printf("elistExtend -> emtpy\n");

        $$ = (expr*) malloc(sizeof(expr));

        if ($$ == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }
        $$->next = NULL;
    }
    | ',' expr elistExtend
    {
        printf("elistExtend -> ',' expr elistExtend\n");
        
        $$ = (expr*) malloc(sizeof(expr));

        if ($$ == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        $$->next = $2;
        $2->next = $3->next;    
    }
;

objectdef:
    '[' ']'
    {
        printf("objectdef -> '[' ']'\n");
        
        expr* t = newexpr(newtable_e);
        t->sym = newtemp();
        emit(iTABLECREATE, t, NULL, NULL, 0, yylineno);
        $$ = t;
    }
    | '[' elist ']'
    {
        printf("objectdef -> '[' elist ']'\n");
    
        expr* t = newexpr(newtable_e);
        t->sym = newtemp();
        emit(iTABLECREATE, t, NULL, NULL, 0, yylineno);

        if ($2 != NULL) $2 = $2->next;

        unsigned int i = 0;
        while ($2 != NULL) {
            emit(iTABLESETELEM, t, newexpr_constnum(i), $2, 0, yylineno);
            ++i;
            $2 = $2->next;
        }
        $$ = t;
    }
    | '[' indexed ']'
    {
        printf("objectdef -> '[' indexed ']'\n");
        
        expr* t = newexpr(newtable_e);
        t->sym = newtemp();
        emit(iTABLECREATE, t, NULL, NULL, 0, yylineno);

        expr* trace = $2;

        while (trace != NULL) {
            if (trace->PairIndex != NULL  && trace->PairValue != NULL) {
                emit(iTABLESETELEM, t, trace->PairIndex, trace->PairValue, 0, yylineno);
            }
            trace = trace->next;
        }
        $$ = t;
    }
;


indexed:
    indexedelem indexedExtend
    {
        printf("indexed -> indexedelem indexedExtend\n");
        
        $$ = newexpr(var_e);
        $$->next = $1;
        $1->next = $2->next;
    }
;
indexedExtend:
    {
        printf("indexedExtend -> empty\n");

        $$ = newexpr(var_e);

        $$->next = NULL;
    }
    | ',' indexedelem indexedExtend
    {
        printf("indexedExtend -> ',' indexedelem indexedExtend\n");
        
        $$ = newexpr(var_e);

        $$->next = $2;
        $2->next = $3->next;
    }
;

indexedelem:
    '{' expr ':' expr '}'
    {
        printf("indexedelem -> '{' expr ':' expr '}'\n");
        
        $$ = newexpr(var_e);

        $$->PairIndex = $2;
        $$->PairValue = $4;
    }
;

blockStmt:
    '{'            { ++scope; ++scopeStmtBlock; }
    program        { hideVariables_sym(scope); --scope; --scopeStmtBlock; }
    '}'            {printf("blockStmt -> '{' program '}'\n");}
;
blockFunc:
    '{'
    {
        push(loopCounterStack, loopcounter, &topLoop);
        loopcounter = 0;
    }
    program
    {
        hideVariables_sym(scope);
        --scope;
        --scopeFuncBlock;
    } 
    '}'
    {
        printf("blockFunc -> '{' program '}'\n");

        loopcounter = pop(loopCounterStack, &topLoop);        
    }
;

funcdef:
    funcprefix funcargs funcbody
    {
        printf("funcdef -> funcprefix funcargs funcbody\n");

        exitscopespace();
        $1->totalLocals= $3;

        int offset = pop(scopeoffsetStack, &topOffset);
        
        restorecurrscopeoffset(offset);
        $$ = $1;
        expr* e = newexpr(programfunc_e);
        e->sym = $1;
        emit(iFUNCEND, e, NULL, NULL, 0, yylineno);
    }
;

funcname:
    ID
    { 
        printf("funcname -> ID\n");

        $$ = $1;

        symbol* foundId = lookup_sym($1, scope);

        if(isLibFunction($1)) {
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
            insert_symbol_table($1, enumFUNC_USER, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
    }
    |
    {
        printf("funcname -> empty");

        $$ = hiddenVarF();
        insert_symbol_table($$, enumFUNC_USER, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
    }
;

funcprefix:
    FUNCTION funcname
    {
        printf("funcprefix -> FUNCTION funcname\n");

        $$ = newsymbol($2, programfunc_s);
        $$->iaddress = nextquadlabel();
        
        expr* e = newexpr(programfunc_e);
        e->sym = $$;

        emit(iFUNCSTART, e, NULL, NULL, 0, yylineno);
        push(scopeoffsetStack, currscopeoffset(), &topOffset);
        enterscopespace();
        resetformalargsoffset();
    }
;

funcargs:
    '(' {++scope; ++scopeFuncBlock;}
    idlist ')'
    {
        printf("funcargs -> '(' idlist ')'\n");
        enterscopespace();
        resetfunctionlocalsoffset();
    }
;

funcbody:
    blockFunc
    {
        printf("funcbody -> blockFunc\n");
        $$ = currscopeoffset();
        exitscopespace();
    }
;


const:
    REAL
    {
        printf("const -> REAL: %lf\n", $1);

        $$ = newexpr(constnum_e);

        double* ptr = (double*) malloc(sizeof(double));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        $$->numConst = ptr;
        *($$->numConst) = $1;
    }
    | INT
    {
        printf("const -> INT: %d\n", $1);
    
        $$ = newexpr(constnum_e);

        double* ptr = (double*) malloc(sizeof(double));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }
        
        $$->numConst = ptr;
        *($$->numConst) = $1;
    }
    | STR
    {
        printf("const -> STR: %s\n", $1);

        $$ = newexpr(conststring_e);
        
        $$->strConst = $1;
    }
    | NIL
    {
        printf("const -> NIL\n");

        $$ = newexpr(nil_e);
    }
    | TRUE
    {
        printf("const -> TRUE\n");
    
        $$ = newexpr(constbool_e);

        bool* ptr = (bool*) malloc(sizeof(bool));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        $$->boolConst = ptr;
        *($$->boolConst) = true;
    }
    | FALSE
    {
        printf("const -> FALSE\n");
    
        $$ = newexpr(constbool_e);

        bool* ptr = (bool*) malloc(sizeof(bool));

        if (ptr == NULL) {
            printf("No memory... Line code: %d\n", __LINE__);
            exit(1);
        }

        $$->boolConst = ptr;
        *($$->boolConst) = false;
    }
;


idlist:
    | ID {
        symbol* foundId = lookup_sym($1, scope);

        if(isLibFunction($1)) {
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
        insert_symbol_table($1, enumFUNC_ARG, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
    }
    idlistExtend           {printf("idlist -> ID idlistExtend\n");}
;
idlistExtend:
    | ',' ID {
        symbol* foundId = lookup_sym($2, scope);

        if(isLibFunction($2)) {
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
            if(isUserFunction($2, scope)) {
                fprintf(stderr, "ERROR in line %d! This argument already exists as user function in symbol table.\n", yylineno);
                fprintf(stderr, "Line Code: %d\n", __LINE__);
                exit(1);
            }
            insert_symbol_table($2, enumFUNC_ARG, yylineno, scope, scopeFuncBlock, scopeStmtBlock);
        }
    }
    idlistExtend                   {printf("idlistExtend -> ',' ID idlistExtend\n");}
;

ifstmt:
    ifprefix stmt elseprefix stmt
    {
        printf("ifstmt -> ifprefix stmt elseprefix stmt\n");
        
        patchlabel($1, $3 + 1);
        patchlabel($3, nextquadlabel());
    }
    | ifprefix stmt
    {
        printf("ifstmt -> ifprefix stmt");
        
        patchlabel($1, nextquadlabel());
    }
;

ifprefix:
    IF '(' expr ')'
    {
        printf("ifprefix -> IF '(' expr ')'\n");

        emit(iIF_EQ, $3, newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
        $$ = nextquadlabel();
        emit(iJUMP, NULL, NULL, NULL, 0, yylineno);
    }
;

elseprefix:
    ELSE
    {
        printf("elseprefix -> ELSE\n");

        $$ = nextquadlabel();
        emit(iJUMP, NULL, NULL, NULL, 0, yylineno);
    }
;

whilestmt:
    whilestart whilecond loopstmt
    {
        printf("whilestmt -> whilestart whilecond loopstmt\n");

        emit(iJUMP, NULL, NULL, NULL, $1, yylineno);
        patchlabel($2, nextquadlabel());
        
        for (int i = 0; i < topBreak; ++i) {
            patchlabel(StackBreak[i], nextquadlabel());
        }

        for (int i = 0; i < topCont; ++i) {
            patchlabel(StackCont[i], $1);
        }

        topBreak = 0;
        topCont = 0;

        //patchlist($3->breakList, nextquadlabel());
        //patchlist($3->contList, $1);
    }
;

whilestart:
    WHILE
    {
        printf("whilestart -> WHILE\n");

        $$ = nextquadlabel();
    }
;

whilecond:
    '(' expr ')'
    {
        printf("whilecond -> '(' expr ')'\n");

        emit(iIF_EQ, $2, newexpr_constbool(1), NULL, nextquadlabel()+2, yylineno);
        $$ = nextquadlabel();
        emit(iJUMP, NULL, NULL, NULL, 0, yylineno);
    }
;

forstmt:
    forprefix N elist ')' N loopstmt N
    {
        printf("forstmt -> forprefix N elist ')' N loopstmt N\n");
    
        patchlabel($1->enter, $5 + 1);
        patchlabel($2, nextquadlabel());
        patchlabel($5, $1->test);
        patchlabel($7, $2 + 1);

        for (int i = 0; i < topBreak; ++i) {
            patchlabel(StackBreak[i], nextquadlabel());
        }

        for (int i = 0; i < topCont; ++i) {
            patchlabel(StackCont[i], $1->test);
        }

        topBreak = 0;
        topCont = 0;

        //patchlist($stmt.breakList, nextquadlabel());
        //patchlist($smst.contlist, $N1+1);
    }
    | forprefixWithoutELIST ')' N loopstmt N
    {
        printf("forstmt -> forprefixWithoutELIST ')' N stmt N\n");

        patchlabel($1->enter, $3 + 1);
        patchlabel($3, nextquadlabel());
        patchlabel($5, $1->test);

        for (int i = 0; i < topBreak; ++i) {
            patchlabel(StackBreak[i], nextquadlabel());
        }

        for (int i = 0; i < topCont; ++i) {
            patchlabel(StackCont[i], $1->test);
        }

        topBreak = 0;
        topCont = 0;

        //patchlist($stmt.breakList, nextquadlabel());
        //patchlist($smst.contlist, $N1+1);
    }
    | forprefix ')' N loopstmt N
    {
        printf("forstmt -> forprefix ')' N stmt N\n");
        
        patchlabel($1->enter, $3 + 1);
        patchlabel($3, nextquadlabel());
        patchlabel($5, $1->test);

        for (int i = 0; i < topBreak; ++i) {
            patchlabel(StackBreak[i], nextquadlabel());
        }

        for (int i = 0; i < topCont; ++i) {
            patchlabel(StackCont[i], $1->test);
        }

        topBreak = 0;
        topCont = 0;

        //patchlist($stmt.breakList, nextquadlabel());
        //patchlist($stmt.contlist, $N1+1);
    }
    | forprefixWithoutELIST N elist ')' N loopstmt N
    {
        printf("forstmt -> forprefixWithoutELIST N elist ')' N stmt N\n");

        patchlabel($1->enter, $5 + 1);
        patchlabel($2, nextquadlabel());
        patchlabel($5, $1->test);
        patchlabel($7, $2 + 1);

        for (int i = 0; i < topBreak; ++i) {
            patchlabel(StackBreak[i], nextquadlabel());
        }

        for (int i = 0; i < topCont; ++i) {
            patchlabel(StackCont[i], $1->test);
        }

        topBreak = 0;
        topCont = 0;
        
        //patchlist($stmt.breakList, nextquadlabel());
        //patchlist($smst.contlist, $N1+1);
    }
;

N:
    {
        printf("N -> empty\n");

        $$ = nextquadlabel();
        emit(iJUMP, NULL, NULL, NULL, 0, yylineno);
    }
;



forprefix:
    forPREprefix ';' expr ';'
    {
        printf("forprefix -> forPREprefix ';' expr ';'\n");

        $$ = (struct forPrefix*) malloc(sizeof(struct forPrefix));

        if ($$ == NULL) {
            printf("No memory... Line Code: %d\n", __LINE__);
            exit(1);
        }

        $$->test = $1->label;
        $$->enter = nextquadlabel();
        emit(iIF_EQ, $3, newexpr_constbool(1), NULL, 0, yylineno);
    }
;

forPREprefix:
    FOR '(' elist
    {
        printf("forPREprefix -> FOR '(' elist\n");

        $$ = (struct forPREpre*) malloc(sizeof(struct forPREpre));

        if ($$ == NULL) {
            printf("No memory... Line Code %d:\n", __LINE__);
            exit(1);
        }

        $$->label = nextquadlabel();
        $$->elist = $3;
    }
;

forprefixWithoutELIST:
    forPREprefixWithoutELIST ';' expr ';'
    {
        printf("forprefixWithoutELIST -> forPREprefixWithoutELIST ';' expr ';'\n");

        $$ = (struct forPrefix*) malloc(sizeof(struct forPrefix));

        if ($$ == NULL) {
            printf("No memory... Line Code: %d\n", __LINE__);
            exit(1);
        }

        $$->test = $1->label;
        $$->enter = nextquadlabel();
        emit(iIF_EQ, $3, newexpr_constbool(1), NULL, 0, yylineno);
    }
;

forPREprefixWithoutELIST:
    FOR '('
    {
        printf("forPREprefixWithoutELIST -> FOR '('\n");

        $$ = (struct forPREpre*) malloc(sizeof(struct forPREpre));

        if ($$ == NULL) {
            printf("No memory... Line Code %d:\n", __LINE__);
            exit(1);
        }

        $$->label = nextquadlabel();
    }
;

loopstart:
    {
        printf("loopstart -> empty\n");

        ++loopcounter;
    }
;

loopend:
    {
        printf("loopend -> empty\n");

        --loopcounter;
    }
;

loopstmt:
    loopstart stmt loopend
    {
        printf("loopstmt -> loopstart stmt loopend\n");
        $$ = $2;
    }
;

returnstmt:
    RETURN expr ';'
    {
        printf("returnstmt -> RETURN expr ';'\n");

        assert(scopeFuncBlock >= 0);

        if (scopeFuncBlock == 0) {
            ++compileErrors;
            assert(indexErrors < 1000);
            strErrors[indexErrors] = yylineno;
            ++indexErrors;
        }
        
        emit(iRET, $2, NULL, NULL, 0, yylineno);    
    }
    | RETURN ';'
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
;


%%


void yyerror(char* s)
{
    fprintf(stderr, "Error: %s", s);
    fprintf(stderr, "Line Code: %d\n", __LINE__);
}

int main(int argc, char** argv)
{
    FILE* fOutput;
	FILE* fBinary;
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
	generateTCode();
	if (!(fBinary = fopen("binary", "wb+"))) {
        fprintf(stderr, "Error opening output file 'binary'!\n");
        return 1;
    }
	generateBinary(fBinary);
	fclose(fBinary);
    
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

expr* newexpr_constnum(double i)
{
    expr* e = newexpr(constnum_e);
    unsigned int* ptr = (unsigned int*) malloc(sizeof(double));
    
    if (ptr == NULL) {
        printf("No memory... Line Code: %d\n", __LINE__);
        exit(1);
    }

    e->numConst = ptr;
    *(e->numConst) = i;
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