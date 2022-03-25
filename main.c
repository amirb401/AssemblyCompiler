#include "fileprocess.h"

/* int main(int argc, char *argv[]) anat */
int main()
{

	const char* fname = "/home/user/Desktop/new/tryyy/ps.as"; /* anat to remove */
	FILE* fp = fopen(fname, "r"); /* anat to remove */

	/* validate amount of files
	if(argc < 2) {
		printf("no file chosen...\n");
		exit(0);
	}*/

	/*loop through the files
	while(--argc) {
		process_file(argv[argc]);
	}*/

	while (fp)
	{
		process_file(fname);
	}
	return 0;
}
