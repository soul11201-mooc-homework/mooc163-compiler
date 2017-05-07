## 作业答案


https://github.com/noname007/mooc163-compiler/compare/c1ca1ff2169e2a267f009a3688687ebcc2425f04...8




## C--语言的代码生成器

在这个作业中，要求你给C--语言实现代码生成器，生成栈式计算机的指令代码。
C--语言的语法

C--语言的语法和上一次作业中的相同，为了方便引用，这里重复给出如下：
prog   -> { decs stms }
decs   -> dec decs
        |
dec    -> type id ;
type   -> int
        | bool
stms   -> stm stms
        |
stm    -> id = exp ;
        | printi(exp) ;
        | printb(exp) ;
exp    -> intnum
        | true
        | false
        | id
        | (exp)
        | exp + exp
        | exp - exp
        | exp * exp
        | exp / exp
        | exp && exp
        | exp || exp
栈式计算机

栈式计算机的指令见课程的讲义，需要特别指出的是，讲义中所给出的指令不足以编译C--，所以需要你自己设计并添加必须的指令。
任务

首先下载我们提供的代码框架：
http://staff.ustc.edu.cn/~bjhua/mooc/codegen.zip

首先编译该代码：

  $ make
然后运行给定的测试例：
  $ ./a.out < test.txt
对给定的测试例，在屏幕上打印了所生成的栈计算机的代码；并且生成了名为stack.exe的可执行程序，如果运行该程序的话：

  $ ./stack.exe
将输出：
  88
  true
代码当中已经给出的是模块和任务是包括：

栈计算机的数据结构定义模块：stack-machine.h.c。你的任务是根据自己的研究和判断，增加必要的新的指令（结合下面的任务2）；
从C--编译到栈计算机的代码生成模块：gen-stack.h.c；你的任务是将这部分代码补充完整（TODO的部分）；
从栈计算机编译到x86汇编代码并生成可执行文件的模块：stack2x86.h.c。（这部分是选做，不做统一要求。）



## 程序结果

输入程序

```
{
  int a;
  int d;
  bool c;

  bool b;

  printb (b);
  a= a + d;
  a = a + 3333;
  a = a - 3333;
  a = a * 3333;
  a = a / 3333;
  b = b && true;
  b = b || true;
  printi(a);
}

```


输出程序结果：


```
lex and parse starting...
lex and parse finished
print the AST starting...
{
  int a;
  int d;
  bool c;
  bool b;

  printb(b);
  a = (a) + (d);
  a = (a) + (3333);
  a = (a) - (3333);
  a = (a) * (3333);
  a = (a) / (3333);
  b = (b) && (true);
  b = (b) || (true);
  printi(a);
}
print the AST finished
semantic analysis starting...
printb(b);
a = (a) + (d);
a = (a) + (3333);
a = (a) - (3333);
a = (a) * (3333);
a = (a) / (3333);
b = (b) && (true);
b = (b) || (true);
printi(a);
semantic analysis finished
stack machine code generation starting...
stack machine code generation finished
stack machine code output starting...
{
  .int a
  .int d
  .int c
  .int b

  load b
  printb
  load a
  load d
  add
  store a
  load a
  push 3333
  add
  store a
  load a
  push 3333
  sub
  store a
  load a
  push 3333
  times
  store a
  load a
  push 3333
  div
  store a
  load b
  push 1
  and
  store b
  load b
  push 1
  or
  store b
  load a
  printi
}
stack machine code output finished
x86 code generation starting...
x86 code generation finished (writing to file "temp.s")
executable generation starting...
executable generation finished (writing to file "stack.exe")
reg machine code generation starting...
reg machine code generation finished
reg machine code output starting...
{
  .int a
  .int d
  .int c
  .int b

  mov b,r1
  printb r1
  mov a,r2
  mov d,r3
  add r2, r3, r4
  mov r4 a
  mov a,r5
  movn 3333, r6
  add r5, r6, r7
  mov r7 a
  mov a,r8
  movn 3333, r9
  sub r8, r9, r10
  mov r10 a
  mov a,r11
  movn 3333, r12
  times r11, r12, r13
  mov r13 a
  mov a,r14
  movn 3333, r15
  div r14, r15, r16
  mov r16 a
  mov b,r17
  movn 1, r18
  and r17, r18, r19
  mov r19 b
  mov b,r20
  movn 1, r21
  or r20, r21, r22
  mov r22 b
  mov a,r23
  printi r23
}
reg machine code output finished
```

