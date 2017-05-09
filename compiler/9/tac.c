/*************************************************************************
	> File Name: tac.c
	> Author: soul11201
	> Mail: soul11201@gmail.com
	> Created Time: 2017年05月07日 星期日 11时47分13秒
 ************************************************************************/

#include "tac.h"

//instr_type func_name(char *x, char *y, char *z)

#define MACRO_TAC_INSTR_NEW(instr_type,func_name,instr_kind) \
    IR_Tac_instr_t func_name(int x, int y, int z)\
    { \
        instr_type p = malloc(sizeof(*p)); \
        p->kind = instr_kind; \
        p->x = x;\
        p->y = y;\
        p->z = z;\
        return (IR_Tac_instr_t) p;\
    }\

MACRO_TAC_INSTR_NEW(IR_Tac_Const_instr_t, IR_Tac_Const_instr_new, IR_TAC_KIND_CONST)
MACRO_TAC_INSTR_NEW(IR_Tac_Move_instr_t, IR_Tac_Move_instr_new, IR_TAC_KIND_MOVE)
MACRO_TAC_INSTR_NEW(IR_Tac_Add_instr_t, IR_Tac_Add_instr_new, IR_TAC_KIND_ADD)
MACRO_TAC_INSTR_NEW(IR_Tac_Minus_instr_t, IR_Tac_Minus_instr_new, IR_TAC_KIND_MINUS)
MACRO_TAC_INSTR_NEW(IR_Tac_Mul_instr_t, IR_Tac_Mul_instr_new, IR_TAC_KIND_MUL)
MACRO_TAC_INSTR_NEW(IR_Tac_Div_instr_t, IR_Tac_Div_instr_new, IR_TAC_KIND_DIV)
MACRO_TAC_INSTR_NEW(IR_Tac_And_instr_t, IR_Tac_And_instr_new, IR_TAC_KIND_AND)
MACRO_TAC_INSTR_NEW(IR_Tac_Or_instr_t, IR_Tac_Or_instr_new, IR_TAC_KIND_OR)


IR_Tac_Prog_instr_t IR_Tac_Prog_instr_new(List_t decs_ids, List_t instrctions)
{
	IR_Tac_Prog_instr_t p = malloc(sizeof(*p));
	p->ids = decs_ids;
	p->instrctions = instrctions;
	return p;
}




void IR_Tac_instr_print(IR_Tac_instr_t s)
{
//	printf("\n tac data: %d %d %d\n",s->x,s->y,s->z);
	switch(s->kind){
		case IR_TAC_KIND_CONST:{
			IR_Tac_Const_instr_t t = (IR_Tac_Const_instr_t) s;
			printf("x_%d = %d\n",t->z,t->x);
			break;
		}
		case IR_TAC_KIND_MOVE:{
			IR_Tac_Move_instr_t t =  (IR_Tac_Move_instr_t) s;
			printf("x_%d = x_%d\n",t->z,t->x);
			break;
		}
		case IR_TAC_KIND_ADD:{
			IR_Tac_Add_instr_t t = (IR_Tac_Add_instr_t) s;
			printf("x_%d = x_%d + x_%d\n",t->z, t->x, t->y);
			break;
		}
		case IR_TAC_KIND_MINUS:{
			IR_Tac_Add_instr_t t = (IR_Tac_Add_instr_t) s;
			printf("x_%d = x_%d + x_%d\n",t->z, t->x, t->y);
			break;
		}
		case IR_TAC_KIND_MUL:{
			IR_Tac_Add_instr_t t = (IR_Tac_Add_instr_t) s;
			printf("x_%d = x_%d + x_%d\n",t->z, t->x, t->y);
			break;
		}
		case IR_TAC_KIND_DIV:{
			IR_Tac_Add_instr_t t = (IR_Tac_Add_instr_t) s;
			printf("x_%d = x_%d + x_%d\n",t->z, t->x, t->y);
			break;
		}
		case IR_TAC_KIND_AND:{
			IR_Tac_Add_instr_t t = (IR_Tac_Add_instr_t) s;
			printf("x_%d = x_%d + x_%d\n",t->z, t->x, t->y);
			break;
		}
		case IR_TAC_KIND_OR:{
			IR_Tac_Add_instr_t t = (IR_Tac_Add_instr_t) s;
			printf("x_%d = x_%d + x_%d\n",t->z, t->x, t->y);
			break;
		}

	}
}

void IR_Tac_tmp_var_table_print(List_t hashtable);

void IR_Tac_Prog_instr_print(IR_Tac_Prog_instr_t tac_prog)
{
	if(!tac_prog)
	{
		fprintf(stderr,"tac_prog is empty\n");
		return;
	}

	List_t ids = tac_prog->ids;
	printf("{\n");
	if(ids)
	{
		IR_Tac_tmp_var_table_print(ids);
	}
	printf ("\n");

	List_t instrs = tac_prog->instrctions;

//	List_t t = instrs;
//	while(t){
//		IR_Tac_instr_t instr = (IR_Tac_instr_t) t->data;
//		printf("\nemit: %d %d %d\n",instr->x,instr->y,instr->z);
//		t = t->next;
//	}

	while (instrs){
		IR_Tac_instr_t s = (IR_Tac_instr_t)instrs->data;
//		printf("\n tac data: %d %d %d\n",s->x,s->y,s->z);
		printf ("  ");
		IR_Tac_instr_print (s);
		printf ("\n");
		instrs = instrs->next;
	}
	printf ("}\n");
	return;

}
//IR_Tac_Add_instr_t IR_Tac_Add_instr_new(char * x, char *y, char *z)
//{
//    IR_Tac_Add_instr_t p = malloc(sizeof(*p));
//    p->kind = IR_TAC_KIND_ADD;
//    p->x = x;
//    p->y = y;
//    p->z = z;
//}


