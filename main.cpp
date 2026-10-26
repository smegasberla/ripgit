#include "src/include/common.hpp"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {

  // Main file for ripgit
  // Made by smegaa

  if (argc < 0)
    sendHelpMessage();

  std::vector<Argument> arguments = detectArguments(argc, argv);
  parseArguments(arguments, argc, argv);

  return 0;
}
