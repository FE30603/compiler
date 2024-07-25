#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define isDigit(ch) ((ch) >= '0' && (ch) <= '9')
#define isAlpha(ch) (((ch) >= 'a' && (ch) <= 'z') || ((ch) >= 'A' && (ch) <= 'Z'))

typedef enum
{
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_LITERAL,
    TOKEN_OPERATOR,
    TOKEN_SEPARATOR,
    TOKEN_CHAR
} TokenType;

extern char code[500];
extern char *tokens[500];
extern char token[30];
extern int tokenTop;
extern int types[500];

void readText(char *filename, char *text, int size);
char *scan(char *p);
void lex(char *code);
void dump(char *tokens[], int top);
void freetoken(char *tokens[], int top);
#endif