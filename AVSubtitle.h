#pragma once


#include "ffmpeg_actual.h"

#include "AVSubtitleRect.h"

using namespace System;

namespace FFMpegNet 
{
	namespace AVCodec
	{
		public ref class AVSubtitle
		{
		public:
			AVSubtitle(short format, int start_display_time, int end_display_time, 
				array<FFMpegNet::AVCodec::AVSubtitleRect^>^ rects, __int64 pts)
			{
				_avSubtitle = new ::AVSubtitle();

				_avSubtitle->format = format;
				_avSubtitle->start_display_time = start_display_time;
				_avSubtitle->end_display_time = end_display_time;
				_avSubtitle->pts = pts;
				// TODO rects

			};

			AVSubtitle(::AVSubtitle* _avSubtitle)
			{
				this->_avSubtitle = new ::AVSubtitle();
				memcpy(this->_avSubtitle, _avSubtitle, sizeof(::AVSubtitle));
			}


			~AVSubtitle()
			{
				delete _avSubtitle;
			}

			__int64 GetPts()
			{
				return _avSubtitle->pts;
			}

			int GetStartDisplayTime()
			{
				return _avSubtitle->start_display_time;
			}

			int GetEndDsplayTime()
			{
				return _avSubtitle->end_display_time;
			}

			__int64 GetPTS()
			{
				return _avSubtitle->pts;
			}

		internal:
			::AVSubtitle * _avSubtitle;
		};
	};
};
