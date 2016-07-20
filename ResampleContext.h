#pragma once

#include "ffmpeg_actual.h"


using namespace System;
using namespace FFMpegNet::AVFormat;

namespace FFMpegNet 
{
	namespace AVCodec
	{

		public ref class ResampleContext
		{
		public:
			ResampleContext(int outputRate, int inputRate, int filterLength, int log2PhaseCount, int linear, double cutoff)
			{
				_resampleContext = ::av_resample_init(outputRate, inputRate, filterLength, log2PhaseCount, linear, cutoff);
			}

			~ResampleContext()
			{
				if (_resampleContext != NULL)
				{
					av_resample_close(_resampleContext);
				}
			}

			int Resample(AVAudioFrame^ inputFrame, AVAudioFrame^ outputFrame)
			{
				int consumed = 0;
				int bytesProduced = ::av_resample(_resampleContext, reinterpret_cast<short *>(outputFrame->Data->ToPointer()),
					reinterpret_cast<short *>(inputFrame->Data->ToPointer()),
					&consumed,
					inputFrame->NumberOfSamples * inputFrame->Channels, 
					outputFrame->NumberOfSamples * outputFrame->Channels, 1);
				
				return bytesProduced;
			}

			//int Resample(IntPtr^ outputBuffer, int outputBufferSize, IntPtr^ inputBuffer, int inputBufferSize)
			//{
			//	int consumed = 0;

			//	return ::av_resample(_resampleContext, reinterpret_cast<short *>(outputBuffer->ToPointer()),
			//		reinterpret_cast<short *>(inputBuffer->ToPointer()), &consumed, inputBufferSize, outputBufferSize, 0);
			//	//return ::audio_resample(_resampleContext, reinterpret_cast<short *>(outputBuffer->ToPointer()), 
			//	//	reinterpret_cast<short *>(inputBuffer->ToPointer()), nb_samples);
			//}


		internal:
			::AVResampleContext * _resampleContext;
			
		};
	};
};