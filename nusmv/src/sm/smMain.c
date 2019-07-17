/**CFile***********************************************************************

  FileName    [smMain.c]

  PackageName [sm]

  Synopsis    [Main NuSMV routine. Parses command line at invocation of NuSMV.]

  Author      [Adapted to NuSMV by Marco Roveri]

  Modified by [Alessandro Ferrante, Francesco Sorrentino and Maurizio Memoli]
  
  The rows modified are preceded by : ++++++++++++++++++++++++++++++++++++++++

  Copyright   [
  This file is part of the ``sm'' package of NuSMV version 2. 
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

#if HAVE_CONFIG_H
# include "config.h"
#endif 

#include "smInt.h"

#if HAVE_SA
#include "sa/stsa/stsaTask.h"
#endif

static char rcsid[] UTIL_UNUSED = "$Id: smMain.c,v 1.28.2.14.2.5.2.31.4.13 2007/03/28 14:31:41 nusmv Exp $";


/*---------------------------------------------------------------------------*/
/* Macro definitions                                                         */
/*---------------------------------------------------------------------------*/
#ifndef  PACKAGE_BUGREPORT
#define  PACKAGE_BUGREPORT "nusmv@irst.itc.it"
#endif


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

/* Used to return a value from sm_parselineoptions */
static char * NuSMV_CMD_LINE = (char *) NULL;


/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Static function prototypes                                                */
/*---------------------------------------------------------------------------*/

static int NusmvrcSource ARGS((void));
static void UsagePrint ARGS((char * program, char * unknown_option));
static void BannerPrint ARGS((FILE * file));
static void sm_ParseLineOptions ARGS((int argc, char ** argv, options_ptr options));

/**AutomaticEnd***************************************************************/


/*---------------------------------------------------------------------------*/
/* Definition of exported functions                                          */
/*---------------------------------------------------------------------------*/

/**Function********************************************************************

  Synopsis    [required]

  Description [optional]

  SideEffects [required]

  SeeAlso     [optional]

******************************************************************************/
int main(int  argc, char ** argv)
{
  int status = 0;
  int quit_flag;
  quit_flag = 0;     /* Quick quit */

  Sm_Init();

  sm_ParseLineOptions(argc, argv, options);
  if (! opt_batch(options)) { /* interactive mode */
    /* initiliazes the commands to handle with options */
    (void) init_options_cmd();
    BannerPrint(nusmv_stdout);
    if (!opt_ignore_init_file(options)) {
      (void) NusmvrcSource();
    }
    if (NuSMV_CMD_LINE != NULL) {
#if HAVE_SA
      char * command = ALLOC(char, strlen(NuSMV_CMD_LINE)
                                   + strlen("source ") + 3);
      sprintf(command, "source \"%s\"", NuSMV_CMD_LINE);
#else
      char * command = ALLOC(char, strlen(NuSMV_CMD_LINE)
                                   + strlen("source ") + 1);
      sprintf(command, "source %s", NuSMV_CMD_LINE);
#endif
      quit_flag = Cmd_CommandExecute(command);
      FREE(command);
      FREE(NuSMV_CMD_LINE);
      NuSMV_CMD_LINE=(char*)NULL;
    }
    while (quit_flag >= 0) {
      quit_flag = Cmd_CommandExecute("source -ip -");
    }
    status = 0;
  }
  else { /* batch mode */
    /* In the batch mode we dont want to read the ~/.nusmvrc file. */
    /* The system has to behave as the original NuSMV */
    /*   if (!opt_ignore_init_file(options)) { */
    /*       (void) NusmvrcSource(); */
    /*     } */
    BannerPrint(nusmv_stdout);

    /*
    Cmd_CommandExecute("read_model");
    Cmd_CommandExecute("flatten_hierarchy");
    Cmd_CommandExecute("show_property");
    return;
    */

    if (opt_verbose_level_gt(options, 0)) {
      fprintf(nusmv_stdout, "Starting the batch interaction.\n");
    }
#if HAVE_SA

    if (get_sa_stsa_task_file(options) != NIL(char))
      /* STSA tasks batch execution */
      {
	STSABatchMain();
      }
    else
      smBatchMain();
#else
    smBatchMain();
#endif
  }
  /* Value of "quit_flag" is determined by the "quit" command */
  if (quit_flag == -1 || quit_flag == -2) {
    status = 0;
  }
  if (quit_flag == -2) {
    /*    Hrc_ManagerFree(globalHmgr); */
    Sm_End();
  } 
  else if (quit_flag == -3) {
    /* Script failed and on_failure_script_quits is set */
    /*    Hrc_ManagerFree(globalHmgr); */
    Sm_End();
    status = -1;
  }
  else {
    Sm_End();
  }
 
  exit(status);
}


/*---------------------------------------------------------------------------*/
/* Definition of internal functions                                          */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Definition of static functions                                            */
/*---------------------------------------------------------------------------*/


/**Function********************************************************************

  Synopsis    [Sources the .nusmvrc file.]

  Description [Sources the .nusmvrc file.  Always sources the .nusmvrc from
  library.  Then source the .nusmvrc from the home directory.  If there is none
  in the home directory, then execute the one in the current directory if one
  is present.  Returns 1 if scripts were successfully executed, else return 0.]

  SideEffects []

  SeeAlso     [optional]

******************************************************************************/
static int
NusmvrcSource()
{
  char *commandLine;
  char *libraryName;
  char *homeFile;
  struct stat home;
  struct stat cur;
  int s1;
  int s2;                       /* flags for checking the stat() call */
  int status0;
  int status1 = TRUE;
  int status2 = TRUE;

  /*
   * First execute the standard .nusmvrc.
   */
  libraryName = Sm_NuSMVObtainLibrary();
  commandLine = ALLOC(char, strlen(libraryName) + 30);
  (void) sprintf(commandLine, "source -s %s/master.nusmvrc", libraryName);
  FREE(libraryName);
  status0 = Cmd_CommandExecute(commandLine);
  FREE(commandLine);

  /*
   * Look in home directory and current directory for .nusmvrc.
   */
  homeFile = util_tilde_expand("~/.nusmvrc");
  s1 = stat(homeFile, &home);
  FREE(homeFile);
  s2 = stat(".nusmvrc", &cur);

  /*
   * If .nusmvrc is present in both the home and current directories, then read
   * it from the home directory.  Otherwise, read it from wherever it's
   * located.
   */
  if ((s1 == 0) && (s2 == 0) && (home.st_ino == cur.st_ino)){
    /* ~/.nusmvrc == .nusmvrc : Source the file only once */
    status1 = Cmd_CommandExecute("source -s ~/.nusmvrc");
  }
  else {
    if (s1 == 0) {
      status1 = Cmd_CommandExecute("source -s ~/.nusmvrc");
    }
    if (s2 == 0) {
      status2 = Cmd_CommandExecute("source -s .nusmvrc");
    }
  }

  return (status0 && status1 && status2);
}


/**Function********************************************************************

  Synopsis    [Prints the usage of the NuSMV shell interface.]

  SideEffects []

  SeeAlso     [optional]

******************************************************************************/
static void
UsagePrint(
  char * program, char * unknown_option)
{
  char *libraryName;
  
  BannerPrint(nusmv_stderr);

  fprintf(nusmv_stderr,"\n");  

  if (unknown_option != NULL) {
    fprintf(nusmv_stderr,
            "The command line option \"%s\" is unknown.\n", unknown_option);
  }
  fprintf(nusmv_stderr, "Usage:\t%s [-h | -help]  [-int] [-load script_file] \\\n", program);
  fprintf(nusmv_stderr, "\t[-s] [-old] [-old_div_op] [-dcx] \\\n");
  fprintf(nusmv_stderr, "\t[-ctt] [-lp] [-n idx] [-v vl] [-cpp] [-pre pp_list] \\\n");
  fprintf(nusmv_stderr, "\t[-is] [-ic] [-ils] [-ips] [-ii] [[-r] [-f]]|[-df] [-flt] [-AG] \\\n");
  fprintf(nusmv_stderr, "\t[-i iv_file] [-o ov_file] [-t tv_file] [-reorder] [-dynamic] \\\n");
  fprintf(nusmv_stderr, "\t[-m method] [[-mono]|[-thresh cp_t]|[-cp cp_t]|[-iwls95 cp_t]] \\\n");
  fprintf(nusmv_stderr, "\t[-coi] [-noaffinity] [-iwls95preorder] [-bmc] [-sat_solver name] \\\n");
  fprintf(nusmv_stderr, "\t[-bmc_length k] [-ofm fm_file] [-obm bm_file] \\\n");
  fprintf(nusmv_stderr, "\t[-sin on|off] [-rin on|off] \\\n");
#if HAVE_SA
  fprintf(nusmv_stderr, "\t[-vars_order type] [-sa_ft_layering] [-sa_ft_dcoi] [-sa_bool_fvars] [-sa_stsa] \\\n");
  fprintf(nusmv_stderr, "\t[-sa_stsa_task file] [-sa_stsa_fout file] [-sa_stsa_eng e] \\\n");
#endif
  fprintf(nusmv_stderr, "\t[input-file]\n");

  fprintf(nusmv_stderr, "Where:\n");
  fprintf(nusmv_stderr, "\t -s\t\t does not read any initialization file\n");
  libraryName = Sm_NuSMVObtainLibrary();
  fprintf(nusmv_stderr, "\t   \t\t (%s/master.nusmvrc, ~/.nusmvrc)\n\t\t\t (default in batch mode)\n", libraryName);
  FREE(libraryName);
  fprintf(nusmv_stderr, "\t -old\t\t keeps backward compatibility with older versions of NuSMV\n");
  fprintf(nusmv_stderr, "\t -old_div_op \t enables the old semantics of \"/\" and \"mod\" operations\n"
	                "\t\t\t (from NuSMV 2.3.0) instead of ANSI C semantics\n");

  fprintf(nusmv_stderr, "\t -ctt\t\t enables checking for the totality of the transition\n\t\t\t relation\n");
  fprintf(nusmv_stderr, "\t -lp\t\t lists all properties in SMV model\n");
  fprintf(nusmv_stderr, "\t -n idx\t\t specifies which property of SMV model\n" \
	  "\t\t\t should be checked\n");
  fprintf(nusmv_stderr, "\t -v vl\t\t sets verbose level to \"vl\"\n");
  fprintf(nusmv_stderr, "\t -cpp\t\t runs preprocessor on SMV files before\n\t\t\t any specified with -pre.\n" 

# if HAVE_CPP
#   if HAVE_GETENV
	  "\t\t\t Environment variable 'CPP' can be used to\n" 
	  "\t\t\t specify a different preprocessor.\n"
#   endif
# else
	  "\t\t\t Preprocessor was not found when NuSMV had been \n"
	  "\t\t\t configured, then 'cpp' will be searched at runtime\n" 
	  "\t\t\t when needed"
#   if HAVE_GETENV
	    ", or the 'CPP' environment variable\n" 
	  "\t\t\t will be used when defined by the user"
#   endif
	  ".\n"
# endif
          "\t\t\t Deprecated: use -pre option instead.\n");

  fprintf(nusmv_stderr, "\t -pre pp_list\t defines a space-separated list of pre-processors\n"\
	  "\t\t\t to run (in the order given) on the input file.\n"\
	  "\t\t\t The list must be in double quotes if there is more\n"\
          "\t\t\t than one pre-processor named.\n");
  if (get_preprocessors_num() > 0) {
    char* preps = get_preprocessor_names();
    fprintf(nusmv_stderr, "\t\t\t The available preprocessors are: %s\n", preps);
    FREE(preps);
  }
  else {
    fprintf(nusmv_stderr, "\t\t\t Warning: there are no available preprocessors.\n");
  }

  fprintf(nusmv_stderr, "\t -is\t\t does not check SPEC\n");

  /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  fprintf(nusmv_stderr, "\t -igs\t\t does not check GRADEDSPEC\n");
  /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
  fprintf(nusmv_stderr, "\t -ic\t\t does not check COMPUTE\n");
  fprintf(nusmv_stderr, "\t -ils\t\t does not check LTLSPEC\n");
  fprintf(nusmv_stderr, "\t -ips\t\t does not check PSLSPEC\n");
  fprintf(nusmv_stderr, "\t -ii\t\t does not check INVARSPEC\n");
  fprintf(nusmv_stderr, "\t -r\t\t enables printing of reachable states\n");
  fprintf(nusmv_stderr, "\t -f\t\t computes the reachable states (forward search) (default)\n");
  fprintf(nusmv_stderr, "\t -df\t\t disables the computation of reachable states\n");
  fprintf(nusmv_stderr, "\t -flt\t\t computes the reachable states also for the LTL Tableau\n");
  fprintf(nusmv_stderr, "\t -int\t\t enables interactive mode\n");
  fprintf(nusmv_stderr, "\t -h | -help\t prints out current message\n");
  fprintf(nusmv_stderr, "\t -i iv_file\t reads order of variables from file \"iv_file\"\n");
  fprintf(nusmv_stderr, "\t -o ov_file\t prints order of variables to file \"ov_file\"\n");
  fprintf(nusmv_stderr, "\t -t tv_file\t reads order of vars for clustering from file \"tv_file\"\n");
  fprintf(nusmv_stderr, "\t -AG\t\t enables AG only search\n");
  fprintf(nusmv_stderr, "\t -load sc_file\t executes NuSMV commands from file \"sc_file\"\n");
  fprintf(nusmv_stderr, "\t              \t in the interactive shell.\n");
  fprintf(nusmv_stderr, "\t -reorder\t enables reordering of variables before exiting\n");
  fprintf(nusmv_stderr, "\t -dynamic\t enables dynamic reordering of variables\n");
  fprintf(nusmv_stderr, "\t -m method\t sets the variable ordering method to \"method\".\n");
  fprintf(nusmv_stderr, "\t\t\t Reordering will be activated\n");
  fprintf(nusmv_stderr, "\t -mono\t\t enables monolithic transition relation\n");
  fprintf(nusmv_stderr, "\t -thresh cp_t\t conjunctive partitioning with threshold of each\n");
  fprintf(nusmv_stderr, "\t\t\t partition set to \"cp_t\" (DEFAULT, with cp_t=1000)\n");
  fprintf(nusmv_stderr, "\t -cp cp_t\t DEPRECATED: use -thresh instead.\n");
  fprintf(nusmv_stderr, "\t -iwls95 cp_t\t enables Iwls95 conjunctive partitioning and sets\n");
  fprintf(nusmv_stderr, "\t\t\t the threshold of each partition to \"cp_t\"\n");
  fprintf(nusmv_stderr, "\t -coi\t\t enables cone of influence reduction\n");
  fprintf(nusmv_stderr, "\t -noaffinity\t disables affinity clustering\n");
  fprintf(nusmv_stderr, "\t -iwls95preorder enables iwls95 preordering\n");
  fprintf(nusmv_stderr, "\t -bmc\t\t enables BMC instead of BDD model checking\n");
  fprintf(nusmv_stderr, "\t -sat_solver str sets the sat_solver variable, used by BMC\n");
  fprintf(nusmv_stderr,"\t\t\t "); Sat_PrintAvailableSolvers(nusmv_stderr); 
  fprintf(nusmv_stderr, "\t -bmc_length k\t sets bmc_length variable, used by BMC\n");
  fprintf(nusmv_stderr, "\t -ofm fm_file\t prints flattened model to file \"fn_file\"\n");
  fprintf(nusmv_stderr, "\t -obm bm_file\t prints boolean model to file \"bn_file\"\n");
  fprintf(nusmv_stderr, "\t -sin on|off\t enables (on) or disables sexp inlining (default is off)\n");
  fprintf(nusmv_stderr, "\t -rin on|off\t enables (on) or disables rbc inlining (default is on)\n");

#if 0 /* To be removed since 2.4.1 */
  fprintf(nusmv_stderr, "\t -word_mono\t enables monolithic ADD encoding of Word expressions\n"\
	                "\t\t\t instead of vector of bits and boolean arithmetic\n");
#endif 

  fprintf(nusmv_stderr, "\t -dcx \t\t disables computation of counter-examples \n");

#if HAVE_SA
  fprintf(nusmv_stderr, "\t -vars_order t\t sets the default static variable order to type \"t\" (sa package only)\n");
  fprintf(nusmv_stderr, "\t -sa_ft_layering enables use of layered fault tree computation (sa package)\n");
  fprintf(nusmv_stderr, "\t -sa_ft_dcoi\t enables use of DCOI fault tree computation (sa package)\n");
  fprintf(nusmv_stderr, "\t -sa_bool_fvars\t enables boolean failure variables (sa package)\n");
  fprintf(nusmv_stderr, "\t -sa_stsa\t enables compatibility mode for STSA (sa package)\n");
  fprintf(nusmv_stderr, "\t -sa_stsa_task f reads task information from file \"f\" (sa package)\n");
  fprintf(nusmv_stderr, "\t -sa_stsa_fout f writes output fault trees to file \"f\" (sa package)\n");
  fprintf(nusmv_stderr, "\t -sa_stsa_eng e uses verification engine \"e\" (stsa package)\n");  
#endif

  fprintf(nusmv_stderr, "\t input-file\t the file both the model and \n");
  fprintf(nusmv_stderr, "\t\t\t the spec were read from\n");

  exit(2);
}


/**Function********************************************************************

  Synopsis    [Prints the banner of NuSMV.]

  SideEffects []

  SeeAlso     []

******************************************************************************/
static void BannerPrint(FILE * file) 
{
  fprintf(file, "*** This is %s\n", Sm_NuSMVReadVersion());
  fprintf(file, "*** For more information on NuSMV see <http://nusmv.irst.itc.it>\n");
  fprintf(file, "*** or email to <nusmv-users@irst.itc.it>.\n");
  fprintf(file, "*** Please report bugs to <%s>.\n\n", PACKAGE_BUGREPORT);

# if HAVE_SOLVER_MINISAT
  fprintf(file, "*** This version of NuSMV is linked to the MiniSat SAT solver. \n");
  fprintf(file, "*** See http://www.cs.chalmers.se/Cs/Research/FormalMethods/MiniSat\n");
  fprintf(file, "*** Copyright (c) 2003-2005, Niklas Een, Niklas Sorensson \n\n");
# endif

# if HAVE_SOLVER_ZCHAFF
  fprintf(file, "WARNING *** This version of NuSMV is linked to the zchaff SAT solver  ***\n");
  fprintf(file, "WARNING *** (see http://www.princeton.edu/~chaff/zchaff.html).        ***\n");
  fprintf(file, "WARNING *** Zchaff is used in Bounded Model Checking when the         ***\n");
  fprintf(file, "WARNING *** system variable \"sat_solver\" is set to \"zchaff\".          ***\n");
  fprintf(file, "WARNING *** Notice that zchaff is for non-commercial purposes only.   ***\n");
  fprintf(file, "WARNING *** NO COMMERCIAL USE OF ZCHAFF IS ALLOWED WITHOUT WRITTEN    ***\n");
  fprintf(file, "WARNING *** PERMISSION FROM PRINCETON UNIVERSITY.                     ***\n");
  fprintf(file, "WARNING *** Please contact Sharad Malik (malik@ee.princeton.edu)      ***\n");
  fprintf(file, "WARNING *** for details.                                              ***\n\n");
# endif

  fflush(NULL); /* to flush all the banner before any other output */
}


/**Function********************************************************************

  Synopsis    [Parses the command line options.]

  Description []

  SideEffects []

******************************************************************************/
static void sm_ParseLineOptions(int argc, char ** argv, options_ptr options)
{
  /* parses the Program Name */
  argc--;
  set_pgm_path(options, *(argv++));

  while (argc > 0) {
    if (strcmp(*argv,"-load") == 0) {
      argv++; argc--;
      if (argc == 0) {
        fprintf(nusmv_stderr, "The \"-load\" command line options requires an argument.\n");
        exit(1);
      }
      unset_batch(options); /* goes in interactive mode by default */
      NuSMV_CMD_LINE = ALLOC(char, strlen(*argv)+1);
      strcpy(NuSMV_CMD_LINE, *argv);
      fprintf(stderr, "FILE ->>> %s \n", NuSMV_CMD_LINE);
      argv++; argc--;
      continue;
    }
    
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    if (strcmp(*argv,"-igs") == 0){
      argv++; argc--;
      set_ignore_gradspec(options);
      continue;
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

    if (strcmp(*argv,"-is") == 0){
      argv++; argc--;
      set_ignore_spec(options);
      continue;
    }
    if (strcmp(*argv,"-ic") == 0){
      argv++; argc--;
      set_ignore_compute(options);
      continue;
    }
    if (strcmp(*argv,"-ils") == 0){
      argv++; argc--;
      set_ignore_ltlspec(options);
      continue;
    }
    if (strcmp(*argv,"-ips") == 0){
      argv++; argc--;
      set_ignore_pslspec(options);
      continue;
    }
    else if (strcmp(*argv,"-ii") == 0){
      argv++; argc--;
      set_ignore_invar(options);
      continue;
    }
    else if (strcmp(*argv,"-r") == 0){
      argv++; argc--;
      set_print_reachable(options);
      set_forward_search(options);
      /* if this option is used, also their use is enabled */
      set_use_reachable_states(options);
      continue;
    }
    else if (strcmp(*argv,"-f") == 0){
      argv++; argc--;
      set_forward_search(options);
      /* if this option is used, also their use is enabled */
      set_use_reachable_states(options);
      continue;
    }
    else if (strcmp(*argv,"-df") == 0){
      argv++; argc--;
      unset_forward_search(options);
      /* if this option is used, also their use is enabled */
      unset_use_reachable_states(options);
      continue;
    }
    else if (strcmp(*argv,"-flt") == 0){
      argv++; argc--;
      set_ltl_tableau_forward_search(options);
      continue;
    }
    else if (strcmp(*argv, "-help") == 0) {
      argv++; argc--;
      UsagePrint(get_pgm_path(options), NULL);
    }
    else if (strcmp(*argv, "-h") == 0) {
      argv++; argc--;
      UsagePrint(get_pgm_path(options), NULL);
    }
    else if (strcmp(*argv,"-int") == 0){
      argv++; argc--;
      unset_batch(options);

#if HAVE_SETVBUF
# if SETVBUF_REVERSED
      setvbuf(nusmv_stdout, _IOLBF, (char *) NULL, 0);
# else
      setvbuf(nusmv_stdout, (char *) NULL, _IOLBF, 0);
# endif
#endif      

      continue;
    }
    else if (strcmp(*argv,"-AG") == 0){
      argv++; argc--;
      set_ag_only(options);
      continue;
    }
    else if (strcmp(*argv,"-bmc") == 0){
      argv++; argc--;
      set_bmc_mode(options);
      continue;
    }
    else if (strcmp(*argv,"-sat_solver") == 0) {
      if (argc < 2) {
        fprintf(nusmv_stderr, "The \"-sat_solver\" command line option requires an argument.\n");
        exit(1);
      }
      argv++; argc--;
      {
        const char* satSolver = *(argv);
        const char* normalizedSatSolver = Sat_NormalizeSatSolverName(satSolver);
	argv++; argc--;
	if (normalizedSatSolver == (const char*) NULL) {
	  fprintf(nusmv_stderr, 
		  "Error: \"%s\" is not a valid value for the \"-sat_solver\" command line option.\n", 
		  satSolver);
	  Sat_PrintAvailableSolvers(nusmv_stderr);
          exit(1);       
        }

        set_sat_solver(options, normalizedSatSolver);
      }
      continue;
    }
    else if (strcmp(*argv,"-bmc_length") == 0){
      if (argc < 2) {
        fprintf(nusmv_stderr, "The \"-bmc_length\" command line option requires an argument.\n");
        exit(1);
      }
      {
        char *err_occ[1];
        int bmc_length;
        
        err_occ[0] = "";
        argv++; argc -= 2;
        bmc_length = strtol(*(argv++),err_occ, 10);
        if (strcmp(err_occ[0], "") != 0) {
          fprintf(nusmv_stderr, "Error: \"%s\" is not a valid value for the \"-bmc_length\" command line option.\n", err_occ[0]);
          exit(1);
        }
        if (bmc_length < 0) {
          fprintf(nusmv_stderr, "Error: \"%d\" is not a valid value for the \"-bmc_length\" command line option.\n", bmc_length);
          exit(1);
        }
        set_bmc_pb_length(options, bmc_length);
      }
      continue;
    }
    else if (strcmp(*argv,"-lp") == 0){
      argv++; argc--;
      set_list_properties(options);
      continue;
    }
    else if (strcmp(*argv,"-n") == 0){
      if (argc < 2) {
        fprintf(nusmv_stderr, "The \"-n\" command line option requires an argument.\n");
        exit(1);
      }
      {
        char *err_occ[1];
        int prop_no;
        
        err_occ[0] = "";
        argv++; argc -= 2;
        prop_no = strtol(*(argv++),err_occ, 10);
        if (strcmp(err_occ[0], "") != 0) {
          fprintf(nusmv_stderr, "Error: \"%s\" is not a valid value for the \"-n\" command line option.\n", err_occ[0]);
          exit(1);
        }
        if (prop_no < 0) {
          fprintf(nusmv_stderr, "Error: \"%d\" is not a valid value for the \"-n\" command line option.\n", prop_no);
          exit(1);
        }
        set_prop_no(options, prop_no);
      }
      continue;
    }
#   if HAVE_CPP
    else if (strcmp(*argv,"-cpp") == 0) {
      /* If -cpp option is specified then cpp is
	 made the first preprocessor to use */
      char* pp_list;
      argv++; argc--;
      pp_list = get_pp_list(options);
      if (strcmp(pp_list, "") == 0) {
	set_pp_list(options, "cpp");
      }
      else {
	char* new_pp_list;
	new_pp_list = ALLOC(char, strlen(pp_list) + 5);
	strcpy(new_pp_list, "cpp ");
	strcat(new_pp_list, pp_list);
	set_pp_list(options, new_pp_list);
	FREE(new_pp_list);
      }
      continue;
    }
#   endif
    else if (strcmp(*argv, "-pre") == 0) {
      char * preprocessors;
      char * pp_list;
      if (argc-- < 2) {
	fprintf(nusmv_stderr, "The \"-pre\" command line option requires an argument.\n");
	exit(1);
      }
        argv++; argc--;
	preprocessors = *(argv++);
	pp_list = get_pp_list(options);
	if (strcmp(pp_list, "") == 0) {
	  set_pp_list(options, preprocessors);
	}
	else {
	  char* new_pp_list;

          new_pp_list = ALLOC(char, strlen(pp_list) + strlen(preprocessors) + 2);
	  strcpy(new_pp_list, pp_list);
	  strcat(new_pp_list, " ");
	  strcat(new_pp_list, preprocessors);
	  set_pp_list(options, new_pp_list);
	  FREE(new_pp_list);
	}

      continue;
    }
    else if (strcmp(*argv, "-reorder") == 0) {
      argv++; argc--;
      set_reorder(options);
      continue;
    }
    else if (strcmp(*argv, "-dynamic") == 0) {
      argv++; argc--;
      set_dynamic_reorder(options);
      dd_autodyn_enable(dd_manager, dd_get_ordering_method(dd_manager));
      continue;
    }
    else if (strcmp(*argv, "-coi") == 0) {
      argv++; argc--;
      set_cone_of_influence(options);
      continue;
    }
    else if (strcmp(*argv, "-ctt") == 0) {
      argv++; argc--;
      set_check_fsm(options);
      continue;
    }
    else if (strcmp(*argv, "-m") == 0){
      if (argc < 2) {
        fprintf(nusmv_stderr, "The \"-m\" command line option requires an argument.\n");
        exit(1);
      }
      argv++; argc -= 2;
      {
        unsigned int reorder_method = StringConvertToDynOrderType(*argv);
        if ( reorder_method == REORDER_NONE) {
          fprintf(nusmv_stderr, "The method \"%s\" is not a valid reorder method.\n",
                         *argv);
          exit(1);
        }
	argv++;
        set_reorder_method(options, reorder_method);
      }
      continue;
    }
    else if (strcmp(*argv,"-v") == 0){
      if (argc < 2) {
        fprintf(nusmv_stderr, "The \"-v\" command line option requires an argument.\n");
        exit(1);
      }
      {
        char *err_occ[1];
        int cur_verbose;
        
        err_occ[0] = "";
        argv++; argc -= 2;
        cur_verbose = strtol(*(argv++),err_occ, 10);
        if (strcmp(err_occ[0], "") != 0) {
          fprintf(nusmv_stderr, "Error: \"%s\" is not a valid value for the \"-v\" command line option.\n", err_occ[0]);
          exit(1);
        }
        set_verbose_level(options, cur_verbose);
      }

#if HAVE_SETVBUF
# if SETVBUF_REVERSED
      setvbuf(nusmv_stdout, _IOLBF, (char *) NULL, 0);
# else
      setvbuf(nusmv_stdout, (char *)NULL, _IOLBF, 0);
# endif
#endif

      continue;
    }
    else if (strcmp(*argv, "-i") == 0){
      argv++; argc -= 2;
      set_input_order_file(options, *(argv++));
      continue;
    }
    else if (strcmp(*argv, "-o") == 0){
      argv++;  argc -= 2;
      set_output_order_file(options, *(argv++));
      continue;
    }
    else if (strcmp(*argv, "-t") == 0){
      argv++;  argc -= 2;
      set_trans_order_file(options, *(argv++));
      continue;
    }
    else if (strcmp(*argv, "-ofm") == 0){
      argv++;  argc -= 2;
      set_output_flatten_model_file(options, *(argv++));
      continue;
    }
		else if (strcmp(*argv, "-obm") == 0){
      argv++;  argc -= 2;
      set_output_boolean_model_file(options, *(argv++));
      continue;
    }

		else if (strcmp(*argv, "-sin") == 0) {
			char* val;

      if (argc < 2) {
        fprintf(nusmv_stderr, "The \"-sin\" command line option requires an argument.\n");
        exit(1);
      }

			argv++; argc -= 2;
			val = *(argv++);
			if (strcmp(val , "off") == 0) unset_symb_inlining(options);
			else if (strcmp(val, "on") == 0) set_symb_inlining(options);
			else {
				fprintf(nusmv_stderr, "Error: \"%s\" is not a valid value for the \"-sin\" command line option.\n", val);
				exit(1);
			}
			continue;
		}

		else if (strcmp(*argv, "-rin") == 0) {
			char* val;

      if (argc < 2) {
        fprintf(nusmv_stderr, "The \"-rin\" command line option requires an argument.\n");
        exit(1);
      }

			argv++; argc -= 2;
			val = *(argv++);			
			if (strcmp(val, "off") == 0) unset_rbc_inlining(options);
			else if (strcmp(val, "on") == 0) set_rbc_inlining(options);
			else {
				fprintf(nusmv_stderr, "Error: \"%s\" is not a valid value for the \"-rin\" command line option.\n", val);
				exit(1);
			}
			continue;
		}

    else if((strcmp(*argv, "-cp") == 0) || (strcmp(*argv, "-thresh") == 0)){
      if (argc < 2) {
        fprintf(nusmv_stderr, "The \"-thresh\" (or \"-cp\") command line option requires an argument.\n");
        exit(1);
      } 
      {
        char *err_occ[1];
        int cur_cpl;
        
        err_occ[0] = "";
        argv++; argc -= 2;
        cur_cpl = strtol(*(argv++), err_occ, 10);
        if (strcmp(err_occ[0], "") != 0) {
          fprintf(stderr, "Error: \"%s\" is not a valid value for the \"-cp\" line option.\n", err_occ[0]);
          exit(1);
        }
        set_conj_partitioning(options);
        set_conj_part_threshold(options, cur_cpl);
      }
      continue;
    }
    else if(strcmp(*argv,"-dp") == 0){
      argv++;
      argc--;
      fprintf(stderr, "WARNING: Disjunctive partitioning is no longer supported.\n");
      continue;
    }
    else if(strcmp(*argv, "-iwls95") == 0){
      if (argc < 2) {
        fprintf(nusmv_stderr, "The \"-iwls95\" command line option requires an argument.\n");
        exit(1);
      } 
      {
        char *err_occ[1];
        int cur_cpl;
        
        err_occ[0] = "";
        argv++; argc -= 2;
        cur_cpl = strtol(*(argv++), err_occ, 10);
        if (strcmp(err_occ[0], "") != 0) {
          fprintf(stderr, "Error: \"%s\" is not a valid value for the \"-iwls95\" line option.\n", err_occ[0]);
          exit(1);
        }
        set_iwls95cp_partitioning(options);
        set_image_cluster_size(options, cur_cpl);
      }
      continue;
    }
    else if(strcmp(*argv,"-mono") == 0){
      argv++;
      argc--;
      set_monolithic(options);
      continue;
    }
    else if(strcmp(*argv,"-s") == 0){
      argv++;
      argc--;
      set_ignore_init_file(options);
      continue;
    }
    else if (argc == 1 && (**argv) != '-'){
      set_input_file(options, *(argv++));
      argc--;
      continue;
    }
    else if (strcmp(*argv,"-iwls95preorder") == 0){
      argv++; argc--;
      set_iwls95_preorder(options);
      continue;
    }
    else if (strcmp(*argv,"-noaffinity") == 0){
      argv++; argc--;
      unset_affinity(options);
      continue;
    }
#if 0 /* to be removed since 2.4.1 */
    else if (strcmp(*argv,"-word_mono") == 0){
      argv++; argc--;
      set_encode_word_monolithic(options);
      continue;
    }
#endif

    else if (strcmp(*argv, "-dcx") == 0) {
      argv++; argc--;
      unset_counter_examples(options);
      continue;
    }

    else if (strcmp(*argv, "-old_div_op") == 0) {
      argv++; argc--;
      unset_use_ansi_c_div_op(options);
      continue;
    }
    else if (strcmp(*argv, "-old") == 0) {
      argv++; argc--;
      set_backward_comp(options);
      continue;
    }

#if HAVE_SA
    else if (strcmp(*argv, "-vars_order") == 0){
      if (argc < 2) {
        fprintf(nusmv_stderr, "The \"-vars_order\" command line option requires an argument.\n");
        exit(1);
      }
      argv++; argc -= 2;
      {
        VarsOrdType vot = Enc_string_to_vars_ord(*argv);
        if ( vot == VARS_ORD_UNKNOWN) {
          fprintf(nusmv_stderr,
		  "The order \"%s\" is not a valid variable order type.\n",
		  *argv);
	  fprintf(nusmv_stderr, "Valid values are: %s\n", 
		  Enc_get_valid_vars_ord_types());
          exit(1);
        }
	argv++;
        set_vars_order_type(options, vot);
      }
      continue;
    }
    else if (strcmp(*argv, "-sa_ft_layering") == 0) {
      argv++; argc--;
      set_sa_ft_layering(options);
      continue;
    }
    else if (strcmp(*argv, "-sa_ft_dcoi") == 0) {
      argv++; argc--;
      set_sa_ft_dcoi(options);
      continue;
    }
    else if (strcmp(*argv, "-sa_bool_fvars") == 0) {
      argv++; argc--;
      set_sa_bool_fvars(options);
      continue;
    }
    else if (strcmp(*argv, "-sa_stsa") == 0) {
      argv++; argc--;
      /* The -sa_stsa command-line option sets the */
      /* environment variables sa_stsa_compatibility and sa_bool_fvars. */
      /* Furthermore, the default trace plugin is set to TraceVIS */
      set_sa_stsa_compatibility(options);
      set_sa_bool_fvars(options);
      if (set_default_trace_plugin(options,
	  TraceManager_get_plugin_size(TracePkg_get_global_trace_manager())-1))
	nusmv_assert(false);
      continue;
    }
    else if (strcmp(*argv, "-sa_stsa_task") == 0){
      argv++; argc -= 2;
      set_sa_stsa_task_file(options, *(argv++));
      continue;
    }
    else if (strcmp(*argv, "-sa_stsa_fout") == 0){
      argv++; argc -= 2;
      set_sa_stsa_ft_output_file(options, *(argv++));
      continue;
    }
    else if (strcmp(*argv, "-sa_stsa_eng") == 0){
      argv++; argc -= 2;
      set_sa_stsa_engine(options, *(argv++));
      continue;
    }
#endif

    else  {
      UsagePrint(get_pgm_path(options), *argv);
    }
  }
}
