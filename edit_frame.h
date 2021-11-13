#include "structures.h"
#pragma once

ID3_frame* search_frame(ID3_tag* tag, char name[]) {
    ID3_frame* frame = tag->frames;

    while (frame && strcmp(name, frame->header.frame_id)) {
        frame = frame->next;
    }

    return frame;
}

void edit_frame(ID3_tag* tag, char name[], char value[]) {
    ID3_frame* frame = search_frame(tag, name);

    if (frame == 0) {
        fprintf(stderr, "\nNo frame with id %s found\nAborting...", name);
        exit(EXIT_FAILURE);
    }

    int size_change = frame->header.size;
    frame->header.size = strlen(value) + 1;
    size_change -= frame->header.size;
    free(frame->body);
    frame->body = value;
    tag->header.size -= size_change;
}