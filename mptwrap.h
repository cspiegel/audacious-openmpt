/*-
 * Copyright (c) 2015-2019 Chris Spiegel
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef QMMP_MPT_MPTWRAP_H
#define QMMP_MPT_MPTWRAP_H

#include <cstddef>
#include <cstdint>
#include <exception>
#include <string>
#include <vector>

#include <libaudcore/vfs.h>

#include <libopenmpt/libopenmpt.h>
#include <libopenmpt/libopenmpt_stream_callbacks_file.h>

class MPTWrap
{
  public:
    struct Interpolator
    {
      Interpolator(const char *name, int value) : name(name), value(value) { }
      const char *name;
      int value;
    };

    class InvalidFile : public std::exception
    {
      public:
        InvalidFile() : std::exception() { }
    };

    explicit MPTWrap(VFSFile &);
    MPTWrap(const MPTWrap &) = delete;
    MPTWrap &operator=(const MPTWrap &) = delete;
    ~MPTWrap();

    static std::vector<Interpolator> get_interpolators();
    static bool is_valid_interpolator(int);
    static int default_interpolator();
    void set_interpolator(int);

    static bool is_valid_stereo_separation(int);
    static int default_stereo_separation();
    void set_stereo_separation(int);

    std::int64_t read(void *, std::int64_t);
    void seek(int pos);

    int rate() { return 44100; }
    int channels() { return 2; }
    int depth() { return 16; }
    int duration() { return duration_; }
    std::string title() { return title_; }
    std::string format() { return format_; }
    int pattern_count() { return pattern_count_; }
    int channel_count() { return channel_count_; }
    int instrument_count() { return instrument_count_; }
    int sample_count() { return sample_count_; }
    std::vector<std::string> instruments() { return instruments_; }
    std::vector<std::string> samples() { return samples_; }
    std::string comment() { return comment_; }

  private:
    std::string copystr(const char *);

    static std::size_t stream_read(void *, void *, std::size_t);
    static int stream_seek(void *, std::int64_t, int);
    static std::int64_t stream_tell(void *);
    static VFSFile *VFS(void *instance) { return reinterpret_cast<VFSFile *>(instance); }

    openmpt_stream_callbacks callbacks = { stream_read, stream_seek, stream_tell };

    static const int interp_none = 1;
    static const int interp_linear = 2;
    static const int interp_cubic = 4;
    static const int interp_windowed = 8;

    openmpt_module *mod;
    int duration_;
    std::string title_;
    std::string format_;
    int pattern_count_;
    int channel_count_;
    int instrument_count_;
    int sample_count_;
    std::vector<std::string> instruments_;
    std::vector<std::string> samples_;
    std::string comment_;
};

#endif
