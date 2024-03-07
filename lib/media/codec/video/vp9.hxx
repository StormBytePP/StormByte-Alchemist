#include "../video.hxx"

namespace Alchemist::Media::Codec::Video {
	class DLL_PUBLIC VP9 final: public Base {
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