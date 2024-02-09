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
  for (int i = 0; i < commands; i++) {
    printf("Command: %s\n", argparser.commands[i].name);
    printf("Help: %s\n", argparser.commands[i].help);
    printf("Arguments: %d\n", argparser.commands[i].count);
    for (int j = 0; j < argparser.commands[i].count; j++) {
      printf("  Argument: %s\n", argparser.commands[i].arguments[j].name);
      printf("  Help: %s\n", argparser.commands[i].arguments[j].help);
      printf("  Type: %d\n", argparser.commands[i].arguments[j].type);
    }
  }
}
