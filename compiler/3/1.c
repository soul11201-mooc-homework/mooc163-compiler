#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Node 
{
    int id;
    char re_c;
    struct _Node  * to;
    // struct _Node  * from;
};

typedef struct _Node  Node;

int node_global_id = 0;


typedef  enum  {RE_BASE,RE_SELECT,RE_CONCAT,RE_CLOSURE}Re_t;
/*
    
    
    ---> 0 --c-- 1   |---->accepted|

 */
typedef struct{
    Re_t kind;
    Node state[2];
}G_Re_t;

typedef struct 
{
    Re_t kind;
    Node state[2];
    // char re_c[2];
}G_BaseRe_t;

G_BaseRe_t * build_obj_of_G_BaseRe(char c)
{
    G_BaseRe_t * g = (G_BaseRe_t *) malloc(sizeof(G_BaseRe_t));

    g->kind = RE_BASE;

    // g->state[0]->id = 0;
    // g->state[0]->from = NULL;
    g->state[0].to   = &(g->state[1]);
    g->state[0].re_c =  c;

    // g->state[1]->id = 1;
    // g->state[1]->from =  &(g->state[0]);
    g->state[1].to =   NULL;

    // g->re_c[0] = c;
    // g->re_c[1] = '\0';

    return g;
}


/*
                         ____
                        /    \
    ----> [0] --e1-- [2]      [3] --e2-- [1]  |---->accepted|
    
    '\0'  伊普西龙转换
 */

typedef struct 
{
    Re_t kind;
    Node state[4];
}G_ConcatRe_t;

G_ConcatRe_t  * build_obj_of_G_ConcatRe_t(G_Re_t * e1,G_Re_t * e2)
{
    G_ConcatRe_t * g =  (G_ConcatRe_t *) malloc ( sizeof ( G_ConcatRe_t ) ) ;

    g->kind = RE_CONCAT;

    g->state[0].to = &(e1->state[0]);
    g->state[0].re_c = '\0';

    g->state[1].to = NULL;

    g->state[2].to = &(g->state[3]);
    g->state[2].re_c = '\0';

    g->state[3].to = &(e2->state[0]);
    g->state[3].re_c = '\0';


    e1->state[1].to = &(g->state[2]);
    e2->state[1].to = &(g->state[0]);

    return g;
    // e1->state[1]->to =  &(g->state[2]);
    // g->state[0]
}


/*

             2 --e1-- 3
           /            \
    start 0              1    |---->accepted|
           \            /
             4 --e2-- 5 
        
    \ <----->epsilone translate

*/

typedef struct 
{
    Re_t kind;
    Node state[4];
}G_SelectRe_t;

G_SelectRe_t * build_obj_of_G_SelectRe_t(G_Re_t* e1,G_Re_t * e2)
{

    G_SelectRe_t * g = (G_SelectRe_t *) malloc(sizeof(G_SelectRe_t));

    
    
}



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
    Re_t kind;
    Node state[6];
}G_ClosureRe_t;

G_ClosureRe_t * build_obj_of_G_ClosureRe_t(G_Re_t * e1)
{

}

/*
   特殊符号  ( )  |   *
*/

// G_Re_t * build_nfa_with_Lpara(const char * re,int len)
// {

// }


// G_Re_t * Re_Stack[100];
// int Re_Stack_index = 0;

G_Re_t *  build_nfa(const char * re,int len)
{
   
    // char c = re[0];
    // int index = 1;
    // char next_c = re[index];
    // G_Re_t * g;

    // if(c != '(' && c != ')' && c != '|' && c != '*')
    // {
    //     // 字符集
    //     g = (G_Re_t *) build_obj_of_G_BaseRe(c);


    //     //和下一个字符左结合成一个整体
    //     if(next_c == '*')
    //     {
    //         g = build_obj_of_G_ClosureRe_t(g);
    //         ++ index;
    //         next_c = re[index];
    //     }

    //     // 右结合没有问题
    //     if(next_c != '|' && next_c != '*')
    //     {
    //         return (G_Re_t *) build_obj_of_G_ConcatRe_t(g,build_nfa(re + index, len - index )) ;
    //     }

    // }
    // else if(c == '(')
    // {
    //     int lp = 1;
    //     int i =0

    //     for(i = 1;i < len && lp != 0 ; ++i)
    //     {
    //         switch(re[i])
    //         {
    //             case ')':
    //                 -- lp;
    //                 break;
    //             case '(':
    //                 ++ lp;
    //                 break;
    //         }
    //     }

    //     g = build_nfa(re + 1, len - 2);

    
    //     next_c = re[i+1]
    
    //     if(next_c == '|')
    //     {
    //         return  (G_Re_t *)  build_obj_of_G_SelectRe_t(g,build_nfa(re + 1,len - 1));
    //     }
    //     else if (next_c == '*')
    //     {
    //         g =   (G_Re_t *) build_obj_of_G_ClosureRe_t(g);
    //     }

    // }
    // else if(c == '|')
    // {
    //     if(c != '(' && c != ')' && c != '|' && c != '*')
    //     {

    //     }            
    // }
    // char c;
    // char stack[100];
    // int top = 0;
    // char stack_top_ele;
    // for(int i = len -1 ; ~ i; --i)
    // {
    //     c = re[i];

    //     if(c != '(' && c != ')' && c != '|' && c != '*')
    //     {
    //         if(top > 0 ){
    //             stack_top_ele = stack[top - 1];
    //         }else{
                
    //             Re_Stack[Re_Stack_index ++] = (G_Re_t*)build_obj_of_G_BaseRe(c);
    //         }

    //     }else{

    //     }
    // }

}

int main(int argc, char const *argv[])
{
    char  re[] = "a(b|c)*";


    // G_Re_t * g = build_nfa(re, strlen(re));
    // 
    // 
    G_Re_t * g =(G_Re_t *) build_obj_of_G_ConcatRe_t(
                    (G_Re_t *)build_obj_of_G_BaseRe('a'),
                    (G_Re_t *)build_obj_of_G_ClosureRe_t(
                            (G_Re_t *)build_obj_of_G_SelectRe_t(
                                (G_Re_t *)build_obj_of_G_BaseRe('b'),
                                (G_Re_t *)build_obj_of_G_BaseRe('c'))));
    return 0;
}