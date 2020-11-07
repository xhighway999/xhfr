#include "Player.hpp"

#include "wave/file.h"
#include <string.h>
#include "SDL.h"

void Player::audioPlayingCallback(void* userdata, uint8_t* stream, int len) {
  Player* rec = (Player*)userdata;

  // Copy audio to stream

  Uint32 remaining = rec->lengthBytes - rec->dataIndex;
  bool end = false;
  if (remaining < len) {
    len = remaining;
    end = true;
  }
  void* d = &rec->buffer[rec->dataIndex];
  memcpy(stream, d, len);
  rec->dataIndex += len;
  if (end) {
    rec->stop();
  }
}

Player::Player() {}

Player::~Player() {
  if (buffer != nullptr) {
    SDL_FreeWAV(buffer);
  }
}

bool Player::play() {
  isPlaying = true;

  SDL_AudioSpec recv;

  /* Set the audio format */
  playSpec.callback = &Player::audioPlayingCallback;
  playSpec.userdata = this;

  /* Open the audio device, forcing the desired format */
  const char* name = NULL;  // SDL_GetAudioDeviceName(recorderId,true);
  deviceId = SDL_OpenAudioDevice(name, false, &playSpec, &recv,
                                 SDL_AUDIO_ALLOW_FORMAT_CHANGE);

  if (deviceId == 0) {
    fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
    return false;
  }

  // writerThread =
  // std::make_unique<std::thread>(&Recorder::writerThreadFunction, this);
  // SDL_PauseAudioDevice( recorderId, SDL_FALSE );
  SDL_PauseAudioDevice(deviceId, false);

  return true;
}

void Player::stop() {
  pause();
  seek(0);
}

void Player::pause() {
  SDL_PauseAudioDevice(deviceId, true);
  isPlaying = false;
}

void Player::seek(float pos) {
  if (pos == 0) {
    dataIndex = 0;
  }
}

void Player::setPath(const std::filesystem::path& value) {
  p = value;

  if (buffer != nullptr) {
    SDL_FreeWAV(buffer);
  }

  // luckly sdl has a function for this so i deont have to mess with thw wave
  // library

  if (!SDL_LoadWAV(value.string().c_str(), &playSpec, &buffer, &lengthBytes)) {
    abort();
  }
}

bool Player::Playing() const {
  return isPlaying;
}
