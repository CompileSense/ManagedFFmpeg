#pragma once

#include "ffmpeg_actual.h"

#include "AVCodec.h"
#include "AVFormatContext.h"
#include "AVFrac.h"
#include "AVRational.h"


using namespace System;

namespace FFMpegNet 
{
	namespace AVFormat
	{
		public ref class AVStream
		{
		public:
			AVStream(AVFormatContext^ formatContext, FFMpegNet::AVCodec::AVCodec^ codec)
			{
				_avStream = ::avformat_new_stream(formatContext->_avFormatContext, codec->_avCodec);
				if (_avStream == NULL ||
					_avStream->codec == NULL /*||
					_avStream->codec->codec == NULL*/)
				{
					throw gcnew Exception("Failed to create stream - missing codec perhaps?");
				}
			};

			property AVFrac^ PTS
			{
				AVFrac^ get()
				{
					return gcnew AVFrac(&_avStream->pts);
				}
			}

			 /// This is the fundamental unit of time (in seconds) in terms
			 /// of which frame timestamps are represented.
			 ///
			 /// decoding: set by libavformat
			 /// encoding: set by libavformat in av_write_header. The muxer may use the
			 /// user-provided value of @ref AVCodecContext.time_base "codec->time_base"
			 /// as a hint.
			property AVUtil::AVRational^ TimeBase
			{
				AVUtil::AVRational^ get()
				{
					return gcnew AVUtil::AVRational(_avStream->time_base.num, _avStream->time_base.den);
				}
			}

			property AVUtil::AVRational^ AverageFrameRate
			{
				AVUtil::AVRational^ get()
				{
					return gcnew AVUtil::AVRational(_avStream->avg_frame_rate.num, _avStream->avg_frame_rate.den);
				}
			}

			property AVUtil::AVRational^ LowestPossibleFramerateGuess
			{
				AVUtil::AVRational^ get()
				{
					return gcnew AVUtil::AVRational(_avStream->r_frame_rate.num, _avStream->r_frame_rate.den);
				}
			}

			property int Index
			{
				int get()
				{
					return _avStream->index;
				}
			}

			property FFMpegNet::AVCodec::AVCodecContext^ CodecContext
			{
				FFMpegNet::AVCodec::AVCodecContext^ get()
				{
					if (_avStream->codec->codec_type == (int) AVUtil::AVMediaType::VIDEO)
					{
						return FFMpegNet::AVCodec::AVVideoCodecContext::Wrap(_avStream->codec);
					}
					else if (_avStream->codec->codec_type == (int) AVUtil::AVMediaType::AUDIO)
					{
						return FFMpegNet::AVCodec::AVAudioCodecContext::Wrap(_avStream->codec);
					}
					return nullptr;
				}
			}

			property int Duration
			{
				int get()
				{
					return (int)_avStream->duration;
				}
			}

		internal:
			::AVStream * _avStream;
		};


	};
};