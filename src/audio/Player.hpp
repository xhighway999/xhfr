#pragma once

#include <SDL2/SDL.h>
#include <filesystem>
#include <vector>

class Player {
 public:
  Player();
  ~Player();
  bool play();
  void stop();
  void pause();
  void seek(float pos);
  void setPath(const std::filesystem::path& value);

  bool Playing() const;

 private:
  static void audioPlayingCallback(void* userdata, uint8_t* stream, int len);
  std::filesystem::path p;
  bool isPlaying = false;
  uint16_t samples, channels, bits;
  // std::vector<float> data;
  Uint8* buffer = nullptr;
  Uint32 lengthBytes;
  Uint32 dataIndex = 0;
  SDL_AudioSpec playSpec;
  SDL_AudioDeviceID deviceId;
};
