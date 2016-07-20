#pragma once

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#define inline _inline

#pragma warning(push)
#pragma warning(disable:4244)	//...warnings about __int64 to __int32 casts and whatnot (meh)


// Note: If you are tempted to put these includes in their own namespace: DON'T
//
// libav* #include standard headers, which have their own namespaces and can't be put
// in yours.

extern "C"
{
	#include "libavcodec/avcodec.h"
	#include "libavformat/avformat.h"
	#include "libavutil/avutil.h"
	#include "libswscale/swscale.h"	
	#include "libswresample/swresample.h"

	#include "libavutil/mem.h"
	#include "libavutil/avstring.h"
	#include "libavutil/error.h"
	#include "libavformat/avio.h"
};



#pragma warning(pop)

