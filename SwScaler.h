#pragma once

#include "ffmpeg_actual.h"
#include "SWS_Flags.h"

namespace FFMpegNet 
{
	namespace SwScale
	{
		public ref class SwScaler
		{
		public:
			SwScaler(int sourceWidth, int sourceHeight, AVUtil::PixelFormat sourceFormat,
				int destWidth, int destHeight, AVUtil::PixelFormat destFormat, 
				SWS_Flag flags) 
					:	sourceWidth(sourceWidth), sourceHeight(sourceHeight), sourceFormat(sourceFormat),
						destWidth(destWidth), destHeight(destHeight), destFormat(destFormat)
			{
				_swsContext = NULL;
				::AVPixelFormat _sourceFormat = static_cast<::AVPixelFormat>(sourceFormat);
				::AVPixelFormat _destFormat = static_cast<::AVPixelFormat>(destFormat);

				if (!sws_isSupportedInput(_sourceFormat))
				{
					throw gcnew ArgumentException("Cannot create scaler - wrong input format");
				}
				if (!sws_isSupportedOutput(_destFormat))
				{
					throw gcnew ArgumentException("Cannot create scaler - wrong output format");
				}

				_swsContext = ::sws_getContext(sourceWidth, sourceHeight, _sourceFormat,
					destWidth, destHeight, _destFormat, 
					static_cast<int>(flags), NULL, NULL, NULL);

			}

			~SwScaler()
			{
				if (_swsContext != NULL)
				{
					::sws_freeContext(_swsContext);
					_swsContext = NULL;
				}
			}

			int Scale(AVCodec::AVFrame^ source, int srcSliceY, int srcSliceH, AVCodec::AVFrame^ dest)
			{
				int result = ::sws_scale(_swsContext, source->_avFrame->data, source->_avFrame->linesize, 
					srcSliceY, srcSliceH, dest->_avFrame->data, dest->_avFrame->linesize);
				return result;
			}

			property int SourceWidth
			{
				int get()
				{
					return sourceWidth;
				}
			}
			property int SourceHeight
			{
				int get()
				{
					return sourceHeight;
				}
			}
			property int DestinationWidth
			{
				int get()
				{
					return destWidth;
				}
			}
			property int DestinationHeight
			{
				int get()
				{
					return destHeight;
				}
			}
			property AVUtil::PixelFormat SourceFormat
			{
				AVUtil::PixelFormat get()
				{
					return sourceFormat;
				}
			}
			property AVUtil::PixelFormat DestinationFormat
			{
				AVUtil::PixelFormat get()
				{
					return destFormat;
				}
			}


		internal:
			::SwsContext * _swsContext;

			// SwsContext is opaque, so we explicitly remember in/out settings
			int sourceWidth, sourceHeight, destWidth, destHeight;
			AVUtil::PixelFormat sourceFormat, destFormat;
		};
	};
};