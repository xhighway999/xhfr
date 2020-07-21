#include "fs.hpp"
#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif
namespace xhfr {
bool fs::init(const char* path) {
  XHFR_INFO("Starting fs subsystem");
#ifdef __EMSCRIPTEN__
  XHFR_INFO("Making fs persistent");
  // assume app wants to store data

  EM_ASM(FS.mkdir('/persistent'); FS.mount(IDBFS, {}, '/persistent');
         FS.syncfs(function(err) { assert(!err); }););
#endif
  XHFR_INFO("Starting Physfs subsystem");
  if (!PHYSFS_init(path)) {
    return false;
  }

  return true;
}

void fs::shutdown() {
#ifdef __EMSCRIPTEN__
  XHFR_INFO("Flush data to indexed db");
  flush();
#endif
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
    if (str.back() != '/') {
      str += '/';
    }
    if (recursive) {
      std::function<std::vector<fs::FileInfo>(std::vector<fs::FileInfo>)>
          getAllFolders = [&](std::vector<fs::FileInfo> files) {
            std::vector<fs::FileInfo> newFiles;

            for (const auto& file : files) {
              if (file.type == FileType::Directory) {
                auto ff = xhfr::fs::listFiles(file.path, false);
                auto fff = getAllFolders(ff);
                newFiles.insert(newFiles.end(), ff.begin(), ff.end());

                newFiles.insert(newFiles.end(), fff.begin(), fff.end());
              }
            }

            return newFiles;
          };
      FileInfo f;
      f.path = path;
      f.type = FileType::Directory;
      dirfiles = getAllFolders({f});

    } else {
      char** files = nullptr;
      files = PHYSFS_enumerateFiles(str.data());
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
    }

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

void fs::flush() {
  XHFR_DEBUG("Flushing file system");
#ifdef __EMSCRIPTEN__
  EM_ASM(FS.syncfs(function(err) { assert(!err); }););
#endif
}

}  // namespace xhfr
