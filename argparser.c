#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memory.h"
#include "hashtable.h"
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


void parseArguments(void) {
  if (argparser.argc == 1) {
    printHelp();
    exit(0);
  }

  HashTable* table = create_table(20);

  for (int i = 1; i < argparser.argc; i++) {
    char* currentArg = argparser.argv[i];
    if (currentArg[0] == '-') {
      // Could be a switch or a flag
      if (currentArg[1] == '-') {
        // It's a flag, get the data after '='
        char* key = strtok(currentArg + 2, "=");
        char* value = strtok(NULL, "=");
        insert(table, key, value);
      } else {
        // It's a switch
        char* key = currentArg + 1;
        char* value = "true";
        insert(table, key, value);
      }
    }
  }

  for (int i = 0; i < argparser.count; i++) {
    Argument argument = argparser.arguments[i];
    HashTableItem* value = search(table, argument.name);
    if (value == NULL) {
      if (argument.type == SWITCH)
        continue;
      printf("Argument Error: %s is required\n", argument.name);
      printHelp();
      exit(1);
    }
    printf("%s: %s\n", argument.name, value->value);
  }

  free_table(table);
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
