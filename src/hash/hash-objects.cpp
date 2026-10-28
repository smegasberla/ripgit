#include "../include/hash-objects.hpp"
#include "../include/common.hpp"
#include <filesystem>
#include <fstream>
#include <openssl/sha.h>
#include <zlib.h>

namespace fs = std::filesystem;

std::string hashObjects(size_t sizeInBytes, std::string fileContents,
                        bool print) {

  std::string sizeStr =
      std::to_string(sizeInBytes); // transform the sizeInBytes to string

  std::string stream =
      "blob " + sizeStr + '\0' + fileContents; // get the string to hash

  std::vector<unsigned char> buffer(20); // declare a buffer

  SHA1(reinterpret_cast<const unsigned char *>(stream.c_str()), stream.size(),
       buffer.data()); // Actually hash the string

  std::string fullHash =
      binaryToHex(buffer); // Converting the binary string to hex.

  std::string dirName = fullHash.substr(0, 2); // directory name from the hash
  std::string fileName = fullHash.substr(2);   // file name from the hash

  fs::path dirPath = OBJ_DIR / dirName / fileName; // path of the directory

  // If it exists we stop here
  if (fs::exists(dirPath)) {
    ripgitError("Object already exists");
    return "";
  }

  uLong sourceLen =
      stream.size(); // saving the size of the stream string as uLong
  uLong boundedSize =
      compressBound(sourceLen); // using compressBound as a safe upper limit and
                                // buffer for compression

  std::vector<unsigned char> compressed(boundedSize); // buffer
  uLongf actualSize = boundedSize; // How much space does the compression have

  // Compression
  int result =
      compress(compressed.data(), &actualSize,
               reinterpret_cast<const Bytef *>(stream.data()), sourceLen);

  // Error check
  if (result != Z_OK) {
    ripgitError("Compression failed");
    return "";
  }

  // Cleanup
  compressed.resize(actualSize);

  // Creating the directory and file
  fs::create_directories(dirPath.parent_path());
  std::ofstream objectFile(dirPath);

  // Writing to the file the raw compressed data
  objectFile.write(reinterpret_cast<const char *>(compressed.data()),
                   compressed.size());

  // Closing the file
  objectFile.close();

  // Printing the full hash to stdout
  if (print) {

    std::cout << "Full hash: " << fullHash << std::endl;
  }

  // returning the hash
  return fullHash;
}
