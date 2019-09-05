#include "fs.hpp"

namespace xhfr {
bool fs::init(const char* path) {
  if (!PHYSFS_init(path)) {
    const PHYSFS_ErrorCode err = PHYSFS_getLastErrorCode();
    std::cerr << "PHYSFS_init() failed!\n  reason: \n"
              << PHYSFS_getErrorByCode(err) << std::endl;
    return false;
  }

  return true;
}

void fs::shutdown() {
  PHYSFS_deinit();
}

bool fs::createDirectory(std::string_view path) {
  return std::filesystem::create_directory(path);
}

std::vector<fs::FileInfo> fs::listFiles(std::string_view path) {
  std::vector<fs::FileInfo> dirfiles;
  if (path.front() == ':') {
    std::string str(path.substr(1));
    char** i;
    PHYSFS_Stat stat;
    char** files = PHYSFS_enumerateFiles(str.data());
    for (i = files; *i != nullptr; i++) {
      FileInfo f;
      f.name = *i;
      f.path = str + f.name;
      PHYSFS_stat(f.path.c_str(), &stat);
      f.path = ":" + f.path;
      f.type = static_cast<FileType>(stat.filetype);
      f.size = stat.filesize;
      f.readonly = stat.readonly;
      dirfiles.push_back(f);
    }
    PHYSFS_freeList(files);

  } else {
  }
  return dirfiles;
}

bool fs::deleteFile(std::string_view path) {
  if (path.front() == ':') {
    std::string str(path.substr(1));
    if (str.front() == '/')
      str = str.substr(1);
    str = str.substr(strlen(PHYSFS_getWriteDir()));
    if (str.front() == '/')
      str = str.substr(1);
    return PHYSFS_delete(str.c_str());
  } else {
    return std::filesystem::remove(path);
  }
}
}  // namespace xhfr
