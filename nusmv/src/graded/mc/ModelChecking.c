/******************************************************************************

    File name:
        ModelChecking.c

    Package name:
        graded/mc

    Synopsis:
        Main graded-CTL model checking algorithm.

    Description:
        Main function for the model checking of graded-CTL formulas.
        
    Author:
        Alessandro Ferrante

******************************************************************************/

#include "ModelChecking.h"

static char rcsid[] UTIL_UNUSED = "$Id: ModelChecking.c,v 1.0.3 2008/12/05 08:55:58 nusmv Exp $";

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/
char *myitoa(int num,char *str,int radix)
{
    /* 索引表 */
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned unum; /* 中间变量 */
    int i=0,j,k;
    char temp;
    /* 确定unum的值 */
    if(radix==10&&num<0) /* 十进制负数 */
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else unum=(unsigned)num; /* 其它情况 */
    /* 逆序 */
    do
    {
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;
    }while(unum);
    str[i]='\0';
    /* 转换 */
    if(str[0]=='-') k=1; /* 十进制负数 */
    else k=0;
    /* 将原来的“/2”改为“/2.0”，保证当num在16~255之间，radix等于16时，也能得到正确结果 */

    for(j=k;j<=(i-k-1)/2.0;j++)
    {
        temp=str[j];
        str[j]=str[i-j-1];
        str[i-j-1]=temp;
    }
    return str;
}

char *search_str(int n)
{
    char *enum_kv[167]={
            "NUSMV_STATEMENTS_SYMBOL_FIRST = NUSMV_CORE_SYMBOL_FIRST",


            "TRANS", /* 101 */
            "INIT",
            "INVAR",
            "ASSIGN",
            "FAIRNESS",
            "JUSTICE",
            "COMPASSION",
            "SPEC",
            "LTLSPEC",
            /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
            "CTLGSPEC",/* 110 */
            /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
            "PSLSPEC", /* 110 */
            "INVARSPEC",
            "COMPUTE",
            "DEFINE",
            "ISA",
            "GOTO",
            "CONSTRAINT",
            "MODULE",
            "PROCESS",
            "MODTYPE",
            "LAMBDA", /* 120 */
            "CONSTANTS",

            /* To be moved elsewhere */
            "PRED",
            "PREDS_LIST",
            "MIRROR",


            "NUSMV_STATEMENTS_SYMBOL_LAST",
            /* ---------------------------------------------------------------------- */


            /* ---------------------------------------------------------------------- */
            "NUSMV_EXPR_SYMBOL_FIRST",

            "FAILURE",
            "CONTEXT",//131
            "EU",
            "AU",
            "EBU",
            "ABU",
            "MINU",
            "MAXU",
            "VAR",
            "IVAR", /* 140 */
            "BOOLEAN",
            "ARRAY",
            "OF",
            "SCALAR",
            "CONS",
            "BDD", /* 145 */
            "SEMI",
             "LP",
  "RP",
  "LB",
  "RB",//150
  "LCB",
  "RCB",
            "EQDEF",
            "TWODOTS",
            "FALSEEXP",
            "TRUEEXP", /* 150 */
            "SELF",
            "CASE",
            "ESAC",
            "COLON",
            "IFTHENELSE",
              "INCONTEXT",
            "SIMPWFF", /* 155 */
            "LTLWFF",
            "CTLWFF",
            /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
            "CTLGWFF",
            /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
                        "COMPWFF",
            "ATOM", /* 160 */
            "NUMBER",//161
            "COMMA",
            "IMPLIES",
            "IFF",
            "OR",
            "XOR",
            "XNOR",
            "AND",
            "NOT",//169
            "EX",
            "AX",
            "EF",//172
            "AF",
            "EG",
            "AG",
            "EE",
 "AA",
            "SINCE",
            "UNTIL",
            "TRIGGERED",
            "RELEASES",
            "EBF", /* 180 */
            "EBG",
            "ABF",
            "ABG",
              /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  "EGX",
  "EGG",
  "EGU",
  "EGF",
  "AGX",
  "AGG",
  "AGU",
  "AGF",
  /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   "BUNTIL",
  "MMIN",
  "MMAX",
            "OP_NEXT",
            "OP_GLOBAL",
            "OP_FUTURE",
            "OP_PREC",
            "OP_NOTPRECNOT",
            "OP_HISTORICAL",
            "OP_ONCE",
            "EQUAL",//191
            "NOTEQUAL",
            "LT",
            "GT",
            "LE",
            "GE",
            "UNION",
            "SETIN",
            "MOD",
            "PLUS", /* 200 */
            "MINUS",
            "TIMES",
            "DIVIDE",
            "UMINUS",
            "NEXT", /* 205 */
            "SMALLINIT",
            "DOT",
            "BIT",
            "RANGE",
            "WORD", /* identifies expressions and types */
            "INTEGER",
            "REAL",

            "NUMBER_WORD", /* identifies constants */
            "NUMBER_FRAC",
            "NUMBER_REAL",
            "NUMBER_EXP",
            "LSHIFT",
            "RSHIFT", /* 220 */
            "LROTATE",
            "RROTATE",
            "BIT_SELECTION",
            "CONCATENATION",
            "CAST_BOOL",
            "CAST_WORD1",
       /* 230 extend the width of a word (signed or unsigned) */
            "WORDARRAY",
            "WAREAD",
            "WAWRITE",
           
  /* Mathsat symbols */
 "SLT", /* signed less then */
  "SLE", /* signed less or equal */
  "SGT", /* signed greater then */
  "SGE", /* signed greater or equal */
  "SIGN_EXTEND", /* sign extend */

            "NUSMV_EXPR_SYMBOL_LAST",
            /* ---------------------------------------------------------------------- */

            "NUSMV_CORE_SYMBOL_LAST",
    };

    if(n>=100&&n<=266)
    {
        return enum_kv[n-100];
    }
    else
    {
        return "";
    }

}


//TODO:boolean,array类型的暂未支持，目前支持number类型的
static int ind;



void bst_print_dot_aux(struct node* node, FILE* stream,char* last_str,int index)
{
    static int nullcount = 0;
    char *inttype=NULL;
    char strtype[1000];
    char buffer[100];
    char total_str[2000];
    int span=0;
    node_val *nv;
    strcpy(total_str,"");


    switch(node->type) {

//        case CONTEXT:
//        case AND:
//        case OR:
//        case XOR:
//        case XNOR:
//        case NOT:
//        case IMPLIES:
//        case IFF:
//        case EX:
//        case AX:
//        case EF:
//        case AG:
//        case AF:
//        case EG:
//        case EU:
//        case AU:
//        case EBU:
//        case ABU:
//        case EBF:
//        case ABF:
//        case EBG:
//        case ABG:
        //


        case ATOM:
//             nv=(node_val*)(node->left.nodetype);
            strcpy(strtype,node->left.strtype->text);
            fprintf(stream, "   \"%d : %s\" -> \"%d : %s\";\n",index, last_str,++ind, strtype);
            break;
        case NUMBER:
//            nv=(node_val*)(node->left.nodetype);
            inttype=myitoa(node->left.inttype,buffer,10);
            fprintf(stream, "   \"%d : %s\" -> \"%d : 【%s】\";\n", index,last_str,++ind, inttype);
            break;

//
//        case FAILURE:
//        case TRUEEXP:
//        case FALSEEXP:
//        case SELF:
//        case BOOLEAN:
//        case DOT:
//        case ARRAY:
//        case NUMBER_UNSIGNED_WORD:
//        case UWCONST:
//        case SWCONST:
//        case NUMBER_SIGNED_WORD:
//        case NUMBER_FRAC:
//        case NUMBER_REAL:
//        case NUMBER_EXP:
//        case BIT:break;

        default:
            if(node->type<100||node->type>266)  break;

            if ((node->left).nodetype)
            {
                inttype=search_str((node->left).nodetype->type);
                fprintf(stream, "   \"%d : %s\" -> \"%d : %s\";\n",index, last_str, ind+1,inttype);
                bst_print_dot_aux((node->left).nodetype, stream,inttype,++ind);

            }


            if ( (node->right).nodetype )
            {

                inttype=search_str((node->right).nodetype->type);

                fprintf(stream, "   \"%d : %s\" -> \"%d : %s\";\n", index,last_str,ind+1, inttype);
                bst_print_dot_aux((node->right).nodetype, stream,inttype,++ind);
//                ind++;
            }

            break;

    }


}

void bst_print_dot(struct node * tree, FILE* stream)
{
    int index=0;
    ind=0;
    fprintf(stream, "digraph Tree {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!(tree->left).nodetype && !(tree->right).nodetype && !(tree->left).strtype && !(tree->right).strtype) {
        fprintf(stream, "%d : Root:%s;\n",index, search_str(tree->type));
    }
    else {
        bst_print_dot_aux(tree, stream,search_str(tree->type),index);
    }

    fprintf(stream, "}\n");
}
/*---------------------------------------------------------------------------*/
/* Static function prototypes                                                */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Definition of exported functions                                          */
/*---------------------------------------------------------------------------*/

/******************************************************************************

    Function name:
        GradedMc_checkGradedCtlSpec
        
    Parameters:
        Prop_ptr    property        The formula to be verified
        
    Result:
        void
        
    Description:
        The main function to make the model checking.
*******************************************************************************/
void GradedMc_checkGradedCtlSpec(Prop_ptr prop) {
	bdd_ptr constraints, fair, initial, states;
	node_ptr exp;
	bdd_ptr tmp1, tmp2;
	BddFsm_ptr fsm;
	BddEnc_ptr enc;
	DdManager* dd;
	 FILE *fp;
	Expr_ptr spec = Prop_get_expr_core(prop);

	if (opt_verbose_level_gt(options, 0)) {
		fprintf(nusmv_stderr, "evaluating ");
		print_spec(nusmv_stderr, prop);
		fprintf(nusmv_stderr, "\n");
	}
	
	if (opt_cone_of_influence(options) == true) {
		Prop_apply_coi_for_bdd(prop, global_fsm_builder);
	}

    /*Recruits the properties of the fsm*/	
	fsm = Prop_get_bdd_fsm(prop);
	if (fsm == BDD_FSM(NULL)) {
		Prop_set_fsm_to_master(prop);
		fsm = Prop_get_bdd_fsm(prop);
		BDD_FSM_CHECK_INSTANCE(fsm);
	}
	enc = BddFsm_get_bdd_encoding(fsm);
	dd = BddEnc_get_dd_manager(enc);
	constraints = BddFsm_get_state_constraints(fsm);
	fair = BddFsm_get_fair_states(fsm);
	initial = BddFsm_get_init(fsm);
	
	if (bdd_is_zero(dd, fair))
		warning_fsm_fairness_empty();
	
	//   fp = fopen("/mnt/d/WSL/NuSMV-2.4.3/nusmv/spec.dot", "w");
	//               if (fp == NULL)
	//                   printf("fail to open the file! \n");
	//               else {
	//                   printf("The file is open! \n");
	//                   bst_print_dot(spec, fp);

	//                   fclose(fp);
	//               }


	/* Evaluates the spec */
  	tmp1 = GradedMc_evalGradedCtlSpec(fsm, enc, spec, Nil);
	tmp2 = bdd_not(dd, tmp1);
	bdd_free(dd, tmp1);
    
    bdd_and_accumulate(dd, &tmp2, constraints);
	bdd_and_accumulate(dd, &tmp2, fair);
	bdd_and_accumulate(dd, &tmp2, initial);
	
    states = BddEnc_apply_state_vars_mask_bdd(enc, tmp2);
    bdd_free(dd, tmp2);
		
	/* Prints out the result, if not true explain. */
	fprintf(nusmv_stdout, "-- ");
	print_spec(nusmv_stdout, prop);
	
	if (bdd_is_zero(dd, states)) {
		fprintf(nusmv_stdout, "is true\n");
		Prop_set_status(prop, Prop_True);
	} else {
		int tr = 0;
		int i = 0;
		
		fprintf(nusmv_stdout, "is false\n");
		Prop_set_status(prop, Prop_False);
		//return;
		/*printf("mau prima\n");
		dd_printminterm(dd_manager, states);*/
		tmp1 = GradedUtils_bddPickOneState(enc, states);
		/*printf("stato selezionato\n");
		dd_printminterm(dd_manager, tmp1);
		printf("mau dopo\n");*/
		
		int nTracce = 1;
		treeNode_ptr albero = GradedMc_explainGraded(fsm, enc, tmp1, spec, Nil);
		
		
		GradedUtils_countTraces(fsm, enc, albero, &nTracce);
		
		cycleInf_ptr cicli = ALLOC(cycleInf, nTracce);
		int j;
		for(j=0; j<nTracce; j++){
		  cicli[j].nStato = 0;
		}
		GradedUtils_findCycle(fsm, enc, albero, cicli);
		
		GradedUtils_stampaPaths(fsm, enc, albero, cicli);
		return;
		
		if (opt_counter_examples(options)) {
			Trace_ptr trace;
			node_ptr* counter;
			char* trace_title = NULL;
			char* trace_title_postfix = " Counterexample";
			bool nullRes = false;
			
			tmp1 = BddEnc_pick_one_state(enc, states);
			
			counter = (node_ptr*)GradedMc_explainGraded(fsm, enc, 
                                cons((node_ptr)bdd_dup(tmp1), Nil), spec, Nil);
			
			if (counter[0] == Nil) {
				counter = ALLOC(node_ptr, 1);
				counter[0] = cons((node_ptr)bdd_dup(tmp1), Nil);
				counter[1] = Nil;
				nullRes = true;
			}
			
			while(counter[i] != Nil) {
				if (nullRes)
					exp =  counter[i];
				else
					exp =  reverse(counter[i]);
					
				if (exp == Nil) {
					/* The counterexample consists of one initial state */
					exp = cons((node_ptr)bdd_dup(tmp1), Nil);
					nullRes = true;
				}
				
				trace_title = ALLOC(char, Prop_get_type_as_string(prop) + 
						strlen(trace_title_postfix) + 1);
				nusmv_assert(trace_title != (char*) NULL);
				strcpy(trace_title, Prop_get_type_as_string(prop));
				strcat(trace_title, trace_title_postfix);
	
				trace = Trace_create_from_state_input_list(enc, trace_title,
						TRACE_TYPE_CNTEXAMPLE, exp);
				FREE(trace_title);
	
				tr = TraceManager_register_trace(global_trace_manager, trace);  
				Prop_set_trace(prop, Trace_get_id(trace));
	
				fprintf(nusmv_stdout, "-- as demonstrated by the following execution sequence\n");
	
				TraceManager_execute_plugin(global_trace_manager, 
						TraceManager_get_default_plugin(global_trace_manager), tr);
	
				if (!nullRes){
					exp =  reverse(exp);
					nullRes = false;
				}

				/*walk_dd(dd_manager, bdd_free, explanation);
				free_list(explanation);*/
				i++;
			}
			bdd_free(dd, tmp1);
			i = 0;
			while (counter[i] != Nil)
				walk_dd(dd, bdd_free, counter[i++]);
		}
	}
	
	bdd_free(dd, states);
	//bdd_free(dd, tmp1);
	bdd_free(dd, initial);
	bdd_free(dd, constraints);
	bdd_free(dd, fair);
}
