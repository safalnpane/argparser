#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memory.h"
#include "argparser.h"


ArgParser argparser;


void InitArgParser() {
  argparser.count = 0;
  argparser.capacity = 0;
  argparser.commands = NULL;
}


Command* CreateCommand(char* name, char* help) {
  Command cmd;
  strcpy(cmd.name, name);
  strcpy(cmd.help, help);
  cmd.count = 0;
  cmd.capacity = 0;
  cmd.requiredArgs = 0;
  cmd.arguments = NULL;

  if (argparser.capacity == argparser.count) {
    int oldCapacity = argparser.capacity;
    argparser.capacity = GROW_CAPACITY(oldCapacity);
    argparser.commands = GROW_ARRAY(Command, argparser.commands, argparser.capacity);
  }

  argparser.commands[argparser.count] = cmd;
  argparser.count++;

  return &argparser.commands[argparser.count - 1];
}


void AddArgument(Command* cmd, char* name, char* help, ArgumentType type) {
  Argument arg;
  strcpy(arg.name, name);
  strcpy(arg.help, help);
  arg.type = type;

  if (type == VALUE) {
    cmd->requiredArgs++;
  }

  if (cmd->capacity == cmd->count) {
    int oldCapacity = cmd->capacity;
    cmd->capacity = GROW_CAPACITY(oldCapacity);
    cmd->arguments = GROW_ARRAY(Argument, cmd->arguments, cmd->capacity);
  }

  cmd->arguments[cmd->count] = arg;
  cmd->count++;
}


void ParseArgs(int argc, char** argv) {
  printf("Parsing arguments\n");
  printf("Argc: %d\n", argc);
  printf("Argv: %s\n", argv[0]);
}


void FreeArgParser() {
  FREE_ARRAY(Argument, argparser.commands, argparser.capacity);
}


void PrintHelp(void) {
  int commands = argparser.count;
  if (commands == 1) {
    printf("Usage: %s [arguments]\n", argparser.commands[0].name);
    printf("%s\n", argparser.commands[0].help);
    printf("\nArguments:\n");
    for (int i = 0; i < argparser.commands[0].count; i++) {
      printf("%s\t", argparser.commands[0].arguments[i].name);
      printf("%s\n", argparser.commands[0].arguments[i].help);
    }
    return;
  } else {
    printf("Usage: %s [command] [arguments]\n", argparser.commands[0].name);
    printf("%s\n", argparser.commands[0].help);
    printf("\nCommands:\n");
    for (int i = 1; i < commands; i++) {
      printf("%s\t", argparser.commands[i].name);
      printf("%s\n", argparser.commands[i].help);
    }
    printf("\nArguments:\n");
    printf("-h\tPrints this help message\n");
    printf("[command] -h Prints help message for the command\n");
  }
}
