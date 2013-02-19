/*****************************************************************************
 * libav_audio.h
 *****************************************************************************
 * Copyright (C) 2012-2013 L-SMASH Works project
 *
 * Authors: Yusuke Nakamura <muken.the.vfrmaniac@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *****************************************************************************/

/* This file is available under an ISC license. */

typedef lw_audio_output_handler_t lwlibav_audio_output_handler_t;

typedef struct
{
    int      length;
    int      keyframe;
    int      sample_rate;
    uint32_t sample_number;
    int64_t  pts;
    int64_t  dts;
    int64_t  file_offset;
} audio_frame_info_t;

typedef struct
{
    AVFormatContext    *format;
    int                 stream_index;
    /* */
    error_handler_t     eh;
    AVCodecContext     *ctx;
    AVIndexEntry       *index_entries;
    int                 index_entries_count;
    int                 dv_in_avi;      /* 1 = 'DV in AVI Type-1', 0 = otherwise */
    int                 seek_base;
    enum AVCodecID      codec_id;
    uint32_t            frame_count;
    uint32_t            delay_count;
    AVPacket            packet;         /* for getting and freeing */
    AVPacket            alter_packet;   /* for consumed by the decoder instead of 'packet'. */
    AVFrame            *frame_buffer;
    audio_frame_info_t *frame_list;
    uint32_t            frame_length;
    uint32_t            last_frame_number;
    uint64_t            next_pcm_sample_number;
} lwlibav_audio_decode_handler_t;

int lwlibav_get_desired_audio_track
(
    const char                     *file_path,
    lwlibav_audio_decode_handler_t *adhp,
    int                             threads
);

uint64_t lwlibav_count_overall_pcm_samples
(
    lwlibav_audio_decode_handler_t *adhp,
    int                             output_sample_rate
);

uint64_t lwlibav_get_pcm_audio_samples
(
    lwlibav_audio_decode_handler_t *adhp,
    lwlibav_audio_output_handler_t *aohp,
    void                           *buf,
    int64_t                         start,
    int64_t                         wanted_length
);

void lwlibav_cleanup_audio_decode_handler( lwlibav_audio_decode_handler_t *adhp );
void lwlibav_cleanup_audio_output_handler( lwlibav_audio_output_handler_t *aohp );