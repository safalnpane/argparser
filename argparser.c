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


void parseCommand(int count, char** args, Command* cmd) {
  for (int i = 0; i < cmd->count; i++) {
    Argument *arg = &cmd->arguments[i];

    for (int j = 0; j < count; j++) {
      char* currentArg = args[j];
      char* strippedArg = currentArg;

      if (currentArg[0] == '-') {
        // flag or switch
        if (currentArg[1] == '-') {
          strippedArg = strtok(currentArg, "=");
          // strip the '--'
          strippedArg += 2;
        } else {
          strippedArg = currentArg + 1;
        }
      } else {
        // value
        if (arg->type == VALUE) {
          strncpy(arg->value, currentArg, ARGUMENT_VALUE_MAX_LENGTH);
          break;
        }
      }

      if (strcmp(strippedArg, arg->name) == 0) {
        if (arg->type == FLAG) {
          // get the value after the '='
          strippedArg = strtok(NULL, "=");
          strncpy(arg->value, strippedArg, ARGUMENT_VALUE_MAX_LENGTH);
          break;
        } else if (arg->type == SWITCH) {
          strncpy(arg->value, "1", ARGUMENT_VALUE_MAX_LENGTH);
          break;
        } else {
          printf("Unknown argument: %s\n", strippedArg);
          return;
        }
      }
    }
  }
}


void ParseArgs(int argc, char** argv) {
  if (argc == 1 || strcmp(argv[1], "-h") == 0) {
    PrintHelp();
    exit(0);
  }

  if (argparser.count == 1) {
    // Handle single command
    parseCommand(argc-1, argv + 1, &argparser.commands[0]);
    return;
  }

  // // Handle multiple commands
  // for (int i = 1; i < argc; i++) {
  //   for (int j = 0; j < argparser.count; j++) {
  //   }
  // }
}


void FreeArgParser() {
  for (int i = 0; i < argparser.count; i++) {
    FREE_ARRAY(Argument, argparser.commands[i].arguments, argparser.commands[i].capacity);
  }
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


void PrintArgs(void) {
  printf("\n");
  for (int i = 0; i < argparser.count; i++) {
    printf("Command: %s\n", argparser.commands[i].name);
    for (int j = 0; j < argparser.commands[i].count; j++) {
      printf("Argument: %s\n", argparser.commands[i].arguments[j].name);
      printf("Value: %s\n", argparser.commands[i].arguments[j].value);
    }
  }
}
