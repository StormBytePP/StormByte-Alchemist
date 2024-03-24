#include "container/avi.hxx"
#include "container/mkv.hxx"
#include "media/info.hxx"

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

std::shared_ptr<Alchemist::Media::Container::Base> Alchemist::Media::Container::Instance(const Type& container) {
	std::shared_ptr<Container::Base> result;

	switch(container) {
		case AVI:
			result.reset(new class Container::AVI());
			break;

		case MKV:
			result.reset(new class Container::MKV());
			break;

		case MP4:
		case OGG:
		case AAC:
		case DTS:
		case MP3:
		case OPUS:
		case UNKNOWN:
			/* Unused here */
			break;
	}

	return result;
}

std::shared_ptr<Alchemist::Media::Container::Base> Alchemist::Media::Container::Instance(const std::string& container, std::shared_ptr<Base> fallback) {
	std::shared_ptr<Base> result = fallback;

	const auto& all_containers = Info::Container::All;

	const auto iterator = std::find_if(
		all_containers.begin(),
		all_containers.end(),
		[&](const Alchemist::Media::Info::Item& item) { return item.short_name == container; }
	);

	if (iterator != all_containers.end())
		result = Container::Instance(static_cast<Type>(iterator->id));

	return result;
}