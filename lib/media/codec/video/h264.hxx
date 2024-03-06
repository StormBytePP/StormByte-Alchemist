#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC H264 final: public Audio {
		public:
			H264();
			H264(const H264&)					= default;
			H264(H264&&)						= default;
			H264& operator=(const H264&)		= default;
			H264& operator=(H264&&)			= default;
			~H264()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}