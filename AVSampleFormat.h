#pragma once
using namespace System;

namespace FFMpegNet 
{
	namespace AVCodec
	{
		
		public enum class AVSampleFormat
		{
			NONE = -1,
			U8,			///< unsigned 8 bits
			S16,		///< signed 16 bits
			S32,		///< signed 32 bits
			FLT,		///< float
			DBL,		///< double
			U8P,		///< unsigned 8 bit planar
			S16P,		///< signed 16 bit planar
			S32P,		///< signed 32 bit planar
			FLTP,		///< float, planar
			DBLP,		///< double, planar

			NB			///< Number of sample formats. DO NOT USE if linking dynamically
		};

		public ref class AVSampleFormatHelper
		{
		public:
			static int BytesPerSample(AVSampleFormat format)
			{
				return ::av_get_bytes_per_sample(static_cast<::AVSampleFormat>(format));
			}

			static bool IsPlanar(AVSampleFormat format)
			{
				return ::av_sample_fmt_is_planar(static_cast<::AVSampleFormat>(format)) != 0;
			}
		};

	};
};