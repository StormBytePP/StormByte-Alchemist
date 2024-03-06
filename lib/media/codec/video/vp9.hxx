#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC VP9 final: public Audio {
		public:
			VP9();
			VP9(const VP9&)					= default;
			VP9(VP9&&)						= default;
			VP9& operator=(const VP9&)		= default;
			VP9& operator=(VP9&&)			= default;
			~VP9()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}