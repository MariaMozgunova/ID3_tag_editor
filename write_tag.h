#include "structures.h"
#pragma once

void fwrite_number(int number, int offset, int n, FILE* mp3) {
    uint8_t str_num[n];

    for (int i = n - 1; i >= 0; --i) {
        str_num[i] = number & ((1 << offset) - 1);
        number >>= offset;
    }

    for (int i = 0; i < n; ++i) {
        fprintf(mp3, "%c", str_num[i]);
    }
}

void fwrite_tag(ID3_tag* tag, FILE* mp3) {
    // print tag header
    fprintf(mp3, "%s%c", tag->header.identifier, tag->header.version_major);
    fprintf(mp3, "%c%c", tag->header.version_minor, tag->header.flags);
    fwrite_number(tag->header.size, 7, 4, mp3);

    // print frames
    ID3_frame* frame = tag->frames;

    while (frame) {
        fprintf(mp3, "%s", frame->header.frame_id);
        fwrite_number(frame->header.size, 8, 4, mp3);
        fwrite_number(frame->header.flags, 8, 2, mp3);
        fprintf(mp3, "%c", frame->encoding);
        fwrite(frame->body, 1, frame->header.size - 1, mp3);
        frame = frame->next;
    }
}

void update_file(ID3_tag* tag, char file_name[]) {
    char tmp_name[] = "some_name.mp3";
    FILE* mp3_original = fopen(file_name, "rb");
    FILE* mp3 = fopen(tmp_name, "wb");

    if (tag->header.padding_size < 2048) {
        tag->header.size += 2048 - tag->header.padding_size;
        tag->header.padding_size = 2048;
    }

    fwrite_tag(tag, mp3);

    for (int i = 0; i < tag->header.padding_size; ++i) {
        fprintf(mp3, "%c", 0);
    }

    fseek(mp3_original, 0L, SEEK_END);  // get file size
    long sz = ftell(mp3_original);  // for the binary files ftell returns # of bytes from the beginning of the file
    fseek(mp3_original, tag->header.old_size + 10, SEEK_SET);

    for (long i = 0; i < sz - tag->header.old_size - 10; ++i) {
        fprintf(mp3, "%c", (int)fgetc(mp3_original));
    }
    
    fclose(mp3_original);
    fclose(mp3);
    remove(file_name);
    rename(tmp_name, file_name);
}