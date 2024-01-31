#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memory.h"
#include "argparser.h"


ArgParser argparser;


void initArgParser(char* name, char* help, int argc, char** argv) {
  argparser.argc = argc;
  argparser.argv = argv;
  argparser.count = 0;
  argparser.capacity = 0;
  strncpy(argparser.name, name, ARGPARSER_NAME_MAX_LENGTH);
  strncpy(argparser.help, help, ARGPARSER_HELP_MAX_LENGTH);
  argparser.arguments = NULL;
}


void addArgument(char* name, char* help, ArgumentType type) {
  Argument argument;
  strncpy(argument.name, name, ARGPARSER_NAME_MAX_LENGTH);
  strncpy(argument.help, help, ARGUMENT_HELP_MAX_LENGTH);
  argument.type = type;

  if (argparser.count == argparser.capacity) {
    argparser.capacity = GROW_CAPACITY(argparser.capacity);
    argparser.arguments = GROW_ARRAY(Argument, argparser.arguments, argparser.capacity);
  }

  argparser.arguments[argparser.count] = argument;
  argparser.count++;
}





void printHelp(void) {
  printf("Usage: %s\n", argparser.name);
  printf("\tARGS\tHELP\n");
  printf("\t%s\t%s\n", "-h", "Print this help message");
  for (int i = 0; i < argparser.count; i++) {
    Argument argument = argparser.arguments[i];
    switch (argument.type) {
      case SWITCH:
        printf("\t-%s\t%s\n", argument.name, argument.help);
        break;
      case FLAG:
        printf("\t--%s\t%s\n", argument.name, argument.help);
        break;
      case VALUE:
        printf("\t%s\t%s\n", argument.name, argument.help);
        break;
      default:
        printf("Unknown argument type\n");
        exit(1);
    }
  }
}
