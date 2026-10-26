#include "include/common.hpp"
#include <cctype>
#include <iostream>
#include <iterator>
#include <vector>

void sendHelpMessage() {

  std::cout << "Ripgit ~ Made by smegaa" << std::endl;
  std::cout << "Version " << VERSION << std::endl;
}
std::vector<Argument> detectArguments(int argc, char *argv[]) {

  std::vector<Argument> argument;

  for (int i = 1; i < argc; i++) {

    for (Argument &x : ARGUMENT_LIST) {

      if (std::string(argv[i]) == x.name) {

        if (x.name == "help") {

          Argument help;
          help.name = "help";
          help.detected = true;
          argument.push_back(help);
          break;

        } else if (x.name == "version") {

          Argument version;
          version.name = "version";
          version.detected = true;
          argument.push_back(version);
          break;

        } else {

          std::cout << "Argument not recognized! " << std::endl;
          break;
        }
      }
    }
  }

  return argument;
}

void parseArguments(std::vector<Argument> arguments, int argc, char *argv[]) {

  for (Argument &x : arguments) {

    if (x.name == "help") {

      sendHelpMessage();

    } else if (x.name == "version") {

      std::cout << VERSION << std::endl;
    }
  }
}
