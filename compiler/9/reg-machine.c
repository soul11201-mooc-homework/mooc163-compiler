#include <stdio.h>
#include <stdlib.h>
#include "reg-machine.h"

/////////////////////////////////////
// instructions

void Reg_Instr_print (Reg_Instr_t s)
{
  switch(s->kind){
  case Reg_INSTR_MOVN:{

    Reg_Instr_Movn p = (Reg_Instr_Movn)s;
    printf ("movn %d, r%d", p->n, p->r);
    break;
  }
  case Reg_INSTR_LOAD:{
    Reg_Instr_Load p = (Reg_Instr_Load)s;
    printf ("mov %s,r%d", p->var_name, p->r);
    break;
  }
  case Reg_INSTR_STORE:{
    Reg_Instr_Store p = (Reg_Instr_Store)s;
    printf ("mov r%d %s", p->r, p->var_name);
    break;
  }
  case Reg_INSTR_ADD:{
    Reg_Instr_Add p = (Reg_Instr_Add)s;
    printf ("add r%d, r%d, r%d", p->r1, p->r2, p->r);
    break;
  }
  case Reg_INSTR_SUB:{
    Reg_Instr_Sub p = (Reg_Instr_Sub)s;
    printf ("sub r%d, r%d, r%d", p->r1, p->r2, p->r);
    break;
  }
  case Reg_INSTR_TIMES:{
    Reg_Instr_Times p = (Reg_Instr_Times)s;
    printf ("times r%d, r%d, r%d", p->r1, p->r2, p->r);
    break;
  }
  case Reg_INSTR_DIV:{
    Reg_Instr_Div p = (Reg_Instr_Div)s;
    printf ("div r%d, r%d, r%d", p->r1, p->r2, p->r);
    break;
  }
  case Reg_INSTR_AND:{
    Reg_Instr_And p = (Reg_Instr_And)s;
    printf ("and r%d, r%d, r%d", p->r1, p->r2, p->r);
    break;
  }
  
  case Reg_INSTR_OR:{
    Reg_Instr_Or p = (Reg_Instr_Or)s;
    printf ("or r%d, r%d, r%d", p->r1, p->r2, p->r);
    break;
  }

  case Reg_INSTR_PRINTI:{
    Reg_Instr_Printi p = (Reg_Instr_Printi)s;
    printf ("printi r%d", p->r);
    break;
  }
  case Reg_INSTR_PRINTB:{
    Reg_Instr_Printb p = (Reg_Instr_Printb)s;
    printf ("printb r%d", p->r);
    break;
  }
  default:
    break;
  }
}

// mov 
Reg_Instr_t Reg_Instr_Movn_new (int n, Reg_t r)
{
  Reg_Instr_Movn p = malloc (sizeof(*p));
  p->kind = Reg_INSTR_MOVN;
  p->n = n;
  p->r = r;
  return (Reg_Instr_t)p;
}

// load x
Reg_Instr_t Reg_Instr_Load_new (char *x, Reg_t r)
{
  Reg_Instr_Load p = malloc (sizeof(*p));
  p->kind = Reg_INSTR_LOAD;
  p->var_name = x;
  p->r = r;
  return (Reg_Instr_t)p;
}

// store x
Reg_Instr_t Reg_Instr_Store_new (char *x, Reg_t r)
{
  Reg_Instr_Store p = malloc (sizeof(*p));
  p->kind = Reg_INSTR_STORE;
  p->var_name = x;
  p->r = r;
  return (Reg_Instr_t)p;
}

// add
Reg_Instr_t Reg_Instr_Add_new (Reg_t r1, Reg_t r2, Reg_t r)
{
  Reg_Instr_Add p = malloc (sizeof(*p));
  p->kind = Reg_INSTR_ADD;
  p->r1 = r1;
  p->r2 = r2;
  p->r = r;
  return (Reg_Instr_t)p;
}

// sub
Reg_Instr_t Reg_Instr_Sub_new (Reg_t r1, Reg_t r2, Reg_t r)
{
  Reg_Instr_Sub p = malloc (sizeof(*p));
  p->kind = Reg_INSTR_SUB;
  p->r1 = r1;
  p->r2 = r2;
  p->r = r;
  return (Reg_Instr_t)p;
}

// times
Reg_Instr_t Reg_Instr_Times_new (Reg_t r1, Reg_t r2, Reg_t r)
{
  Reg_Instr_Times p = malloc (sizeof(*p));
  p->kind = Reg_INSTR_TIMES;
  p->r1 = r1;
  p->r2 = r2;
  p->r = r;
  return (Reg_Instr_t)p;
}

// div
Reg_Instr_t Reg_Instr_Div_new (Reg_t r1, Reg_t r2, Reg_t r)
{
  Reg_Instr_Div p = malloc (sizeof(*p));
  p->kind = Reg_INSTR_DIV;
  p->r1 = r1;
  p->r2 = r2;
  p->r = r;
  return (Reg_Instr_t)p;
}

// div
Reg_Instr_t Reg_Instr_And_new (Reg_t r1, Reg_t r2, Reg_t r)
{
  Reg_Instr_And p = malloc (sizeof(*p));
  p->kind = Reg_INSTR_AND;
  p->r1 = r1;
  p->r2 = r2;
  p->r = r;
  return (Reg_Instr_t)p;
}

// div
Reg_Instr_t Reg_Instr_Or_new (Reg_t r1, Reg_t r2, Reg_t r)
{
  Reg_Instr_Or p = malloc (sizeof(*p));
  p->kind = Reg_INSTR_OR;
  p->r1 = r1;
  p->r2 = r2;
  p->r = r;
  return (Reg_Instr_t)p;
}


// printi
Reg_Instr_t Reg_Instr_Printi_new (Reg_t r)
{
  Reg_Instr_Printi p = malloc (sizeof(*p));
  p->kind = Reg_INSTR_PRINTI;
  p->r = r;
  return (Reg_Instr_t)p;
}

// printb
Reg_Instr_t Reg_Instr_Printb_new (Reg_t r)
{
  Reg_Instr_Printb p = malloc (sizeof(*p));
  p->kind = Reg_INSTR_PRINTB;
  p->r = r;
  return (Reg_Instr_t)p;
}

///////////////////////////////////////
// prog
Reg_Prog_t Reg_Prog_new (List_t ids, List_t instrs)
{
  Reg_Prog_t p = malloc (sizeof (*p));
  p->ids = ids;
  p->instrs = instrs;
  return p;
}

void Reg_Prog_print (Reg_Prog_t prog)
{
  List_t ids = prog->ids;
  printf ("{\n");
  while (ids){
    char *id = (char *)ids->data;
    printf ("  .int %s\n", id);
    ids = ids->next;
  }

  printf ("\n");

  List_t instrs = prog->instrs;
  while (instrs){
    Reg_Instr_t s = (Reg_Instr_t)instrs->data;
    printf ("  ");
    Reg_Instr_print (s);
    printf ("\n");
    instrs = instrs->next;
  }
  printf ("}\n");
  return;
}


