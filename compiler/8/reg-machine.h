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

typedef struct Reg_Instr_t *Reg_Instr_t;
struct Reg_Instr_t
{
  enum Reg_Instr_Kind_t kind;
};
void Reg_Instr_print (Reg_Instr_t);

// push n
typedef struct Reg_Instr_Push *Reg_Instr_Mov;
struct Reg_Instr_Mov
{
  enum Reg_Instr_Kind_t kind;
  int n;
};
Reg_Instr_t Reg_Instr_Mov_new (int n);

// load x
typedef struct Reg_Instr_Load *Reg_Instr_Load;
struct Reg_Instr_Load
{
  enum Reg_Instr_Kind_t kind;
  char *x;
};
Reg_Instr_t Reg_Instr_Load_new (char *);

// store x
typedef struct Reg_Instr_Store *Reg_Instr_Store;
struct Reg_Instr_Store
{
  enum Reg_Instr_Kind_t kind;
  char * var_name;
};
Reg_Instr_t Reg_Instr_Store_new (char *);

typedef struct Reg_inster_binary_oprator * Reg_inster_binary_oprator;
struct Reg_inster_binary_oprator
{
  enum Reg_Instr_Kind_t kind;
};

// add
typedef struct Reg_inster_binary_oprator Reg_Instr_Add;
Reg_Instr_t Reg_Instr_Add_new ();

// sub
typedef struct Reg_Instr_Sub *Reg_Instr_Sub;
struct Reg_Instr_Sub
{
  enum Reg_Instr_Kind_t kind;
};
Reg_Instr_t Reg_Instr_Sub_new ();

// times
typedef struct Reg_Instr_Times *Reg_Instr_Times;
struct Reg_Instr_Times
{
  enum Reg_Instr_Kind_t kind;
};
Reg_Instr_t Reg_Instr_Times_new ();

// div
typedef struct Reg_Instr_Div *Reg_Instr_Div;
struct Reg_Instr_Div
{
  enum Reg_Instr_Kind_t kind;
};
Reg_Instr_t Reg_Instr_Div_new ();

// and
typedef struct Reg_Instr_And *Reg_Instr_And;
struct Reg_Instr_And
{
  enum Reg_Instr_Kind_t kind;
};
Reg_Instr_t Reg_Instr_And_new ();

// or
typedef struct Reg_Instr_Or *Reg_Instr_Or;
struct Reg_Instr_Or
{
  enum Reg_Instr_Kind_t kind;
};
Reg_Instr_t Reg_Instr_Or_new ();


// printi
typedef struct Reg_Instr_Printi *Reg_Instr_Printi;
struct Reg_Instr_Printi
{
  enum Reg_Instr_Kind_t kind;
};
Reg_Instr_t Reg_Instr_Printi_new ();

// printb
typedef struct Reg_Instr_Printb *Reg_Instr_Printb;
struct Reg_Instr_Printb
{
  enum Reg_Instr_Kind_t kind;
};
Reg_Instr_t Reg_Instr_Printb_new ();

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
