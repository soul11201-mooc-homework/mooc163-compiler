有一个`exp.out`的文件输出，是bison输出的 LR 状态机转换表示


## [作业1 答案]()

https://github.com/noname007/mooc163-compiler/compare/79e0a1cfb6731cac62ef3eb8ac2c69ae23412dc6...fe4ae608047ecb8492f4137f6abc55625bf02f18

    make

输出结果：
    
    ((((2) - (3)) * (4)) - (((3) + (5)) / (5))) - (1)



## [作业2 答案]()

https://github.com/noname007/mooc163-compiler/compare/83285ca2c5ad09f93cceb98e7c8dff2cf0f0f81c...dc9611a44ceff8234be8d585470f5b86b9fe9a9f
    


    make compile

输出栈式计算机指令

```shell
$ make compile
sh -c "bison exp.y"
gcc -g -O2 *.c
./a.exe < test.txt
Compile starting
((((2) - (3)) * (4)) - (((3) + (5)) / (5))) - (1)

the Stack instructons:
push 2
push 3
minus
push 4
mul
push 3
push 5
add
push 5
div
minus
push 1
minus

Compile finished
```


### 优化

    make compile-opt

输出优化后的栈式计算机指令。

```shell

$ make compile-opt
sh -c "bison exp.y"
gcc -g -O2 -D=OPT *.c
./a.exe < test.txt
Compile starting
((((2) - (3)) * (4)) - (((3) + (5)) / (5))) - (1)

the Stack instructons:
push -6

Compile finished
```

