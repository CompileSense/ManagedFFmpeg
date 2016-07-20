#pragma once

#include "ffmpeg_actual.h"

#include "AVFormatContext.h"

using namespace System;

namespace FFMpegNet 
{
	namespace AVFormat
	{
		public ref class AVFrac
		{
		public:
			AVFrac(::AVFrac* _avFrac)
			{
				//_avFrac = new ::AVFrac();
				this->_avFrac = _avFrac;
			};

			
			property __int64 Value
			{
				__int64 get()
				{
					return _avFrac->val;
				}
			}

			property __int64 Numerator
			{
				__int64 get()
				{
					return _avFrac->num;
				}
			}

			property __int64 Denominator
			{
				__int64 get()
				{
					return _avFrac->den;
				}
			}

		internal:
			::AVFrac* _avFrac;
		};


	};
};