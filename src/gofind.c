#include "simple_header.h"

int main(int argc, char *argv[])
{	
	
	FILE *PATHS_FILE = NULL; // closed
	FILE *TEMP_FILE = NULL; // closed
	char *PATHS_PNTR = NULL; // freed
	char *KEYWORD_PNTR = NULL; //freed
	glob_t my_gl;
	int i = 0;
	int found_counts = 0;	
	int or_flag = 0;

	check_debug(argc > 1, "Usage: Enter one keyword at least.");
	if (argc > 1){
		if (strcmp(argv[1], "-o") == 0) {
			debug("or flag set.");
			or_flag = 1;
			keyword_counts = argc - 2;
		} else keyword_counts = argc - 1;
	}

	if (or_flag){
		check_debug(argc > 2, "Usage: Enter a keyword after -o modifier.");
	}


	PATHS_PNTR = malloc(path_length * sizeof(char));
	PATHS_FILE = fopen(".paths", "r");

	if (PATHS_FILE){
		while (fgets(PATHS_PNTR, path_length, PATHS_FILE) != NULL){			
			PATHS_PNTR[strcspn(PATHS_PNTR, "\n")] = 0;
			if (glob(PATHS_PNTR, GLOB_ERR, NULL, &my_gl) == 0 && my_gl.gl_pathc > 0){
				//debug("glob() call succeeded with my_gl.gl_pathc = %ld",my_gl.gl_pathc);
				for (i = 0; i < my_gl.gl_pathc; i++){
					//debug("opening %s ...",my_gl.gl_pathv[i]);
					TEMP_FILE = fopen(my_gl.gl_pathv[i], "r");
					if (TEMP_FILE){
						KEYWORD_PNTR = malloc(log_size * sizeof(char));
						fread(KEYWORD_PNTR, log_size, 1, TEMP_FILE);
						for (int j = 1; j < argc; j++)
						{
							if (strstr(KEYWORD_PNTR, argv[j])){
								found_counts += 1;
								//debug("Found in %s", my_gl.gl_pathv[i]);
							}
						}
						if (found_counts == keyword_counts){
							debug("Found all in:%s", my_gl.gl_pathv[i]);
							found_counts = 0;
							printf("%s\n", my_gl.gl_pathv[i]);

						} else if (or_flag && found_counts > 0){
							debug("Found based on or flag:%s", my_gl.gl_pathv[i]);
							printf("%s\n", my_gl.gl_pathv[i]);

							found_counts = 0;
						}

						found_counts = 0;
						//free(KEYWORD_PNTR);
					}	
				}			
			}
		}
	}

	if (KEYWORD_PNTR) free(KEYWORD_PNTR);
	if (PATHS_PNTR) free(PATHS_PNTR);
	if (PATHS_FILE) fclose(PATHS_FILE);
	if (TEMP_FILE) fclose(TEMP_FILE);
	return 0;

error:

	if (KEYWORD_PNTR) free(KEYWORD_PNTR);
	if (PATHS_PNTR) free(PATHS_PNTR);
	if (PATHS_FILE) fclose(PATHS_FILE);
	if (TEMP_FILE) fclose(TEMP_FILE);
	return 1;	
}
