#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "gl/Backend.hpp"
#include "imgui.h"
#include "stb_image.h"

#include <string_view>

namespace xhfr {

class Image {
 public:
  Image();
  ~Image();
  Image(const Image&) = delete;
  void operator=(const Image&) = delete;
  ImTextureID textureID();
  bool loadImageFromFile(const char* path);
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
  stbi_uc* pixels = nullptr;
  GLuint texture = 0;
};

}  // namespace xhfr

#endif  // IMAGE_HPP
