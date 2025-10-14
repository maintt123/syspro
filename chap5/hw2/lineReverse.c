#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_COLS 100

char savedText[MAX_LINES][MAX_COLS];

int main() {
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("파일 열기 실패");
        return 1;
    }

    char buf;
    int row = 0, col = 0;

    // 파일을 한 글자씩 읽어서 줄 단위로 저장
    while (read(fd, &buf, 1) == 1) {
        if (buf == '\n') {
            savedText[row][col] = '\0';
            row++;
            col = 0;
            if (row >= MAX_LINES) break;
        } else {
            if (col < MAX_COLS - 1)
                savedText[row][col++] = buf;
        }
    }

    // 마지막 줄에 개행이 없을 경우 처리
    if (col > 0) {
        savedText[row][col] = '\0';
        row++;
    }

    int total_lines = row;
    close(fd);

    // 줄을 역순으로 출력
    for (int i = total_lines - 1; i >= 0; i--) {
        printf("%d: %s\n", i + 1, savedText[i]);
    }

    return 0;
}

