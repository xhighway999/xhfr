#ifndef FS_HPP
#define FS_HPP

#include <cstring>
#include <filesystem>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

#include "../core/debug.hpp"

#include "physfs.h"
namespace xhfr {
namespace fs {
enum FileType { Regular, Directory, Symlink, Other };
struct FileInfo {
  std::string name;
  std::string path;
  long long size;
  FileType type;
  bool readonly;
  bool operator==(const FileInfo& fileInfo) const {
    return path == fileInfo.path;
  }
};

bool init(const char* path);
void shutdown();
bool exists(std::string_view path);
bool createDirectory(std::string_view path);
std::vector<FileInfo> listFiles(std::string_view path, bool recursiv = false);
FileInfo getFileInfo(std::string_view path);

bool deleteFile(std::string_view path);
void flush();
};  // namespace fs
}  // namespace xhfr

#endif  // FS_HPP
