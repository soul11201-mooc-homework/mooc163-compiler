/*************************************************************************
	> File Name: gen-tac.h
	> Author: soul11201
	> Mail: soul11201@gmail.com
	> Created Time: 2017年05月07日 星期日 15时29分00秒
 ************************************************************************/

#ifndef _GEN_TAC_H
#define _GEN_TAC_H

#include "ast.h"
#include "tac.h"
#include "list.h"
#include <string.h>

IR_Tac_Prog_instr_t gen_tac(Prog_t);


// 模拟  hashtable  将源程序中的变量转化成临时变量================================
typedef struct IR_Tac_tmp_var_table_t* IR_Tac_tmp_var_table_t;
struct IR_Tac_tmp_var_table_t
{
	char * key;
	int id_code;
};

IR_Tac_tmp_var_table_t IR_Tac_tmp_var_table_new(char* key, int id_code);

int IR_Tac_tmp_var_table_set(char *key);
int IR_Tac_tmp_var_table_get_id_code(char* key);
void IR_Tac_tmp_var_table_print(List_t hashtable);

// 模拟  hashtable ================================
#endif
