#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	char c;
	FILE* fp1, *fp2;
	if(argc != 4){
		fprintf(stderr, "How to use:%s flag[0, 1, 2] File1 File2\n", argv[0]);
		return 1;
	}
	
	fp1 = fopen(argv[2], "r");
	if(fp1 == NULL){
		fprintf(stderr, "File %s Open Error\n", argv[1]);
		return 2;
	}

	fp2 = fopen(argv[3], "w");

	if(!strcmp(argv[1],"0")){
		while((c = fgetc(fp1)) != EOF)
			fputc(c, fp2);
	}
	else if(!strcmp(argv[1], "1")){
		while((c = fgetc(fp1)) != EOF){
			if((c >= 'A') && (c <= 'Z')){
				c = c + 32;
			}
			fputc(c, fp2);
		}
	}
	else if(!strcmp(argv[1], "2")){
		while((c = fgetc(fp1)) != EOF){
			if((c <= 'z') && (c >= 'a')){
				c = c - 32;
			}
			fputc(c, fp2);
		}
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}
