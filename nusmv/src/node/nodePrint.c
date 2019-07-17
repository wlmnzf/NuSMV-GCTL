/**CFile***********************************************************************

  FileName    [nodePrint.c]

  PackageName [node]

  Synopsis    [Pretty prints a node struct.]

  Description [This function pretty print a node struct, in a way
  similar to a s-expression in LISP.]

  SeeAlso     []

  Author      [Marco Roveri]

  Copyright   [
  This file is part of the ``node'' package of NuSMV version 2.
  Copyright (C) 1998-2001 by CMU and ITC-irst.

  NuSMV version 2 is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  NuSMV version 2 is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.

  For more information on NuSMV see <http://nusmv.irst.itc.it>
  or email to <nusmv-users@irst.itc.it>.
  Please report bugs to <nusmv-users@irst.itc.it>.

  To contact the NuSMV development board, email to <nusmv@irst.itc.it>. ]

******************************************************************************/
#include "nodeInt.h"
#include "parser/mbp_symbols.h"
#include "utils/ustring.h"
#include "utils/WordNumber.h" /* for WordNumber_ptr printing */

static char UTIL_UNUSED rcsid[] = "$Id: nodePrint.c,v 1.7.4.3.2.1.2.21.4.3 2007/05/09 14:25:03 nusmv Exp $";

/*---------------------------------------------------------------------------*/
/* Definition of exported functions                                          */
/*---------------------------------------------------------------------------*/
void print_sexp(FILE *file, node_ptr node)
{
  print_sexp_custom(file, node, (custom_print_sexp_t *)NULL);  
}

/**Function********************************************************************

  Synopsis           [Main node printing function.]

  Description        [In order to allow handling of unknown node types
  (for example, to print expressions based on any SMV extension), one can
  specify an <i>external</i> recursion function. On unknown node types 
  this external function is supposed to return true iff an exception
  occurred on handling of external node types. In such cases an
  <i>un-handled</i> message type is generated.]

  SideEffects        []

  SeeAlso            [print_sexp]

******************************************************************************/
void print_sexp_custom(FILE *file, node_ptr node, custom_print_sexp_t cps_fun)
{
  /*  if(!node)return; */
  if(node == (node_ptr)(-1)) {
    fprintf(file,"No value");
    return;
  }
  if (node == Nil) {
    fprintf(file," Nil ");
    return;
  }
  switch(node_get_type(node)){
  case MODULE:
    fprintf(file,"\n(MODULE ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,") ");
    break;
  case GAME:
    fprintf(file,"\n(GAME ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,") ");
    break;
  case PLAYER:
    fprintf(file,"\n(PLAYER %d ", NODE_TO_INT(car(node)));
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,") ");
    break;
  case MODTYPE:
    fprintf(file,"\n(MODTYPE ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case CASE:
    fprintf(file,"\n(CASE ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case CONS:
    fprintf(file,"\n(CONS ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    /*
    print_sexp_list(file,node);
    */
    break;
  case VAR:
    fprintf(file,"\n(VAR ");
    if ((car(node) != Nil) && (cdr(node) != Nil)) {
      fprintf(file,"(CAR ");
      fprintf(file,"(BDD TO BE PRINTED)");
      fprintf(file,")(CDR ");
      print_sexp_custom(file,cdr(node),cps_fun);
      fprintf(file,")");
    } else if (cdr(node) != Nil) {
      fprintf(file,"(CDR ");
      print_sexp_custom(file,cdr(node),cps_fun);
      fprintf(file,")");
      } else print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case ASSIGN:
    fprintf(file,"\n(ASSIGN ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case INVAR:
    fprintf(file,"\n(INVAR ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case TRANS:
    fprintf(file,"\n(TRANS ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case INIT:
    fprintf(file,"\n(INIT ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case SPEC:
    fprintf(file,"\n(SPEC ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case LTLSPEC:
    fprintf(file,"\n(SPEC ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case INVARSPEC:
    fprintf(file,"\n(SPEC ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case COMPUTE:
    fprintf(file,"\n(COMPUTE ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case PSLSPEC:
    fprintf(file,"\n(PSL specification)");
    break;
  case CONSTANTS:
    fprintf(file,"\n(CONSTANTS ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case REACHTARGET:
    fprintf(file,"\n(REACHTARGET of %d ", NODE_TO_INT(car(node)));
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case AVOIDTARGET:
    fprintf(file,"\n(AVOIDTARGET of %d ", NODE_TO_INT(car(node)));
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case REACHDEADLOCK :
    fprintf(file,"\n(REACHDEADLOCK of %d ", NODE_TO_INT(car(node)));
    fprintf(file,")");
    break;
  case AVOIDDEADLOCK:
    fprintf(file,"\n(AVOIDDEADLOCK of %d ", NODE_TO_INT(car(node)));
    fprintf(file,")");
    break;
  case BUCHIGAME:
    fprintf(file,"\n(BUCHIGAME of %d ", NODE_TO_INT(car(node)));
    print_sexp_custom(file, cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case GENREACTIVITY:
    fprintf(file,"\n(GENREACTIVITY of %d ", NODE_TO_INT(car(node)));
    print_sexp_custom(file, cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case MBP_SPEC_WRAPPER:
    fprintf(file,"\n(MBP_SPEC_WRAPPER ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,") ");
    break;
  case MBP_EXP_LIST:
    fprintf(file,"(");
    print_sexp_custom(file, car(node),cps_fun);
    fprintf(file,")");
    break;
  case MBP_TWO_EXP_LISTS:
    fprintf(file,"(");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,") -> (");
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;

  case FAILURE:
    fprintf(file, "(FAILURE line = %d, message = \"%s\", kind = %d)",
	    failure_get_lineno(node),
	    failure_get_msg(node), 
	    failure_get_kind(node));
    break;
  case ATOM:
    {
      string_ptr tmp_strp = (string_ptr) car(node);
      char * str = (char *) tmp_strp->text;
      fprintf(file,"(ATOM %s)",str);
      break;
    }
  case NUMBER:
    {
      int num = NODE_TO_INT(car(node));
      fprintf(file,"\n(NUMBER %d)",num);
      break;
    }
  case NUMBER_WORD:
    {
      fprintf(file,"\n(NUMBER_WORD ");
      WordNumber_print(file, WORD_NUMBER(car(node)));
      fprintf(file,")");
      break;
    }
  case NUMBER_REAL:
    {
      const char* num = get_text((string_ptr)car(node));
      fprintf(file,"\n(NUMBER_REAL %s)",num);
      break;
    }
  case NUMBER_FRAC:
    {
      const char* num = get_text((string_ptr)car(node));
      fprintf(file,"\n(NUMBER_FRAC %s)",num);
      break;
    }
  case NUMBER_EXP:
    {
      const char* num = get_text((string_ptr)car(node));
      fprintf(file,"\n(NUMBER_EXP %s)",num);
      break;
    }
  case TRUEEXP:
    {
      fprintf(file,"(TRUE)");
      break;
    }
  case FALSEEXP:
    {
      fprintf(file,"(FALSE)");
      break;
    }
  case BIT:
    {
      int num = NODE_TO_INT(cdr(node));
      fprintf(file,"\n(BIT ");
      print_sexp_custom(file, car(node), cps_fun);
      fprintf(file," %d)", num);
      break;
    }
  case BOOLEAN:
    fprintf(file,"(BOOLEAN)");
    break;
  case INTEGER:
    fprintf(file,"(INT)");
    break;
  case REAL:
    fprintf(file,"(REAL)");
    break;
  case WORD:
    fprintf(file,"(WORD ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case SELF:
    fprintf(file,"(SELF)");
    break;
  case SCALAR:
    fprintf(file,"(SCALAR ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case ARRAY:
    fprintf(file,"\n(ARRAY ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,") ");
    break;
  case DOT:
    fprintf(file,"(DOT ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case CONCATENATION:
    fprintf(file,"(CONCATENATION ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case BIT_SELECTION:
    fprintf(file,"(BIT_SELECTION ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,car(cdr(node)),cps_fun);
    print_sexp_custom(file,cdr(cdr(node)),cps_fun);
    fprintf(file,")");
    break;
  case CAST_BOOL:
    fprintf(file,"(CAST_BOOL ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case CAST_WORD1:
    fprintf(file,"(CAST_WORD1 ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case TWODOTS:
    fprintf(file,"\n(TWODOTS ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case COLON:
    fprintf(file,"\n(COLON ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case EQDEF:
    fprintf(file,"\n\t(EQDEF ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case NEXT:
    fprintf(file,"\n(NEXT (");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")) ");
    break;
  case SMALLINIT:
    fprintf(file,"\n(SMALLINIT ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case AND:
    fprintf(file,"\n(AND ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case OR:
    fprintf(file,"\n(OR ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case XOR:
    fprintf(file,"\n(XOR ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case XNOR:
    fprintf(file,"\n(XNOR ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case IMPLIES:
    fprintf(file,"\n(IMPLIES ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case IFF:
    fprintf(file,"\n(IFF ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case NOT:
    fprintf(file,"\n(NOT ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case EX:
    fprintf(file,"\n(EX ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case AX:
    fprintf(file,"\n(AX ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case EF:
    fprintf(file,"\n(EF ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case AF:
    fprintf(file,"\n(AF ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case EG:
    fprintf(file,"\n(EG ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case AG:
    fprintf(file,"\n(AG ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case OP_GLOBAL:
    fprintf(file,"\n(G ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case OP_HISTORICAL:
    fprintf(file,"\n(H ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case RELEASES:
    fprintf(file,"\n(V ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case TRIGGERED:
    fprintf(file,"\n(T ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case UNTIL:
    fprintf(file,"\n(U ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case SINCE:
    fprintf(file,"\n(S ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case OP_NEXT:
    fprintf(file,"\n(X ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case OP_PREC:
    fprintf(file,"\n(Y ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case OP_NOTPRECNOT:
    fprintf(file,"\n(Z ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case OP_FUTURE:
    fprintf(file,"\n(F ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case OP_ONCE:
    fprintf(file,"\n(O ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case AU:
    fprintf(file,"\n(AU ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case EU:
    fprintf(file,"\n(EU ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case EBF:
    fprintf(file,"\n(EBF ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case ABF:
    fprintf(file,"\n(ABF ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case EBG:
    fprintf(file,"\n(EBG ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case ABG:
    fprintf(file,"\n(ABG ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case ABU:
    fprintf(file,"\n(ABU ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case EBU:
    fprintf(file,"\n(EBU ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case LSHIFT:
    fprintf(file,"\n(LSHIFT ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case RSHIFT:
    fprintf(file,"\n(RSHIFT ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case LROTATE:
    fprintf(file,"\n(LROTATE ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case RROTATE:
    fprintf(file,"\n(RROTATE ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case WORDARRAY:
    fprintf(file,"\n(WORDARRAY ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case WAREAD:
    fprintf(file,"\n(WAREAD ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case WAWRITE:
    fprintf(file,"\n(WAWRITE ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case PLUS:
    fprintf(file,"\n(PLUS ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case MINUS:
    fprintf(file,"\n(MINUS ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case UMINUS:
    fprintf(file,"\n(UMINUS ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case TIMES:
    fprintf(file,"\n(TIMES ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case DIVIDE:
    fprintf(file,"\n(DIVIDE ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case MOD:
    fprintf(file,"\n(MOD ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case EQUAL:
    fprintf(file,"\n(EQUAL ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case NOTEQUAL:
    fprintf(file,"\n(NOTEQUAL ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case LT:
    fprintf(file,"\n(LT ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case GT:
    fprintf(file,"\n(GT ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case LE:
    fprintf(file,"\n(LE ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case GE:
    fprintf(file,"\n(GE ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case UNION:
    fprintf(file,"\n(UNION ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case SETIN:
    fprintf(file,"\n(SETIN ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case MINU:
    fprintf(file,"\n(MINU ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case MAXU:
    fprintf(file,"\n(MAXU ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case PROCESS:
    fprintf(file,"\n(PROCESS ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case FAIRNESS:
    fprintf(file,"\n(FAIRNESS ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case ISA:
    fprintf(file,"\n(ISA ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case DEFINE:
    fprintf(file,"\n(DEFINE ");
    print_sexp_custom(file,car(node),cps_fun);
    fprintf(file,")");
    break;
  case CONTEXT:
    fprintf(file,"\n(CONTEXT ");
    print_sexp_custom(file,car(node),cps_fun);
    print_sexp_custom(file,cdr(node),cps_fun);
    fprintf(file,")");
    break;
  case BDD:
    /* print_bdd(file,(bdd_ptr)car(node)); */
    fprintf(file,"(BDD TO BE PRINTED)");
    break;
  case SEMI:
    fprintf(file, "\n(SEMI ");
    print_sexp_custom(file, car(node), cps_fun);
    print_sexp_custom(file, cdr(node), cps_fun);
    fprintf(file, ")\n");
    break;
  case IFTHENELSE:
    fprintf(file, "\n (IFTHENELSE ");
    print_sexp_custom(file, car(node), cps_fun);
    print_sexp_custom(file, cdr(node), cps_fun);
    fprintf(file, ")\n");
    break;
  default:
    if(
       node_get_type(node) <= NUSMV_CORE_SYMBOL_LAST
       || cps_fun==(custom_print_sexp_t *)NULL 
       || cps_fun(file,node)
       ){
	fprintf(file,"\n\n ********* No Match \n");
	fprintf(file,"********** Descriptor: %d \n", node_get_type(node));
      }
    break;
  }
  fprintf(file, "\n");
}


