#pragma once
using namespace System;

namespace FFMpegNet 
{
	namespace AVCodec
	{
		// Note: Would perhaps be nicer to do these as enums, but the layout construction
		// syntax gets a bit sticky.
		namespace Channel
		{
			static const int FRONT_LEFT = 0x00000001;
			static const int FRONT_RIGHT = 0x00000002;
			static const int FRONT_CENTER = 0x00000004;
			static const int LOW_FREQUENCY = 0x00000008;
			static const int BACK_LEFT = 0x00000010;
			static const int BACK_RIGHT = 0x00000020;
			static const int FRONT_LEFT_OF_CENTER = 0x00000040;
			static const int FRONT_RIGHT_OF_CENTER = 0x00000080;
			static const int BACK_CENTER = 0x00000100;
			static const int SIDE_LEFT = 0x00000200;
			static const int SIDE_RIGHT = 0x00000400;
			static const int TOP_CENTER = 0x00000800;
			static const int TOP_FRONT_LEFT = 0x00001000;
			static const int TOP_FRONT_CENTER = 0x00002000;
			static const int TOP_FRONT_RIGHT = 0x00004000;
			static const int TOP_BACK_LEFT = 0x00008000;
			static const int TOP_BACK_CENTER = 0x00010000;
			static const int TOP_BACK_RIGHT = 0x00020000;
			static const int STEREO_LEFT = 0x20000000;  ///< Stereo downmix.
			static const int STEREO_RIGHT = 0x40000000;  ///< See CH_STEREO_LEFT.

			namespace  Layout
			{
			/** Channel mask value used for AVCodecContext.request_channel_layout
				to indicate that the user requests the channel order of the decoder output
				to be the native codec channel order. */
				static const __int64 NATIVE = 0x8000000000000000LL;


				static const __int64 MONO = (Channel::FRONT_CENTER);
				static const __int64 STEREO = (Channel::FRONT_LEFT|Channel::FRONT_RIGHT);
				static const __int64 TWO_ONE = (STEREO|Channel::BACK_CENTER);
				static const __int64 SURROUND = (STEREO|Channel::FRONT_CENTER);
				static const __int64 FOURPOINTZERO = (SURROUND|Channel::BACK_CENTER);
				static const __int64 TWO_TWO = (STEREO|Channel::SIDE_LEFT|Channel::SIDE_RIGHT);
				static const __int64 QUAD = (STEREO|Channel::BACK_LEFT|Channel::BACK_RIGHT);
				static const __int64 FIVEPOINTZERO = (SURROUND|Channel::SIDE_LEFT|Channel::SIDE_RIGHT);
				static const __int64 FIVEPOINTONE = (FIVEPOINTZERO|Channel::LOW_FREQUENCY);
				static const __int64 FIVEPOINTZERO_BACK = (SURROUND|Channel::BACK_LEFT|Channel::BACK_RIGHT);
				static const __int64 FIVEPOINTONE_BACK = (FIVEPOINTZERO_BACK|Channel::LOW_FREQUENCY);
				static const __int64 SEVENPOINTZERO = (FIVEPOINTZERO|Channel::BACK_LEFT|Channel::BACK_RIGHT);
				static const __int64 SEVENPOINTONE = (FIVEPOINTONE|Channel::BACK_LEFT|Channel::BACK_RIGHT);
				static const __int64 SEVENPOINTONE_WIDE = (FIVEPOINTONE_BACK| Channel::FRONT_LEFT_OF_CENTER|Channel::FRONT_RIGHT_OF_CENTER);
				static const __int64 STEREO_DOWNMIX = (Channel::STEREO_LEFT|Channel::STEREO_RIGHT);
			};
		};

	};
};