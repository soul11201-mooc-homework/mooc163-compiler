#include "ast.h"
#include <stdio.h>
#include <stdlib.h>


extern Exp_t tree;
void yyparse ();

// Data structures for the Stack language.
enum Stack_Kind_t {
    STACK_ADD,
    STACK_MINUS,
    STACK_DIV,
    STACK_TIMES,
    STACK_PUSH
};


struct Stack_t
{
  enum Stack_Kind_t kind;
};

typedef struct Stack_Add *  Stack_Add;
struct Stack_Add
{
  enum Stack_Kind_t kind;
};

typedef Stack_Add Stack_Minus;
typedef Stack_Add Stack_Times;
typedef Stack_Add Stack_Div;

struct Stack_Push
{
  enum Stack_Kind_t kind;
  int i;
};

// "constructors"
struct Stack_t *Stack_Add_new ()
{
  Stack_Add p = ( Stack_Add ) malloc (sizeof(*p));
  p->kind = STACK_ADD;
  return (struct Stack_t *)p;
}
struct Stack_t *Stack_Minus_new ()
{
  Stack_Minus p = ( Stack_Minus )malloc (sizeof(*p));
  p->kind = STACK_MINUS;
  return (struct Stack_t *)p;
}
struct Stack_t *Stack_Times_new ()
{
  Stack_Times p = (Stack_Times)malloc (sizeof(*p));
  p->kind = STACK_TIMES;
  return (struct Stack_t *)p;
}
struct Stack_t *Stack_Div_new ()
{
  Stack_Div p = (Stack_Div)malloc (sizeof(*p));
  p->kind = STACK_DIV;
  return (struct Stack_t *)p;
}

struct Stack_t *Stack_Push_new (int i)
{
  struct Stack_Push *p = (struct Stack_Push *)malloc (sizeof(*p));
  p->kind = STACK_PUSH;
  p->i = i;
  return (struct Stack_t *)p;
}

/// instruction list
struct List_t
{
  struct Stack_t *instr;
  struct List_t *next;
};

struct List_t *List_new (struct Stack_t *instr, struct List_t *next)
{
  struct List_t *p = (struct List_t *)malloc (sizeof (*p));
  p->instr = instr;
  p->next = next;
  return p;
}

// "printer"
void List_reverse_print (struct List_t *list)
{
  // TODO();
  if(list == NULL){
    printf("\n\nthe Stack instructons: \n");
    return;
  }else{
     List_reverse_print(list->next);
  }
 

  switch(list->instr->kind){
    case STACK_PUSH:{
      struct Stack_Push *p = (struct Stack_Push *)list->instr;
      printf("push %d\n",p->i);
      break;
    }
    case STACK_ADD:{
      printf("add\n");
      break;
    }
    case STACK_MINUS:{
      printf("minus\n");
      break;
    }
    case STACK_TIMES:{
      printf("mul\n");
      break;
    }
     case STACK_DIV:{
      printf("div\n");
      break;
    }
  }

}

//////////////////////////////////////////////////
// a compiler from Sum to Stack
struct List_t *all = 0;

void emit (struct Stack_t *instr)
{
  all = List_new (instr, all);
}

void compile (struct Exp_t *exp)
{
  switch (exp->kind){
  case EXP_INT:{
    struct Exp_Int *p = (struct Exp_Int *)exp;
    emit (Stack_Push_new (p->n));
    break;
  }
  case EXP_ADD:{
    Exp_Add p = (Exp_Add) exp;
    compile(p->left);
    compile(p->right);
    emit(Stack_Add_new());
    // TODO();
    break;
  }
  case EXP_MINUS:{
    Exp_Minus p = (Exp_Minus) exp;
    compile(p->left);
    compile(p->right);
    emit(Stack_Minus_new());
    // TODO();
    break;
  }
  case EXP_TIMES:{
    Exp_Times p = (Exp_Times) exp;
    compile(p->left);
    compile(p->right);
    emit(Stack_Times_new());
    // TODO();
    break;
  }

  case EXP_DIV:{
    Exp_Div p = (Exp_Div) exp;
    compile(p->left);
    compile(p->right);
    emit(Stack_Div_new());
    // TODO();
    break;
  }
  default:
    break;
  }
}

//////////////////////////////////////////
//opt ast

void opt(struct Exp_t *exp)
{
    switch(exp->kind)
    {
        case EXP_ADD:
        {
            Exp_Add p = (Exp_Add )exp;
            opt(p->left);
            opt(p->right);

           

            if(p->left->kind == EXP_INT && p->right->kind == EXP_INT){
              struct Exp_Int * left =( struct Exp_Int * )p->left; 
              struct Exp_Int * right =( struct Exp_Int * )p->right; 
              
              int i = right->n + left->n;
              p->kind = EXP_INT;

              ((struct Exp_Int *)p)->n = i;
            }

        }
            break;
        case EXP_DIV:
        {
            Exp_Div p = (Exp_Div )exp;
            opt(p->left);
            opt(p->right);

           

            if(p->left->kind == EXP_INT && p->right->kind == EXP_INT){
              struct Exp_Int * left =( struct Exp_Int * )p->left; 
              struct Exp_Int * right =( struct Exp_Int * )p->right; 
              
              int i = left->n / right->n;
              p->kind = EXP_INT;

              ((struct Exp_Int *)p)->n = i;
            }

        }
            break;
        case EXP_TIMES:  
        {
            Exp_Times p = (Exp_Times )exp;
            opt(p->left);
            opt(p->right);

           

            if(p->left->kind == EXP_INT && p->right->kind == EXP_INT){
              struct Exp_Int * left =( struct Exp_Int * )p->left; 
              struct Exp_Int * right =( struct Exp_Int * )p->right; 
              
              int i = right->n * left->n;
              p->kind = EXP_INT;

              ((struct Exp_Int *)p)->n = i;
            }
        }
            break;
        case EXP_MINUS:
        {
            Exp_Minus p = (Exp_Minus )exp;
            opt(p->left);
            opt(p->right);

           

            if(p->left->kind == EXP_INT && p->right->kind == EXP_INT){
              struct Exp_Int * left =( struct Exp_Int * )p->left; 
              struct Exp_Int * right =( struct Exp_Int * )p->right; 
              
              int i = left->n - right->n;
              p->kind = EXP_INT;

              ((struct Exp_Int *)p)->n = i;
            }

        }
            break;
        default:
            return;
    };

   
}

//////////////////////////////////////////////////
// program entry
int main()
{
  printf("Compile starting\n");
  // build an expression tree:
  //            +
  //           / \
  //          +   4
  //         / \
  //        2   3
  yyparse();
  Exp_print (tree);
  
#ifdef OPT
  opt(tree);
#endif

  // compile this tree to Stack machine instructions
  compile (tree);

  // print out the generated Stack instructons:
  List_reverse_print (all);

  printf("\nCompile finished\n");
  return 0;
}

