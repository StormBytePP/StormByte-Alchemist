#include <Alchemy/media/audio/codec/fdk_aac.hxx>

using namespace Alchemy::Media::Audio;

FDK_AAC::FDK_AAC() noexcept:Codec("FDK AAC", "fdk_aac", "Fraunhoffer Institute AAC") {
	#ifndef ENABLE_FDK_AAC
	m_supported = false;
	#endif
}