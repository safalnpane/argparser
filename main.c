#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "argparser.h"


int main(int argc, char* argv[]) {
  InitArgParser();
  Command* argParser = CreateCommand("argparser", "just an experiment on arg parsing");
  AddArgument(argParser, "database", "database file", VALUE);
  AddArgument(argParser, "name", "person's name", FLAG);
  AddArgument(argParser, "age", "person's age", FLAG);
  AddArgument(argParser, "create", "create action", SWITCH);

  Command* anotherCmd = CreateCommand("anotherCmd", "just another command");
  AddArgument(anotherCmd, "sex", "person's sex", FLAG);
  AddArgument(anotherCmd, "destroy", "destroy action", SWITCH);

  Command* parsedCmd = ParseArgs(argc, argv);
  if (parsedCmd == NULL) {
    printf("Unknown command\n");
    return 1;
  }

  if (strcmp(parsedCmd->name, "argparser") == 0) {
    // Main command
    char* db = GetArgValue(parsedCmd, "database");
    if (strlen(db) <= 1) {
      printf("Database file is required\n");
      FreeArgParser();
      return 1;
    }
    printf("Database: %s\n", db);

    char* name = GetArgValue(parsedCmd, "name");
    if (strlen(name) > 0) {
      printf("Name: %s\n", name);
    }

    char* create = GetArgValue(parsedCmd, "create");
    if (strlen(create) > 0) {
      printf("Create: %s\n", create);
    }

  }

  if (strcmp(parsedCmd->name, "anotherCmd") == 0) {
    // Another command
    char* sex = GetArgValue(parsedCmd, "sex");
    if (strlen(sex) > 0) {
      printf("Sex: %s\n", sex);
    }
  }


  FreeArgParser();
  return 0;
}
