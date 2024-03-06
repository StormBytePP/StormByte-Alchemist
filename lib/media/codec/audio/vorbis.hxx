#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC VORBIS final: public Audio {
		public:
			VORBIS();
			VORBIS(const VORBIS&)					= default;
			VORBIS(VORBIS&&)						= default;
			VORBIS& operator=(const VORBIS&)		= default;
			VORBIS& operator=(VORBIS&&)				= default;
			~VORBIS()								= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}