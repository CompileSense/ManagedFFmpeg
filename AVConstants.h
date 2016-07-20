#pragma once

using namespace System;

namespace FFMpegNet 
{
	namespace AVFormat
	{		
		public ref class AVConstants
		{
		public:
			AVConstants()
			{
				
			};

			static __int64 NOPTS_VALUE = 0x8000000000000000;
		};
	};
};