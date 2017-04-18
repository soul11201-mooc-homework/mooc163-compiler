# 作业

http://staff.ustc.edu.cn/~bjhua/mooc/semant.html


## C--语言的语义分析器

在这个作业中，要求你给C--语言实现一个语义分析器（类型检查器）。

### C--语言的语法

C--语言的语法由如下的上下文无关文法定义。
```bnf
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
```

每个程序prog由一个程序块组成（注意一对左右花括号）；程序块包括变量声明列表 decs和语句列表stms两部分。
变量声明列表decs包含零个或多个声明dec，每一个声明dec的形式 都是type id；其中id是变量名，type是类型。一共有两种不同形式的类型： int和bool，他们都是程序的保留关键字；保留关键字用黑体表示。

语句列表stms包含零个或多个语句stm，每一个语句stm可能有三种不同的形式： 赋值语句、整型值打印语句和布尔值打印语句。每条语句都以分号分隔。 赋值语句id=exp将exp的值赋值给变量id；整型值打印printi(exp) 把exp的值打印到标准输出，并以换行符结尾；布尔值打印printb(exp) 把exp的值打印到标准输出，并以换行符结尾。注意： printi和printb是程序的保留关键字。

表达式exp包括整型值常数intnum、布尔常数true和false、变量id、 括号表达式(exp)以及四种整数运算及两种布尔运算。

### 语义规则

C--语言的语义规则如下（方括号里的编号R1，R2等表示规则的编号， 这个编号将在代码中直接引用）：
- [R1] 每个变量使用前必须先声明；
- [R2] 每个变量最多声明一次，即变量不能重复声明；
- [R3] 赋值语句左侧变量的类型必须和右侧表达式的类型一致；
- [R4] 整型值打印语句的参数表达式必须是整型；
- [R5] 布尔值打印语句的参数表达式必须是布尔型；
- [R6] 四种整型运算的操作数的类型必须都是整型；
- [R7] 两种布尔运算的操作数的类型必须都是布尔类型。

## 任务

首先下载我们提供的代码框架：

http://staff.ustc.edu.cn/~bjhua/mooc/semant.zip

首先编译该代码：

  $ make

然后运行给定的测试例：
  
  $ ./a.out < test.txt

其中已经提供了词法分析、语法分析、抽象语法树、语义分析 等模块；你的任务是在语义分析模块semant.c中添加缺少的代码，将其补充完整， 能对任意C--程序做语义分析；即对上面的七条规则做检查，对不符合这些规则的程序报错。