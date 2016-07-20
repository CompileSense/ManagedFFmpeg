#pragma once
using namespace System;

namespace FFMpegNet 
{
	namespace SwScale
	{
		[ Flags ]
		public enum class SWS_Flag
		{
			NONE = 0,
			FAST_BILINEAR = 1,
			BILINEAR = 2,
			BICUBIC = 4,
			X = 8,
			POINT = 0x10,
			AREA = 0x20,
			BICUBLIN = 0x40,
			GAUSS = 0x80,
			SINC = 0x100,
			LANCZOS = 0x200,
			SPLINE = 0x400,
		};
	};
};