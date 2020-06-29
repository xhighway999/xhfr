#include "fs.hpp"

namespace xhfr {
bool fs::init(const char* path) {
  if (!PHYSFS_init(path)) {
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

std::vector<fs::FileInfo> fs::listFiles(std::string_view path, bool recursive) {
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
    auto addNormalFile = [&dirfiles](const auto& p) {
      FileInfo f;
      f.path = p.path();
      f.name = p.path().filename();

      auto perms = std::filesystem::status(p.path()).permissions();

      // TODO: implement properly
      // assume we are the owner
      f.readonly = (perms & std::filesystem::perms::owner_write) ==
                   std::filesystem::perms::none;

      if (p.is_regular_file()) {
        f.size = p.file_size();
        f.type = Regular;
      } else if (p.is_directory()) {
        f.type = Directory;
      } else if (p.is_symlink()) {
        f.type = Symlink;
      } else {
        f.type = Other;
      }
      dirfiles.push_back(f);
    };
    if (recursive) {
      for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
        addNormalFile(p);
      }
    } else {
      for (auto& p : std::filesystem::directory_iterator(path)) {
        addNormalFile(p);
      }
    }
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

bool fs::exists(std::string_view path) {
  if (path.empty()) {
    return false;
  }
  if (path.front() == ':') {
    std::string str(path.substr(1));
    if (str.front() == '/')
      str = str.substr(1);
    // auto newstr = str.substr(strlen(PHYSFS_getWriteDir()));
    // str = newstr;
    if (str.front() == '/')
      str = str.substr(1);
    return PHYSFS_exists(str.c_str());
  } else {
    return std::filesystem::exists(path);
  }
}

}  // namespace xhfr
