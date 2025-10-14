#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int main(int argc, char* argv[]){
	FILE *fp, fp2;
	int c;
	bool numberingFlag = 0;
	int i = 1;
	
	if(strcmp(argv[1], "-n") == 0){
                        i++;
                        numberingFlag = 1;
                }

	while(argv[i] != NULL){
		fp = fopen(argv[i], "r");
		i++;
		c = getc(fp);

		int lineNum = 1;
		bool atLineStart = true;
		if(numberingFlag == 1){
        		while(c != EOF){
				if(atLineStart){
					printf("\n");
					printf("%d ", lineNum++);
					atLineStart = false;
					if(ftell(fp) == 1) putc(c, stdout);
					c = getc(fp);
					continue;
				}
                		putc(c, stdout);
                		c = getc(fp);
				if( c == '\n') atLineStart = true;
        		}
			printf("\b\b\b\b\b\b");
		}

		while(c != EOF && numberingFlag == 0){
			putc(c, stdout);
			c = getc(fp);
		}
        	fclose(fp);
	}
	return 0;
}
