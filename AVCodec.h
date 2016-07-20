#pragma once

#include "ffmpeg_actual.h"

//#include "AVCodecContext.h"
#include "CodecCap.h"
#include "AVSampleFormat.h"
#include "AVMediaType.h"
#include "AVCodecID.h"
#include "AVRational.h"
#include "PixelFormat.h"

using namespace System;
using namespace FFMpegNet::AVFormat;

namespace FFMpegNet 
{
	namespace AVCodec
	{

		public ref class AVCodec
		{
		public:			


			AVCodec() : _avCodec(0)
			{
			}

			static AVCodec^ FindEncoder(AVCodecID codecID)
			{
				AVCodec^ codec = gcnew AVCodec();
				codec->_avCodec = ::avcodec_find_encoder(static_cast<::AVCodecID>(codecID));
				if (codec->_avCodec == NULL)
				{
					throw gcnew ArgumentException("Failed to find selected encoder");
				}
				return codec;
			}

			static AVCodec^ Wrap(::AVCodec * _avCodec)
			{
				AVCodec^ outputCodec = gcnew AVCodec();
				outputCodec->_avCodec = _avCodec;
				return outputCodec;
			}

			static AVCodec^ Empty()
			{
				return gcnew AVCodec();
			}
			
			static void RegisterAll()
			{
				::avcodec_register_all();
			}

			static AVCodec^ Next(AVCodec^ c)
			{				
				::AVCodec * codec = ::av_codec_next(c->_avCodec);
				return Wrap(codec);
			}

			property String^ LongName
			{
				String^ get()
				{
					return gcnew String(_avCodec->long_name);				
				}
			}

			property String^ Name
			{
				String^ get()
				{
					return gcnew String(_avCodec->name);
				}
			}

			property AVUtil::AVMediaType MediaType
			{
				AVUtil::AVMediaType get()
				{
					return static_cast<AVUtil::AVMediaType>(_avCodec->type);
				}
			}

#ifdef CodecID
#undef CodecID
#define ___CodecID
#endif
			property FFMpegNet::AVCodec::AVCodecID CodecID
			{
				FFMpegNet::AVCodec::AVCodecID get()
				{
					return static_cast<FFMpegNet::AVCodec::AVCodecID>(_avCodec->id);
				}
			}
			
#ifdef ___CodecID
#undef ___CodecID
#define CodecID AVCodecID
#endif

			property FFMpegNet::AVCodec::CodecCap Capabilities
			{
				FFMpegNet::AVCodec::CodecCap get()
				{
					return static_cast<FFMpegNet::AVCodec::CodecCap>(_avCodec->capabilities);
				}
			}

			property array<FFMpegNet::AVUtil::AVRational^>^ SupportedFramerates
			{
				array<FFMpegNet::AVUtil::AVRational^>^ get()
				{
					if (_avCodec->supported_framerates != NULL)
					{
						int i = 0;
						AVRational rational = _avCodec->supported_framerates[i];
						while(rational.num != 0 && rational.den != 0)	// terminator, defined in API docs
						{
							rational = _avCodec->supported_framerates[++i];
						}

						int count = i;


						array<FFMpegNet::AVUtil::AVRational^>^ rtn = gcnew array<FFMpegNet::AVUtil::AVRational^>(count);
						for(i = 0; i < count; i++)
						{
							rational = _avCodec->supported_framerates[i];
							rtn[i] = gcnew FFMpegNet::AVUtil::AVRational(_avCodec->supported_framerates + i);
						}

						return rtn;
					}
					return nullptr;
				}
			}

			property array<FFMpegNet::AVUtil::PixelFormat>^ PixelFormats
			{
				array<FFMpegNet::AVUtil::PixelFormat>^ get()
				{
					if (_avCodec->pix_fmts != NULL)
					{
						int i = 0;
						while(_avCodec->pix_fmts[i++] != -1)	// terminator, defined in API docs
						{
							// 
						}
						int count = i;
						array<FFMpegNet::AVUtil::PixelFormat>^ rtn = gcnew array<FFMpegNet::AVUtil::PixelFormat>(count);
						for(i = 0; i < count; i++)
						{
							rtn[i] = static_cast<FFMpegNet::AVUtil::PixelFormat>(_avCodec->pix_fmts[i]);
						}

						return rtn;
					}
					return nullptr;
				}
			}

			property array<FFMpegNet::AVCodec::AVSampleFormat>^ SampleFormats
			{
				array<FFMpegNet::AVCodec::AVSampleFormat>^ get()
				{
					if (_avCodec->sample_fmts != NULL)
					{
						int i = 0;
						while(_avCodec->sample_fmts[i++] != -1)	// terminator, defined in API docs
						{
							// 
						}
						int count = i;
						array<FFMpegNet::AVCodec::AVSampleFormat>^ rtn = gcnew array<FFMpegNet::AVCodec::AVSampleFormat>(count);
						for(i = 0; i < count; i++)
						{
							rtn[i] = static_cast<FFMpegNet::AVCodec::AVSampleFormat>(_avCodec->sample_fmts[i]);
						}

						return rtn;
					}
					return nullptr;
				}
			}
			
			property array<int>^ SupportedSampleRates
			{
				array<int>^ get()
				{
					if (_avCodec->supported_samplerates != NULL)
					{
						int i = 0;
						while(_avCodec->supported_samplerates[i++] != 0)	// terminator, defined in API docs
						{
							// 
						}
						int count = i;
						array<int>^ rtn = gcnew array<int>(count);
						for(i = 0; i < count; i++)
						{
							rtn[i] = static_cast<int>(_avCodec->supported_samplerates[i]);
						}

						return rtn;
					}
					return nullptr;
				}
			}

			property array<__int64>^ ChannelLayouts
			{
				array<__int64>^ get()
				{
					if (_avCodec->channel_layouts != NULL)
					{
						int i = 0;
						while(_avCodec->channel_layouts[i++] != 0)	// terminator, defined in API docs
						{
							// 
						}
						int count = i;
						array<__int64>^ rtn = gcnew array<__int64>(count);
						for(i = 0; i < count; i++)
						{
							rtn[i] = static_cast<__int64>(_avCodec->channel_layouts[i]);
						}

						return rtn;
					}
					return nullptr;
				}
			}

			bool CanEncode()
			{
				return (_avCodec->encode2 != 0);
			}

			bool CanDecode()
			{
				return (_avCodec->decode != 0);
			}

			//bool Open()
			//{
			//	::AVDictionary * options = NULL;
			//	int result = ::avcodec_open2(avCodecContext->_avCodecContext, _avCodec, &options);
			//	return result == 0;
			//}

			//void Close()
			//{
			//	::avcodec_close(avCodecContext->_avCodecContext);
			//}

		internal:
			::AVCodec * _avCodec;
			//AVCodecContext^ avCodecContext;
		};
	};
};