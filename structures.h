#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <stddef.h>
#include <wchar.h>  // https://www.cplusplus.com/reference/cwchar/
#include <locale.h>
#pragma once

typedef struct ID3_tag_header_s {
    char identifier[4];
    uint8_t version_major;
    uint8_t version_minor;
    uint8_t flags;
    int size;
    int old_size;
    int padding_size;
} ID3_tag_header;

typedef struct ID3_frame_header_s {
    char frame_id[5];
    int size;
    uint16_t flags;
} ID3_frame_header;

typedef struct ID3_frame_s {
    ID3_frame_header header;
    uint8_t encoding;
    char* body;
    struct ID3_frame_s* next;
} ID3_frame;

typedef struct ID3_tag_s {
    ID3_tag_header header;
    ID3_frame* frames;  // frames are stored in a linked list
} ID3_tag;