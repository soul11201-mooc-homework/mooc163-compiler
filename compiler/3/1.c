#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node 
{
    int id;
    char re_c;
    struct _Node  * to;
    // struct _Node  * from;
}Node;

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
    Re_t kind
    Node state[2];
    // char re_c[2];
}G_BaseRe_t;

G_BaseRe_t * build_obj_of_G_BaseRe(char c)
{
    G_BaseRe_t * g = (G_BaseRe_t *) malloc(sizeof(G_BaseRe_t));

    g->kind = RE_BASE;

    // g->state[0]->id = 0;
    // g->state[0]->from = NULL;
    g->state[0]->to =     &(g->state[1])
    g->state[0]->re_c = c;

    // g->state[1]->id = 1;
    // g->state[1]->from =  &(g->state[0]);
    g->state[1]->to =   NULL;

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

    g->state[0]->to = &(e1->state[0]);
    g->state[0]->re_c = '\0';

    g->state[1]->to = null;

    g->state[2]->to = &(g->state[3])
    g->state[2]->re_c = '\0';

    g->state[3]->to = &(e2->state[0])
    g->state[3]->re_c = '\0';


    e1->state[1]->to = &(g->state[2])
    e2->state[1]->to = &(g->state[0])

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


/*
   特殊符号  ( )  |   *
*/

G_Re_t *  build_nfa(const char * re,int len)
{
    char lp = 0;
    char c = re[0];

    switch(c)
    {
        case '(':
        {
            ++ lp;
            int i = 1;
            for( i = 1;i< len && lp != 0;++i)
            {
                switch(re[i])
                {
                    case ')':
                        -- lp;
                        break;
                    case '(':
                        ++ lp;
                        break;
                }
            }
            build_nfa(re + 1,  i - 1);
            break;
        }
        case '*':
        {
            break;
        }
        case '|':
        {
            break;
        }
        default:
        {
            G_Re_t * g= build_nfa(re + 1,len - 1)
            // switch(g->kind){
            //     case RE_BASE:{
            //         g = (G_BaseRe_t *)g
            //         break;
            //     }
            //     case RE_CONCAT:{
            //         g = ()g
            //         break;
            //     }
            //     case RE_CLOSURE:{
            //         g = ()g
            //         break;
            //     }
            //     case RE_SELECT:{
            //         g = ()g
            //         break;
            //     }

            // }
            G_BaseRe_t * b = build_obj_of_G_BaseRe(c);

            return (G_Re_t *) build_obj_of_G_ConcatRe_t((G_Re_t * )b,g)
        }
   }
}

int main(int argc, char const *argv[])
{
    char * re = "a(b|c)*";
    G_Re_t * g = build_nfa(re, strlen(re));

    
    return 0;
}