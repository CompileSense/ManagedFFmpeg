#pragma once

#include "ffmpeg_actual.h"

#include "AVPacket.h"
//#include "AVFormatParameters.h"
#include "URL.h"
#include "AVOutputFormat.h"
using namespace System;

namespace FFMpegNet 
{
	namespace AVFormat
	{

		public ref class AVFormatContext
		{
		public:
			AVFormatContext()
			{
				_avFormatContext = ::avformat_alloc_context();
			}

			int InterleavedWriteFrame(AVCodec::AVPacket^ packet)
			{
				return ::av_interleaved_write_frame(_avFormatContext, packet->_avPacket);
			}

			int WriteFrame(AVCodec::AVPacket^ packet)
			{
				return ::av_write_frame(_avFormatContext, packet->_avPacket);
			}

			void Fixup()
			{
				_avFormatContext->streams[0]->pts.den = 25;
				_avFormatContext->streams[0]->pts.num = 12;
				_avFormatContext->streams[0]->time_base.num = 1;
				_avFormatContext->streams[0]->time_base.den = 25;
				_avFormatContext->streams[0]->pts_wrap_bits = 64;
			}

			// Todo: put this in the constructor?
			void SetOutputFormat(AVOutputFormat^ outputFormat)
			{
				_avFormatContext->oformat = outputFormat->_avOutputFormat;
			}

			AVOutputFormat^ GetOutputFormat()
			{
				return AVOutputFormat::Wrap(_avFormatContext->oformat);
			}

			//void SetParameters(AVFormatParameters^ params)
			//{
			//	::av_set_parameters(_avFormatContext, params->_avFormatParameters);
			//}

			int OpenFile(String^ filename, AVIO::AVIO_FLAG options)
			{
				const char * _filename = (char *) (void *) Marshal::StringToHGlobalAnsi(filename);
				return ::avio_open(&_avFormatContext->pb, _filename, static_cast<int> (options));
				//return ::url_fopen(&_avFormatContext->pb, _filename, static_cast<int> (options));
			}

			int CloseFile()
			{
				return ::avio_close(_avFormatContext->pb);
			}

			int WriteHeader()
			{
				// This initialises streams (held in _avFormatContext) time bases.
				// Audio streams are inited to: stream->time_base.num / stream->codec->sample_rate
				// Video streams are inited to: stream->time_base.num / stream->codec->time_base.den
				return ::avformat_write_header(_avFormatContext, NULL);
			}

			int WriteTrailer()
			{
				return ::av_write_trailer(_avFormatContext);
			}
		internal:
			::AVFormatContext * _avFormatContext;
		};



	};
};