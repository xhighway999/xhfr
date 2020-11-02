#pragma once

#include <atomic>
#include <string>
#include <thread>
#include <vector>

#include "SDL2/SDL.h"

class Recorder {
 public:
  enum Quality { Error = 0, High, Ultra };
  Recorder();
  bool start();
  void stop();
  void setStoragePath(const std::string& value);

  bool IsRecording() const;

  void setPath(const std::string& value);

 private:
  static void audioRecordingCallback(void* userdata, uint8_t* stream, int len);
  void writerThreadFunction();
  std::string storagePath;
  bool isRecording = false;
  std::string path;
  size_t singleSampleBits = 0;
  size_t recorderId = 2, sampleSize = 1024;
  std::vector<uint8_t> copyBuffer;
  Quality quality = High;
  std::unique_ptr<std::thread> writerThread;
  std::atomic<bool> copyBufferEmpty = true;
};
