#ifndef argparser_argument_h
#define argparser_argument_h


#define ARGPARSER_NAME_MAX_LENGTH 20
#define ARGPARSER_HELP_MAX_LENGTH 256
#define ARGUMENT_HELP_MAX_LENGTH 100
#define ARGUMENT_VALUE_MAX_LENGTH 100



typedef enum {
  FLAG,
  SWITCH,
  VALUE
} ArgumentType;


typedef struct {
  char name[ARGPARSER_NAME_MAX_LENGTH];
  char help[ARGUMENT_HELP_MAX_LENGTH];
  ArgumentType type;
  char value[ARGUMENT_VALUE_MAX_LENGTH];
} Argument;


typedef struct {
  char name[ARGPARSER_NAME_MAX_LENGTH];
  char help[ARGPARSER_HELP_MAX_LENGTH];
  Argument* arguments;
  int argc;
  int count;
  int capacity;
  char **argv;
} ArgParser;


void initArgParser(char* name, char* help, int argc, char **argv);
void addArgument(char* name, char* help, ArgumentType type);
void printHelp(void);


#endif
