#include <Alchemy/media/audio/codec/wav.hxx>

using namespace Alchemy::Media::Audio;

WAV::WAV() noexcept:Codec("WAV", "pcm_s16le", "PCM signed 16-bit little-endian") {}