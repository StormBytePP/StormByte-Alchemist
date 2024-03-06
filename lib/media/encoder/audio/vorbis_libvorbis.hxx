#include "../audio.hxx"

namespace Alchemist::Media::Encoder {
	class DLL_PUBLIC VORBIS_LIBVORBIS final: public Audio {
		public:
			VORBIS_LIBVORBIS();
			VORBIS_LIBVORBIS(const VORBIS_LIBVORBIS&)				= default;
			VORBIS_LIBVORBIS(VORBIS_LIBVORBIS&&)					= default;
			VORBIS_LIBVORBIS& operator=(const VORBIS_LIBVORBIS&)	= default;
			VORBIS_LIBVORBIS& operator=(VORBIS_LIBVORBIS&&)			= default;
			~VORBIS_LIBVORBIS()										= default;
	};
}