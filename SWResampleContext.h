#pragma once

#include "ffmpeg_actual.h"
#include "SWS_Flags.h"
#include "AVSampleFormat.h"

#if 1

namespace FFMpegNet 
{
	namespace SwResample
	{
		public ref class SwResampleContext
		{
		public:
			SwResampleContext(__int64 out_ch_layout, FFMpegNet::AVCodec::AVSampleFormat out_sample_fmt, int out_sample_rate,
                              __int64  in_ch_layout, FFMpegNet::AVCodec::AVSampleFormat  in_sample_fmt, int  in_sample_rate
                              /*, int log_offset, void *log_ctx*/) 
					:	out_ch_layout(out_ch_layout), out_sample_fmt(out_sample_fmt), out_sample_rate(out_sample_rate),
						in_ch_layout(in_ch_layout), in_sample_fmt(in_sample_fmt), in_sample_rate(in_sample_rate)
			{
				_swrContext = NULL;
	
				//_swrContext = ::swr_alloc();
				_swrContext = ::swr_alloc_set_opts(NULL, out_ch_layout, static_cast<::AVSampleFormat>(out_sample_fmt), out_sample_rate,
					in_ch_layout, static_cast<::AVSampleFormat>(in_sample_fmt), in_sample_rate, 0, NULL);
				if (_swrContext == NULL)
				{
					throw gcnew Exception("Could not allocate SwResampleContext");
				}
			}

			~SwResampleContext()
			{
				if (_swrContext != NULL)
				{
					pin_ptr<SwrContext*> _p;
					_p = &_swrContext;
					::swr_free(_p);
					_swrContext = NULL;
				}
			}

			int Init()
			{
				int rtn = swr_init(_swrContext);
				return rtn;
			}

			// outputBuffer and inputBuffer need to be pointers to an array of buffer (pointers). 
			// eg. uint8_t[]* or similar. ie. you can pass the .Data member of an AvFrame in safely.
			int Convert(IntPtr^ outputBuffer, int outputSampleCapacity, IntPtr^ inputBuffer, int inputSampleCapacity)
			{
				// According to the docs, outputBuffer is expected to be a list of pointers to buffers.
				int rtn = swr_convert(_swrContext, static_cast<uint8_t **>( outputBuffer->ToPointer() ), outputSampleCapacity, 
					static_cast<const uint8_t **>( inputBuffer->ToPointer() ), inputSampleCapacity);
				//throw gcnew NotImplementedException();
				return rtn;
			}

			//int Scale(AVCodec::AVFrame^ source, int srcSliceY, int srcSliceH, AVCodec::AVFrame^ dest)
			//{
			//	int result = ::sws_scale(_swsContext, source->_avFrame->data, source->_avFrame->linesize, 
			//		srcSliceY, srcSliceH, dest->_avFrame->data, dest->_avFrame->linesize);
			//	return result;
			//}

			//property int SourceWidth
			//{
			//	int get()
			//	{
			//		return sourceWidth;
			//	}
			//}
			//property int SourceHeight
			//{
			//	int get()
			//	{
			//		return sourceHeight;
			//	}
			//}
			//property int DestinationWidth
			//{
			//	int get()
			//	{
			//		return destWidth;
			//	}
			//}
			//property int DestinationHeight
			//{
			//	int get()
			//	{
			//		return destHeight;
			//	}
			//}
			//property AVUtil::PixelFormat SourceFormat
			//{
			//	AVUtil::PixelFormat get()
			//	{
			//		return sourceFormat;
			//	}
			//}
			//property AVUtil::PixelFormat DestinationFormat
			//{
			//	AVUtil::PixelFormat get()
			//	{
			//		return destFormat;
			//	}
			//}


		internal:
			::SwrContext * _swrContext;

			int out_sample_rate, in_sample_rate;
			__int64 out_ch_layout, in_ch_layout;
			FFMpegNet::AVCodec::AVSampleFormat out_sample_fmt; 
			FFMpegNet::AVCodec::AVSampleFormat  in_sample_fmt; 
			// SwsContext is opaque, so we explicitly remember in/out settings
			//int sourceWidth, sourceHeight, destWidth, destHeight;
			//AVUtil::PixelFormat sourceFormat, destFormat;
		};
	};
};

#endif