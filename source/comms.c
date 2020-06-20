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

#include <libdlp/comms.h>

void libdlp_comms_init(
    struct libdlp_comms *comms,
    libdlp_comms_read_t fn_read,
    libdlp_comms_write_t fn_write,
    void *context)
{
    comms->context = context;
    comms->fn_read = fn_read;
    comms->fn_write = fn_write;
}

int libdlp_comms_read(struct libdlp_comms *comms, uint8_t *ptr, size_t length)
{
    return comms->fn_read(comms->context, ptr, length);
}

int libdlp_comms_write(struct libdlp_comms *comms, const uint8_t *ptr, size_t length)
{
    return comms->fn_write(comms->context, ptr, length);
}
