#include "include/common.hpp"
#include <cctype>
#include <iostream>
#include <iterator>
#include <vector>

void sendHelpMessage() {

  std::cout << "Ripgit ~ Made by smegaa" << std::endl;
  std::cout << "Version: " << VERSION << std::endl;
  std::cout << " Usage: ripgit [command]" << std::endl;
  std::cout << " Commands:" << std::endl;
  std::cout << "  help --> shows this message" << std::endl;
  std::cout << "  version --> print the version of ripgit to the screen"
            << std::endl;
}

int ripgitError(std::string string) {

  std::cout << "ripgit fatal error: " << string << std::endl;
  return 1;
}

std::vector<Argument> detectArguments(int argc, char *argv[]) {

  std::vector<Argument> argument;
  bool found = false;

  for (int i = 1; i < argc; i++) {

    for (Argument &x : ARGUMENT_LIST) {

      if (std::string(argv[i]) == x.name) {
        found = true;

        if (x.name == "help") {

          Argument help;
          help.name = "help";
          argument.push_back(help);
          break;

        } else if (x.name == "version") {

          Argument version;
          version.name = "version";
          argument.push_back(version);
          break;
        }
      }
    }
    if (!found) {

      ripgitError("unknown argument: " + std::string(argv[i]));
      break;
    }
  }
  return argument;
}

void parseArguments(std::vector<Argument> arguments, int argc, char *argv[]) {

  for (Argument &x : arguments) {

    if (x.name == "help") {

      sendHelpMessage();

    } else if (x.name == "version") {

      std::cout << "Version: " << VERSION << std::endl;
    }
  }
}
