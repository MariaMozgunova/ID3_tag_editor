#include "structures.h"
#pragma once

void print_frame(ID3_frame* frame) {
    if (frame->header.frame_id[0] == 'T' || strcmp(frame->header.frame_id, "APIC") == 0) {
        printf("%s %d ", frame->header.frame_id, frame->header.size);
        printf(frame->body);
        printf("\n");
    } else {
        fprintf(stderr, "No implementation for %s frame\nAborting...", frame->header.frame_id);
        exit(EXIT_FAILURE);
    }
}

void print_tag(ID3_tag* tag) {
    printf("===== %sv2.%d.%d =====\n", tag->header.identifier, tag->header.version_major, tag->header.version_minor);
    ID3_frame* frame = tag->frames;

    while (frame) {
        print_frame(frame);
        frame = frame->next;
    }
}