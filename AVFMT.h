#pragma once

using namespace System;

namespace FFMpegNet 
{
	namespace AVFormat
	{
		[ Flags ]
		public enum class AVFMT
		{
			//NONE = 0,
			NOFILE        = 0x0001,
			NEEDNUMBER    = 0x0002, /**< Needs '%d' in filename. */
			SHOW_IDS      = 0x0008, /**< Show format stream IDs numbers. */
			RAWPICTURE    = 0x0020, /**< Format wants AVPicture structure for
											  raw picture data. */
			GLOBALHEADER  = 0x0040, /**< Format wants global header. */
			NOTIMESTAMPS  = 0x0080, /**< Format does not need / have any timestamps. */
			GENERIC_INDEX = 0x0100, /**< Use generic index building code. */
			TS_DISCONT    = 0x0200, /**< Format allows timestamp discontinuities. */
			VARIABLE_FPS  = 0x0400, /**< Format allows variable fps. */
			NODIMENSIONS  = 0x0800, /**< Format does not need width/height */

		};
	};
};