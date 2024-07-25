Compiler

語法

```
E = F (op E)*
F = (E) | Number | Id
PROG = STMTS
BLOCK = { STMTS }
STMTS = STMT*
STMT = WHILE | BLOCK | ASSIGN
WHILE = while (E) STMT
ASSIGN = id '=' E;
```

結果

```
$make
gcc -std=c99 -O0 lexer.c compiler.c main.c -o compiler

$/compiler ./test/while.txt
while (a<10) {
    a = a + 3;
}
===========TOKEN=========
token = while
token = (
token = a
token = <
token = 10
token = )
token = {
token = a
token = =
token = a
token = +
token = 3
token = ;
token = }
==========dump=======
0:while
1:(
2:a
3:<
4:10
5:)
6:{
7:a
8:=
9:a
10:+
11:3
12:;
13:}
======parse======
(L0)
t0 = a
t1 = 10
t2 = t0 < t1
if not T2 goto L1
t3 = a
t4 = 3
t5 = t3 + t4
a = t5
goto L0
(L1)
``` 
