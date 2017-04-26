#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semant.h"
#include "todo.h"

//////////////////////////////////////
// the symbol table
List_t table = 0;

// lookup an "id" in the symbol table.
// return "type" on success; and -1 for failure
Type_t Table_lookup (char *id)
{
  List_t p = table;
  while (p){
    Dec_t d = (Dec_t)p->data;
    if (strcmp(d->id, id)==0)
      return d->type;
    p = p->next;
  }
  return -1;
}

void Table_insert (Dec_t dec)
{
  
  if (Table_lookup (dec->id) != -1){
    fprintf (stderr, "Error: the variable "
	     "\"%s\" has been declared!\n", dec->id);
    exit (0);
  }
  table = List_new (dec, table);
  return;
}

//////////////////////////////////////////
// dec
void check_dec(Dec_t d)
{
  Table_insert (d);
}

void check_decs(List_t decs)
{
  while (decs){
    Dec_t d = (Dec_t)decs->data;
    check_dec(d);
    decs = decs->next;
  }
  return;
}

////////////////////////////////////////
// exp

// Your job:
Type_t check_exp (Exp_t exp)
{
  // TODO();
  switch(exp->kind)
  {
    case EXP_INT:
        return TYPE_INT;
    case EXP_TRUE:
        return TYPE_BOOL;
    case EXP_FALSE: 
        return TYPE_BOOL;
    case EXP_ADD:{
      Exp_Add p = (Exp_Add) exp;
      
      if(check_exp(p->left) != TYPE_INT || check_exp(p->right) != TYPE_INT)
      {
      
        fprintf(stderr, "+ add type mismatch\n");
        exit(0);
      
      } else {
        return TYPE_INT;
      }
    }
      break;
    case EXP_ID:{
      Exp_Id p = (Exp_Id) exp;
      
      Type_t t =  Table_lookup(p->id);
      if(t == -1)
      {
          fprintf(stderr, "Error: the variable "
              " \"%s\" hasn't declared",p->id);
          exit(0);
      }

      return t;

    }
      break;

    case EXP_SUB:{
      Exp_Sub p = (Exp_Sub) exp;
      
      if(check_exp(p->left) != TYPE_INT || check_exp(p->right) != TYPE_INT)
      {
      
        fprintf(stderr, "- type mismatch\n");
        exit(0);
      
      } else {
        return TYPE_INT;
      }
    }
      break;
    case EXP_TIMES:{
      Exp_Times p = (Exp_Times) exp;
      
      if(check_exp(p->left) != TYPE_INT || check_exp(p->right) != TYPE_INT)
      {
      
        fprintf(stderr, "* type mismatch\n");
        exit(0);
      
      } else {
        return TYPE_INT;
      }
    }
      break;
    case EXP_DIVIDE:{
      Exp_Divide p = (Exp_Divide) exp;
      
      if(check_exp(p->left) != TYPE_INT || check_exp(p->right) != TYPE_INT)
      {
      
        fprintf(stderr, "/ type mismatch\n");
        exit(0);
      
      } else {
        return TYPE_INT;
      }
    }
      break;
    case EXP_AND:{
      Exp_And p = (Exp_And) exp;
      
      if(check_exp(p->left) != TYPE_BOOL || check_exp(p->right) != TYPE_BOOL)
      {
      
        fprintf(stderr, "&& type mismatch\n");
        exit(0);
      
      } else {
        return TYPE_BOOL;
      }
    }
      break;
    case EXP_OR:{
      Exp_Or p = (Exp_Or) exp;
      
      if(check_exp(p->left) != TYPE_BOOL || check_exp(p->right) != TYPE_BOOL)
      {
      
        fprintf(stderr, " || type mismatch\n");
        exit(0);
      
      } else {
        return TYPE_BOOL;
      }
    }
      break;

  }
}

////////////////////////////////////////
// stm

// Your job:
void check_stm (Stm_t stm)
{
  // TODO();
  switch (stm->kind){
    case STM_ASSIGN:
    {
      Stm_Assign p = (Stm_Assign) stm;
      
      Type_t id_type;
      id_type = Table_lookup(p->id);

      if(id_type == -1)
      {
        fprintf(stderr, "Error: the variable "
              " \"%s\" hasn't declared",p->id);
        exit(0);
      }
      // printf("%d %s\n",id_type,p->id ); 
      if(id_type != check_exp(p->exp))
      {
        Exp_print(p->exp);
        fprintf(stderr, "= type mismatch\n");
        exit(0);
      }

    }
      break;
    case STM_PRINTI:{
      Stm_Printi p = (Stm_Printi) stm;
      if(check_exp(p->exp) != TYPE_INT)
      {
          Exp_print(p->exp);
          fprintf(stderr, "printi type mismatch\n");
          exit(0);
      }
    }
      break;
    case STM_PRINTB:{
      Stm_Printb p = (Stm_Printb) stm;
      if(check_exp(p->exp) != TYPE_BOOL)
      {
          Exp_print(p->exp);
          fprintf(stderr, "----->printb type mismatch\n");
          exit(0);
      }
    }
      break;
  }
}

void check_stms(List_t stms)
{
  while (stms){
    Stm_t s = (Stm_t)stms->data;
    Stm_print(s);
    printf("\n");
    check_stm(s);
    stms = stms->next;
  }
  return;
  TODO();
}


void Semant_check(Prog_t prog)
{
  // create table
  check_decs(prog->decs);
  // check stm
  check_stms(prog->stms);
  return;
}
