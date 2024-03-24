#include "container.hxx"

std::shared_ptr<Alchemist::Media::Container::Base> Alchemist::Media::Container::Instance(const Type&) {
	return nullptr;
}

const std::list<Alchemist::Media::Stream>& Alchemist::Media::Container::Base::get_streams() const {
	return m_streams;
}

void Alchemist::Media::Container::Base::add_stream(const Stream& stream) {
	m_streams.push_back(stream);
	sort_streams();
}

void Alchemist::Media::Container::Base::add_stream(Stream&& stream) {
	m_streams.push_back(std::move(stream));
	sort_streams();
}

void Alchemist::Media::Container::Base::sort_streams() {
	m_streams.sort([](const Stream& first, const Stream& second) { return first.get_index() <= second.get_index(); });
}