#include "media/decoder.hxx"

namespace Alchemist::Media::Decoder::Audio {
	class DLL_LOCAL Base: public Decoder::Base {
		public:
			Base(const Type&);
			Base(Type&&);
			Base(const Base&)				= default;
			Base(Base&&)					= default;
			Base& operator=(const Base&)	= default;
			Base& operator=(Base&&)			= default;
			virtual ~Base()					= 0;
	};
}