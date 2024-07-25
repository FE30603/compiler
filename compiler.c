#include "compiler.h"
#include <assert.h>

#define isDigit(ch) ((ch) >= '0' && (ch) <= '9')
#define isAlpha(ch) (((ch) >= 'a' && (ch) <= 'z') || ((ch) >= 'A' && (ch) <= 'Z'))

int tokenidx = 0;
int tempidx = 0, labelidx = 0;

void BLOCK();
void STMT();
int E();
void IF();

/*
int isNext(char *set)
{
    char eset[1000], etoken[1000];
    sprintf(eset, "%s", set);
    sprintf(etoken, "%s", tokens[tokenidx]);
    printf("eset:%s etoken:%s\n", set, tokens[tokenidx]);
    return (tokenidx < tokenTop && strstr(eset, etoken) != NULL);
    // return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL);
}
*/
int isNext(char *s)
{
    if (tokenidx >= tokenTop)
        return 0;
    return strcmp(tokens[tokenidx], s) == 0;
}

char *next()
{
    return tokens[tokenidx++];
}

char *skip(char *set)
{

    if (isNext(set))
    {
        return next();
    }
    else
    {
        assert(0);
        return NULL;
    }
}

int isEnd()
{
    return tokenidx >= tokenTop;
}

// F = (E) | Number | Id
int F()
{
    int f;
    if (isNext("("))
    {
        next();
        f = E();
        next();
    }
    else
    {
        f = tempidx++;
        char *item = next();
        if (isDigit(*item))
        {
            printf("t%d = %s\n", f, item);
        }
        else
        {
            if (isNext("++"))
            {
                next();
                printf("%s = %s + 1\n", item, item);
            }
            printf("t%d = %s\n", f, item);
        }
    }
    return f;
}

// E = F (op E)*
int E()
{
    int i1 = F();
    while (isNext("+") || isNext("-") || isNext("*") || isNext("/") || isNext("&") ||
           isNext("|") || isNext("!") || isNext("<") || isNext(">") || isNext("=") ||
           isNext(">=") || isNext("<=") || isNext("==") || isNext("!="))
    {
        char *op = next();
        int i2 = E();
        int i = tempidx++;
        printf("t%d = t%d %s t%d\n", i, i1, op, i2);
        i1 = i;
    }
    return i1;
}

void WHILE()
{
    int whilebegin = labelidx++;
    int whileend = labelidx++;
    printf("(L%d)\n", whilebegin);
    skip("while");
    skip("(");
    int e = E();
    printf("if not T%d goto L%d\n", e, whileend);
    skip(")");
    STMT();
    printf("goto L%d\n", whilebegin);
    printf("(L%d)\n", whileend);
}

void IF()
{
    skip("if");
    skip("(");
    E();
    skip(")");
    STMT();
    if (isNext("else"))
    {
        skip("else");
        STMT();
    }
}

void ASSIGN()
{
    char *id = next();
    skip("=");
    int e = E();
    skip(";");
    printf("%s = t%d\n", id, e);
}

void STMT()
{
    if (isNext("while"))
    {
        WHILE();
    }
    else if (isNext("if"))
    {
        IF();
    }
    else if (isNext("{"))
    {
        BLOCK();
    }
    else
    {
        ASSIGN();
    }
}

void STMTS()
{
    while (!isEnd() && !isNext("}"))
    {
        STMT();
    }
}

void BLOCK()
{
    skip("{");
    STMTS();
    skip("}");
}

void parse()
{
    printf("======parse======\n");
    STMTS();
}