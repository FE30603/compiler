#include "compiler.h"
#include "lexer.h"

int main(int argc, char *argv[])
{
    readText(argv[1], code, sizeof(code));
    puts(code);
    printf("===========TOKEN=========\n");
    lex(code);
    dump(tokens, tokenTop);
    parse();
    freetoken(tokens, tokenTop);
    return 0;
}