#include "File.hpp"

namespace xhfr {

File::File(std::string_view path, bool write) {
  open(path, write);
}

File::~File() {
  close();
}

bool File::open(std::string_view path, bool write) {
  if (path.front() == ':') {
    std::string str = path.data();
    str = str.substr(1);
    if (str.front() == '/') {
      str = str.substr(1);
    }
    if (write) {
      auto writeDir = PHYSFS_getWriteDir();
      str = str.substr(strlen(writeDir));
      if (str.front() == '/') {
        str = str.substr(1);
      }
      phFile = PHYSFS_openWrite(str.c_str());
    } else {
      phFile = PHYSFS_openRead(str.c_str());
    }
    isPhFile = true;
    return phFile;
  }
  file = fopen(path.data(), write ? "rw" : "w");
  return file;
}

ssize_t File::size() {
  if (isPhFile)
    return PHYSFS_fileLength(phFile);
  else {
    return fileSize;
  }
}

void File::close() {
  if (!file) {
    return;
  }
  isPhFile ? PHYSFS_close(phFile) : fclose(file);
  file = nullptr;
}

int64_t File::read(void* buffer, size_t size) {
  if (isPhFile) {
    return PHYSFS_readBytes(phFile, buffer, size);
  } else {
    return fread(buffer, 1, size, file);
  }
}

std::string File::readAll() {
  ssize_t fsize = size();
  std::string buffer;
  buffer.resize(fsize);
  read(buffer.data(), fsize);
  return buffer;
}

int64_t File::write(void* buffer, size_t size) {
  if (isPhFile) {
    return PHYSFS_writeBytes(phFile, buffer, size);
  } else {
    return fwrite(buffer, 1, size, file);
  }
}

int64_t File::write(std::string_view str) {
  return write((void*)str.data(), strlen(str.data()));
}

}  // namespace xhfr
