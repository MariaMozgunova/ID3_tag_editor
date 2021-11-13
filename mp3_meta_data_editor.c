#include "parse_tag.h"
#include "print_tag.h"
#include "edit_frame.h"
#include "write_tag.h"

void parse_args(int count, char** args, char file_path[], char cmd[], char name[], char value[]) {
    for (int i = 1; i < count; ++i) {
        if (strcmp(args[i], "--show") == 0) {
            strncpy(cmd, args[i] + 2, 5);
        } else if (strncmp(args[i],"--filepath", 10) == 0) {
            strncpy(file_path, args[i] + 11, strlen(args[i]) - 10);
        } else if (strncmp(args[i], "--get", 5) == 0 | strncmp(args[i], "--set", 5) == 0) {
            strncpy(cmd, args[i] + 2, 3);
            cmd[3] = '\0';
            strncpy(name, args[i] + 6, strlen(args[i]) - 5);
        } else if (strncmp(args[i], "--value", 7) == 0) {
            strcpy(value, args[i] + 8);
        } 
    }
}

int main(int argc, char** argv) {
    char file_path[20];
    char cmd[5];
    char name[5];
    char value[100];

    parse_args(argc, argv, file_path, cmd, name, value);
    ID3_tag tag;
    parse_tag(&tag, file_path);

    if (strcmp(cmd, "show") == 0) {
        print_tag(&tag);
    } else if (strcmp(cmd, "get") == 0) {
        print_frame(search_frame(&tag, name));
    } else if (strcmp(cmd, "set") == 0) {
        edit_frame(&tag, name, value);
        update_file(&tag, file_path);
        print_tag(&tag);
    }
}