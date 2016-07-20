#pragma once

#include "ffmpeg_actual.h"

//#include "AVFormatContext.h"

using namespace System;

namespace FFMpegNet 
{
	namespace AVUtil
	{
		public ref class AVError
		{
		public:
			AVError()
			{
			};

			AVError(int errorCode)
			{
			};

			static String^ MakeString(int errorCode)
			{
				char errorBuffer[AV_ERROR_MAX_STRING_SIZE];
				
				::av_make_error_string(errorBuffer, AV_ERROR_MAX_STRING_SIZE, errorCode);
				//String^ errorString = marshal_as<String^>(errorBuffer);
				String^ errorString = Marshal::PtrToStringAnsi((IntPtr)errorBuffer);
				return errorString;
			}
		//public:
		//	AVRational(const ::AVRational* _avRational) : Numerator(_avRational->num), Denominator(_avRational->den)
		//	{

		//	};

		//	AVRational(long numerator, long denominator) : Numerator(numerator), Denominator(denominator)
		//	{
		//		
		//	};


		//	static __int64 RescaleQ(__int64 input, AVRational^ r1, AVRational^ r2)
		//	{
		//		::AVRational _r1, _r2;
		//		_r1.num = r1->Numerator;
		//		_r1.den = r1->Denominator;
		//		_r2.num = r2->Numerator;
		//		_r2.den = r2->Denominator;

		//		return ::av_rescale_q(input, _r1, _r2);
		//	}

		//	const long Numerator;
		//	const long Denominator;
		//	

		//private:
		//	//const ::AVRational _avRational;
		//	bool deleteInternal;
		};


	};
};