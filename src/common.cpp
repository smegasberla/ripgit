#include "include/common.hpp"
#include "include/init.hpp"
#include <cctype>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

void sendHelpMessage() {

  std::cout << "Ripgit ~ Made by smegaa" << std::endl;
  std::cout << "Version: " << VERSION << std::endl;
  std::cout << " Usage: ripgit [command]" << std::endl;
  std::cout << " Commands:" << std::endl;
  std::cout << "  help --> shows this message" << std::endl;
  std::cout << "  version --> print the version of ripgit to the screen"
            << std::endl;
  std::cout << "  init --> initialize a git project" << std::endl;
}

int ripgitError(std::string string) {

  std::cout << "ripgit fatal error: " << string << std::endl;
  return 1;
}

std::vector<Argument> detectArguments(int argc, char *argv[]) {

  std::vector<Argument> argument;

  for (int i = 1; i < argc; i++) {
    bool found = false;

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
        } else if (x.name == "init") {

          Argument init;
          init.name = "init";
          argument.push_back(init);
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

    } else if (x.name == "init") {

      // We use the init function to start the initialization of a git project
      init();
    }
  }
}

std::string binaryToHex(std::vector<unsigned char> &digest) {

  std::ostringstream oss;

  for (auto x : digest) {

    oss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(x);
  }

  return oss.str();
}
