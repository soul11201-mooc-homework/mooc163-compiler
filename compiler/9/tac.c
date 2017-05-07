/*************************************************************************
	> File Name: tac.c
	> Author: soul11201
	> Mail: soul11201@gmail.com
	> Created Time: 2017年05月07日 星期日 11时47分13秒
 ************************************************************************/

#include "tac.h"

#define MACRO_TAC_INSTR_NEW(instr_type,func_name,instr_kind) \
    instr_type func_name(char *x, char *y, char *z)\
    { \
        instr_type p = malloc(sizeof(*p)); \
        p->kind = instr_kind; \
        p->x = x;\
        p->y = y;\
        p->z = z;\
        return p;\
    }\


MACRO_TAC_INSTR_NEW(IR_Tac_Add_instr_t, IR_Tac_Add_instr_new, IR_TAC_KIND_ADD)
MACRO_TAC_INSTR_NEW(IR_Tac_Minus_instr_t, IR_Tac_Minus_instr_new, IR_TAC_KIND_MINUS)
MACRO_TAC_INSTR_NEW(IR_Tac_Mul_instr_t, IR_Tac_Mul_instr_new, IR_TAC_KIND_MUL)
MACRO_TAC_INSTR_NEW(IR_Tac_Div_instr_t, IR_Tac_Div_instr_new, IR_TAC_KIND_DIV)
MACRO_TAC_INSTR_NEW(IR_Tac_And_instr_t, IR_Tac_And_instr_new, IR_TAC_KIND_AND)
MACRO_TAC_INSTR_NEW(IR_Tac_Or_instr_t, IR_Tac_Or_instr_new, IR_TAC_KIND_OR)

//IR_Tac_Add_instr_t IR_Tac_Add_instr_new(char * x, char *y, char *z)
//{
//    IR_Tac_Add_instr_t p = malloc(sizeof(*p));
//    p->kind = IR_TAC_KIND_ADD;
//    p->x = x;
//    p->y = y;
//    p->z = z;
//}


