#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC EAC3 final: public Base {
		public:
			EAC3();
			EAC3(const EAC3&)				= default;
			EAC3(EAC3&&)					= default;
			EAC3& operator=(const EAC3&)	= default;
			EAC3& operator=(EAC3&&)		= default;
			~EAC3()						= default;
	};
}