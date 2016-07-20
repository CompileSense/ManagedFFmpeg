#pragma once

#if 0
#include "ffmpeg_actual.h"

namespace FFMpegNet 
{
	namespace AVFormat
	{

		public ref class AVFormatParameters
		{
		public:
			AVFormatParameters()
			{
				_avFormatParameters = new ::AVFormatParameters();
			}

		internal:
			::AVFormatParameters * _avFormatParameters;
		};
	};
};
#endif