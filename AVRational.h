#pragma once

#include "ffmpeg_actual.h"

#include "AVFormatContext.h"

using namespace System;

namespace FFMpegNet 
{
	namespace AVUtil
	{
		public ref class AVRational
		{
		public:
			AVRational(const ::AVRational* _avRational) : Numerator(_avRational->num), Denominator(_avRational->den)
			{

			};

			AVRational(long numerator, long denominator) : Numerator(numerator), Denominator(denominator)
			{
				// Use temp and copy to comply with constness
				//::AVRational * avRational = new ::AVRational();
				//avRational.num = numerator;
				//avRational.den = denominator;
				//this->_avRational = avRational;
				//this->deleteInternal = true;
				
			};

			//~AVRational()
			//{
			//	//if (this->deleteInternal == true)
			//	//{
			//	//	delete this->_avRational;
			//	//}
			//};

			//property long Numerator
			//{
			//	long get()
			//	{
			//		return _avRational->num;
			//	}
			//}

			//property long Denominator
			//{
			//	long get()
			//	{
			//		return _avRational->den;
			//	}
			//}

			static __int64 RescaleQ(__int64 input, AVRational^ r1, AVRational^ r2)
			{
				::AVRational _r1, _r2;
				_r1.num = r1->Numerator;
				_r1.den = r1->Denominator;
				_r2.num = r2->Numerator;
				_r2.den = r2->Denominator;

				return ::av_rescale_q(input, _r1, _r2);
			}

			const long Numerator;
			const long Denominator;
			

		private:
			//const ::AVRational _avRational;
			bool deleteInternal;
		};


	};
};