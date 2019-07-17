/**CFile***********************************************************************

  FileName    [propCmd.c]

  PackageName [prop]

  Synopsis    [Shell interface for the prop package.]

  Description [This file contains the interface of the prop package
  with the interactive shell.]

  SeeAlso     [cmdCmd.c]

  Author      [Marco Roveri]

  Modified by [Alessandro Ferrante, Francesco Sorrentino and Maurizio Memoli]
  
  The rows modified are preceded by : ++++++++++++++++++++++++++++++++++++++++

  Copyright   [
  This file is part of the ``prop'' package of NuSMV version 2.
  Copyright (C) 2000-2001 by ITC-irst.

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

#include "propInt.h"

#include "cmd/cmd.h"
#include "compile/compile.h"
#include "enc/enc.h"
#include "mc/mc.h"

#include "utils/error.h" /* for CATCH */


static char rcsid[] UTIL_UNUSED = "$Id: propCmd.c,v 1.17.2.4.2.1.2.8.4.2 2006/10/24 15:00:51 nusmv Exp $";

/* prototypes of the command functions */
int CommandShowProperty ARGS((int argc, char** argv));
int CommandAddProperty  ARGS((int argc, char** argv));
int CommandCheckProperty ARGS((int argc, char** argv));

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Macro declarations                                                        */
/*---------------------------------------------------------------------------*/


/**AutomaticStart*************************************************************/

/*---------------------------------------------------------------------------*/
/* Static function prototypes                                                */
/*---------------------------------------------------------------------------*/
static int UsageShowProperty ARGS((void));
static int UsageAddProperty ARGS((void));
static int UsageCheckProperty ARGS((void));

/**AutomaticEnd***************************************************************/


/*---------------------------------------------------------------------------*/
/* Definition of exported functions                                          */
/*---------------------------------------------------------------------------*/

/**Function********************************************************************

  Synopsis           [Initiliaze the prop package for commands]

  Description [Initialize the prop package for commands.  This must be
  called independently from the package initialization function]

  SideEffects        []

  SeeAlso            []

******************************************************************************/
void PropPkg_init_cmd(void)
{
  Cmd_CommandAdd("show_property",  CommandShowProperty, 0, true);
  Cmd_CommandAdd("add_property",   CommandAddProperty, 0, true);
  Cmd_CommandAdd("check_property", CommandCheckProperty, 0, true);
}

/**Function********************************************************************

  Synopsis           [Quit the prop package for commands]

  Description        [This must be called independently from 
  the package initialization function]

  SideEffects        []

  SeeAlso            []

******************************************************************************/
void PropPkg_quit_cmd(void)
{
  /* TODO */
}


/*---------------------------------------------------------------------------*/
/* Definition of internal functions                                          */
/*---------------------------------------------------------------------------*/

/**Function********************************************************************

  Synopsis           [Shows the currently stored properties]

  CommandName        [show_property]

  CommandSynopsis    [Shows the currently stored properties]

  CommandArguments   [\[-h\] \[\[-c | -g | -l | -i | -q\] \[-u | -t | -f\]\]
  | \[-n property_number\] \[-m | -o output-file\]]

  CommandDescription [
  Shows the properties currently stored in the list of properties. This list
  is initialized with the properties (CTL, GCTL, LTL, INVAR, COMPUTE) present
  in the input file, if any; then all of the properties added by the user
  with the relative <tt>check</tt> or <tt>add_property<\tt> commands are appended
  to this list.
  For every property, the following informations are displayed:
  <ul>
  <li>the identifier of the property (a progressive number);
  <li>the property formula;
  <li>the type (CTL, LTL, INVAR, COMPUTE)
  <il>the status of the formula (Unchecked, True, False) or the result of the
  quantitative expression, if any (it can be infinite);
  <li>if the formula has been found to be false, the number of the
  corresponding counterexample trace.
  </ul>
  By default, all the properties currently stored in the list of properties
  are shown. Specifying the suitable options, properties with a certain
  status (Unchecked, True, False) and/or of a certain type (e.g. CTL,
  LTL), or with a given identifier, it is possible to let the system show a
  restricted set of properties. It is allowed to insert only one option
  per status and one option per type.
  <p>
  Command options:<p>
  <dl>
    <dt> <tt>-c</tt>
       <dd> Prints only CTL properties.
    <dt> <tt>-g</tt>
       <dd> Prints only Graded CTL properties.
    <dt> <tt>-l</tt>
       <dd> Prints only LTL properties.
    <dt> <tt>-i</tt>
       <dd> Prints only INVAR properties.
    <dt> <tt>-q</tt>
       <dd> Prints only quantitative (COMPUTE) properties.
    <dt> <tt>-u</tt>
       <dd> Prints only unchecked properties.
    <dt> <tt>-t</tt>
       <dd> Prints only those properties found to be true.
    <dt> <tt>-f</tt>
       <dd> Prints only those properties found to be false.
    <dt> <tt>-n property-number</tt>
       <dd> Prints out the property numbered <tt>property-number</tt>.
    <dt> <tt>-m</tt>
       <dd> Pipes the output through the program specified by the
       <tt>PAGER</tt> shell variable if defined, else through the
       <tt>UNIX</tt> "more" command.
    <dt> <tt>-o output-file</tt>
       <dd> Writes the output generated by the command to <tt>output-file<\tt>.
  </dl>]

  SideEffects        []

  SeeAlso            [add_property check_spec check_ltlspec check_invar compute]

******************************************************************************/
int CommandShowProperty(int argc, char** argv)
{
  int c;
  int retval = 0;
  int prop_no = -1;
  int useMore = 0;
  Prop_Type type = Prop_NoType;
  Prop_Status status = Prop_NoStatus;
  char* outFileName = NIL(char);
  FILE* old_nusmv_stdout = NULL;

  util_getopt_reset();
  while((c = util_getopt(argc, argv, "hlcgiqutfn:vmo:")) != EOF){
    switch(c){
    case 'h': return(UsageShowProperty());
    
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    case 'g':
      {
        if ((type != Prop_NoType) || (prop_no != -1))
          return(UsageShowProperty());
        type = Prop_Ctlg;
        break;
      }
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    
    case 'c':
      {
        if ((type != Prop_NoType) || (prop_no != -1))
          return(UsageShowProperty());
        type = Prop_Ctl;
        break;
      }
    case 'l':
      {
        if ((type != Prop_NoType) || (prop_no != -1))
          return(UsageShowProperty());
        type = Prop_Ltl;
        break;
      }
    case 'i':
      {
        if ((type != Prop_NoType) || (prop_no != -1))
          return(UsageShowProperty());
        type = Prop_Invar;
        break;
      }
    case 'q':
      {
        if ((type != Prop_NoType) || (prop_no != -1))
          return(UsageShowProperty());
        type = Prop_Compute;
        break;
      }
    case 'u':
      {
        if ((status != Prop_NoStatus) || (prop_no != -1))
          return(UsageShowProperty());
        status = Prop_Unchecked;
        break;
      }
    case 't':
      {
        if ((status != Prop_NoStatus) || (prop_no != -1))
          return(UsageShowProperty());
        status = Prop_True;
        break;
      }
    case 'f':
      {
        if ((status != Prop_NoStatus) || (prop_no != -1))
          return(UsageShowProperty());
        status = Prop_False;
        break;
      }
    case 'n':
      {
        if ((type != Prop_NoType)     ||
            (status != Prop_NoStatus) ||
            (prop_no != -1))
          return(UsageShowProperty());

        prop_no = PropDb_get_prop_index_from_string(util_optarg);
        if (prop_no == -1) return(1);

        break;
      }
    case 'o':
      {
        if (useMore == 1) return(UsageShowProperty());
        outFileName = util_strsav(util_optarg);
        break;
      }
    case 'm':
      {
        if (outFileName != NIL(char)) return(UsageShowProperty());
        useMore = 1;
        break;
      }
    default: return(UsageShowProperty());
    }
  }

  if (argc != util_optind) return(UsageShowProperty());

  /* command hierarchy control */
  if (Compile_check_if_flattening_was_built(nusmv_stderr)) return 1;

  if (useMore == 1) {
    old_nusmv_stdout = nusmv_stdout;
    nusmv_stdout = CmdOpenPipe(useMore);
    if (nusmv_stdout == NIL(FILE)) {
      nusmv_stdout = old_nusmv_stdout;
      return(1);
    }
  }
  if (outFileName != NIL(char)) {
    old_nusmv_stdout = nusmv_stdout;
    nusmv_stdout = CmdOpenFile(outFileName);
    if (nusmv_stdout == NIL(FILE)) {
      nusmv_stdout = old_nusmv_stdout;
      return(1);
    }
  }

  PropDb_print_list_header(nusmv_stdout);
  if ((type == Prop_NoType) && (status == Prop_NoStatus) &&
                               (prop_no == -1)) {
    PropDb_print_all(nusmv_stdout);
  } else if ((type != Prop_NoType) && (status != Prop_NoStatus)) {
    PropDb_print_all_status_type(nusmv_stdout, status, type);
  } else if ((type != Prop_NoType) && (status == Prop_NoStatus)) {
    PropDb_print_all_type(nusmv_stdout, type);
  } else if ((type == Prop_NoType) && (status != Prop_NoStatus)) {
    PropDb_print_all_status(nusmv_stdout, status);
  } else if (prop_no != -1) {
    retval = PropDb_print_prop_at_index(nusmv_stdout, prop_no);
  }

  if (useMore) {
    CmdClosePipe(nusmv_stdout);
    nusmv_stdout = old_nusmv_stdout;
  }
  if (outFileName != NIL(char)) {
    CmdCloseFile(nusmv_stdout);
    nusmv_stdout = old_nusmv_stdout;
  }
  return(retval);
}

static int UsageShowProperty()
{
  fprintf(nusmv_stderr, "usage: show_property [-h] [ [[-c | -g  | -l | -i | -q] [-u | -t | -f]] | [-n index] ] \n");
  fprintf(nusmv_stderr, "\t\t [-m | -o file]\n");
  fprintf(nusmv_stderr, "  -h \t\tPrints the command usage.\n");
  fprintf(nusmv_stderr, "  -c \t\tPrints only CTL properties.\n");

  /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  fprintf(nusmv_stderr, "  -g \t\tPrints only Graded CTL properties.\n");
  /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  fprintf(nusmv_stderr, "  -l \t\tPrints only LTL properties.\n");
  fprintf(nusmv_stderr, "  -i \t\tPrints only INVAR properties.\n");
  fprintf(nusmv_stderr, "  -q \t\tPrints only quantitative properties (COMPUTE).\n");
  fprintf(nusmv_stderr, "  -u \t\tPrints only unchecked properties.\n");
  fprintf(nusmv_stderr, "  -t \t\tPrints only those properties found to be true.\n");
  fprintf(nusmv_stderr, "  -f \t\tPrints only those properties found to be false.\n");
  fprintf(nusmv_stderr, "  -n index\tPrints out the property numbered \"index\".\n");
  fprintf(nusmv_stderr, "  -m \t\tPipes output through the program specified by the \"PAGER\"\n");
  fprintf(nusmv_stderr, "    \t\tenvironment variable if defined, else through UNIX \"more\".\n");
  fprintf(nusmv_stderr, "  -o file\tWrites the generated output to \"file\".\n");
  return(1);
}

/**Function********************************************************************

  Synopsis           [Adds a property to the list of properties]

  CommandName        [add_property]

  CommandSynopsis    [Adds a property to the list of properties]

  CommandArguments   [\[-h\] \[(-c | -g | -l | -i | -q | -s) -p "formula \[IN context\]"\]]

  CommandDescription [
  Adds a property in the list of properties. It is possible to insert
  LTL, CTL, GCTL, INVAR, PSL and quantitative (COMPUTE) properties. Every
  newly inserted property is initialized to unchecked. A type option
  must be given to properly execute the command.
  <p>
  Command options:<p>
  <dl>
    <dt> <tt>-c</tt>
       <dd> Adds a CTL property.
    <dt> <tt>-c</tt>
       <dd> Adds a Graded CTL property.
    <dt> <tt>-l</tt>
       <dd> Adds an LTL property.
    <dt> <tt>-i</tt>
       <dd> Adds an INVAR property.
    <dt> <tt>-s</tt>
       <dd> Adds a PSL property.
    <dt> <tt>-q</tt>
       <dd> Adds a quantitative (COMPUTE) property.
    <dt> <tt>-p "formula \[IN context\]"</tt>
       <dd> Adds the <tt>formula</tt> specified on the command-line. <BR>
            <tt>context</tt> is the module instance name which the variables
            in <tt>formula</tt> must be evaluated in.
  </dl>]

  SeeAlso            [show_property]

  SideEffects        []

******************************************************************************/
int CommandAddProperty (int argc, char** argv)
{
  int c = 0;
  short int usedType = 0;
  Prop_Type type = Prop_NoType;
  char* prop = NIL(char);

  util_getopt_reset();
  while((c = util_getopt(argc, argv, "hlcgisqp:")) != EOF){
    switch(c){
    case 'h': return(UsageAddProperty());
    case 'l':
      if (++usedType > 1) return(UsageAddProperty());
      type = Prop_Ltl;
      break;
    case 'c':
      if (++usedType > 1) return(UsageAddProperty());
      type = Prop_Ctl;
      break;
    
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    case 'g':
      if (++usedType > 1) return(UsageAddProperty());
      type = Prop_Ctlg;
      break;
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

    case 'i':
      if (++usedType > 1) return(UsageAddProperty());
      type = Prop_Invar;
      break;
    case 's':
      if (++usedType > 1) return(UsageAddProperty());
      type = Prop_Psl;
      break;
    case 'q':
      if (++usedType > 1) return(UsageAddProperty());
      type = Prop_Compute;
      break;
    case 'p':
      /* this option is optional */
      if (usedType == 0 || prop != NIL(char)) return(UsageAddProperty());
      prop = util_optarg;
      break;
    default: return(UsageAddProperty());
    }
  }

  if (prop == NIL(char)) {
    /* option -p not used: the property has still to be parsed */
    if (argc != util_optind + 1) return(UsageAddProperty());
    prop = argv[util_optind];
  }
  else {
    /* option -p used: the property has already been parsed */
    if (argc != util_optind) return(UsageAddProperty());
  }

  if (type == Prop_NoType) {
    return(UsageAddProperty());
  }

  /* command hierarchy control */
  if (Compile_check_if_flattening_was_built(nusmv_stderr)) return 1;

  argv += util_optind-1;
  argc -= util_optind-1;

  { /* parse and add the property */
    int result;
    result = PropDb_prop_parse_and_add(Compile_get_global_symb_table(), 
				       prop, type);
    if (result == -1) return 1; /* error */
  }

  return(0);
}

static int UsageAddProperty()
{
  fprintf(nusmv_stderr, "usage: add_property [-h] [(-c | -g | -l | -i | -s | -q)"\
	  " -p \"formula\"]\n");
  fprintf(nusmv_stderr, "  -h \t\tPrints the command usage.\n");
  fprintf(nusmv_stderr, "  -c \t\tAdds a CTL property.\n");

  /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  fprintf(nusmv_stderr, "  -g \t\tAdds a Graded CTL properties.\n");
  /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  fprintf(nusmv_stderr, "  -l \t\tAdds an LTL property.\n");
  fprintf(nusmv_stderr, "  -i \t\tAdds an INVAR property.\n");
  fprintf(nusmv_stderr, "  -s \t\tAdds a PSL property.\n");
  fprintf(nusmv_stderr, "  -q \t\tAdds a quantitative (COMPUTE) property.\n");
  fprintf(nusmv_stderr, "  -p \"formula\"\tThe property to be added. "\
	  "It must be of the type specified.\n");
  return(1);
}


/**Function********************************************************************

  Synopsis           [Checks properties]

  CommandName        [check_property]

  CommandSynopsis    [Checks a property into the current list of properties, 
  or a newly specified property]

  CommandArguments   [\[-h\] \[-n number\] | \[(-c | -g | -l | -i | -s | -q )
  \[-p "formula \[IN context\]"\]\] ]

  CommandDescription [
  Checks the specified property taken from the property list, or adds
  the new specified property and checks it.

  <p>
  Command options:<p>
  <dl>
    <dt> <tt>-h</tt>
       <dd> Prints the help.
    <dt> <tt>-c</tt>
       <dd> Checks all the CTL properties not already checked
    <dt> <tt>-g</tt>
       <dd> Checks all the Graded CTL properties not already checked
    <dt> <tt>-l</tt>
       <dd> Checks all the LTL properties not already checked
    <dt> <tt>-i</tt>
       <dd> Checks all the INVAR properties not already checked
    <dt> <tt>-s</tt>
       <dd> Checks all the PSL properties not already checked
    <dt> <tt>-q</tt>
       <dd> Checks all the COMPUTE properties not already checked
    <dt> <tt>-n number</tt>
       <dd> Checks the property with id <tt>number</tt> in the
            property list if it exists.
    <dt> <tt>-p "formula \[IN context\]"</tt>
       <dd> Checks the <tt>formula</tt> specified on the command-line. <BR>
            <tt>context</tt> is the module instance name which the variables
            in <tt>formula</tt> must be evaluated in.
  </dl>
  If no property has been specified via <tt>-n</tt> or <tt>-p</tt>,
  then all the properties (of a given type) in the property list will be
  evaluated.]

  SeeAlso            [check_property]

  SideEffects        []

******************************************************************************/
int CommandCheckProperty (int argc, char **argv)
{
  int c = 0;
  int prop_no = -1;
  Prop_Type pt = Prop_NoType;
  char* formula = NIL(char);
  util_getopt_reset();

  while((c = util_getopt(argc, argv, "hn:p:cglisq")) != EOF){
    switch(c){
    case 'h': return(UsageCheckProperty());
    case 'n':
      {
        if (pt != Prop_NoType) return(UsageCheckProperty());
        if (formula != NIL(char)) return(UsageCheckProperty());
        if (prop_no != -1) return(UsageCheckProperty());

        prop_no = PropDb_get_prop_index_from_string(util_optarg);
        if (prop_no == -1) return(1);

        break;
      }
    case 'p':
      {
        if (pt == Prop_NoType) return(UsageCheckProperty());
        if (prop_no != -1) return(UsageCheckProperty());
        if (formula != NIL(char)) return(UsageCheckProperty());

        formula = util_strsav(util_optarg);
        break;
      }
    case 'c':
      {
        if (prop_no != -1 || pt != Prop_NoType) {
          return(UsageCheckProperty());
        }
        pt = Prop_Ctl;
        break;
      }
      
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    case 'g':
      {
        if (prop_no != -1 || pt != Prop_NoType) {
          return(UsageCheckProperty());
        }
        pt = Prop_Ctlg;
        break;
      }
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    
    case 'l':
      {
        if (prop_no != -1 || pt != Prop_NoType) {
          return(UsageCheckProperty());
        }
        pt = Prop_Ltl;
        break;
      }
    case 'i':
      {
        if (prop_no != -1 || pt != Prop_NoType) {
          return(UsageCheckProperty());
        }
        pt = Prop_Invar;
        break;
      }
    case 's':
      {
        if (prop_no != -1 || pt != Prop_NoType) {
          return(UsageCheckProperty());
        }
        pt = Prop_Psl;
        break;
      }
    case 'q':
      {
        if (prop_no != -1 || pt != Prop_NoType) {
          return(UsageCheckProperty());
        }
        pt = Prop_Compute;
        break;
      }
    default:
      return(UsageCheckProperty());
    }
  }
  if (argc != util_optind) return(UsageCheckProperty());

  /* command hierarchy control */
  if (Compile_check_if_model_was_built(nusmv_stderr, false)) return 1;

  if (pt != Prop_NoType) {
    if (formula == NIL(char)) {
      CATCH {
        PropDb_verify_all_type(pt);
      }
      FAIL {
        return(1);
      }
    }
    else {
      int result;
      result = PropDb_prop_parse_and_add(Compile_get_global_symb_table(), 
					 formula, pt);
      if (result == -1) return(1); /* error */
      PropDb_verify_prop_at_index(result);
    }
  }
  else {
    if (prop_no == -1) {
      CATCH {
        PropDb_verify_all();
      } FAIL {
        return(1);
      }
    }
    else {
      CATCH {
        PropDb_verify_prop_at_index(prop_no);
      }
      FAIL {
        return(1);
      }
    }
  }
  return(0);
}

static int UsageCheckProperty()
{
  fprintf(nusmv_stderr, "usage: check_property [-h]\n" \
	  "       [-n number] | [-c | -g  | -l | -i | -s | -q [-p \"formula\"]]\n");
  fprintf(nusmv_stderr, "  -h \t\t Prints the command usage.\n");
  fprintf(nusmv_stderr, "  -n number \t Checks property number.\n");
  fprintf(nusmv_stderr, "  -c \t\t Checks CTL properties.\n");

  /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  fprintf(nusmv_stderr, "  -g \t\t Checks Graded CTL properties.\n");
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  fprintf(nusmv_stderr, "  -l \t\t Checks LTL properties.\n");
  fprintf(nusmv_stderr, "  -i \t\t Checks INVAR properties.\n");
  fprintf(nusmv_stderr, "  -s \t\t Checks PSL properties.\n");
  fprintf(nusmv_stderr, "  -q \t\t Checks COMPUTE properties.\n");
  fprintf(nusmv_stderr, "  -p \"formula\"\t Checks the given formula.\n");
  return(1);
}

/*---------------------------------------------------------------------------*/
/* Definition of static functions                                            */
/*---------------------------------------------------------------------------*/


