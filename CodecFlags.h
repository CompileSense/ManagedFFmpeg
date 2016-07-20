#pragma once
using namespace System;

namespace FFMpegNet 
{
	namespace AVCodec
	{
		[ Flags ]
		public enum class CodecFlag
		{
			NONE = 0,
			QSCALE = 0x0002,///< Use fixed qscale.
			_4MV = 0x0004,///< 4 MV per MB allowed / advanced prediction for H.263.
			QPEL   = 0x0010  , ///< Use qpel MC.
			GMC    = 0x0020  , ///< Use GMC.
			MV0    = 0x0040  , ///< Always try a MB with MV=<0,0>.
			PART   = 0x0080  , ///< Use data partitioning.
			/**
			 * The parent program guarantees that the input for B-frames containing
			 * streams is not written to for at least s->max_b_frames+1 frames, if
			 * this is not set the input will be copied.
			 */
			INPUT_PRESERVED = 0x0100,
			PASS1           = 0x0200, ///< Use internal 2pass ratecontrol in first pass mode.
			PASS2           = 0x0400, ///< Use internal 2pass ratecontrol in second pass mode.
			EXTERN_HUFF     = 0x1000, ///< Use external Huffman table (for MJPEG).
			GRAY            = 0x2000, ///< Only decode/encode grayscale.
			EMU_EDGE        = 0x4000, ///< Don't draw edges.
			PSNR            = 0x8000, ///< error[?] variables will be set during encoding.
			TRUNCATED       = 0x00010000, /** Input bitstream might be truncated at a random
															  location instead of only at frame boundaries. */
			NORMALIZE_AQP  = 0x00020000, ///< Normalize adaptive quantization.
			INTERLACED_DCT = 0x00040000, ///< Use interlaced DCT.
			LOW_DELAY      = 0x00080000, ///< Force low delay.
			ALT_SCAN       = 0x00100000, ///< Use alternate scan.
			GLOBAL_HEADER  = 0x00400000, ///< Place global headers in extradata instead of every keyframe.
			BITEXACT       = 0x00800000, ///< Use only bitexact stuff (except (I)DCT).
			/* Fx : Flag for h263+ extra options */
			AC_PRED        = 0x01000000, ///< H.263 advanced intra coding / MPEG-4 AC prediction
			H263P_UMV      = 0x02000000, ///< unlimited motion vector
			CBP_RD         = 0x04000000, ///< Use rate distortion optimization for cbp.
			QP_RD          = 0x08000000, ///< Use rate distortion optimization for qp selectioon.
			H263P_AIV      = 0x00000008, ///< H.263 alternative inter VLC
			OBMC           = 0x00000001, ///< OBMC
			LOOP_FILTER    = 0x00000800, ///< loop filter
			H263P_SLICE_STRUCT = 0x10000000,
			INTERLACED_ME  = 0x20000000, ///< interlaced motion estimation
			SVCD_SCAN_OFFSET = 0x40000000, ///< Will reserve space for SVCD scan offset user data.
			CLOSED_GOP     = 0x80000000
		};

		public enum class CodecFlag2
		{
			FAST          = 0x00000001 , ///< Allow non spec compliant speedup tricks.
			STRICT_GOP    = 0x00000002 , ///< Strictly enforce GOP size.
			NO_OUTPUT     = 0x00000004 , ///< Skip bitstream encoding.
			LOCAL_HEADER  = 0x00000008 , ///< Place global headers at every keyframe instead of in extradata.
			BPYRAMID      = 0x00000010 , ///< H.264 allow B-frames to be used as references.
			WPRED         = 0x00000020 , ///< H.264 weighted biprediction for B-frames
			MIXED_REFS    = 0x00000040 , ///< H.264 one reference per partition, as opposed to one reference per macroblock
			_8X8DCT        = 0x00000080 , ///< H.264 high profile 8x8 transform
			FASTPSKIP     = 0x00000100 , ///< H.264 fast pskip
			AUD           = 0x00000200 , ///< H.264 access unit delimiters
			BRDO          = 0x00000400 , ///< B-frame rate-distortion optimization
			INTRA_VLC     = 0x00000800 , ///< Use MPEG-2 intra VLC table.
			MEMC_ONLY     = 0x00001000 , ///< Only do ME/MC (I frames -> ref, P frame -> ME+MC).
			DROP_FRAME_TIMECODE = 0x00002000 , ///< timecode is in drop frame format.
			SKIP_RD       = 0x00004000 , ///< RD optimal MB level residual skipping
			CHUNKS        = 0x00008000 , ///< Input bitstream might be truncated at a packet boundaries instead of only at frame boundaries.
			NON_LINEAR_QUANT = 0x00010000 , ///< Use MPEG-2 nonlinear quantizer.
			BIT_RESERVOIR = 0x00020000 , ///< Use a bit reservoir when encoding if possible
			MBTREE        = 0x00040000 , ///< Use macroblock tree ratecontrol (x264 only)
			PSY           = 0x00080000 , ///< Use psycho visual optimizations.
			SSIM          = 0x00100000 ///< Compute SSIM during encoding, error[] values are undefined.
		};

	};
};