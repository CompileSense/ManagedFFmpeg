#pragma once


#include "ffmpeg_actual.h"

#include "PixelFormat.h"


using namespace System;

namespace FFMpegNet 
{
	namespace AVCodec
	{
		public ref class AVFrame
		{
		
		protected:
			AVFrame() : refCount(0)
			{
				objCount++;
			}


			bool manageMemory;

			// TODO - COPY CONSTRUCTOR!!
		public:
			AVFrame(::AVFrame* _avFrame)
			{
				if (_avFrame == 0)
				{
					throw gcnew ArgumentNullException("Cannot create an AVFrame with a null reference");
				}
				this->_avFrame = _avFrame;
			}
		
			~AVFrame()
			{

				if (refCount > 0)
				{
					throw gcnew Exception("Memory leak: You're disposing of an AVframe but references still exist");
				}
			}


			static AVFrame()
			{
				objCount = 0;
			}

			static int objCount;

			int refCount;
			void AddRef()
			{
				refCount++;
				//System::Console::WriteLine("RefCount++ now {0} on {1}", refCount, GetHashCode());
			}

			void Release()
			{
				refCount--;
				//System::Console::WriteLine("RefCount-- now {0} on {1}", refCount, GetHashCode());
				if (refCount <= 0)
				{
					if (_avFrame != NULL && manageMemory)
					{
						//System::Console::WriteLine("De-allocating AVFrame");
						if (_avFrame->format == static_cast<::AVMediaType>(AVUtil::AVMediaType::VIDEO))
						{
							::avpicture_free((::AVPicture*)_avFrame);
						}
						else if (_avFrame->format == static_cast<::AVMediaType>(AVUtil::AVMediaType::AUDIO))
						{
							for(int i = 0; i < AV_NUM_DATA_POINTERS; i++)
							{
								if (_avFrame->data[i] != NULL)
								{
									//fprintf(stderr, "about to free %d\n", _avFrame->data[0]);
									free(_avFrame->data[i]);
									_avFrame->data[i] = 0;
									_avFrame->linesize[i] = 0;
								}
							}
						}
						else
						{
							throw gcnew NotImplementedException();
						}
						::av_free(_avFrame);
						_avFrame = NULL;

						objCount--;
					}
				}
			}

			// Type of value will actually depend on sample format. Templated type?
			void SetSample(int sampleNumber, short value)
			{
				_avFrame->data[0][2* sampleNumber] = (uint8_t)value;
				_avFrame->data[0][2* sampleNumber + 1] = (uint8_t)value;
			}

			short GetSample(int sampleNumber)
			{
				return _avFrame->data[0][2 * sampleNumber];
			}

			void SetType(int type)
			{
				_avFrame->format = type;
			}

			property __int64 Pts
			{
				__int64 get()
				{
					return _avFrame->pts;
				}
				void set(__int64 value)
				{
					_avFrame->pts = value;
				}
			}


			property bool KeyFrame
			{
				bool get()
				{
					return (bool)(_avFrame->key_frame == 0);
				}
			}

			IntPtr^ GetData(int line)
			{
				if (line >= AV_NUM_DATA_POINTERS)
				{
					throw gcnew ArgumentException("line must be less than AV_NUM_DATA_POINTERS");
				}
				return gcnew IntPtr(_avFrame->data[line]);
			}

			int GetLineSize(int line)
			{
				if (line >= AV_NUM_DATA_POINTERS)
				{
					throw gcnew ArgumentException("line must be less than AV_NUM_DATA_POINTERS");
				}
				return _avFrame->linesize[line];
			}

			property IntPtr^ Data
			{
				IntPtr^ get()
				{
					// What about planar data types?
					return gcnew IntPtr(_avFrame->data);
				}
			}

			property IntPtr^ LineSizes
			{
				IntPtr^ get()
				{
					return gcnew IntPtr(_avFrame->linesize);
				}
			}


			property int Size
			{
				int get()
				{
					int totalSize = 0;
					for(int i = 0 ; i < AV_NUM_DATA_POINTERS; i++)
					{
						totalSize += _avFrame->linesize[i];
					}
					return totalSize;
				}
			}

			property int CodedFrameNumber
			{
				int get()
				{
					return _avFrame->coded_picture_number;
				}
			}

			void Debug_DumpFrame(String^ filename)
			{
				const char * p = (const char *)Marshal::StringToHGlobalAnsi(filename).ToPointer();
				FILE * f = fopen(p, "wb");
				if (f != NULL)
				{
					for (int i = 0; i < AV_NUM_DATA_POINTERS; i++)
					{
						if (_avFrame->data[i] != NULL)
						{
							int bytesToWrite = 0;
							if (_avFrame->linesize[i] != 0)
							{
								bytesToWrite = _avFrame->linesize[i];
							}
							else
							{
								bytesToWrite = _avFrame->linesize[0];
							}
							fwrite(&i, sizeof(int), 1, f);
							fwrite(&bytesToWrite, sizeof(int), 1, f);
							int zero = 0;
							fwrite(&zero, sizeof(int), 1, f);
							fwrite(&zero, sizeof(int), 1, f);
							fwrite(&zero, sizeof(int), 1, f);
							fwrite(&zero, sizeof(int), 1, f);
							fwrite(_avFrame->data[i], sizeof(uint8_t), bytesToWrite, f); 
						}
					}
					fclose(f);
				}
				
			}

		internal:
			::AVFrame * _avFrame;
		};

		public ref class AVVideoFrame : AVFrame
		{
		public:
			AVVideoFrame(AVUtil::PixelFormat pixelFormat, int width, int height) : AVFrame()
			{
				::AVPixelFormat avPixelFormat = static_cast<::AVPixelFormat>(pixelFormat);
				_avFrame = ::av_frame_alloc();
				::avpicture_alloc((::AVPicture *)_avFrame, avPixelFormat, width, height);
				_avFrame->width = width;
				_avFrame->height = height;
				_avFrame->format = avPixelFormat;
				_avFrame->extended_data = _avFrame->data;
				
				_avFrame->format = static_cast<::AVPictureType>(FFMpegNet::AVUtil::AVMediaType::VIDEO);
				manageMemory = true;
			};

			AVVideoFrame(AVUtil::PixelFormat pixelFormat, int width, int height, IntPtr^ p) : AVFrame()
			{
				::AVPixelFormat avPixelFormat = static_cast<::AVPixelFormat>(pixelFormat);
				_avFrame = ::av_frame_alloc();
				int size = ::avpicture_get_size(avPixelFormat, width, height);
				::avpicture_fill((::AVPicture *)_avFrame, static_cast<uint8_t *>(p->ToPointer()), avPixelFormat, width, height);
				
				_avFrame->format = static_cast<::AVPictureType>(FFMpegNet::AVUtil::AVMediaType::VIDEO);
				manageMemory = false;
			}

			// Horribly, horribly slow.
			void SetPixel(int plane, int x, int y, int argb)
			{
				_avFrame->data[plane][y * _avFrame->linesize[plane] + 3*x] = argb >> 24;
				_avFrame->data[plane][y * _avFrame->linesize[plane] + 3*x + 1] = argb >> 16;
				_avFrame->data[plane][y * _avFrame->linesize[plane] + 3*x + 2] = argb >> 8;
			}

			property int Width
			{
				int get()
				{
					return _avFrame->width;
				}
			}

			property int Height
			{
				int get()
				{
					return _avFrame->height;
				}
			}

			property AVUtil::PixelFormat PixelFormat
			{
				AVUtil::PixelFormat get()
				{
					return static_cast<AVUtil::PixelFormat>(_avFrame->format);
				}
			}
		};

		public ref class AVAudioFrame : AVFrame
		{
		public:
			AVAudioFrame(FFMpegNet::AVCodec::AVSampleFormat sampleFormat, int numberOfSamples, int channels, int sampleRate) : AVFrame()
			{
				int audioBufferLength = Init(sampleFormat, numberOfSamples, channels, sampleRate);
				// The audio buffer length calculation asks ffmpeg what the bytes-per-sample is, 
				// and handles planar/interleaved for us.

				manageMemory = true;
				
				int isPlanar = ::av_sample_fmt_is_planar((::AVSampleFormat)sampleFormat);
				if (isPlanar == 0)
				{
					_avFrame->data[0] = (uint8_t *)malloc(audioBufferLength);
					//fprintf(stderr, "malloc gave (0 - interleaved) %d\n", _avFrame->data[0]);
				}
				else
				{
					// Does the channel count imply a particular layout? I'm going to assume channels
					// are allocated from zero and proceed contiguously until count.
					for(int i = 0; i < channels; i++)
					{
						_avFrame->data[i] = (uint8_t *)malloc(audioBufferLength);
						//fprintf(stderr, "malloc gave (%d - planar) %d\n", i, _avFrame->data[i]);
					}
				}
				_avFrame->extended_data = _avFrame->data;	// to avoid warning
			}

			AVAudioFrame(FFMpegNet::AVCodec::AVSampleFormat sampleFormat, int numberOfSamples, int channels, int sampleRate, IntPtr^ p) : AVFrame()
			{
				int audioBufferLength = Init(sampleFormat, numberOfSamples, channels, sampleRate);
				
				manageMemory = false;

				_avFrame->data[0] = static_cast<uint8_t *> (p->ToPointer());
				_avFrame->extended_data = _avFrame->data;	// to avoid warning
			}

		private:
			int Init(FFMpegNet::AVCodec::AVSampleFormat sampleFormat, int numberOfSamples, int channels, int sampleRate)
			{
				if (numberOfSamples <= 0)
				{
					throw gcnew ArgumentOutOfRangeException("numberOfSamples must be >0");
				}
				if (channels <= 0)
				{
					throw gcnew ArgumentOutOfRangeException("channels must be >0");
				}
				if (sampleRate <= 0)
				{
					throw gcnew ArgumentOutOfRangeException("sampleRate must be >0");
				}

				_avFrame = ::av_frame_alloc();
				_avFrame->format = static_cast<::AVSampleFormat>(sampleFormat);
				_avFrame->nb_samples = numberOfSamples;

				int bytesPerSample = ::av_get_bytes_per_sample((::AVSampleFormat)_avFrame->format);

				int isPlanar = ::av_sample_fmt_is_planar((::AVSampleFormat)_avFrame->format);
				int audioSampleLength = bytesPerSample;	
				if (isPlanar == 0)
				{
					audioSampleLength = bytesPerSample * channels;	
				}
				int audioBufferLength = audioSampleLength * _avFrame->nb_samples;
				
				_avFrame->linesize[0] = audioBufferLength;
				if (isPlanar != 0)
				{
					for(int i = 0; i < channels; i++)
					{
						_avFrame->linesize[i] = audioBufferLength;
					}
				}
				
				_avFrame->sample_rate = sampleRate;
				_avFrame->channels = channels;

				_avFrame->format = static_cast<::AVMediaType>(FFMpegNet::AVUtil::AVMediaType::AUDIO);

				return audioBufferLength;
			}
		public:

			property int NumberOfSamples
			{
				int get()
				{
					return _avFrame->nb_samples;
				}
			}

			property int SampleRate
			{
				int get()
				{
					return _avFrame->sample_rate;
				}
			}

			property int Channels
			{
				int get()
				{
					return (int) _avFrame->channels;
				}
			}



			property FFMpegNet::AVCodec::AVSampleFormat SampleFormat
			{
				FFMpegNet::AVCodec::AVSampleFormat get()
				{
					return static_cast<FFMpegNet::AVCodec::AVSampleFormat>(_avFrame->format);
				}
			}
		};

	};
};
