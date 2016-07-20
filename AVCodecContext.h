#pragma once

#include "ffmpeg_actual.h"

//#include "AVStream.h"
#include "AVMediaType.h"
#include "AVSubtitle.h"
#include "AVCodecID.h"
#include "CodecFlags.h"
#include "PixelFormat.h"
#include "AVSampleFormat.h"

using namespace System;


namespace FFMpegNet 
{
	namespace AVCodec
	{


		public ref class AVCodecContext abstract
		{
		public:
			AVCodecContext(/*AVFormat::AVStream^ stream*/)
			{
				//_avCodecContext = stream->_avStream->codec;
			}



			// Properties in the same order as the C typedef

			// AVClass *av_class
			// int log_level_offset

			property AVUtil::AVMediaType MediaType
			{
				AVUtil::AVMediaType get()
				{
					return static_cast<AVUtil::AVMediaType>(_avCodecContext->codec_type);
				}
				void set(AVUtil::AVMediaType value)
				{
					_avCodecContext->codec_type = static_cast<::AVMediaType> (value);
				}
			}

			// AVCodec *codec;
			// char codec_name[32]

			// Warning:
			// In the ffmpeg codebase (linked through ffmpeg_actual.h) you might find code like
			//#if FF_API_CODEC_ID
			//#define CodecID AVCodecID
			//#endif
			// Which might only kick in on release builds!

#ifdef CodecID
#undef CodecID
#define ___CodecID
#endif

			property FFMpegNet::AVCodec::AVCodecID CodecID
			{
				FFMpegNet::AVCodec::AVCodecID get()
				{
					return static_cast<FFMpegNet::AVCodec::AVCodecID> (_avCodecContext->codec_id);
				}
				void set(FFMpegNet::AVCodec::AVCodecID value)
				{
					_avCodecContext->codec_id = static_cast<::AVCodecID>(value);
				}
			}
			
#ifdef ___CodecID
#undef ___CodecID
#define CodecID AVCodecID
#endif

			property int CodecTag
			{
				int get()
				{
					return _avCodecContext->codec_tag;
				}
			}

			property int StreamCodecTag
			{
				int get()
				{
					return _avCodecContext->stream_codec_tag;
				}
			}

			// void *priv_data
			// AVCodecInternal *internal
			// void *opaque
			

			property int BitRate
			{
				int get()
				{
					return _avCodecContext->bit_rate;
				}
				void set(int value)
				{
					_avCodecContext->bit_rate = value;
				}
			}
			
			property int BitRateTolerance
			{
				int get()
				{
					return _avCodecContext->bit_rate_tolerance;
				}
				void set(int value)
				{
					_avCodecContext->bit_rate_tolerance = value;
				}
			}

			property int GlobalQuality
			{
				int get()
				{
					return _avCodecContext->global_quality;
				}
				void set(int value)
				{
					_avCodecContext->global_quality = value;
				}
			}

			property int CompressionLevel
			{
				int get()
				{
					return _avCodecContext->compression_level;
				}
				void set(int value)
				{
					_avCodecContext->compression_level = value;
				}
			}

			property CodecFlag Flags
			{
				CodecFlag get()
				{
					return static_cast<CodecFlag>(_avCodecContext->flags);
				}
				void set(CodecFlag flags)
				{
					_avCodecContext->flags = static_cast<int>(flags);
				}
			}

			property CodecFlag2 Flags2
			{
				CodecFlag2 get()
				{
					return static_cast<CodecFlag2>(_avCodecContext->flags2);
				}
				void set(CodecFlag2 flags)
				{
					_avCodecContext->flags2 = static_cast<int>(flags);
				}
			}
			// uint8_t *extradata
			// int extradata_size
			
			property AVUtil::AVRational^ TimeBase
			{
				AVUtil::AVRational^ get()
				{
					return gcnew AVUtil::AVRational(_avCodecContext->time_base.num, _avCodecContext->time_base.den);
				}
				void set(AVUtil::AVRational^ value)
				{
					_avCodecContext->time_base.num = (value->Numerator);
					_avCodecContext->time_base.den = (value->Denominator);
				}
			}

			property int TicksPerFrame
			{
				int get()
				{
					return _avCodecContext->ticks_per_frame;
				}
			}

			property int Delay
			{
				int get()
				{
					return _avCodecContext->delay;
				}
			}



 
			// float b_quant_factor
			// int rc_strategy
			// int b_frame_strategy
			// float b_quant_offset
			// int has_b_frames
			// int mpeg_quant
			// float i_quant_factor
			// float i_quant_offset
			// float lumi_masking
			// float temporal_cplx_masking
			// float spatial_cplx_masking
			// float p_masking
			// float dark_masking
			// int slice_count
			// int prediction_method
			// int *slice_offset
			// AVRational sample_aspect_ratio
			// int me_cmp
			// int me_sub_cmp
			// int mb_cmp
			// int ildct_cmp;
			//int dia_size;
			//int last_predictor_count;
			//int pre_me;
			//int me_pre_cmp;
			//int pre_dia_size;
			//int me_subpel_quality;
			//int dtg_active_format;

			//	int me_range;
			//	int intra_quant_bias;
			//#define FF_DEFAULT_QUANT_BIAS 999999
			//	int inter_quant_bias;
			//	int slice_flags;
			//#define SLICE_FLAG_CODED_ORDER    0x0001 ///< draw_horiz_band() is called in coded order instead of display
			//#define SLICE_FLAG_ALLOW_FIELD    0x0002 ///< allow draw_horiz_band() with field slices (MPEG2 field pics)
			//#define SLICE_FLAG_ALLOW_PLANE    0x0004 ///< allow draw_horiz_band() with 1 component at a time (SVQ1)
			//	int xvmc_acceleration;

			void SetMBDecision(int a)
			{
				_avCodecContext->mb_decision = a;
			}

			//#define FF_MB_DECISION_SIMPLE 0        ///< uses mb_cmp
			//#define FF_MB_DECISION_BITS   1        ///< chooses the one which needs the fewest bits
			//#define FF_MB_DECISION_RD     2        ///< rate distortion
			//	uint16_t *intra_matrix;
			//	uint16_t *inter_matrix;
			//	int scenechange_threshold;
			//	int noise_reduction;
			//	int me_threshold;
			//	int mb_threshold;
			//	int intra_dc_precision;
			//	int skip_top;
			//	int skip_bottom;
			//	float border_masking;
			//	int mb_lmin;
			//	int mb_lmax;
			//	int me_penalty_compensation;
			//	int bidir_refine;
			//	int brd_scale;
			//	int keyint_min;
			//	int refs;
			//	int chromaoffset;
			//	int scenechange_factor;
			//	int mv0_threshold;
			//	int b_sensitivity;
			//	enum AVColorPrimaries color_primaries;
			//	enum AVColorTransferCharacteristic color_trc;
			//	enum AVColorSpace colorspace;
			//	enum AVColorRange color_range;
			//	enum AVChromaLocation chroma_sample_location;
			//	int slices;
			//	enum AVFieldOrder field_order;
			


			property int FrameNumber
			{
				int get()
				{
					return _avCodecContext->frame_number;
				}
			}

			property int BlockAlign
			{
				int get()
				{
					return _avCodecContext->block_align;
				}
			}

			property int Cutoff
			{
				int get()
				{
					return _avCodecContext->cutoff;
				}
			}
			//	enum AVAudioServiceType audio_service_type;
			//	enum AVSampleFormat request_sample_fmt;

			//	float qcompress;  ///< amount of qscale change between easy & hard scenes (0.0-1.0)
			//	float qblur;      ///< amount of qscale smoothing over time (0.0-1.0)
			//	int qmin;
			//	int qmax;
			//	int max_qdiff;
			//	float rc_qsquish;

			//	float rc_qmod_amp;
			//	int rc_qmod_freq;
			//	int rc_buffer_size;
			//	int rc_override_count;
			//	RcOverride *rc_override;
			//	const char *rc_eq;
			//	int rc_max_rate;
			//	int rc_min_rate;

			//	float rc_buffer_aggressivity;
			//	float rc_initial_cplx;
			//	float rc_max_available_vbv_use;
			//	float rc_min_vbv_overflow_use;
			//	int rc_initial_buffer_occupancy;

			//	int coder_type;
			//	int context_model;
			//	int lmin;
			//	int lmax;
			//	int frame_skip_threshold;
			//	int frame_skip_factor;
			//	int frame_skip_exp;
			//	int frame_skip_cmp;
			//	int trellis;
			//	int min_prediction_order;
			//	int max_prediction_order;
			//	int64_t timecode_frame_start;

			//	int rtp_payload_size;   
			//	int mv_bits;
			//	int header_bits;
			//	int i_tex_bits;
			//	int p_tex_bits;
			//	int i_count;
			//	int p_count;
			//	int skip_count;
			//	int misc_bits;
			//	int frame_bits;
			//	char *stats_out;
			//	char *stats_in;
			//	int workaround_bugs;
			
			//	int strict_std_compliance;
			//#define FF_COMPLIANCE_VERY_STRICT   2 ///< Strictly conform to an older more strict version of the spec or reference software.
			//#define FF_COMPLIANCE_STRICT        1 ///< Strictly conform to all the things in the spec no matter what consequences.
			//#define FF_COMPLIANCE_NORMAL        0
			//#define FF_COMPLIANCE_UNOFFICIAL   -1 ///< Allow unofficial extensions
			//#define FF_COMPLIANCE_EXPERIMENTAL -2 ///< Allow nonstandardized experimental things.
			property int StrictStdCompliance
			{
				int get()
				{
					return _avCodecContext->strict_std_compliance;
				}
				void set(int val)
				{
					_avCodecContext->strict_std_compliance = val;
				}
			}



			//	int error_concealment;
			//	int debug;
			//	int debug_mv;
			//	int err_recognition;
			//	int64_t reordered_opaque;
			//	struct AVHWAccel *hwaccel;
			//	void *hwaccel_context;
			//	uint64_t error[AV_NUM_DATA_POINTERS];
			//	int dct_algo;
			//	int idct_algo;
			//	 int bits_per_coded_sample;
			//	int bits_per_raw_sample;
			//	 int lowres;
			//	AVFrame *coded_frame;
			//	int thread_count;
			//	int thread_type;
			//	int active_thread_type;
			//	int thread_safe_callbacks;
			//	void *thread_opaque;
			//	 int nsse_weight;
			//	int profile;

			//	 int level;
			//	enum AVDiscard skip_loop_filter;
			//	enum AVDiscard skip_idct;
			//	enum AVDiscard skip_frame;
			//	uint8_t *subtitle_header;
			//	int subtitle_header_size;
			//	int error_rate;
			//	AVPacket *pkt;
			//	uint64_t vbv_delay;
			//	AVRational pkt_timebase;
			//	const AVCodecDescriptor *codec_descriptor;
			//	int64_t pts_correction_num_faulty_pts; /// Number of incorrect PTS values so far
			//	int64_t pts_correction_num_faulty_dts; /// Number of incorrect DTS values so far
			//	int64_t pts_correction_last_pts;       /// PTS of the last frame
			//	int64_t pts_correction_last_dts;       /// DTS of the last frame

			AVFrame^ GetCodedFrame()
			{
				return gcnew AVFrame(_avCodecContext->coded_frame);
			}

			virtual int Encode(AVPacket^ packet, AVFrame^ input) = 0;

			int EncodeSubtitle(IntPtr^ outputBuffer, int outputBufferSize, FFMpegNet::AVCodec::AVSubtitle^ input)
			{
				return ::avcodec_encode_subtitle(_avCodecContext, reinterpret_cast<uint8_t*>(outputBuffer->ToPointer()),
					outputBufferSize, input->_avSubtitle);
			}

			void FlushBuffers()
			{
				::avcodec_flush_buffers(_avCodecContext);
			}

			//void DefaultFreeBuffers()
			//{
			//	::avcodec_default_free_buffers(_avCodecContext);
			//}

			int Open(FFMpegNet::AVCodec::AVCodec^ avCodec)
			{
				::AVDictionary * options = NULL;
				int result = ::avcodec_open2(_avCodecContext, avCodec->_avCodec, &options);
				return result;
			}

			void Close()
			{
				::avcodec_close(_avCodecContext);
			}

		internal:
			::AVCodecContext * _avCodecContext;
		};


		public ref class AVVideoCodecContext : AVCodecContext
		{
		public:
			AVVideoCodecContext()
			{
			}

			static AVVideoCodecContext^ Wrap(::AVCodecContext* _avCodecContext)
			{
				// TODO: bad cast and enum from wrong domain
				if (_avCodecContext->codec_type == (int) AVUtil::AVMediaType::VIDEO)
				{
					AVVideoCodecContext^ rtn = gcnew AVVideoCodecContext();
					rtn->_avCodecContext = _avCodecContext;

					return rtn;
				}
				else
				{
					return nullptr;
				}
			}

			virtual int Encode(AVPacket^ packet, AVFrame^ input) override
			{
				int got_packet_ptr;
				int size = ::avcodec_encode_video2(_avCodecContext, 
					packet->_avPacket,
					input->_avFrame, &got_packet_ptr);
				return size;
			}


			property AVUtil::PixelFormat PixelFormat
			{
				AVUtil::PixelFormat get()
				{
					return static_cast<AVUtil::PixelFormat>(_avCodecContext->pix_fmt);
				}
				void set(AVUtil::PixelFormat value)
				{
					_avCodecContext->pix_fmt = static_cast<AVPixelFormat>(value);
				}
			}

			property int Width
			{
				int get()
				{
					return _avCodecContext->width;
				}
				void set(int value)
				{
					_avCodecContext->width = value;
				}
			}

			property int Height
			{
				int get()
				{
					return _avCodecContext->height;
				}
				void set(int value)
				{
					_avCodecContext->height = value;
				}
			}

			property int CodedWidth
			{
				int get()
				{
					return _avCodecContext->coded_width;
				}
				void set(int value)
				{
					_avCodecContext->coded_width = value;
				}
			}

			property int CodedHeight
			{
				int get()
				{
					return _avCodecContext->coded_height;
				}
				void set(int value)
				{
					_avCodecContext->coded_height = value;
				}
			}

			property int QMin
			{
				int get()
				{
					return _avCodecContext->qmin;
				}
				void set(int value)
				{
					_avCodecContext->qmin = value;
				}
			}

			property int QMax
			{
				int get()
				{
					return _avCodecContext->qmax;
				}
				void set(int value)
				{
					_avCodecContext->qmax = value;
				}
			}

           void SetGOPSize(int gopSize)
			{
				_avCodecContext->gop_size = gopSize;
			}


			void SetMotionEstimationMethod(int m)
			{
				_avCodecContext->me_method = m;
			}
			
			void SetMaxBFrames(int b)
			{
				_avCodecContext->max_b_frames = b;
			}
			
		};

		public ref class AVAudioCodecContext : public AVCodecContext
		{
		public:
			AVAudioCodecContext()
			{
				
			}

			static AVAudioCodecContext^ Wrap(::AVCodecContext* _avCodecContext)
			{
				// TODO: bad cast and enum from wrong domain
				if (_avCodecContext->codec_type == (int) AVUtil::AVMediaType::AUDIO)
				{
					AVAudioCodecContext^ rtn = gcnew AVAudioCodecContext();
					rtn->_avCodecContext = _avCodecContext;

					return rtn;
				}
				else
				{
					return nullptr;
				}
			}

			property int SampleRate
			{
				int get()
				{
					return _avCodecContext->sample_rate;
				}
				void set(int value)
				{
					_avCodecContext->sample_rate = value;
				}
			}

			property int Channels
			{
				int get()
				{
					return _avCodecContext->channels;
				}
				void set(int value)
				{
					_avCodecContext->channels = value;
				}
			}

						//	uint64_t channel_layout;
			property __int64 ChannelLayout
			{
				__int64 get()
				{
					return _avCodecContext->channel_layout;
				}
				void set(__int64 value)
				{
					_avCodecContext->channel_layout = value;
				}
			}


			property FFMpegNet::AVCodec::AVSampleFormat SampleFormat
			{
				FFMpegNet::AVCodec::AVSampleFormat get()
				{
					return static_cast<FFMpegNet::AVCodec::AVSampleFormat>(_avCodecContext->sample_fmt);
				}
				void set(FFMpegNet::AVCodec::AVSampleFormat value)
				{
					_avCodecContext->sample_fmt = static_cast<::AVSampleFormat>(value);
				}
			}

			property int FrameSize
			{
				int get()
				{
					return _avCodecContext->frame_size;
				}
			}

			virtual int Encode(AVPacket^ packet, AVFrame^ input) override
			{
				// This function encodes _avCodecContext->frame_size * _avCodecContext->channels worth of samples.
				// Multiply that number by the size given by the sample format to determine the number of bytes.
				int got_packet_ptr;
				int size = ::avcodec_encode_audio2(_avCodecContext, packet->_avPacket, input->_avFrame, &got_packet_ptr);
				return size;
			}
		};

	};
};