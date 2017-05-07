/*************************************************************************
	> File Name: tac.h
	> Author: soul11201
	> Mail: soul11201@gmail.com
	> Created Time: 2017年05月07日 星期日 11时26分09秒
 ************************************************************************/

#ifndef _TAC_H
#define _TAC_H
#include<stdio.h>
#include<stdlib.h>
#include "list.h"

typedef enum {
    IR_TAC_KIND_CONST,
    IR_TAC_KIND_MOVE,
    IR_TAC_KIND_ADD,
    IR_TAC_KIND_MINUS,
    IR_TAC_KIND_MUL,
    IR_TAC_KIND_DIV,
    IR_TAC_KIND_OR,
    IR_TAC_KIND_AND,
} IR_Tac_Kind_t;

typedef struct IR_Tac_instr_t* IR_Tac_instr_t;

struct IR_Tac_instr_t{
    IR_Tac_Kind_t kind;
};

typedef struct IR_Tac_Add_instr_t* IR_Tac_Add_instr_t;

struct IR_Tac_Add_instr_t{
  IR_Tac_Kind_t kind;
  char *x;
  char *y;
  char *z;
};

IR_Tac_Add_instr_t IR_Tac_Add_instr_new(char *, char *, char *);

typedef IR_Tac_Add_instr_t IR_Tac_Minus_instr_t;
IR_Tac_Add_instr_t IR_Tac_Minus_instr_new(char *, char *, char *);

typedef IR_Tac_Add_instr_t IR_Tac_Mul_instr_t;
IR_Tac_Add_instr_t IR_Tac_Mul_instr_new(char *, char *, char *);

typedef IR_Tac_Add_instr_t IR_Tac_Div_instr_t;
IR_Tac_Add_instr_t IR_Tac_Div_instr_new(char *, char *, char *);

typedef IR_Tac_Add_instr_t IR_Tac_Or_instr_t;
IR_Tac_Add_instr_t IR_Tac_Or_instr_new(char *, char *, char *);

typedef IR_Tac_Add_instr_t IR_Tac_And_instr_t;
IR_Tac_Add_instr_t IR_Tac_And_instr_new(char *, char *, char *);


typedef struct IR_Tac_Prog_instr_t *IR_Tac_Prog_instr_t;
struct IR_Tac_Prog_instr_t
{
  // tac declare
  List_t ids;

  // tac instrctions
  List_t instrs;
};

IR_Tac_Prog_instr_t IR_Tac_Prog_instr_new(List_t , List_t)
void IR_Tac_Prog_instr_print(IR_Tac_Prog_instr_t);

#endif

