#include "../video.hxx"

namespace Alchemist::Media::Codec::Video {
	class DLL_PUBLIC AV1 final: public Base {
		public:
			AV1();
			AV1(const AV1&)					= default;
			AV1(AV1&&)						= default;
			AV1& operator=(const AV1&)		= default;
			AV1& operator=(AV1&&)			= default;
			~AV1()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}