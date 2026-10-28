#include <cstddef>
#include <iostream>
#include <vector>

// Common header file
// Contains common information that could be needed for majority of files

// Written by smegaa the 26/10/2026 at 18:23

const std::string VERSION = "0.1.0";

void sendHelpMessage();

struct SubArg;

struct Argument {

  std::string name;
  bool detected;
  std::vector<SubArg> subArgs;
};

typedef struct SubArg {
  Argument *main = nullptr;
  std::string name;
  std::string value;
  bool isFlag = false;
  bool isLong = false;
  SubArg *before = nullptr;
  SubArg *after = nullptr;
} SubArg;

inline std::vector<Argument> ARGUMENT_LIST = {

    {"help", false},
    {"version", false},
    {"init", false},
    {"hash-object", false},
};

std::vector<Argument> detectArguments(int argc, char *argv[]);

void parseArguments(std::vector<Argument> arguments, int argc, char *argv[]);

int ripgitError(std::string string);

std::string binaryToHex(std::vector<unsigned char> &digest);
