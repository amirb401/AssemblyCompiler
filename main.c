#include "fileprocess.h"

int main(int argc, char *argv[])
{

	/* validate amount of files */
	if(argc < 2) {
		printf("no file chosen...\n");
		exit(0);
	}

	/*loop through the files*/
	while(--argc) {
		process_file(argv[argc]);
	}

	return 0;
}
