#pragma once

#include "ffmpeg_actual.h"

using namespace System;
using namespace System::Runtime::InteropServices; // for class Marshal

//#include "AVCodec.h"
#include "AVCodecID.h"
#include "AVFMT.h"
#include "AVOutputFormat.h"

namespace FFMpegNet 
{
	namespace AVFormat
	{

		public ref class AVOutputFormat
		{
		public:
			AVOutputFormat() : _avOutputFormat(0)
			{
			}

			static AVOutputFormat^ GuessFormat(String^ shortName, String^ filename, String^ mimeType)
			{
				const char * _shortName = (char *) (void *) Marshal::StringToHGlobalAnsi(shortName);
				const char * _filename = (char *) (void *) Marshal::StringToHGlobalAnsi(filename);
				const char * _mimeType = (char *) (void *) Marshal::StringToHGlobalAnsi(mimeType);

				AVOutputFormat^ outputFormat = nullptr;
				::AVOutputFormat * avOutputFormat = ::av_guess_format(_shortName, _filename, _mimeType);
				if (avOutputFormat != NULL)
				{
					outputFormat = gcnew AVOutputFormat();
					outputFormat->_avOutputFormat = avOutputFormat;
				}
				
				Marshal::FreeHGlobal((System::IntPtr)(void*)_shortName);
				Marshal::FreeHGlobal((System::IntPtr)(void*)_filename);
				Marshal::FreeHGlobal((System::IntPtr)(void*)_mimeType);
				return outputFormat;
			}

			static AVOutputFormat^ Wrap(::AVOutputFormat * _avOutputFormat)
			{
				AVOutputFormat^ outputFormat = gcnew AVOutputFormat();
				outputFormat->_avOutputFormat = _avOutputFormat;
				return outputFormat;
			}

			static AVOutputFormat^ Empty()
			{
				return gcnew AVOutputFormat();
			}
			
			//static bool operator==(const AVOutputFormat^ lhs, const AVOutputFormat^ rhs)
			//{
			//	return lhs->_avOutputFormat == rhs->_avOutputFormat;
			//}

			//static bool operator!=(const AVOutputFormat^ lhs, const AVOutputFormat^ rhs)
			//{
			//	return lhs->_avOutputFormat != rhs->_avOutputFormat;
			//}

			property FFMpegNet::AVCodec::AVCodecID VideoCodecID	// default video codec
			{
				FFMpegNet::AVCodec::AVCodecID get()
				{
					return static_cast<AVCodec::AVCodecID> (_avOutputFormat->video_codec);
				}
			}

			property FFMpegNet::AVCodec::AVCodecID AudioCodecID	// default audio codec
			{
				FFMpegNet::AVCodec::AVCodecID get()
				{
					return static_cast<FFMpegNet::AVCodec::AVCodecID> (_avOutputFormat->audio_codec);
				}
			}

			property AVFMT Flags
			{
				AVFMT get()
				{
					return static_cast<AVFMT> (_avOutputFormat->flags);
				}
			}

			static AVOutputFormat^ Next(AVOutputFormat^ format)
			{				
				if (format == nullptr)
				{
					::AVOutputFormat * oformat = ::av_oformat_next(NULL);
					return Wrap(oformat);
				}
				::AVOutputFormat * oformat = ::av_oformat_next(format->_avOutputFormat);
				return Wrap(oformat);
			}

			property String^ LongName
			{
				String^ get()
				{
					return gcnew String(_avOutputFormat->long_name);				
				}
			}

			property String^ Name
			{
				String^ get()
				{
					return gcnew String(_avOutputFormat->name);
				}
			}

			property String^ MimeType
			{
				String^ get()
				{
					return gcnew String(_avOutputFormat->mime_type);
				}
			}

			property String^ Extensions
			{
				String^ get()
				{
					return gcnew String(_avOutputFormat->extensions);
				}
			}

			// Get the list of recommended codecs for this format, in better-first order.
			FFMpegNet::AVCodec::AVCodecID GetCodecID(int index)
			{
				//enum CodecID av_codec_get_id(const struct AVCodecTag * const *tags, unsigned int tag);
				return static_cast<FFMpegNet::AVCodec::AVCodecID> (av_codec_get_id(_avOutputFormat->codec_tag, index));
			}

			property array<FFMpegNet::AVCodec::AVCodecID>^ RecommendedCodecs
			{
				array<FFMpegNet::AVCodec::AVCodecID>^ get()
				{
					int count = 0;

					// arbitrary maximum
					for(int i = 0; i < 1024; i++)
					{
						FFMpegNet::AVCodec::AVCodecID codec = GetCodecID(i);
						count++;

						if (codec == FFMpegNet::AVCodec::AVCodecID::NONE)
						{
							break;
						}
					}

					array<FFMpegNet::AVCodec::AVCodecID>^ rtn = gcnew array<FFMpegNet::AVCodec::AVCodecID>(count);
					for(int i = 0; i < count; i++)
					{
						rtn[i] = GetCodecID(i);
					}
					return rtn;
				}
			}

		internal:
			::AVOutputFormat * _avOutputFormat;
		};

	};
};