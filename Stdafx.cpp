// stdafx.cpp : source file that includes just the standard includes
// SVFFMpeg.Net.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// Need to include all these headers somewhere so that the class implementations
// are available.

#include "FFMpeg.h"


#include "AVCodec.h"
#include "AVCodecContext.h"
#include "AVFrame.h"
#include "AVPacket.h"
#include "Channel.h"
#include "CodecCap.h"
#include "CodecFlags.h"
#include "AVCodecID.h"
#include "ResampleContext.h"

#include "AVSampleFormat.h"

#include "AVConstants.h"
#include "AVFMT.h"
#include "AVError.h"
#include "AVFormatContext.h"
#include "AVFormatParameters.h"
#include "AVFrac.h"
#include "AVOutputFormat.h"
#include "AVStream.h"

#include "AVMediaType.h"
#include "AVRational.h"
#include "PixelFormat.h"

#include "SwScaler.h"
#include "SWResampleContext.h"