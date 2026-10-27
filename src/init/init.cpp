#include "../include/init.hpp"
#include "../include/common.hpp"
#include <filesystem>
#include <fstream>

int init() {

  fs::path gitDir = fs::current_path() / ".git/";

  // Create the .git folder

  if (!fs::exists(gitDir)) {

    fs::create_directory(gitDir);
  } else {

    ripgitError("Directory already exists");
    return 1;
  }

  // Create .git/objects/ and .git/refs/heads

  fs::create_directory(gitDir / "objects");
  fs::create_directories(gitDir / "refs" / "heads");

  std::ofstream head(gitDir / "HEAD");

  if (!head) {
    ripgitError("Failed to create file");
    return 1;
  }

  head << "ref: refs/heads/main";
  head.close();

  std::ofstream config(gitDir / "config");

  if (!config) {

    ripgitError("Failed to create file");
    return 1;
  }

  config << "[core]" << std::endl;
  config << "  repositoryformatversion = 0" << std::endl;
  config << "  filemode = false" << std::endl;
  config << "  bare = false" << std::endl;

  config.close();

  std::cout << "Git folder initialized at: " << gitDir.string() << std::endl;
  return 0;
}
