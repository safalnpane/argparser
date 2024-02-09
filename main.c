
#include "argparser.h"


int main(int argc, char* argv[]) {
  InitArgParser();
  Command* argParser = CreateCommand("argparser", "just an experiment on arg parsing");
  AddArgument(argParser, "database", "database file", VALUE);
  AddArgument(argParser, "name", "person's name", FLAG);
  AddArgument(argParser, "age", "person's age", FLAG);
  AddArgument(argParser, "create", "create action", SWITCH);

  ParseArgs(argc, argv);
  PrintArgs();

  FreeArgParser();
  return 0;
}
