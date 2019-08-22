//
// Created by william on 19-3-14.
//

#ifndef NUSMV_PRINTINFO_H
#define NUSMV_PRINTINFO_H

//#include "utils/OStream.h"
//#include "utils/StreamMgr.h"
//#include "utils/Logger.h"
//#include "node/NodeMgr.h"
//#include "utils/ErrorMgr.h"
//#include "node/printers/MasterPrinter.h"
#include "mc/mc.h"
#include "mc/mcInt.h"

#include "parser/symbols.h"
#include "utils/error.h"
#include "compile/symb_table/SymbTable.h"
//#include "wff/wff.h"


char *myitoa(int num,char *str,int radix);
char *search_str(int n);
void bst_print_dot_aux(struct node* node, FILE* stream,char* last_str,int index);
void bst_print_dot(struct node * tree, FILE* stream);


//go可以代替底下的4条
//read_model
//flatten_hierarchy
//encode_variabes
//build_model

#endif //NUSMV_PRINTINFO_H