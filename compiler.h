#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <stdio.h>
#include <string.h>
#include "lexer.h"

extern char *tokens[500];
extern int tokenTop;
extern char token[30];
extern int types[500];
void parse();
#endif