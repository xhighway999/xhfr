#include "Image.hpp"

namespace xhfr {

Image::Image() {
  glGenTextures(1, &texture);
}

Image::Image(const char* path) {
  glGenTextures(1, &texture);
  loadImageFromFile(path);
}

Image::~Image() {
  glDeleteTextures(1, &texture);
}

ImTextureID Image::textureID() {
  return reinterpret_cast<ImTextureID>(texture);
}

bool Image::loadImageFromFile(const char* path) {
  xhfr::File f(path);
  auto s = f.size();
  auto data = (unsigned char*)malloc(s);
  f.read(data, s);
  f.close();

  int desired = 0;
#ifdef __EMSCRIPTEN__
  // webgl 2.0 does not support the texture swizzling parameter, therfore the
  // image needs to have 4 channels for greyscale
  desired = 4;
#endif
  stbi_uc* imgdata = stbi_load_from_memory(data, s, &x, &y, &channels, desired);
  if (!imgdata)
    return false;
  loadImageFromRaw(imgdata, x, y, channels);

  stbi_image_free(imgdata);
  return true;
}

void Image::loadImageFromRaw(const unsigned char* data,
                             int w,
                             int h,
                             int channels) {
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping parameters
#ifdef __EMSCRIPTEN__
  constexpr auto wrapMode = GL_CLAMP_TO_EDGE;
#else
  constexpr auto wrapMode = GL_REPEAT;
#endif
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps

  if (channels == 1) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE,
                 data);
  } else if (channels == 2) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, w, h, 0, GL_RG, GL_UNSIGNED_BYTE,
                 data);
#ifndef __EMSCRIPTEN__
    GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_GREEN};
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
#endif
  } else if (channels == 3) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 data);
  } else if (channels == 4) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 data);
  } else {
    // TODO: Error handling
  }

  glGenerateMipmap(GL_TEXTURE_2D);
  x = w;
  y = h;
}

void Image::loadImageFromRaw(int w,
                             int h,
                             const unsigned char* data,
                             GLint format,
                             GLint type,
                             GLenum internalFormat) {
  glBindTexture(GL_TEXTURE_2D, texture);

  if (format == GL_DEPTH_COMPONENT) {
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, type, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  } else {
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, format, type, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
  x = w;
  y = h;
}

int Image::X() {
  return x;
}

int Image::Y() {
  return y;
}

ImVec2 Image::Size() {
  return ImVec2(x, y);
}

}  // namespace xhfr
