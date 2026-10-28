#include "../include/hash-objects.hpp"
#include "../include/common.hpp"
#include <filesystem>
#include <fstream>
#include <openssl/sha.h>
#include <zlib.h>

namespace fs = std::filesystem;

std::string hashObjects(size_t sizeInBytes, std::string fileContents) {

  std::string sizeStr = std::to_string(sizeInBytes);

  std::string stream = "blob " + sizeStr + '\0' + fileContents;

  std::vector<unsigned char> buffer(20);

  SHA1(reinterpret_cast<const unsigned char *>(stream.c_str()), stream.size(),
       buffer.data());

  std::string fullHash = binaryToHex(buffer);

  std::string dirName = fullHash.substr(0, 2);
  std::string fileName = fullHash.substr(2);

  fs::path dirPath = OBJ_DIR / dirName / fileName;

  if (fs::exists(dirPath)) {
    ripgitError("Object already exists");
    return "";
  }

  uLong sourceLen = stream.size();
  uLong boundedSize = compressBound(sourceLen);

  std::vector<unsigned char> compressed(boundedSize);
  uLongf actualSize = boundedSize;

  int result =
      compress(compressed.data(), &actualSize,
               reinterpret_cast<const Bytef *>(stream.data()), sourceLen);

  if (result != Z_OK) {
    ripgitError("Compression failed");
    return "";
  }

  compressed.resize(actualSize);

  fs::create_directories(dirPath.parent_path());
  std::ofstream objectFile(dirPath);

  objectFile.write(reinterpret_cast<const char *>(compressed.data()),
                   compressed.size());
  objectFile.close();

  std::cout << "Full hash: " << fullHash << std::endl;
  return fullHash;
}
