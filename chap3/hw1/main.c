#include <stdio.h>
#include "copy.h"

char line[MAXLINE];
char stringArr[5][MAXLINE];

main(){
  int max;
  max = 0;
  int i = 0;

  while(i < 5) {
	  gets(stringArr[i]);
	i++;
  }
  
  for(int j = 0; j < 5; j++){
	  	for(int k = j; k < 5; k++){
	  		if(strlen(stringArr[j]) < strlen(stringArr[k])){
				char tmp[MAXLINE];
				copy(stringArr[j], tmp);
				copy(stringArr[k], stringArr[j]);
				copy(tmp, stringArr[k]);
	  	}
	  }
  }

  for(int j = 0; j < 5; j++){
  	printf("%s\n", stringArr[j]);
  }

  return 0;
}


