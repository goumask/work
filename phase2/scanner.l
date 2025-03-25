%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

char *mystrcpy(char *str);
char* isolate_string();

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

"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"for"       { return FOR; }
"function"  { return FUNCTION; }
"return"    { return RETURN; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"and"       { return AND; }
"not"       { return NOT; }
"or"        { return OR; }
"local"     { return LOCAL; }
"true"      { return TRUE; }
"false"     { return FALSE; }
"nil"       { return NIL; }

"="         { return yytext[0]; }
"=="        { return EQUAL_EQUAL; }
"!="        { return NOT_EQUAL; }
"++"        { return PLUS_PLUS; }
"--"        { return MINUS_MINUS; }
"+"         { return yytext[0]; }
"-"         { return yytext[0]; }
"*"         { return yytext[0]; }
"/"         { return yytext[0]; }
"%"         { return yytext[0]; }
"<="        { return LESS_EQUAL; }
">="        { return GREATER_EQUAL; }
">"         { return yytext[0]; }
"<"         { return yytext[0]; }



\{          { return yytext[0]; }
\}          { return yytext[0]; }
\[          { return yytext[0]; }
\]          { return yytext[0]; }
\(          { return yytext[0]; }
\)          { return yytext[0]; }
;           { return yytext[0]; }
,           { return yytext[0]; }
::          { return COLON_COLON; }
:           { return yytext[0]; }
\.\.        { return DOT_DOT; }
\.          { return yytext[0]; }

{integer}           { yylval.numInt = atoi(yytext); return INT; }
{real}              { yylval.numReal = atof(yytext); return REAL; }
{string}            { yylval.string = isolate_string(yytext); return STR; }
{whiteSpace}        { }

{identifier}        { yylval.string = mystrcpy(yytext); return ID; }

{lineComment}       {  }

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
    /* return NOTHING */
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

char *mystrcpy(char *str) {
    char *buf = malloc(strlen(str)*sizeof(char)); // Be careful! I had bug! Not: malloc(strlen(str));

    if(buf == NULL) {
        printf("No memory... strcpy\n");
        exit(1);
    }
    strcpy(buf, str);
    return buf;
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