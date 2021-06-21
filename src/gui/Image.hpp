#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string_view>

#include "../fs/File.hpp"
#include "backends/Backend.hpp"
#include "imgui.h"
#include "stb_image.h"

namespace xhfr {

class Image {
 public:
  Image();
  Image(const char* path);
  ~Image();
  // Image(const Image&) = delete;
  // void operator=(const Image&) = delete;
  ImTextureID textureID();
  void setInterpolationMode(GLenum interp);
  bool loadImageFromFile(const char* path);
  bool loadImageFromMemory(const char* data, unsigned size);
  void loadImageFromRaw(const unsigned char* data, int w, int h, int channels);
  void loadImageFromRaw(int w,
                        int h,
                        const unsigned char* data = nullptr,
                        GLint format = GL_RGB,
                        GLint type = GL_UNSIGNED_BYTE,
                        GLenum internalFormat = GL_RGB);
  int X();
  int Y();
  ImVec2 Size();

 private:
  int x, y, channels;

  using TextureRef = std::shared_ptr<GLuint>;

  TextureRef textureref = 0;
};

}  // namespace xhfr

#endif  // IMAGE_HPP
