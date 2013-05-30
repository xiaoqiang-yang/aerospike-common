/******************************************************************************
 * Copyright 2008-2013 by Aerospike.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/

#pragma once

#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include <citrusleaf/cf_atomic.h>
#include <citrusleaf/cf_shash.h>

/******************************************************************************
 * TYPES
 *****************************************************************************/

enum as_val_t {
    AS_UNKNOWN      = 0,
    AS_NIL          = 1,
    AS_BOOLEAN      = 2,
    AS_INTEGER      = 3,
    AS_STRING       = 4,
    AS_LIST         = 5,
    AS_MAP          = 6,
    AS_REC          = 7,
    AS_PAIR         = 8,
    AS_BYTES        = 9
} __attribute__((packed));

typedef enum as_val_t as_val_t;

struct as_val_s {
    enum as_val_t 	type;
    bool            is_malloc;
    cf_atomic32     count;
};

typedef struct as_val_s as_val;

/******************************************************************************
 * MACROS
 *****************************************************************************/
 
#define as_val_type(__v)     (((as_val *)__v)->type)

#define as_val_reserve(__v) ( as_val_val_reserve((as_val *)__v) )

#define as_val_destroy(__v) ( as_val_val_destroy((as_val *)__v) )

#define as_val_hashcode(__v) ( as_val_val_hashcode((as_val *)__v) )

#define as_val_tostring(__v) ( as_val_val_tostring((as_val *)__v) )

/******************************************************************************
 * FUNCTIONS
 *****************************************************************************/

as_val *    as_val_val_reserve(as_val *);
as_val *    as_val_val_destroy(as_val *);
uint32_t    as_val_val_hashcode(const as_val *);
char *      as_val_val_tostring(const as_val *);

/******************************************************************************
 * INLINE FUNCTIONS
 *****************************************************************************/

inline void as_val_init(as_val * v, as_val_t type, bool is_malloc) {
    v->type = type; 
    v->is_malloc = is_malloc; 
    v->count = 1;
}
