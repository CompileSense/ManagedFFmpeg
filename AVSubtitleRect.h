#pragma once


#include "ffmpeg_actual.h"

#include "AVSubtitleType.h"

using namespace System;

namespace FFMpegNet 
{
	namespace AVCodec
	{
		public ref class AVSubtitleRect
		{
		public:
			AVSubtitleRect(int x, int y, int w, int h, int nb_colors, System::Drawing::Bitmap^ pic, 
				FFMpegNet::AVCodec::AVSubtitleType type, String^ text, String^ ass)
			{
				_avSubtitleRect = new ::AVSubtitleRect();

				_avSubtitleRect->x = x;
				_avSubtitleRect->y = y;
				_avSubtitleRect->w = w;
				_avSubtitleRect->h = h;
				_avSubtitleRect->nb_colors = nb_colors;
				_avSubtitleRect->type = static_cast<::AVSubtitleType>(type);

				// TODO: Marshal text and ass strings
				// TODO: Transform Bitmap into AVPicture (subset of AVFrame?) 
			};

			~AVSubtitleRect()
			{
				delete _avSubtitleRect;
			}

			AVSubtitleRect(::AVSubtitleRect* _avSubtitleRect)
			{
				//this->_avSubtitleRect = _avSubtitleRect;	// Can't do this, unless we use smart pointers or something.
				_avSubtitleRect = new ::AVSubtitleRect();
				memcpy(this->_avSubtitleRect, _avSubtitleRect, sizeof(::AVSubtitleRect));
			}


			int GetX()
			{
				return _avSubtitleRect->x;
			}

			int GetY()
			{
				return _avSubtitleRect->y;
			}

			int GetW()
			{
				return _avSubtitleRect->w;
			}

			int GetH()
			{
				return _avSubtitleRect->h;
			}

			int GetNumberOfColors()
			{
				return _avSubtitleRect->nb_colors;
			}

		internal:

			::AVSubtitleRect * _avSubtitleRect;
		};
	};
};
