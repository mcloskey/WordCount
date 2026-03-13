#include <stdio.h>
#include <string.h>

int is_delimiter(char ch) {
    return (ch == ' ' || ch == '\t' || ch == '\n' || ch == ',');
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int ch;
    long count = 0;
    int in_word = 0;

    if (argc != 3) {
        printf("用法: %s [-c|-w] [input_file_name]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-w") != 0) {
        printf("参数错误: 仅支持 -c 或 -w\n");
        return 1;
    }

    fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("无法打开文件: %s\n", argv[2]);
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0) {
        while ((ch = fgetc(fp)) != EOF) {
            count++;
        }
        printf("字符数: %ld\n", count);
    } else {
        while ((ch = fgetc(fp)) != EOF) {
            if (is_delimiter((char)ch)) {
                in_word = 0;
            } else {
                if (!in_word) {
                    count++;
                    in_word = 1;
                }
            }
        }
        printf("单词数: %ld\n", count);
    }

    fclose(fp);
    return 0;
}
