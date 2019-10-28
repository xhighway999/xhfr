#ifndef FILE_HPP
#define FILE_HPP

#include <stdio.h>

#include <cstring>

#include "fs.hpp"
namespace xhfr {

class File {
 public:
  File() = default;
  File(std::string_view path, bool write = false) /*openmode*/;
  ~File();
  bool open(std::string_view path, bool write);  // open mode
  ssize_t size();
  void close();
  int64_t read(void* buffer, size_t size);
  std::string readAll();
  int64_t write(void* buffer, size_t size);
  int64_t write(std::string_view str);

  union {
    FILE* file;
    PHYSFS_File* phFile;
  };

  std::uintmax_t fileSize;
  bool isPhFile = false;
};

}  // namespace xhfr

#endif  // FILE_HPP
