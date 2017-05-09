#include "gen-tac.h"
#define d() printf("\n==========>>> File:%s Line:%d [%s %s]\n",__FILE__,__LINE__,__DATE__,__TIME__)
static List_t instrs = 0;

static void emit (IR_Tac_instr_t instr)
{
//  printf("\nemit: %d %d %d\n",instr->x,instr->y,instr->z);
  instrs = List_new (instr, instrs);
  return;
}

IR_Tac_tmp_var_table_t IR_Tac_tmp_var_table_new(char* key, int id_code)
{
	IR_Tac_tmp_var_table_t p = malloc(sizeof(*p));
	p->key = key;
	p->id_code = id_code;
	return p;
}

static List_t hashtable = 0;
static int tac_tmp_var_counter = 0;

List_t IR_Tac_tmp_var_table_gen(List_t decs)
{
	while(decs)
	{
		++ tac_tmp_var_counter;
		Dec_t d = (Dec_t)decs->data;
		Dec_print(d);
		hashtable = List_new(IR_Tac_tmp_var_table_new(d->id, tac_tmp_var_counter), hashtable);
		emit(IR_Tac_Const_instr_new(0,0,tac_tmp_var_counter));
		decs = decs->next;
	}

	return hashtable;
}

int IR_Tac_tmp_var_table_gen_one()
{
	++ tac_tmp_var_counter;
	hashtable = List_new(IR_Tac_tmp_var_table_new(0, tac_tmp_var_counter), hashtable);
	return tac_tmp_var_counter;
}

int IR_Tac_tmp_var_table_set(char *key)
{
//	printf("\n tac key: %s\n",key);
	int id_code = IR_Tac_tmp_var_table_get_id_code(key);

	if(id_code > 0)
	{
		fprintf(stderr,"%s has already exists,id_code:%d\n", key, id_code);
		return id_code;
	}

	++ tac_tmp_var_counter;
	hashtable = List_new(IR_Tac_tmp_var_table_new(key, tac_tmp_var_counter), hashtable);
	return tac_tmp_var_counter;
}

int IR_Tac_tmp_var_table_get_id_code(char* key)
{
	List_t tmp = hashtable;

	while(tmp)
	{
		IR_Tac_tmp_var_table_t t = (IR_Tac_tmp_var_table_t) tmp->data;
//		printf("  want:%s but see: %s id_code:%d\n ",key,t->key,t->id_code);
		// 自己給自己挖了一個坑，忘記可以为 0 了表示生成的临时变量，还没有分配名字。有名字的是从声明的变量转化过来的。
		if (t->key != 0 && strcmp(key, t->key) == 0 )
		{
			return t->id_code;
		}
		tmp = tmp->next;
	}
	return -1;
}

void IR_Tac_tmp_var_table_print(List_t hashtable)
{
	printf("\n\n----------- tac tmp_var map------------------------\n\n");
	while(hashtable)
	{
		IR_Tac_tmp_var_table_t t = (IR_Tac_tmp_var_table_t) hashtable->data;
//		printf("x_%d = 0",)
		printf("%s:%d\n",t->key?t->key:"<noname>",t->id_code);
		hashtable = hashtable -> next;
	}
	printf("\n\n----------- tac tmp_var map------------------------\n\n");
}


int IR_Tac_gen_exp(Exp_t exp)
{
//	printf("\nExp_type: %d\n",exp->kind);
	switch(exp->kind)
	{
		case EXP_ID:{
			Exp_Id e = (Exp_Id) exp;
			return  IR_Tac_tmp_var_table_set(e->id);
			break;
		}
		case EXP_INT:{
			Exp_Int e = (Exp_Int) exp;
			int tmp_var_id_code = IR_Tac_tmp_var_table_gen_one();
			emit(IR_Tac_Const_instr_new(e->n,0,tmp_var_id_code));
			return tmp_var_id_code;
			break;
		}
		case EXP_FALSE:{
			int tmp_var_id_code = IR_Tac_tmp_var_table_gen_one();
			emit(IR_Tac_Const_instr_new(0,0,tmp_var_id_code));
			return tmp_var_id_code;
			break;
		}
		case EXP_TRUE:{
			int tmp_var_id_code = IR_Tac_tmp_var_table_gen_one();
			emit(IR_Tac_Const_instr_new(1,0,tmp_var_id_code));
			return tmp_var_id_code;
			break;
		}

		case EXP_ADD:{
			Exp_Add e = (Exp_Add) exp;
			int left_tmp_var_id_code = IR_Tac_gen_exp(e->left);
			int right_tmp_var_id_code = IR_Tac_gen_exp(e->right);
			int tmp_var_id_code = IR_Tac_tmp_var_table_gen_one();
			emit(IR_Tac_Add_instr_new(left_tmp_var_id_code,right_tmp_var_id_code, tmp_var_id_code));
			return tmp_var_id_code;
			break;
		}
		case EXP_SUB:{
			Exp_Sub e = (Exp_Sub) exp;
			int left_tmp_var_id_code = IR_Tac_gen_exp(e->left);
			int right_tmp_var_id_code = IR_Tac_gen_exp(e->right);
			int tmp_var_id_code = IR_Tac_tmp_var_table_gen_one();
			emit(IR_Tac_Minus_instr_new(left_tmp_var_id_code,right_tmp_var_id_code, tmp_var_id_code));
			return tmp_var_id_code;
			break;
		}
		case EXP_TIMES:{
			Exp_Times e = (Exp_Times) exp;
			int left_tmp_var_id_code = IR_Tac_gen_exp(e->left);
			int right_tmp_var_id_code = IR_Tac_gen_exp(e->right);
			int tmp_var_id_code = IR_Tac_tmp_var_table_gen_one();
			emit(IR_Tac_Mul_instr_new(left_tmp_var_id_code,right_tmp_var_id_code, tmp_var_id_code));
			return tmp_var_id_code;
			break;
		}
		case EXP_DIVIDE:{
			Exp_Divide e = (Exp_Divide) exp;
			int left_tmp_var_id_code = IR_Tac_gen_exp(e->left);
			int right_tmp_var_id_code = IR_Tac_gen_exp(e->right);
			int tmp_var_id_code = IR_Tac_tmp_var_table_gen_one();
			emit(IR_Tac_Div_instr_new(left_tmp_var_id_code,right_tmp_var_id_code, tmp_var_id_code));
			return tmp_var_id_code;
			break;
		}
		case EXP_AND:{
			Exp_And e = (Exp_And) exp;
			int left_tmp_var_id_code = IR_Tac_gen_exp(e->left);
			int right_tmp_var_id_code = IR_Tac_gen_exp(e->right);
			int tmp_var_id_code = IR_Tac_tmp_var_table_gen_one();
			emit(IR_Tac_And_instr_new(left_tmp_var_id_code,right_tmp_var_id_code, tmp_var_id_code));
			return tmp_var_id_code;
			break;
		}
		case EXP_OR:{
			Exp_Or e = (Exp_Or) exp;
			int left_tmp_var_id_code = IR_Tac_gen_exp(e->left);
			int right_tmp_var_id_code = IR_Tac_gen_exp(e->right);
			int tmp_var_id_code = IR_Tac_tmp_var_table_gen_one();
			emit(IR_Tac_Or_instr_new(left_tmp_var_id_code,right_tmp_var_id_code, tmp_var_id_code));
			return tmp_var_id_code;
			break;
		}
		default:{
			fprintf(stderr,"error----------------<------");
		}
//		EXPCASE(ADD,Add);
//      麻蛋的，没设计好，不好用宏做代码替换。

	}

}

void IR_Tac_gen_stm(Stm_t stm)
{
//	d();
//	Stm_print(stm);

	switch(stm->kind)
	{
		case STM_ASSIGN:
		{
			Stm_Assign s = (Stm_Assign) stm;
			int exp_tmp_var_code = IR_Tac_gen_exp(s->exp);
			int tmp_var_code = IR_Tac_tmp_var_table_set(s->id);
			emit(IR_Tac_Move_instr_new(exp_tmp_var_code,0,tmp_var_code));
			break;
		}
//		case STM_IF:{
//			Stm_If s = (Stm_If) stm;
//			int exp_tmp_var_code = IR_Tac_gen_exp(s->exp);
//
//			break;
//		}

	}
}

List_t IR_Tac_gen_stms(List_t stms)
{
	while(stms)
	{
		IR_Tac_gen_stm((Stm_t) stms->data);
		stms = stms->next;
	}
//	List_t t = instrs;
//	while(t){
//		IR_Tac_instr_t instr = (IR_Tac_instr_t) t->data;
//		printf("\nemit: %d %d %d\n",instr->x,instr->y,instr->z);
//		t = t->next;
//	}
	return instrs;
}



IR_Tac_Prog_instr_t gen_tac(Prog_t prog)
{
//	printf("=========>>>>>>111111111111\n");
    List_t dec_ids = IR_Tac_tmp_var_table_gen(prog->decs);

//    IR_Tac_tmp_var_table_print(dec_ids);

//    d();

    List_t instrs = IR_Tac_gen_stms(prog->stms);

//    printf("=========>>>>>>22222222222\n");
//    d();

    return IR_Tac_Prog_instr_new(List_rev(hashtable), List_rev(instrs));
}

