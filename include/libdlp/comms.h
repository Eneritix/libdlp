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

#ifndef __LIBDLP_COMMS_H__
#define __LIBDLP_COMMS_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

typedef int (*libdlp_comms_read_t)(void *context, uint8_t *ptr, size_t length);
typedef int (*libdlp_comms_write_t)(void *context, const uint8_t *ptr, size_t length);

struct libdlp_comms
{
    void *context;
    libdlp_comms_read_t fn_read;
    libdlp_comms_write_t fn_write;
};

/**
 * @brief initialize a libdlp comms object
 * libdlp_comms_init initializes a comms object with callback functions for
 * reading and writing. The context parameter is passed to the read and write
 * callbacks when they are called.
 */
void libdlp_comms_init(
    struct libdlp_comms *comms,
    libdlp_comms_read_t fn_read,
    libdlp_comms_write_t fn_write,
    void *context);

/**
 * @brief read from a comms object
 * libdlp_comms_read reads data from a comms object.
 * @returns the amount of bytes read, or -1 upon failure
 */
int libdlp_comms_read(struct libdlp_comms *comms, uint8_t *ptr, size_t length);

/**
 * @brief write to a comms object
 * libdlp_comms_write writes data to a comms object
 * @returns 0 on success, or -1 upon failure
 */
int libdlp_comms_write(struct libdlp_comms *comms, const uint8_t *ptr, size_t length);

__END_DECLS

#endif
