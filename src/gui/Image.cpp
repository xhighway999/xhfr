#include "Image.hpp"
#include "../core/debug.hpp"
namespace xhfr {

Image::Image() {
  textureref = std::make_shared<GLuint>();
  glGenTextures(1, textureref.get());
}

Image::Image(const char* path) {
  textureref = std::make_shared<GLuint>();
  glGenTextures(1, textureref.get());
  loadImageFromFile(path);
}

Image::~Image() {
  if (textureref.unique()) {
    glDeleteTextures(1, textureref.get());
  }
}

ImTextureID Image::textureID() {
  return reinterpret_cast<ImTextureID>(*textureref);
}

void Image::setInterpolationMode(GLenum interp) {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, interp);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, interp);
}

bool Image::loadImageFromFile(const char* path) {
  xhfr::File f(path);
  auto s = f.size();
  auto data = (unsigned char*)malloc(s);
  f.read(data, s);
  f.close();

  int desired = 0;
#ifdef __EMSCRIPTEN__
  desired = 4;
  // webgl 2.0 does not support the texture swizzling parameter, therfore the
  // image needs to have 4 channels for greyscale
#endif
  stbi_uc* imgdata = stbi_load_from_memory(data, s, &x, &y, &channels, desired);
  free(data);
  if (!imgdata) {
    XHFR_ERROR(stbi_failure_reason());
    return false;
  }
#ifdef __EMSCRIPTEN__
  channels = desired;
#endif
  loadImageFromRaw(imgdata, x, y, channels);
  stbi_image_free(imgdata);
  return true;
}

bool Image::loadImageFromMemory(const char* data, unsigned size) {
  stbi_uc* imgdata = stbi_load_from_memory((const unsigned char*)data, size, &x,
                                           &y, &channels, 3);

  if (!imgdata) {
    XHFR_ERROR(stbi_failure_reason());
    return false;
  }
  loadImageFromRaw(imgdata, x, y, channels);
  stbi_image_free(imgdata);
  return true;
}

void Image::loadImageFromRaw(const unsigned char* data,
                             int w,
                             int h,
                             int channels) {
  GLuint i = *textureref;
  glBindTexture(GL_TEXTURE_2D, i);

  // opengl has the requirement that each row is divisible by 4 for aligment
  // purposes. Check if this is the case and, if not, change the aligment
  // (propably hurting performance).
  if (w % 4 != 0) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    XHFR_WARN("Texture / Image cannot be divided by 4 ... aligment changed");
  }

  // set the texture wrapping parameters
#if 1
  constexpr auto wrapMode = GL_CLAMP_TO_EDGE;
#else
  constexpr auto wrapMode = GL_REPEAT;
#endif
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);  // needed to use this filter for
                                             // mindmaps, not GL_LINEAR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps

  if (channels == 1) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE,
                 data);
    GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_NONE};
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, &swizzleMask[0]);
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, &swizzleMask[1]);
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, &swizzleMask[2]);
    // glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, &swizzleMask[3]);
  } else if (channels == 2) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, w, h, 0, GL_RG, GL_UNSIGNED_BYTE,
                 data);
    GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_GREEN};
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, &swizzleMask[0]);
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, &swizzleMask[1]);
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, &swizzleMask[2]);
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, &swizzleMask[3]);

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
  glBindTexture(GL_TEXTURE_2D, *textureref);

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
