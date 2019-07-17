/**CHeaderFile*****************************************************************

  FileName    [optInt.h]

  PackageName [opt]

  Synopsis    [The internal header file of the opt package.]

  Description [The internal header file of the opt package.]

  Author      [Marco Roveri]

  Modified by [Alessandro Ferrante, Francesco Sorrentino and Maurizio Memoli]
  
  The rows modified are preceded by : ++++++++++++++++++++++++++++++++++++++++

  Copyright   [
  This file is part of the ``opt'' package of NuSMV version 2. 
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

  Revision    [$Id: optInt.h,v 1.5.4.6.2.2.2.22.4.13 2007/04/06 11:06:34 nusmv Exp $]

******************************************************************************/

#ifndef _OPTINTH
#define _OPTINTH

#include <stdio.h>
#include <limits.h>

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include "utils/utils.h"
#include "opt/opt.h"
#include "sm/sm.h"
#include "util.h"
#include "node/node.h"
#include "set/set.h"
#include "dd/dd.h"
#include "rbc/rbc.h"
#include "cmd/cmd.h"
#include "compile/compile.h"
#include "prop/prop.h"
#include "opt/opt.h"
#include "bmc/bmc.h"
#include "utils/ucmd.h"
#include "trans/trans.h" /* for TransType */

/**Macro***********************************************************************

  Synopsis     [Makes append_cluster option visible to the shell interface]

  Description  [Makes append_cluster option visible to the shell
  interface. The default is that it is not visible. Notice that only
  the printing hide it. The set unset function handle it.]

******************************************************************************/
#define APPEND_CLUSTERS_VISIBLE 0

/**Struct**********************************************************************

  Synopsis    [The option data structure.]

  Description [The option data structure contains the following fields:
  <ul>
  <li><b>pgm_name</b></li>
  <li><b>pgm_path</b></li>
  <li><b>input_file</b></li>
  <li><b>input_order_file</b></li>
  <li><b>output_order_file</b></li>
  <li><b>trans_order_file</b></li>
  <li><b>output_word_format</b></li>
  <li><b>verbose</b></li>
  <li><b>pp_list</b></li>
  <li><b>check_fsm</li>
  <li><b>ignore_gradspec</b></li>
  <li><b>ignore_spec</b></li>
  <li><b>ignore_compute</b></li>
  <li><b>ignore_ltlspec</b></li>
  <li><b>ignore_pslspec</b></li>
  <li><b>ignore_invar</b></li>
  <li><b>forward_search</b></li>
  <li><b>ltl_tableau_forward_search</b></li>
  <li><b>print_reachable</b></li>
  <li><b>enable_reorder</b></li>
  <li><b>partition_method</b></li>
  <li><b>conj_part_threshold</b></li>
  <li><b>image_cluster_size</b></li>
  <li><b>ignore_init_file</b></li>
  <li><b>ag_only</b></li>
  <li><b>cone_of_influence</b></li>
  <li><b>bmc_mode</b></li>
  <li><b>bmc_dimacs_filename</b></li>
  <li><b>bmc_invar_dimacs_filename</b></li>
  <li><b>bmc_pb_length</b></li>
  <li><b>bmc_pb_loop</b></li>
  <li><b>bmc_invar_alg</b></li>
  <li><b>bmc_inc_invar_alg</b></li>
  <li><b>bmc_optimized_tableau</b></li>
  <li><b>bmc_force_pltl_tableau</b></li> 
  <li><b>sat_solver</b></li>
  </ul>]

  SeeAlso     [optional]

******************************************************************************/
typedef struct options_TAG {
  char* pgm_name;
#define PROGRAM_NAME      "program_name"
  char* pgm_path;
#define PROGRAM_PATH      "program_path"
  char* input_file;
#define INPUT_FILE        "input_file"
  char* input_order_file;
#define INPUT_ORDER_FILE  "input_order_file"
  char* output_order_file;
#define OUTPUT_ORDER_FILE "output_order_file"
  char* output_flatten_model_file;

  /********************************************************************/
  /** 12/9/06, Wendy Johnston, University of Queensland **/
  /** include transition order file **/
  char* trans_order_file;
#define TRANS_ORDER_FILE  "trans_order_file"
  /********************************************************************/

#define OUTPUT_FLATTEN_MODEL_FILE "output_flatten_model_file"
  char* output_boolean_model_file;
#define OUTPUT_BOOLEAN_MODEL_FILE "output_boolean_model_file"
  int output_word_format;
#define OUTPUT_WORD_FORMAT "output_word_format"
  boolean backward_compatibility;
#define BACKWARD_COMPATIBILITY "backward_compatibility"
  boolean type_checking_warning_on;
#define TYPE_CHECKING_WARNING_ON "type_checking_warning_on"
  int verbose;
#define VERBOSE_LEVEL     "verbose_level"
  /* deprecated option */
  int run_cpp;
#define RUN_CPP           "run_cpp"
  /* end of deprecated code */
  char* pp_list;
#define PP_LIST           "pp_list"
  int shown_states;
#define SHOWN_STATES      "shown_states"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  boolean ignore_gradspec;
#define IGNORE_GRADSPEC       "ignore_gradspec"
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  boolean ignore_spec;
#define IGNORE_SPEC       "ignore_spec"
  boolean ignore_compute;
#define IGNORE_COMPUTE    "ignore_compute"
  boolean ignore_ltlspec;
#define IGNORE_LTLSPEC    "ignore_ltlspec"
  boolean ignore_pslspec;
#define IGNORE_PSLSPEC    "ignore_pslspec"
  boolean check_fsm;
#define OPT_CHECK_FSM   "check_fsm"
  boolean ignore_invar;
#define IGNORE_INVAR      "ignore_invar"
  boolean forward_search;
#define FORWARD_SEARCH    "forward_search"
  boolean ltl_tableau_forward_search;
#define LTL_TABLEAU_FORWARD_SEARCH "ltl_tableau_forward_search"
  boolean print_reachable;
#define PRINT_REACHABLE   "print_reachable"
  boolean reorder;
#define ENABLE_REORDER    "enable_reorder"
  unsigned int reorder_method;
#define REORDER_METHOD    "reorder_method"
  boolean dynamic_reorder;
#define DYNAMIC_REORDER   "dynamic_reorder"
  boolean batch;

  TransType partition_method;
#define PARTITION_METHOD  "partition_method"
  int conj_part_threshold;
#define CONJ_PART_THRESHOLD "conj_part_threshold"
  int image_cluster_size;
#define IMAGE_CLUSTER_SIZE "image_cluster_size"
  boolean ignore_init_file;
#define IGNORE_INIT_FILE  "ignore_init_file"
  boolean ag_only;
#define AG_ONLY_SEARCH    "ag_only_search"
  boolean cone_of_influence;
#define CONE_OF_INFLUENCE "cone_of_influence"
  boolean list_properties;
#define LIST_PROPERTIES "list_properties"
  int prop_no;
#define PROP_NO         "prop_no"
  /* BMC Stuff */
  boolean bmc_mode;
#define BMC_MODE          "bmc_mode"
  char* bmc_dimacs_filename;
#define BMC_DIMACS_FILENAME "bmc_dimacs_filename"
  char* bmc_invar_dimacs_filename;
#define BMC_INVAR_DIMACS_FILENAME "bmc_invar_dimacs_filename"
  int bmc_pb_length;
#define BMC_PB_LENGTH      "bmc_length"
  char* bmc_pb_loop;
#define BMC_PB_LOOP        "bmc_loopback"
  const char* bmc_invar_alg;
#define BMC_INVAR_ALG        "bmc_invar_alg"

#if HAVE_INCREMENTAL_SAT
  const char* bmc_inc_invar_alg;
#define BMC_INC_INVAR_ALG        "bmc_inc_invar_alg"
#endif

  boolean bmc_optimized_tableau;
#define BMC_OPTIMIZED_TABLEAU "bmc_optimized_tableau"
  boolean bmc_force_pltl_tableau;
#define BMC_FORCE_PLTL_TABLEAU "bmc_force_pltl_tableau"
  boolean preorder;

#define A_SAT_SOLVER "sat_solver"
  const char* sat_solver;

  /* SBMC options */
#define BMC_SBMC_IL_OPT "bmc_sbmc_il_opt"  
  boolean bmc_sbmc_il_opt;
#define BMC_SBMC_GF_FG_OPT "bmc_sbmc_gf_fg_opt"  
  boolean bmc_sbmc_gf_fg_opt;
#define BMC_SBMC_CACHE_OPT "bmc_sbmc_cache_opt"  
  boolean bmc_sbmc_cache_opt;

#define IWLS95_PREORDER  "iwls95preorder"
  boolean affinity;
#define AFFINITY_CLUSTERING  "affinity"

  boolean append_clusters;
#define APPEND_CLUSTERS  "append_clusters"

boolean use_reachable_states;
#define USE_REACHABLE_STATES  "use_reachable_states"
boolean use_fair_states;
#define USE_FAIR_STATES  "use_fair_states"

boolean encode_word_monolithic;
#define ENCODE_WORD_MONOLITHIC  "encode_word_monolithic"

boolean counter_examples;
#define COUNTER_EXAMPLES  "counter_examples"

#define DEFAULT_TRACE_PLUGIN  "default_trace_plugin"

boolean on_failure_script_quits;
#define ON_FAILURE_SCRIPT_QUITS "on_failure_script_quits"

boolean write_order_dumps_bits;
#define WRITE_ORDER_DUMPS_BITS "write_order_dumps_bits"

  /* MBP Stuff */
#if HAVE_MBP
  boolean mbp_game;

#define MBP_PRINT_PLAN "mbp_print_strategy"
  boolean mbp_print_strategy;
#define MBP_GAME_INITIAL_CONDITION  "mbp_game_initial_condition"
  char mbp_game_initial_condition;
#endif

  /* SA Stuff */
#if HAVE_SA
#define SA_FT_LAYERING "sa_ft_layering"
  boolean sa_ft_layering;
#define SA_FT_DCOI "sa_ft_dcoi"
  boolean sa_ft_dcoi;
#define SA_BOOL_FVARS "sa_bool_fvars"
  boolean sa_bool_fvars;
#define SA_STSA_COMPATIBILITY "sa_stsa_compatibility"
  boolean sa_stsa_compatibility;
#define SA_STSA_TASK_FILE "sa_stsa_task_file"
  char* sa_stsa_task_file;
#define SA_STSA_FT_OUTPUT_FILE "sa_stsa_ft_output_file"
  char* sa_stsa_ft_output_file;
#define SA_STSA_ENGINE "sa_stsa_engine"
  char* sa_stsa_engine;
#endif

  boolean use_ansi_c_div_op;
#define USE_ANSI_C_DIV_OP "use_ansi_c_div_op"

  VarsOrdType vars_ord_type;
#define VARS_ORD_TYPE "vars_order_type"

  /* Inlining */
#define SYMB_INLINING "sexp_inlining"
  boolean symb_inlining;
#define RBC_INLINING "rbc_inlining"
  boolean rbc_inlining;
#define RBC_INLINING_LAZY "rbc_inlining_lazy"
  boolean rbc_inlining_lazy;

} Options; 




/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

extern avl_tree *cmdFlagTable;
extern options_ptr options;
extern DdManager * dd_manager;
extern cmp_struct_ptr cmps;

#endif /* _OPTINTH */
