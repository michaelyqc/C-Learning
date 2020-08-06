/*
 * brief : test multi process operate same file
 * sprintf(stdin,)
 * sprintf(stdout,)
 * sprintf(stderr,)
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// printf("File : %s Func : %s Line : %d errno [%d] error msg [%s]. \n", 
//          __FILE__, 
//          __FUNCTION__,
//          __LINE__,
//          errno, 
//          strerror(errno)
//       );

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage : ./multi_process_operate_same_file r/r+/a/a+/w/w+ \n");
        return 0;
    } else {
        // DO NOTHING
    }

    FILE* pfile = NULL;
    
    // MAX FILE NAME LENGTH
    const int MAX_FILE_NAME_LEN = 256;

    // TEMP TEST FILE
    // char filename[MAX_FILE_NAME_LEN] = { "/c/Users/Administrator/Desktop/tmp.test.file" };
    char filename[MAX_FILE_NAME_LEN] = { "tmp.test.file" };

    pfile = fopen(filename, argv[1]);

    // IF ERROR
    if (pfile == NULL) {
        fprintf(stderr, "open file %s failed. errno = %d, strerror = %s. \n", 
                filename, 
                errno, 
                strerror(errno)
               );
        return 0;
    }

    // PRINT FILE PTYTHICAL MEMORY ADRESS
    printf("pfile = %p. \n", pfile);

    if (strcmp(argv[1], "w+") == 0) {
        fprintf(pfile, "i want to know, when first process open tmp.test.file and write this line, \
                after, second process open same file, the return value of ftell function call \
                in two process is same or not.\n"
               );

        fflush(pfile);
        
        // SLEEP 60 SECONDS
        sleep(60);
    } else {
        // DO NOTHING
    }

    printf("the ftell : %ld. \n", ftell(pfile) );

    fclose(pfile);

    return 0;
}
