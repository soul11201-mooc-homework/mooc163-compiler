#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int id;
    struct _Node  * to;
    struct _Node  * from;
}Node;

/*
    
    
    ---> 0 --c-- 1   |---->accepted|

 */
typedef struct 
{
    Node start[2];
    char re_str[1];
}G_BaseRe_t;


/*
                         ____
                        /    \
    ----> [0] --e1-- [1]      [2] --e2-- [3]  |---->accepted|
    
    '\0'  伊普西龙转换
 */

typedef struct 
{
    Node state[4];
}G_ConcatRe_t;



/*

             1 --e1-- 2
           /            \
    start 0              5    |---->accepted|
           \            /
             3 --e2-- 4 
        
    \ <----->epsilone translate

*/

typedef struct 
{
    Node state[4];
}G_SelectRe_t;

/*           
               --<--<--
              /        \
             1 -- e1 -- 2
           /             \
    ----> 0               3    |---->accepted|
            \____________/
 
        
 */

typedef struct 
{
    Node state[6];
}G_ClosureRe_t;




int main(int argc, char const *argv[])
{
    
    return 0;
}