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
  if (pixels)
    stbi_image_free(pixels);
  glDeleteTextures(1, &texture);
}

ImTextureID Image::textureID() {
  return reinterpret_cast<ImTextureID>(texture);
}

bool Image::loadImageFromFile(const char* path) {
  stbi_uc* data = stbi_load(path, &x, &y, &channels, 0);
  if (!data)
    return false;
  loadImageFromRaw(data, x, y, channels);

  stbi_image_free(data);
  return true;
}

void Image::loadImageFromRaw(const unsigned char* data,
                             int w,
                             int h,
                             int channels) {
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default
                               // wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps

  if (channels == 1) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE,
                 data);
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
