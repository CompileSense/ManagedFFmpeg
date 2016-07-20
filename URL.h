#pragma once

using namespace System;

namespace FFMpegNet 
{
	namespace AVIO
	{
		[ Flags ]
		public enum class URL
		{
			//NONE = 0,
			RDONLY = 0,	// URL_RDONLY
			WRONLY = 1,
			RDWR = 2
		};

		[Flags]
		public enum class AVIO_FLAG
		{
			READ = 1,
			WRITE = 2,
			NONBLOCK = 8,
			DIRECT = 0x8000

		};
	};
};