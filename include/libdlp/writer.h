/*
    Copyright (c) 2020 Eneritix (Pty) Ltd

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef __LIBDLP_WRITER_H__
#define __LIBDLP_WRITER_H__

#include <sys/cdefs.h>
#include <libdlp/libdlp.h>

__BEGIN_DECLS

struct libdlp_writer
{
    struct libdlp_comms *comms;
    struct libdlp_frame_header frame_header;
};

/**
 * @brief initialize a libdlp writer
 * libdlp_writer_init initializes a writer object
 * with the supplied comms object
 */
void libdlp_writer_init(
    struct libdlp_writer *writer,
    struct libdlp_comms *comms);

/**
 * @brief write a frame to the libdlp writer
 * libdlp_writer_write packs and writes a frame header
 * to the supplied comms object, followed by the frame data
 * @returns 0 on success, or -1 upon failure
 */
int libdlp_writer_write(
    struct libdlp_writer *writer,
    const uint8_t *frame,
    size_t frame_length);

__END_DECLS

#endif
