#ifndef argparser_argument_h
#define argparser_argument_h

#include "hashtable.h"


#define ARGPARSER_NAME_MAX_LENGTH 20
#define ARGPARSER_HELP_MAX_LENGTH 256
#define ARGUMENT_HELP_MAX_LENGTH 100
#define ARGUMENT_VALUE_MAX_LENGTH 100


// Type of arguments we support.
typedef enum {
  FLAG,
  SWITCH,
  VALUE
} ArgumentType;


/*
 * Argument is the user-defined template which gives us
 * hints on how to parse the actual command-line args.
 * The info of the Argument allows us to generate the
 * help text later on.
 */
typedef struct {
  char name[ARGPARSER_NAME_MAX_LENGTH];
  char help[ARGUMENT_HELP_MAX_LENGTH];
  char value[ARGUMENT_VALUE_MAX_LENGTH];
  ArgumentType type;
} Argument;


/*
 * Command is the collection of arguments. This has a name and it's own
 * help text which is generated using its `arguments` list.
 * If the command has `sub=1` it will be regarded as a sub command.
 * ./program subcmd <subcmd_args>
 */
typedef struct {
  char name[ARGPARSER_NAME_MAX_LENGTH];
  char help[ARGPARSER_HELP_MAX_LENGTH];
  Argument* arguments;
  int count;
  int capacity;
  int requiredArgs;
  int sub;
} Command;


/*
 * Argparser is the main struct the user will initialize to start
 * using the ArgParser. This has a list of commands. By default,
 * it has a single command. If the user creates more commands,
 * all of the commands will be regarded as a subcommands.
 */
typedef struct {
  Command* commands;
  int capacity;
  int count;
} ArgParser;


void InitArgParser();
Command* CreateCommand(char* name, char* help);
void AddArgument(Command* cmd, char* name, char* help, ArgumentType type);
void ParseArgs(int argc, char** argv);
void PrintHelp(void);
void PrintArgs(void);
void FreeArgParser(void);


#endif
