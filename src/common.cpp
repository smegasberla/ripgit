#include "include/common.hpp"
#include "include/init.hpp"
#include <cctype>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
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

  std::vector<Argument> result;
  Argument *currentCommand = nullptr;
  SubArg *lastSubArg = nullptr;
  bool seenAnyCommand = false;

  for (int i = 1; i < argc; i++) {
    bool found = false;
    std::string str = std::string(argv[i]);

    if (str.rfind("--", 0) == 0) {

      SubArg longArg;
      longArg.name = str.substr(2);

      continue;
    } else if (str.rfind("-", 0) == 0) {

      SubArg shortArg;
      shortArg.name = str.substr(1);

      continue;
    }

    for (Argument &x : ARGUMENT_LIST) {
      if (std::string(argv[i]) == x.name) {
        found = true;

        if (x.name == "help") {
          found = true;

          Argument help;
          help.name = "help";
          result.push_back(help);
          break;

        } else if (x.name == "version") {
          found = true;

          Argument version;
          version.name = "version";
          result.push_back(version);
          break;
        } else if (x.name == "init") {
          found = true;

          Argument init;
          init.name = "init";
          result.push_back(init);
          break;
        }
      }
    }
    if (!found) {
      ripgitError("unknown argument: " + std::string(argv[i]));
      break;
    }
  }
  return result;
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

  // Creates a string stream, like cout but instead of printing, everything
  // accumulates in memory
  std::ostringstream oss;

  for (auto x : digest) {

    // std::hex = formats the integers to hexadecimal
    // std::setfill('0') = pads the value minimum value with 0 (es: instead of
    // having 5, we have 05) std::setw(2) = applies to the very next thing in
    // the stream, sets a minimum of 2 charachters for that one value
    oss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(x);
  }

  return oss.str();
}
