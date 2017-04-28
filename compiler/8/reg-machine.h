#ifndef Reg_MACHINE_H
#define Reg_MACHINE_H


#include "list.h"

/////////////////////////////////////
// instructions
enum Reg_Instr_Kind_t{
  Reg_INSTR_MOV,
  Reg_INSTR_MOVN,
  Reg_INSTR_LOAD,
  Reg_INSTR_STORE,
  Reg_INSTR_ADD,
  Reg_INSTR_SUB,
  Reg_INSTR_TIMES,
  Reg_INSTR_DIV, 
  Reg_INSTR_AND, 
  Reg_INSTR_OR, 
  Reg_INSTR_PRINTI,
  Reg_INSTR_PRINTB
};
typedef int Reg_t;

typedef struct Reg_Instr_t *Reg_Instr_t;
struct Reg_Instr_t
{
  enum Reg_Instr_Kind_t kind;
};
void Reg_Instr_print (Reg_Instr_t);

// mov n
typedef struct Reg_Instr_Movn *Reg_Instr_Movn;
struct Reg_Instr_Movn
{
  enum Reg_Instr_Kind_t kind;
  int n;
  Reg_t r;
};
Reg_Instr_t Reg_Instr_Movn_new (int n, Reg_t);

// load x
typedef struct Reg_Instr_Load *Reg_Instr_Load;
struct Reg_Instr_Load
{
  enum Reg_Instr_Kind_t kind;
  char * var_name;
  Reg_t r;
};
Reg_Instr_t Reg_Instr_Load_new (char *, Reg_t);

// store x
typedef struct Reg_Instr_Store *Reg_Instr_Store;
struct Reg_Instr_Store
{
  enum Reg_Instr_Kind_t kind;
  char * var_name;
  Reg_t r;
};
Reg_Instr_t Reg_Instr_Store_new (char *, Reg_t);

typedef struct Reg_inster_binary_oprator * Reg_inster_binary_oprator;
struct Reg_inster_binary_oprator
{
  enum Reg_Instr_Kind_t kind;
  Reg_t r1;
  Reg_t r2;
  Reg_t r;
};

// add
typedef Reg_inster_binary_oprator Reg_Instr_Add;
Reg_Instr_t Reg_Instr_Add_new (Reg_t r1, Reg_t r2, Reg_t r);

// sub
typedef Reg_inster_binary_oprator Reg_Instr_Sub;
Reg_Instr_t Reg_Instr_Sub_new (Reg_t r1, Reg_t r2, Reg_t r);

// times
typedef Reg_inster_binary_oprator Reg_Instr_Times;
Reg_Instr_t Reg_Instr_Times_new (Reg_t r1, Reg_t r2, Reg_t r);

// div
typedef Reg_inster_binary_oprator Reg_Instr_Div;
Reg_Instr_t Reg_Instr_Div_new (Reg_t r1, Reg_t r2, Reg_t r);

// and
typedef Reg_inster_binary_oprator Reg_Instr_And;
Reg_Instr_t Reg_Instr_And_new (Reg_t r1, Reg_t r2, Reg_t r);

// or
typedef Reg_inster_binary_oprator Reg_Instr_Or;
Reg_Instr_t Reg_Instr_Or_new (Reg_t r1, Reg_t r2, Reg_t r);


// printi
typedef struct Reg_Instr_Printi *Reg_Instr_Printi;
struct Reg_Instr_Printi
{
  enum Reg_Instr_Kind_t kind;
  Reg_t r;
};
Reg_Instr_t Reg_Instr_Printi_new (Reg_t);

// printb
typedef struct Reg_Instr_Printb *Reg_Instr_Printb;
struct Reg_Instr_Printb
{
  enum Reg_Instr_Kind_t kind;
  Reg_t r;
};
Reg_Instr_t Reg_Instr_Printb_new (Reg_t);

/////////////////////////////////////
// prog
typedef struct Reg_Prog_t *Reg_Prog_t;
struct Reg_Prog_t{
  List_t ids;  // List_t<char *>
  List_t instrs;   // List_t<Stm_t>
};
Reg_Prog_t Reg_Prog_new (List_t, List_t);
void Reg_Prog_print (Reg_Prog_t);

#endif
