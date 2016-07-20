#pragma once

#include "ffmpeg_actual.h"

#include "AVFrame.h"
using namespace System;


namespace FFMpegNet 
{
	namespace AVCodec
	{
		public enum class AVPKTFLAG
		{
			KEY = 1
		};

		public ref class AVPacket
		{
		public:
			AVPacket()
			{
				_avPacket = new ::AVPacket();
				::av_init_packet(_avPacket);
			}

			~AVPacket()
			{
				if (_avPacket != NULL)
				{
					::av_free_packet(_avPacket);
					delete _avPacket;
					_avPacket = NULL;
				}
			}
			
			void FreeData()
			{
				if (_avPacket != NULL &&
					_avPacket->data != NULL)
				{					
					::av_free(_avPacket->data);
					_avPacket->data = 0;
					_avPacket->size = 0;
				}
			}

			property AVPKTFLAG Flags
			{
				AVPKTFLAG get()
				{
					return static_cast<AVPKTFLAG>(_avPacket->flags);
				}
				void set(AVPKTFLAG value)
				{
					_avPacket->flags = static_cast<int>(value);
				}
			}


			void SetData(AVFrame^ frame)
			{
				_avPacket->data = (uint8_t *)frame->_avFrame;
				_avPacket->size = sizeof(::AVFrame);
			}

			property IntPtr^ Data
			{
				IntPtr^ get()
				{
					return gcnew IntPtr(_avPacket->data);
				}
				void set(IntPtr^ data)
				{
					_avPacket->data = reinterpret_cast<uint8_t*>(data->ToPointer());					
				}
			}

			property int Size
			{
				int get()
				{
					return _avPacket->size;
				}
				void set(int value)
				{
					_avPacket->size = value;
				}
			}

			
			property int StreamIndex
			{
				int get()
				{
					return _avPacket->stream_index;
				}
				void set(int value)
				{
					_avPacket->stream_index = value;
				}
			}

			property __int64 Pts
			{
				__int64 get()
				{
					return _avPacket->pts;
				}
				void set(__int64 value)
				{
					_avPacket->pts = value;
				}

			}

			property __int64 Dts
			{
				__int64 get()
				{
					return _avPacket->dts;
				}
				void set(__int64 value)
				{
					_avPacket->dts = value;
				}
			}

		//internal:
			::AVPacket * _avPacket;
		};

	};
};