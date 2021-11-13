#include "structures.h"
#pragma once  // to include file only once

int parse_number(FILE* mp3, int offset, int n) {
    int res = 0;

    for (int i = 0; i < n; ++i) {
        res = (res << offset) + fgetc(mp3);
    }

    return res;
}

void parse_tag_header(ID3_tag* tag, FILE* mp3) {
    fread(tag->header.identifier, 1, 3, mp3);
    tag->header.identifier[3] = '\0';
    tag->header.version_major = fgetc(mp3);
    tag->header.version_minor = fgetc(mp3);
    tag->header.flags = fgetc(mp3);
    tag->header.size = parse_number(mp3, 7, 4);  // in every byte 7th bit is reserved
    tag->header.old_size = tag->header.size;
}

void parse_frame_header(ID3_frame* frame, FILE* mp3) {
    fread(frame->header.frame_id, 1, 4, mp3);    
    frame->header.frame_id[4] = '\0';
    frame->header.size = parse_number(mp3, 8, 4);
    frame->header.flags = parse_number(mp3, 8, 2);
}

void parse_text_frame(ID3_frame* frame, FILE* mp3, ID3_tag* tag) {
    frame->encoding = fgetc(mp3);

    if (frame->encoding) {  // Unicode
        frame->encoding = 0;
        frame->header.size = (frame->header.size - 1) / 2;
        wchar_t wc[frame->header.size];
        frame->body = (char*)calloc(frame->header.size, sizeof(char));
        fseek(mp3, 2, SEEK_CUR);  // skip Unicode BOM - byte order mark | FE FF - Big endian, FF FE - Little endian

        for (int i = 0; i < frame->header.size - 1; ++i) {
            wc[i] = fgetwc(mp3);
        }

        wcstombs(frame->body, wc, frame->header.size - 1);
        tag->header.size -= 2 + frame->header.size;
        tag->header.padding_size -= 2 + frame->header.size;
    } else {
        frame->body = (char*)calloc(frame->header.size, sizeof(char));
        fread(frame->body, 1, frame->header.size - 1, mp3);
    }
}

void new_frame(ID3_frame* frame, FILE* mp3, ID3_tag* tag) {
    parse_frame_header(frame, mp3);

    if (frame->header.frame_id[0] == 'T') {  // all text frames start with 'T' 
        parse_text_frame(frame, mp3, tag);
    } else if (strcmp(frame->header.frame_id, "APIC") == 0) {  // picture frame
        frame->encoding = fgetc(mp3);
        frame->body = (char*)calloc(frame->header.size, sizeof(char));
        fread(frame->body, 1, frame->header.size - 1, mp3);
    } else {
        fprintf(stderr, "No implementation for %s frame\nAborting...", frame->header.frame_id);
        exit(EXIT_FAILURE);
    }
}

void parse_frames(ID3_tag* tag, FILE* mp3) {
    char c = '\0';
    tag->frames = (ID3_frame*)calloc(1, sizeof(ID3_frame));  // we are guaranteed that there is at least one frame in ID3v2 tag
    new_frame(tag->frames, mp3, tag);
    ID3_frame* frame_list = tag->frames;
    tag->header.padding_size = tag->header.size - 10 - frame_list->header.size;

    while (tag->header.padding_size && (c = fgetc(mp3)) != '\0') {  // until hit padding
        fseek(mp3, -1, SEEK_CUR);
        frame_list->next = (ID3_frame*)calloc(1, sizeof(ID3_frame));
        frame_list = frame_list->next;
        new_frame(frame_list, mp3, tag);
        tag->header.padding_size -= 10 + frame_list->header.size;
    }
    
    frame_list->next = 0;
}

void parse_tag(ID3_tag* tag, char file_name[]) {
    FILE* mp3 = fopen(file_name, "rb");
    parse_tag_header(tag, mp3);
    parse_frames(tag, mp3);
    fclose(mp3);
}