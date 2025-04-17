#include "player.hpp"
#include "portaudio.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <loguru.hpp>
#include <vector>

namespace player
{
Player::Player()
{
}

Player::~Player()
{
  Pa_Terminate();
}

bool Player::init()
{
  return Pa_Initialize() == paNoError;
}

bool Player::play(const std::string& file_path)
{
  LOG_S(INFO) << "Playing: " << file_path;

  // Open the WAV file
  std::ifstream wav_file(file_path, std::ios::binary);
  if(!wav_file)
  {
    LOG_S(ERROR) << "Failed to open WAV file: " << file_path;
    return false;
  }

  // Read the WAV header
  char header[44];
  wav_file.read(header, sizeof(header));
  if(wav_file.gcount() < sizeof(header))
  {
    LOG_S(ERROR) << "Invalid WAV file: " << file_path;
    return false;
  }

  // Extract audio format information from the header
  int sample_rate = *reinterpret_cast<int*>(header + 24);
  short channels = *reinterpret_cast<short*>(header + 22);
  short bits_per_sample = *reinterpret_cast<short*>(header + 34);

  if(std::strncmp(header, "RIFF", 4) != 0 || std::strncmp(header + 8, "WAVE", 4) != 0)
  {
    LOG_S(ERROR) << "Invalid WAV file format: " << file_path;
    return false;
  }

  if(bits_per_sample != 16)
  {
    LOG_S(ERROR) << "Only 16-bit WAV files are supported.";
    return false;
  }

  // Configure PortAudio
  PaStream* stream;
  PaStreamParameters output_params;
  output_params.device = Pa_GetDefaultOutputDevice();
  output_params.channelCount = channels;
  output_params.sampleFormat = paInt16;

  if(output_params.device == paNoDevice)
  {
    LOG_S(ERROR) << "No default output device available.";
    return false;
  }

  if(Pa_GetDeviceInfo(output_params.device) == nullptr)
  {
    LOG_S(ERROR) << "Failed to get device info.";
    return false;
  }
  output_params.suggestedLatency = Pa_GetDeviceInfo(output_params.device)->defaultLowOutputLatency;
  output_params.hostApiSpecificStreamInfo = nullptr;

  if(Pa_OpenStream(&stream, nullptr, &output_params, sample_rate, paFramesPerBufferUnspecified, paClipOff, nullptr,
         nullptr) != paNoError)
  {
    LOG_S(ERROR) << "Failed to open PortAudio stream.";
    return false;
  }

  if(Pa_StartStream(stream) != paNoError)
  {
    LOG_S(ERROR) << "Failed to start PortAudio stream.";
    Pa_CloseStream(stream);
    return false;
  }

  // Read and play audio data
  const size_t buffer_size = 4096;
  std::vector<char> buffer(buffer_size);

  while(wav_file.read(buffer.data(), buffer_size))
  {
    std::streamsize frames_read = wav_file.gcount() / (bits_per_sample / 8 * channels);
    if(Pa_WriteStream(stream, buffer.data(), (unsigned long)frames_read) != paNoError)
    {
      LOG_S(ERROR) << "Error writing to PortAudio stream.";
      break;
    }
  }

  // Handle any remaining data in the buffer
  if(wav_file.gcount() > 0)
  {
    std::streamsize frames_read = wav_file.gcount() / (bits_per_sample / 8 * channels);
    Pa_WriteStream(stream, buffer.data(), (unsigned long)frames_read);
  }

  // Clean up
  Pa_StopStream(stream);
  Pa_CloseStream(stream);
  wav_file.close();

  LOG_S(INFO) << "Finished playing: " << file_path;

  return true;
}
} // namespace player
