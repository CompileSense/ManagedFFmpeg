#pragma once
namespace FFMpegNet 
{
	namespace AVUtil
	{
		public enum class AVMediaType 
		{
			UNKNOWN = -1,
			VIDEO,
			AUDIO,
			DATA,
			SUBTITLE,
			ATTACHMENT,
			NB
		};

	};
};