/*
 *
 * Copyright 2015, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef GRPC_INTERNAL_CORE_SUPPORT_STRING_H
#define GRPC_INTERNAL_CORE_SUPPORT_STRING_H

#include <stddef.h>

#include <grpc/support/port_platform.h>
#include <grpc/support/slice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* String utility functions */

/* Flags for gpr_dump function. */
#define GPR_DUMP_HEX   0x00000001
#define GPR_DUMP_ASCII 0x00000002

/* Converts array buf, of length len, into a C string  according to the flags.
   Result should be freed with gpr_free() */
char *gpr_dump(const char *buf, size_t len, gpr_uint32 flags);

/* Calls gpr_dump on a slice. */
char *gpr_dump_slice(gpr_slice slice, gpr_uint32 flags);

/* Parses an array of bytes into an integer (base 10). Returns 1 on success,
   0 on failure. */
int gpr_parse_bytes_to_uint32(const char *data, size_t length,
                              gpr_uint32 *result);

/* Minimum buffer size for calling ltoa */
#define GPR_LTOA_MIN_BUFSIZE (3 * sizeof(long))

/* Convert a long to a string in base 10; returns the length of the
   output string (or 0 on failure).
   output must be at least GPR_LTOA_MIN_BUFSIZE bytes long. */
int gpr_ltoa(long value, char *output);

/* Reverse a run of bytes */
void gpr_reverse_bytes(char *str, int len);

/* Join a set of strings, returning the resulting string.
   Total combined length (excluding null terminator) is returned in total_length
   if it is non-null. */
char *gpr_strjoin(const char **strs, size_t nstrs, size_t *total_length);

/* A vector of strings... for building up a final string one piece at a time */
typedef struct {
  char **strs;
  size_t count;
  size_t capacity;
} gpr_strvec;

/* Initialize/destroy */
void gpr_strvec_init(gpr_strvec *strs);
void gpr_strvec_destroy(gpr_strvec *strs);
/* Add a string to a strvec, takes ownership of the string */
void gpr_strvec_add(gpr_strvec *strs, char *add);
/* Return a joined string with all added substrings, optionally setting
   total_length as per gpr_strjoin */
char *gpr_strvec_flatten(gpr_strvec *strs, size_t *total_length);

#ifdef __cplusplus
}
#endif

#endif  /* GRPC_INTERNAL_CORE_SUPPORT_STRING_H */
