#include <stdio.h>

int main(int argc, char** argv) {
	
	if(argc > 1) {
		printf("ERROR: invalid number of arguments\nThis tool not accept arguments");
		return 1;
	}
	
	return 0;
}
