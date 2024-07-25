#include "lexer.h"

char code[500];
char *tokens[500];
int tokenTop = 0;
char token[30];
int types[500];

void readText(char *filename, char *text, int size)
{
    FILE *fileptr = fopen(filename, "r");
    int len = fread(text, 1, size, fileptr);
    text[len] = '\0';
    fclose(fileptr);
}

char *scan(char *p)
{
    while (isspace(*p)) // Space
        p++;

    char *start = p;
    int type;
    if (*p == '\0')
        return NULL;

    if (*p == '"') //"string"
    {
        p++;
        while (*p != '"')
            p++;
        p++;
        type = TOKEN_KEYWORD;
    }
    else if (isDigit(*p)) // isDigit   123456789
    {
        while (isDigit(*p))
            p++;
        type = TOKEN_LITERAL;
    }
    else if (isAlpha(*p)) // isAlpha    abcde
    {
        while (isAlpha(*p) || isDigit(*p) || *p == '_')
            p++;
        type = TOKEN_IDENTIFIER;
    }
    else // isChar  ; =
    {
        p++;
        type = TOKEN_CHAR;
    }

    int len = p - start;
    char *token = (char *)malloc(len + 1);
    strncpy(token, start, len);
    token[len] = '\0';
    types[tokenTop] = type;
    tokens[tokenTop++] = token;
    printf("token = %s\n", token);
    return p;
}

// Lex code
void lex(char *code)
{
    char *p = code;
    while (1)
    {
        p = scan(p);
        if (p == NULL)
            break;
    }
}

// Print tokens
void dump(char *tokens[], int top)
{
    printf("==========dump=======\n");
    for (int i = 0; i < top; i++)
    {
        printf("%d:%s\n", i, tokens[i]);
    }
}

// Free tokens
void freetoken(char *tokens[], int top)
{
    for (int i = 0; i < top; i++)
    {
        free(tokens[i]);
    }
}
