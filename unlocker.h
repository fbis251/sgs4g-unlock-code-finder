#include <stdio.h>
#include <stdlib.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NV_DATA_PATH
#define NV_DATA_PATH "/efs/root/afs/settings/nv_data.bin"
#endif

#ifndef CODE_LOCATION
#define CODE_LOCATION 0x1469 // Magic byte location for lock status + ASCII code
#endif

#ifndef CODE_LENGTH
#define CODE_LENGTH 13 // How many bytes are the lock status + ASCII code?
#endif

#ifndef CODE_OFFSET
#define CODE_OFFSET 5 // ASCII unlock code compared to CODE_LOCATION
#endif

#ifndef ASCII_0
#define ASCII_0 '0'
#endif

#ifndef ASCII_9
#define ASCII_9 '9'
#endif

#ifndef UNLOCKED
#define UNLOCKED 0
#endif

#ifndef LOCKED
#define LOCKED 1
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

/* Function declarations */
void printUsage();
void readUnlockCode( const char * );
