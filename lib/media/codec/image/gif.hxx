#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC GIF final: public Audio {
		public:
			GIF();
			GIF(const GIF&)					= default;
			GIF(GIF&&)						= default;
			GIF& operator=(const GIF&)		= default;
			GIF& operator=(GIF&&)			= default;
			~GIF()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}