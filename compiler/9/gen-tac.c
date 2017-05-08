#include "gen-tac.h"

static List_t instrs = 0;

List_t IR_Tac_gen_decs(List_t decs)
{
    List_t ids = 0;

    while(decs)
    {
        Dec_t d = (Dec_t)decs->data;
        ids = List_new(d->id, ids);
        decs = decs->next;
    }

    return ids;
}

List_t IR_Tac_gen_stm(Stm_t stm)
{
	switch(stm->kind)
	{

	}
}

List_t IR_Tac_gen_stms(List_t stms)
{
	while(stms)
	{
		IR_Tac_gen_stm((Stm_t) stms->data);
		stms = stms->next;
	}
	return instrs;
}



IR_Tac_Prog_instr_t gen_tac(Prog_t prog)
{
    List_t dec_ids = IR_Tac_gen_decs(prog->decs);
    

    List_t instrs = IR_Tac_gen_stms(prog->stms);

    return IR_Tac_Prog_instr_new(List_rev(dec_ids), List_rev(instrs));
}

