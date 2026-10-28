#include <filesystem>
#include <openssl/sha.h>
#include <zlib.h>

namespace fs = std::filesystem;

const fs::path OBJ_DIR = fs::current_path() / ".git" / "objects";

std::string hashObjects(size_t sizeInBytes, std::string fileContents);
