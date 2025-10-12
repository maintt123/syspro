#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_COLS  100

char savedText[MAX_LINES][MAX_COLS];

// 줄 출력 함수
void print_line(int line_num, int total_lines) {
    if (line_num >= 0 && line_num < total_lines) {
        printf("%d: %s\n", line_num + 1, savedText[line_num]);
    } else {
        printf(" 잘못된 줄 번호: %d\n", line_num + 1);
    }
}

int main(void) {
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("test.txt");
        return 1;
    } else printf("File read success\n");

    char buf;
    int row = 0, col = 0;

    // 파일에서 문자 단위로 읽어 줄 저장
    while (read(fd, &buf, 1) == 1) {
        if (buf == '\n') {
            savedText[row][col] = '\0';
            row++;
            col = 0;
            if (row >= MAX_LINES) break;  // 줄 수 초과 방지
        } else {
            if (col < MAX_COLS - 1) {
                savedText[row][col++] = buf;
            }
        }
    }
    printf("Total Line : %d\n", row - 1);

    // 마지막 줄 처리 (파일 끝에 \n이 없는 경우)
    if (col > 0) {
        savedText[row][col] = '\0';
        row++;
    }

    int total_lines = row;
    close(fd);

    if (total_lines == 0) {
        printf("파일에 내용이 없습니다.\n");
        return 0;
    }

    // 사용자 입력 받기
    char input[100];
    printf("You can choose 1 ~ 4 Line\nPls 'Enter' the line to select : ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // 개행 제거

    // 모든 줄 출력
    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < total_lines; i++) {
            print_line(i, total_lines);
        }
    }
    // 범위 입력: n-m
    else if (strchr(input, '-') != NULL) {
        int start, end;
        if (sscanf(input, "%d-%d", &start, &end) == 2) {
            for (int i = start - 1; i <= end - 1 && i < total_lines; i++) {
                print_line(i, total_lines);
            }
        } else {
            printf("잘못된 범위 입력입니다.\n");
        }
    }
    // 리스트 입력: n,m,...
    else if (strchr(input, ',') != NULL) {
        char *token = strtok(input, ",");
        while (token != NULL) {
            int idx = atoi(token) - 1;
            print_line(idx, total_lines);
            token = strtok(NULL, ",");
        }
    }
    // 단일 줄 번호
    else {
        int idx = atoi(input) - 1;
        print_line(idx, total_lines);
    }

    return 0;
}

