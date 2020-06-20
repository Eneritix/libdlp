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

#ifndef __LIBDLP_READER_H__
#define __LIBDLP_READER_H__

#include <sys/cdefs.h>
#include <libdlp/libdlp.h>

__BEGIN_DECLS

typedef void (*libdlp_reader_callback_t)(void *context, const uint8_t *frame_buffer, size_t frame_length);

struct libdlp_reader
{
    struct libdlp_comms *comms;
    uint8_t *read_buffer;
    size_t read_buffer_size;
    libdlp_reader_callback_t callback;
    void *callback_context;

    struct libdlp_frame_header frame_header;
    int state;
    uint8_t sync_byte;
    uint8_t *read_ptr;
    size_t bytes_remaining;
};

/**
 * @brief initialzie a libdlp reader
 * libdlp_reader_init initializes a reader object
 * with the supplied comms object, read buffer, and
 * frame callback.
 */
void libdlp_reader_init(
    struct libdlp_reader *reader,
    struct libdlp_comms *comms,
    uint8_t *read_buffer,
    size_t read_buffer_size,
    libdlp_reader_callback_t callback,
    void *callback_context);

/**
 * @brief executes a libdlp reader
 * libdlp_reader_process reads from the comms object and extracts
 * valid frames from the incoming data. Frames are passed back
 * to the caller via the callback provided to libdlp_reader_init
 * @returns 0 on success, or -1 upon failure
 */
int libdlp_reader_process(struct libdlp_reader *reader);

__END_DECLS

#endif
