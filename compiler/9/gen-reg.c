#include <stdio.h>
#include <stdlib.h>
#include "gen-reg.h"
#include "todo.h"
#include "list.h"



static List_t instrs = 0;
static void emit (Reg_Instr_t instr)
{
  instrs = List_new (instr, instrs);
  return;
}
static Reg_t fresh()
{
    static count = 0;
    return ++ count;
}

////////////////////////////////
// decs
List_t reg_gen_decs (List_t decs)
{
  List_t ids = 0;
  while (decs){
    Dec_t d = (Dec_t)decs->data;
    ids = List_new (d->id, ids);
    decs = decs->next;
  }
  return ids;
}

////////////////////////////////////////
// exp
Reg_t reg_gen_exp (Exp_t exp)
{
  switch (exp->kind){
  case EXP_INT:{
    Exp_Int p = (Exp_Int)exp;
    Reg_t r = fresh();
    emit (Reg_Instr_Movn_new(p->n,r));
    return r;
  }
  case EXP_TRUE:{
    Reg_t r = fresh();
    emit (Reg_Instr_Movn_new (1,r));
    return r;
  }
  case EXP_FALSE:{
    Reg_t r = fresh();
    emit (Reg_Instr_Movn_new (0,r));
    return r;
  }
  case EXP_ID:{
    Exp_Id p = (Exp_Id)exp;
    Reg_t r = fresh();
    emit (Reg_Instr_Load_new(p->id,r));
    return r;
  }
  case EXP_ADD:{
    Exp_Add p = (Exp_Add)exp;
    Reg_t r1 = reg_gen_exp (p->left);
    Reg_t r2 = reg_gen_exp (p->right);
    Reg_t r =  fresh();
    emit (Reg_Instr_Add_new(r1, r2, r));
    return r;
  }
  case EXP_SUB:{
    Exp_Sub p = (Exp_Sub)exp;
    Reg_t r1 = reg_gen_exp (p->left);
    Reg_t r2 = reg_gen_exp (p->right);
    Reg_t r =  fresh();
    emit (Reg_Instr_Sub_new(r1, r2, r));
    return r;
  }
  case EXP_TIMES:{
    Exp_Times p = (Exp_Times)exp;
    Reg_t r1 = reg_gen_exp (p->left);
    Reg_t r2 = reg_gen_exp (p->right);
    Reg_t r =  fresh();
    emit (Reg_Instr_Times_new(r1, r2, r));
    return r;
  }
  case EXP_DIVIDE:{
    Exp_Divide p = (Exp_Divide)exp;
    Reg_t r1 = reg_gen_exp (p->left);
    Reg_t r2 = reg_gen_exp (p->right);
    Reg_t r =  fresh();
    emit (Reg_Instr_Div_new(r1, r2, r));
    return r;
  }
  case EXP_AND:{
    Exp_And p = (Exp_And)exp;
    Reg_t r1 = reg_gen_exp (p->left);
    Reg_t r2 = reg_gen_exp (p->right);
    Reg_t r =  fresh();
    emit (Reg_Instr_And_new(r1, r2, r));
    return r;
  }
  case EXP_OR:{
    Exp_Or p = (Exp_Or)exp;
    Reg_t r1 = reg_gen_exp (p->left);
    Reg_t r2 = reg_gen_exp (p->right);
    Reg_t r =  fresh();
    emit (Reg_Instr_Or_new(r1, r2, r));
    return r;
  }
  default:
    return 0;
  }
}

////////////////////////////////////////
// stms
void reg_gen_stm (Stm_t s)
{
  switch (s->kind){
  case STM_ASSIGN:{
    Stm_Assign p = (Stm_Assign)s;
    Reg_t r =  reg_gen_exp (p->exp);
    emit (Reg_Instr_Store_new (p->id,r));
    break;
  }
  case STM_PRINTI:{
    Stm_Printi p = (Stm_Printi)s;
    Reg_t r =  reg_gen_exp(p->exp);
    emit (Reg_Instr_Printi_new (r));
    break;
  }
  case STM_PRINTB:{
    Stm_Printb p = (Stm_Printb)s;
    Reg_t r =  reg_gen_exp(p->exp);
    emit (Reg_Instr_Printb_new (r));
    break;
  }
  default:
    break;
  }
}

void reg_gen_stms(List_t stms)
{
  while (stms){
    reg_gen_stm((Stm_t)stms->data);
    stms = stms->next;
  }
  return;
}

/////////////////////////////////////////
// prog
Reg_Prog_t Gen_reg(Prog_t prog)
{
  List_t ids = reg_gen_decs (prog->decs);
  instrs = 0;
  reg_gen_stms (prog->stms);
  return Reg_Prog_new (List_rev(ids)
             , List_rev(instrs));
}
