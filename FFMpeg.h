// SVFFMpeg.Net.h

#pragma once

#include "ffmpeg_actual.h"
#include "AVOutputFormat.h"
using namespace System;

#define _ENABLE_LOGGING

static void __cdecl _avLogCallback(void * ptr, int level, const char * fmt, va_list args)
{
#ifndef _ENABLE_LOGGING
	return;
#else
	char message[8192];
	char * _f = (char *)fmt;
	bool _pc = false;
	bool _t = false;
	bool _d = false;
	while(_f != 0 && *_f != '\0' && *_f != '\n')
	{
		if (*_f == '%')
		{
			_pc = true;
			_f++;
			continue;
		}

		if (_pc && !_t && *_f == 't')
		{
			_t = true;
			_f++;
			continue;
		}

		if (_pc && _t && *_f == 'd')
		{
			_d = true;
			return;
		}
		_d = false;
		_t = false;
		_pc = false;
		_f++;
	}
	vsprintf_s(message, 8192, fmt, args);
	size_t messageLength = strlen(message);
	fprintf(stderr, message);
#endif
}

namespace FFMpegNet 
{
	namespace AVFormat
	{
		public ref class FFMpeg
		{
		public:
			FFMpeg()
			{
			}

			static void RegisterAll()
			{
				::av_register_all();

				::av_log_set_callback(_avLogCallback);
			}

			static property array<FFMpegNet::AVFormat::AVOutputFormat^>^ OutputFormats
			{
				array<FFMpegNet::AVFormat::AVOutputFormat^>^ get()
				{
					// Count the output formats
					int numberOfOutputFormats = 0;
					::AVOutputFormat * outputFormat = av_oformat_next(NULL);
	
					while(outputFormat != NULL)
					{
						if (outputFormat->video_codec != AV_CODEC_ID_NONE)
						{
							numberOfOutputFormats++;			
						}
						outputFormat = av_oformat_next(outputFormat);
					}

					outputFormat = av_oformat_next(NULL);
					array<FFMpegNet::AVFormat::AVOutputFormat^>^ rtn = gcnew array<FFMpegNet::AVFormat::AVOutputFormat^>(numberOfOutputFormats);
					for(int i = 0; i < numberOfOutputFormats; i++)
					{
						if(outputFormat != NULL)
						{
							rtn[i] = AVOutputFormat::Wrap(outputFormat);
							
						}
						outputFormat = av_oformat_next(outputFormat);
					}
					return rtn;
				}
			}


				//outputFormats = new OutputFormat[numberOfOutputFormats];
	
				//outputFormat = av_oformat_next(NULL);
				//int i = 0;
				//while(outputFormat != NULL)
				//{
				//	if (outputFormat != NULL)
				//	{
				//		if (outputFormat->video_codec != CODEC_ID_NONE)
				//		{
				//			outputFormats[i].extensions = outputFormat->extensions;
				//			outputFormats[i].name = outputFormat->name;
				//			outputFormats[i].longName = outputFormat->long_name;

				//			if (outputFormat->codec_tag != NULL)
				//			{
				//				int tag = 0;
				//				int numberOfValidCodecs = 0;
				//				while(true)
				//				{
				//					CodecID codecID = av_codec_get_id(outputFormat->codec_tag, tag);
				//					if (codecID == CODEC_ID_NONE)
				//					{
				//						break;
				//					}
				//					if (avcodec_find_encoder(codecID) != 0)
				//					{
				//						numberOfValidCodecs++;
				//					}
				//					tag++;
				//				}

				//				if (numberOfValidCodecs == 0)
				//				{
				//					outputFormats[i].name = 0;
				//					outputFormats[i].longName = 0;
				//					outputFormat = av_oformat_next(outputFormat);
				//					i++;
				//					continue;
				//				}

				//				outputFormats[i].numberOfCodecs = numberOfValidCodecs;
				//				outputFormats[i].codecInfos = new CodecInfo[numberOfValidCodecs];
				//				tag = 0;	
				//				int validCodec = 0;
				//				while(true)
				//				{
				//					CodecID codecID = av_codec_get_id(outputFormat->codec_tag, tag);
				//					if (codecID == CODEC_ID_NONE)
				//					{
				//						break;
				//					}
				//					AVCodec * codec = avcodec_find_encoder(codecID);
				//					if (codec != NULL)
				//					{
				//						outputFormats[i].codecInfos[validCodec].name = codec->name;
				//						outputFormats[i].codecInfos[validCodec].longName = codec->long_name;
				//						validCodec++;
				//					}	
				//					tag++;				
				//				}
				//			}
				//			else
				//			{
				//				if (outputFormat->video_codec != CODEC_ID_NONE)
				//				{
				//					AVCodec * codec = avcodec_find_encoder(outputFormat->video_codec);
				//					if (codec != NULL)
				//					{
				//						outputFormats[i].numberOfCodecs = 1;
				//						outputFormats[i].codecInfos = new CodecInfo[1];
				//		
				//						outputFormats[i].codecInfos[0].name = codec->name;
				//						outputFormats[i].codecInfos[0].longName = codec->long_name;
				//					}
				//				}
				//			}
				//			i++;
				//		}
				//		outputFormat = av_oformat_next(outputFormat);
				//	}
				//}

			//}
			
			static int MinBufferSize = 16384;

		};
	};
}
