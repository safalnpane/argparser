
#include "argparser.h"


int main(int argc, char* argv[]) {
  initArgParser("argparser", "A simple argument parser",
                argc, argv);
  addArgument("name", "Your name", SWITCH);
  addArgument("age", "Your name", SWITCH);
  addArgument("bug", "Bug id", FLAG);
  printHelp();
  return 0;
}
