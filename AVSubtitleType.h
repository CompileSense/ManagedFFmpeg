#pragma once


namespace FFMpegNet 
{
	namespace AVCodec
	{
		public enum class AVSubtitleType 
		{
			SUBTITLE_NONE,

			SUBTITLE_BITMAP,                ///< A bitmap, pict will be set

			/**
			 * Plain text, the text field must be set by the decoder and is
			 * authoritative. ass and pict fields may contain approximations.
			 */
			SUBTITLE_TEXT,

			/**
			 * Formatted text, the ass field must be set by the decoder and is
			 * authoritative. pict and text fields may contain approximations.
			 */
			SUBTITLE_ASS,
		};

	};
}