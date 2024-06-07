#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[]) {
	if(argc != 2) {
		printf("[ERROR] Invalid ARGS : \n");
		return 1;
	}
	for(int ci = 0;ci < strlen(argv[1]);ci++) {
		if(!((argv[1][ci] >= '0' && argv[1][ci] <= '9')||(argv[1][ci] == '-'))) {
			printf("[ERROR] Invalid ARGS : %s\n",argv[1]);
			return 1;
		}
	}
	int iNum = atoi(argv[1]);
	iNum=(-iNum);
	printf("%x\n",iNum);
	return 0;
}
