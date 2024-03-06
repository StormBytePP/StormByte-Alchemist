#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC MPEG4 final: public Audio {
		public:
			MPEG4();
			MPEG4(const MPEG4&)					= default;
			MPEG4(MPEG4&&)						= default;
			MPEG4& operator=(const MPEG4&)		= default;
			MPEG4& operator=(MPEG4&&)			= default;
			~MPEG4()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}