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

#include <libdlp/reader.h>

enum libdlp_reader_state
{
    READER_STATE_SYNC,
    READER_STATE_HEADER,
    READER_STATE_DATA
};

void libdlp_reader_init(
    struct libdlp_reader *reader,
    struct libdlp_comms *comms,
    uint8_t *read_buffer,
    size_t read_buffer_size,
    libdlp_reader_callback_t callback,
    void *callback_context)
{
    reader->comms = comms;
    reader->read_buffer = read_buffer;
    reader->read_buffer_size =read_buffer_size;
    reader->callback = callback;
    reader->callback_context = callback_context;

    reader->state = READER_STATE_SYNC;
    reader->frame_header.sync = 0;
    reader->read_ptr = &reader->sync_byte;
    reader->bytes_remaining = 1;
}

int libdlp_reader_process(struct libdlp_reader *reader)
{
    int bytes_read = libdlp_comms_read(reader->comms, reader->read_ptr, reader->bytes_remaining);
    if (bytes_read <= 0) {
        return bytes_read;
    }

    switch (reader->state) {

    case READER_STATE_SYNC: {
        reader->frame_header.sync >>= 8;
        reader->frame_header.sync |= reader->sync_byte << 8;
        if (reader->frame_header.sync == LIBDLP_SYNC_SEQUENCE) {
            reader->state = READER_STATE_HEADER;
            reader->read_ptr = (uint8_t *)&reader->frame_header.crc;
            reader->bytes_remaining = 4;
        }
    } break;

    case READER_STATE_HEADER: {
        reader->read_ptr += bytes_read;
        reader->bytes_remaining -= bytes_read;
        if (reader->bytes_remaining == 0) {
            if ((reader->frame_header.length > 0) && (reader->frame_header.length < reader->read_buffer_size)) {
                reader->state = READER_STATE_DATA;
                reader->read_ptr = reader->read_buffer;
                reader->bytes_remaining = reader->frame_header.length;
            } else {
                reader->state = READER_STATE_SYNC;
                reader->frame_header.sync = 0;
                reader->read_ptr = &reader->sync_byte;
                reader->bytes_remaining = 1;
            }
        }
    } break;

    case READER_STATE_DATA: {
        reader->read_ptr += bytes_read;
        reader->bytes_remaining -= bytes_read;
        if (reader->bytes_remaining == 0) {
            if (libdlp_crc(reader->read_buffer, reader->frame_header.length) == reader->frame_header.crc) {
                reader->callback(reader->callback_context, reader->read_buffer, reader->frame_header.length);
            }

            reader->state = READER_STATE_SYNC;
            reader->frame_header.sync = 0;
            reader->read_ptr = &reader->sync_byte;
            reader->bytes_remaining = 1;
        }

    } break;
    }
}
