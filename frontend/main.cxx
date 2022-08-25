#include "ffmpeg/ffmpeg.hxx"
#include "application.hxx"
#include <iostream>

int main(int argc, char **argv) {
	/* EXAMPLE
	StormByte::VideoConvert::Stream::Video::HEVC::HDR hdr = StormByte::VideoConvert::Stream::Video::HEVC::DEFAULT_HDR;
	StormByte::VideoConvert::Stream::Video::HEVC video(0);
	StormByte::VideoConvert::Stream::Audio::AAC audio1(0);
	StormByte::VideoConvert::Stream::Audio::Copy audio2(1);
	StormByte::VideoConvert::Stream::Subtitle::Copy subtitle1(0), subtitle2(1);
	video.set_HDR(hdr);

	StormByte::VideoConvert::FFmpeg ffmpeg("/warehouse/Multimedia/Video/Pelis/It - Capítulo 1 - m4K HDR.mkv", "/tmp/out.mkv");
	ffmpeg.add_stream(std::move(video));
	ffmpeg.add_stream(std::move(audio1));
	ffmpeg.add_stream(std::move(audio2));
	ffmpeg.add_stream(std::move(subtitle1));
	ffmpeg.add_stream(std::move(subtitle2));

	ffmpeg.exec();

	StormByte::VideoConvert::Database::SQLite3 sqlite3("/tmp/bd.sqlite");
	*/

	StormByte::VideoConvert::Application app;

	return app.run(argc, argv);
}
