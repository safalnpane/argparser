#include <stdio.h>
#include <stdlib.h>

#include "argparser.h"
#include "hashtable.h"


int main(int argc, char* argv[]) {
  initArgParser("argparser", "A simple argument parser",
                argc, argv);
  addArgument("name", "Your name", FLAG);
  addArgument("dbfile", "Database file", VALUE);
  HashTable* args = parseArguments();

  HashTableItem* name = search(args, "name");
  HashTableItem* dbfile = search(args, "dbfile");

  if (name != NULL)
    printf("Hello, %s\n", name->value);
  if (dbfile != NULL)
    printf("Using database file: %s\n", dbfile->value);

  freeArgParser(args);
  return 0;
}
