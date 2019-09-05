#ifndef FS_HPP
#define FS_HPP

#include <cstring>
#include <filesystem>
#include <string_view>
#include <vector>
#include "physfs.h"
namespace xhfr {
namespace fs {
  enum FileType { Regular, Directory, Symlink, Other };
  struct FileInfo {
    std::string name, path;
    long long size;
    FileType type;
    bool readonly;
    bool operator==(const FileInfo& fileInfo) const {
      return path == fileInfo.path;
    }
  };

  bool init(const char* path);
  void shutdown();
  bool createDirectory(std::string_view path);
  std::vector<FileInfo> listFiles(std::string_view path);
  bool deleteFile(std::string_view path);
};
}  // namespace xhfr

#endif  // FS_HPP
