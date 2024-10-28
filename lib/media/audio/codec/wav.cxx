#include "wav.hxx"

using namespace Alchemist::Media::Audio;

WAV::WAV() noexcept:Codec("WAV", "pcm_s16le", "PCM signed 16-bit little-endian") {}