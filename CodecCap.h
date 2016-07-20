#pragma once
using namespace System;

namespace FFMpegNet 
{
	namespace AVCodec
	{
		[ Flags ]
		public enum class CodecCap
		{
			NONE = 0,
			DRAW_HORIZ_BAND = 0x0001, ///< Decoder can use draw_horiz_band callback.

			/*
			 * Codec uses get_buffer() for allocating buffers and supports custom allocators.
			 * If not set, it might not use get_buffer() at all or use operations that
			 * assume the buffer was allocated by avcodec_default_get_buffer.
			 */
			DR1 = 0x0002,
			/* If 'parse_only' field is true, then avcodec_parse_frame() can be used. */
			//PARSE_ONLY = 0x0004,
			TRUNCATED = 0x0008,
			/* Codec can export data for HW decoding (XvMC). */
			HWACCEL = 0x0010,
			/**
			 * Codec has a nonzero delay and needs to be fed with NULL at the end to get the delayed data.
			 * If this is not set, the codec is guaranteed to never be fed with NULL data.
			 */
			DELAY = 0x0020,
			/**
			 * Codec can be fed a final frame with a smaller size.
			 * This can be used to prevent truncation of the last audio samples.
			 */
			SMALL_LAST_FRAME = 0x0040,
			/**
			 * Codec can export data for HW decoding (VDPAU).
			 */
			HWACCEL_VDPAU = 0x0080,
			/**
			 * Codec can output multiple frames per AVPacket
			 * Normally demuxers return one frame at a time, demuxers which do not do
			 * are connected to a parser to split what they return into proper frames.
			 * This flag is reserved to the very rare category of codecs which have a
			 * bitstream that cannot be split into frames without timeconsuming
			 * operations like full decoding. Demuxers carring such bitstreams thus
			 * may return multiple frames in a packet. This has many disadvantages like
			 * prohibiting stream copy in many cases thus it should only be considered
			 * as a last resort.
			 */
			SUBFRAMES = 0x0100,
			/**
			 * Codec is experimental and is thus avoided in favor of non experimental
			 * encoders
			 */
			EXPERIMENTAL = 0x0200,

			CHANNEL_CONF = 0x0400,

			NEG_LINESIZES = 0x0800,

			FRAME_THREADS = 0x1000,
			SLICE_THREADS = 0x2000,
			PARAM_CHANGE = 0x4000,
			AUTO_THREADS = 0x8000,
			VARIABLE_FRAME_SIZE = 0x10000,
			INTRA_ONLY = 0x40000000,
			LOSSLESS = 0x80000000,

		};


	};
};