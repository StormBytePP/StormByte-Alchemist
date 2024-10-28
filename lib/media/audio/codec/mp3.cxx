#include "mp3.hxx"

using namespace Alchemist::Media::Audio;

MP3::MP3() noexcept:Codec("MP3", "libmp3lame", "MPEG Audio Layer 3") {
	#ifndef ENABLE_LAME
	m_supported = false;
	#endif
}