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


void AddArgument(Command* cmd, char* name, char* help, ArgumentType type) {

}


void ParseArguments(int argc, char** argv) {
}


void FreeArgParser() {
  FREE_ARRAY(Argument, argparser.commands, argparser.capacity);
}


void PrintHelp(void) {
}
