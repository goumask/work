%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define YY_DECL int alpha_yylex (void* yylval)

int token_counter = 0;

typedef enum {
    IF_T, ELSE_T, WHILE_T, FOR_T, FUNCTION_T, RETURN_T, BREAK_T, 
    CONTINUE_T, AND_T, NOT_T, OR_T, LOCAL_T, TRUE_T, FALSE_T, NIL_T,
    
    EQUAL_T, PLUS_T, MINUS_T, MUL_T, DIV_T, MOD_T, EQUAL_EQUAL_T, NOT_EQUAL_T, PLUS_PLUS_T, 
    MINUS_MINUS_T, GREATER_T, GREATER_EQUAL_T, LESS_T, LESS_EQUAL_T,
    
    CURLY_O_T, CURLY_C_T, SQUARE_BRACKET_O_T, SQUARE_BRACKET_C_T, DOT_T, DOT_DOT_T,
    PARENTHESIS_O_T, PARENTHESIS_C_T, SEMICOLON_T, COMMA_T, COLON_T, COLON_COLON_T,
    
    LINE_COMMENT_T, BLOCK_COMMENT_T,

    CONST_INT_T, CONST_REAL_T, STRING_T,

    ID_T, UNKNOWN_T, BEGINSTATE_FIRST_NODE
}TypeToken_t;

typedef struct alpha_token {
    unsigned int    numline;
    unsigned int    numToken;
    char            *content;
    
    TypeToken_t     type;

    char           *category;

    struct alpha_token *next;
} alpha_token_t;


char* isolate_string();
alpha_token_t* insert_new_token(alpha_token_t **lastNode, TypeToken_t type);
char *mystrcpy(char *str);
char* token_category(TypeToken_t token);
char* token2str(alpha_token_t *token);

%}


%option noyywrap
%option yylineno


string          \"(\\[\"nt\\]|[^\"\\])*\"
lineComment     \/\/.*
integer         [0-9][0-9]*
real            [0-9]*\.[0-9]+
identifier      [a-zA-Z][a-zA-Z_0-9]*
whiteSpace      [\r\n \t\v]

%%

"if"        { insert_new_token( (alpha_token_t**) &yylval, IF_T);         }
"else"      { insert_new_token( (alpha_token_t**) &yylval, ELSE_T);       }
"while"     { insert_new_token( (alpha_token_t**) &yylval, WHILE_T);          }
"for"       { insert_new_token( (alpha_token_t**) &yylval, FOR_T);              }
"function"  { insert_new_token( (alpha_token_t**) &yylval, FUNCTION_T);   }
"return"    { insert_new_token( (alpha_token_t**) &yylval, RETURN_T);     }
"break"     { insert_new_token( (alpha_token_t**) &yylval, BREAK_T);      }
"continue"  { insert_new_token( (alpha_token_t**) &yylval, CONTINUE_T);   }
"and"       { insert_new_token( (alpha_token_t**) &yylval, AND_T);        }
"not"       { insert_new_token( (alpha_token_t**) &yylval, NOT_T);        }
"or"        { insert_new_token( (alpha_token_t**) &yylval, OR_T);         }
"local"     { insert_new_token( (alpha_token_t**) &yylval, LOCAL_T);     }
"true"      { insert_new_token( (alpha_token_t**) &yylval, TRUE_T);       }
"false"     { insert_new_token( (alpha_token_t**) &yylval, FALSE_T);      }
"nil"       { insert_new_token( (alpha_token_t**) &yylval, NIL_T);        }

"="         { insert_new_token( (alpha_token_t**) &yylval, EQUAL_T);                  }
"=="        { insert_new_token( (alpha_token_t**) &yylval, EQUAL_EQUAL_T);      } 
"!="        { insert_new_token( (alpha_token_t**) &yylval, NOT_EQUAL_T);          }
"++"        { insert_new_token( (alpha_token_t**) &yylval, PLUS_PLUS_T);          }
"--"        { insert_new_token( (alpha_token_t**) &yylval, MINUS_MINUS_T);      }
"+"         { insert_new_token( (alpha_token_t**) &yylval, PLUS_T);                    }
"-"         { insert_new_token( (alpha_token_t**) &yylval, MINUS_T);                  }
"*"         { insert_new_token( (alpha_token_t**) &yylval, MUL_T);                      }
"/"         { insert_new_token( (alpha_token_t**) &yylval, DIV_T);                      }
"%"         { insert_new_token( (alpha_token_t**) &yylval, MOD_T);                      }
"<="        { insert_new_token( (alpha_token_t**) &yylval, LESS_EQUAL_T);        }
">="        { insert_new_token( (alpha_token_t**) &yylval, GREATER_EQUAL_T);  }
">"         { insert_new_token( (alpha_token_t**) &yylval, GREATER_T);              }
"<"         { insert_new_token( (alpha_token_t**) &yylval, LESS_T);                    }



\{          { insert_new_token( (alpha_token_t**) &yylval, CURLY_O_T);      }
\}          { insert_new_token( (alpha_token_t**) &yylval, CURLY_C_T);      }
\[          { insert_new_token( (alpha_token_t**) &yylval, SQUARE_BRACKET_O_T);      }
\]          { insert_new_token( (alpha_token_t**) &yylval, SQUARE_BRACKET_C_T);      }
\(          { insert_new_token( (alpha_token_t**) &yylval, PARENTHESIS_O_T);      }
\)          { insert_new_token( (alpha_token_t**) &yylval, PARENTHESIS_C_T);      }
;           { insert_new_token( (alpha_token_t**) &yylval, SEMICOLON_T);      }
,           { insert_new_token( (alpha_token_t**) &yylval, COMMA_T);      }
::          { insert_new_token( (alpha_token_t**) &yylval, COLON_COLON_T);     }
:           { insert_new_token( (alpha_token_t**) &yylval, COLON_T);      }
\.\.        { insert_new_token( (alpha_token_t**) &yylval, DOT_DOT_T);     }
\.          { insert_new_token( (alpha_token_t**) &yylval, DOT_T);      }



{integer}           { insert_new_token( (alpha_token_t**) &yylval, CONST_INT_T);                    }
{real}              { insert_new_token( (alpha_token_t**) &yylval, CONST_REAL_T);                   }
{string}            { insert_new_token( (alpha_token_t**) &yylval, STRING_T);                       }
{whiteSpace}        {                                                                                            }

{identifier}        { insert_new_token( (alpha_token_t**) &yylval, ID_T);             }

{lineComment}       { insert_new_token( (alpha_token_t**) &yylval, LINE_COMMENT_T);    }

"/*"                {
    int openNestedCommentsBl = 1;
    int c;
    int firstLineComment = yylineno;
    int endLineComment = -1;
    
    printf("Begin a multi comment yytext: %s, in line: %d\n", yytext, firstLineComment);

    while( (c = input()) != EOF) {
        if(c == '*') {
            if( (c = input()) == '/') {
                --openNestedCommentsBl;
                if(openNestedCommentsBl != 0) {
                    printf("\tEnd nested multi comment in line: %d\n", yylineno);
                }
            }
            else {
                unput(c);
            }
        }
        else if(c == '/') {
            if( (c = input()) == '*') {
                ++openNestedCommentsBl;
                printf("\tBegin Nested multi comment yytext: %s, in line: %d\n", yytext, yylineno);
            }
            else {
                unput(c);
            }
        }
        if(openNestedCommentsBl == 0) break;
    }
    if(c == EOF) {
        printf("Unclosed multi-line comment. EXIT!\n");
        exit(1);
    } else {
        endLineComment = yylineno;
        printf("End block comment yylineno = %d\n", endLineComment);
    }
    insert_new_token( (alpha_token_t**) &yylval, BLOCK_COMMENT_T);
}

.                   {
    if(yytext[0] =='\"') {
        printf("Unclosed string in line: %d, yytext: %s\n", yylineno, yytext);
    } else {
        printf("Unexpected character: %s in line: %d\n", yytext, yylineno);
    }
    exit(1);
}

%%


int main(int argc, char **argv) {
    alpha_token_t *headList = NULL;
    alpha_token_t *endList = NULL;
    alpha_token_t *traceList = NULL;

    FILE* fOutput;

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

    headList = insert_new_token(&endList, BEGINSTATE_FIRST_NODE);
    
    alpha_yylex(endList);

    headList = headList->next; /* I don't to free the previous head Node. */

    traceList = headList;
    while(traceList != NULL)
    {
        if(argc == 3) {
            fprintf(fOutput, "%-5d: #%-10d \"%s\" %-15s %-10s %-15s %-10s\n",
                traceList->numline, \
                traceList->numToken, \
                traceList->content,   \
                " ",                     \
                traceList->category,         \
                " ",                            \
                token2str(traceList)         \
            );
        } else {
            printf("%-5d: #%-10d \"%s\" %-15s %-10s %-15s %-10s\n",
                traceList->numline, \
                traceList->numToken, \
                traceList->content,   \
                " ",                     \
                traceList->category,         \
                " ",                            \
                token2str(traceList)         \
            );
        }
        
        traceList = traceList->next;
    }

    while(cEndProgram != 'q') {
        printf("Type 'q' to end programm.\n");
        cEndProgram = getchar();
    }

    return 0;
}

char* isolate_string()
{
    int i = 0;
    char* c = (char*) malloc(  (1 + strlen(yytext)) * sizeof(char));

    int fullTheString = 0;

    if(c == NULL) return NULL;
    if(strlen(yytext) == 0) {
        c[0] = '\0';
        return c;
    }  

    while(yytext[i] != '\0')
    {
        if(i == 0) {
            /* Ignore the first quote character: ` " ` */
        } else {
            if(yytext[i] == '\\') {
                if(yytext[i+1] == 'n') {
                    c[fullTheString] = '\n';
                }
                else if(yytext[i+1] == 't') {
                    c[fullTheString] = '\t';
                }
                else if(yytext[i+1] == '\\') {
                    c[fullTheString] = '\\';
                } 
                else if(yytext[i+1] == '\"') {
                    c[fullTheString] = '\"';
                }
                else {
                    fprintf(stderr, "There is no case...\n");
                    exit(1);
                }
                ++i;
            } else {
                if(yytext[i] == '\"') {
                    break; /* The last quote character: ` " ` */
                }
                c[fullTheString] = yytext[i];
            }
            ++fullTheString;
        }
        ++i;
    }
    c[fullTheString] = '\0';

    return c;
}

alpha_token_t* insert_new_token(alpha_token_t **lastNode, TypeToken_t type)
{
    alpha_token_t *newNode = NULL;

    newNode = (alpha_token_t*) malloc(sizeof(alpha_token_t));

    if(newNode == NULL) {
        printf("No memory...\n");
        exit(1);
    }
    
    if (type == LINE_COMMENT_T) {
       newNode->content = "";
    }
    else if(type == BLOCK_COMMENT_T) {
        newNode->content = "B ... ";
    }
    else if(type == STRING_T) {
        newNode->content = isolate_string();
    }    
    else if(type == BEGINSTATE_FIRST_NODE) {
        /* Nothing */
    }
    else {
        newNode->content = mystrcpy(yytext);
    }
    

    
    newNode->type = type;

    newNode->category = token_category(type);

    newNode->next = NULL;

    if(*lastNode != NULL) {
        newNode->numline = yylineno;
        newNode->numToken = ++token_counter;
        (*lastNode)->next = newNode;
    }
    (*lastNode) = newNode;

    return newNode;
}

char *mystrcpy(char *str) {
    char *buf = malloc(strlen(str));

    if(buf == NULL) {
        printf("No memory... strcpy\n");
        exit(1);
    }
    strcpy(buf, str);
    return buf;
}

char* token_category(TypeToken_t token)
{
    switch(token)
    {
        case IF_T: case ELSE_T: case WHILE_T: case FOR_T: case FUNCTION_T:
        case RETURN_T: case BREAK_T: case CONTINUE_T: case AND_T: case NOT_T:
        case OR_T: case LOCAL_T: case TRUE_T: case FALSE_T: case NIL_T:
            return "KEYWORD";

        case EQUAL_T: case PLUS_T: case MINUS_T: case MUL_T: case DIV_T: case MOD_T:
        case EQUAL_EQUAL_T: case NOT_EQUAL_T: case PLUS_PLUS_T: case MINUS_MINUS_T:
        case GREATER_T: case GREATER_EQUAL_T: case LESS_T: case LESS_EQUAL_T:
            return "OPERATOR";

        case CURLY_O_T: case CURLY_C_T: case SQUARE_BRACKET_O_T: case SQUARE_BRACKET_C_T:
        case DOT_T: case DOT_DOT_T: case PARENTHESIS_O_T: case PARENTHESIS_C_T: case SEMICOLON_T:
        case COMMA_T: case COLON_T: case COLON_COLON_T:
            return "PUNCUATION";

        case LINE_COMMENT_T: case BLOCK_COMMENT_T:
            return "COMMENT";

        case CONST_INT_T:
            return "CONST_INT";

        case CONST_REAL_T:
            return "CONST_REAL";

        case STRING_T:
            return "STRING";

        case ID_T:
            return "ID";

        case BEGINSTATE_FIRST_NODE:
            return "";

        case UNKNOWN_T:
            return "UNKNOWN";

        default: assert(0); /* NEVER */
    }
}

char* token2str(alpha_token_t *token)
{
    switch(token->type)
    {
        case IF_T:               return "IF            <-- enum";
        case ELSE_T:             return "ELSE          <-- enum";
        case WHILE_T:            return "WHILE         <-- enum";
        case FOR_T:              return "FOR           <-- enum";
        case FUNCTION_T:         return "FUNCTION      <-- enum";
        case RETURN_T:           return "RETURN        <-- enum";
        case BREAK_T:            return "BREAK         <-- enum";
        case CONTINUE_T:         return "CONTINUE      <-- enum";
        case AND_T:              return "AND           <-- enum";
        case NOT_T:              return "NOT           <-- enum";
        case OR_T:               return "OR            <-- enum";
        case LOCAL_T:            return "LOCAL         <-- enum";
        case TRUE_T:             return "TRUE          <-- enum";
        case FALSE_T:            return "FALSE         <-- enum";
        case NIL_T:              return "NIL           <-- enum";

        case EQUAL_T:            return "EQUAL         <-- enum";
        case PLUS_T:             return "PLUS          <-- enum";
        case MINUS_T:            return "MINUS         <-- enum";
        case MUL_T:              return "MUL           <-- enum";
        case DIV_T:              return "DIV           <-- enum";
        case MOD_T:              return "MOD           <-- enum";
        case EQUAL_EQUAL_T:      return "EQUAL_EQUAL   <-- enum";
        case NOT_EQUAL_T:        return "NOT_EQUAL     <-- enum";
        case PLUS_PLUS_T:        return "PLUS_PLUS     <-- enum";
        case MINUS_MINUS_T:      return "MINUS_MINUS   <-- enum";
        case GREATER_T:          return "GREATER       <-- enum";
        case GREATER_EQUAL_T:    return "GREATER_EQUAL <-- enum";
        case LESS_T:             return "LESS          <-- enum";
        case LESS_EQUAL_T:       return "LESS_EQUAL    <-- enum";

        case CURLY_O_T:          return "CURLY_O       <-- enum";
        case CURLY_C_T:          return "CURLY_C       <-- enum";
        case SQUARE_BRACKET_O_T: return "SQUARE_BRACKET_O <-- enum";
        case SQUARE_BRACKET_C_T: return "SQUARE_BRACKET_C <-- enum";
        case DOT_T:              return "DOT           <-- enum";
        case DOT_DOT_T:            return "DOT_DOT       <-- enum";
        case PARENTHESIS_O_T:    return "PARENTHESIS_O <-- enum";
        case PARENTHESIS_C_T:    return "PARENTHESIS_C <-- enum";
        case SEMICOLON_T:        return "SEMICOLON     <-- enum";
        case COMMA_T:            return "COMMA         <-- enum";
        case COLON_T:            return "COLON         <-- enum";
        case COLON_COLON_T:      return "COMMA_COLON   <-- enum";

        case LINE_COMMENT_T:     return "LINE_COMMENT  <-- enum";
        case BLOCK_COMMENT_T:    return "BLOCK_COMMENT <-- enum";

        case CONST_INT_T:  case CONST_REAL_T: case STRING_T:
        case ID_T:
           return token->content;

        case BEGINSTATE_FIRST_NODE:
            return "1st Node";
        case UNKNOWN_T:
            return "UNKNOWN";

        default: assert(0); /* NEVER */
    }
}
