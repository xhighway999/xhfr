#include "Recorder.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

#include "wave/file.h"

void Recorder::audioRecordingCallback(void* userdata,
                                      uint8_t* stream,
                                      int len) {
  Recorder* rec = (Recorder*)userdata;

  // Copy audio from stream

  if (rec->copyBufferEmpty == false) {
    // abort();
  }

  rec->copyBuffer.insert(rec->copyBuffer.end(), stream, stream + len);
  // memcpy( &gRecordingBuffer[ gBufferBytePosition ], stream, len );
  rec->copyBufferEmpty = false;
}

void Recorder::setPath(const std::string& value) {
  path = value;
}

Recorder::Recorder() {}

bool Recorder::start() {
  isRecording = true;

  SDL_AudioSpec wanted, recv;
  extern void fill_audio(void* udata, Uint8* stream, int len);

  /* Set the audio format */

  // 'ultra' settings
  wanted.freq = 44100;
  wanted.format = AUDIO_F32;
  wanted.channels = 2;         /* 1 = mono, 2 = stereo */
  wanted.samples = sampleSize; /* Good low-latency value for callback */
  wanted.callback = audioRecordingCallback;
  wanted.userdata = this;
  singleSampleBits = 32;

  switch (quality) {
    case Recorder::Quality::High:
      // more reasonable settings
      wanted.freq = 32000;
      wanted.format = AUDIO_S16;
      wanted.channels = 1;
      singleSampleBits = 16;
      break;
  }

  /* Open the audio device, forcing the desired format */
  const char* name = NULL;  // SDL_GetAudioDeviceName(recorderId,true);
  auto deviceId = SDL_OpenAudioDevice(name, true, &wanted, &recv,
                                      SDL_AUDIO_ALLOW_FORMAT_CHANGE);
  recorderId = deviceId;
  sampleSize = recv.samples;

  if (deviceId == 0) {
    fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
    return false;
  }

  // basically the call to start
  copyBufferEmpty = true;
  // writerThread =
  // std::make_unique<std::thread>(&Recorder::writerThreadFunction, this);
  // SDL_PauseAudioDevice( recorderId, SDL_FALSE );
  SDL_PauseAudioDevice(recorderId, false);

  return true;
}

void Recorder::stop() {
  isRecording = false;
  SDL_PauseAudioDevice(recorderId, true);
  wave::File f;
  if (f.Open(path, wave::OpenMode::kOut)) {
    abort();
  }

  // convert

  std::vector<float> samples;
  switch (quality) {
    case Recorder::Quality::Ultra: {
      size_t sampleCount = copyBuffer.size() / sizeof(float);
      samples.resize(sampleCount);
      memcpy(&samples[0], &copyBuffer[0], copyBuffer.size());
      f.set_channel_number(2);
      f.set_bits_per_sample(singleSampleBits);
      f.set_sample_rate(44100);
      f.Write(samples);

    } break;
    case Recorder::Quality::High: {
      size_t sampleCount =
          copyBuffer.size() / sizeof(uint16_t);  // basically divide by 2
      samples.resize(sampleCount);

      // funny thing: the audio is recorded in s16 (in this case) and stored in
      // s16 aswell, but this library does not have a way to pass int instead of
      // float converting
      for (size_t i = 0; i < copyBuffer.size(); i += 2) {
        uint16_t combined =
            copyBuffer[i];  // little endian, first bite is not shifted
                            // (assuming this is x86, or not a retarded ARM Cpu)
        combined = copyBuffer[i + 1] << 8;
        samples[i / 2] = combined;
        ;
      }
      // memcpy(&samples[0],&copyBuffer[0],copyBuffer.size());
      f.set_channel_number(1);
      f.set_bits_per_sample(singleSampleBits);
      f.set_sample_rate(32000);
      f.Write(samples);
    } break;
  }

  /*for (int i = 0; i < floatCount; ++i) {
      float sample;
      mem
  }*/

  // generate a saw
  /*int s = 128;
  int step = 0;
  for (int i = 0; i < 1024; ++i) {
      float v = float(step++) / 128.f;
      if (i % 2 == 0) {
          v = -v;
      }
      samples.push_back(v);
      if (step == s) {
          step = 0;
      }
  }
  */

  // writeWAV(copyBuffer);
  // flush data
}

void Recorder::setStoragePath(const std::string& value) {
  storagePath = value;
}

bool Recorder::IsRecording() const {
  return isRecording;
}
