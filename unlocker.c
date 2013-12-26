/*
 * Filename: unlocker.c
 * Author: Fernando Barillas (@fbis251)
 * Description: Searches for the carrier unlock code for the Samsung Galaxy S 4G
                in a fast and easy way. The location of the unlock code is fixed
                at 0x146E in the nv_data.bin file. :)
 * Target Phone Models:
 *     Samsung SGH-T959V
 *     Samsung SGH-T959W
 * Date: Dec 26, 2013
 * Compilation Instructions:
 *     Compile using the makefile:
 *     make
 *
 *     or
 *
 *     Compile with the codesourcery cross compiler:
 *     arm-none-linux-gnueabi-gcc --static -o unlock_code unlocker.c
 */
#include "unlocker.h"

static const int DEBUG = FALSE;
static char ** programPath;
static int lockStatus = 1; // 0 for unlocked, 1 for locked

void printUsage() {
    (void) fprintf( stderr, "Usage: %s <filename>\n", *programPath );
    (void) fprintf( stderr, "Arguments:\n" );
    (void) fprintf( stderr, "\t<filename>: (optional)\n" );
    (void) fprintf( stderr, "\t\tLooks for %s\n", NV_DATA_PATH );
    (void) fprintf( stderr, "\t\tif <filename> parameter is not specified\n" );
}

void readUnlockCode( const char * filename ) {
    FILE *filePtr;                // Pointer to the file we're reading from
    char unlockCode[CODE_LENGTH]; // Will hold the unlock code string
    int  isCodeCorrect = TRUE;    // Was the unlock code valid?
    int  freadResult;             // Result from fread(), used for error checks

    // Open the file for reading
    if( ( filePtr = fopen( filename, "rb" ) ) == NULL ) {
        // Could not open the file, show an error to the user
        perror( filename );
        printUsage();
        exit( EXIT_FAILURE );
    }

    // Seek to the magic location that contains the unlock code
    fseek( filePtr, CODE_LOCATION , SEEK_SET );
    freadResult = fread( unlockCode, 1, CODE_LENGTH, filePtr );
    fclose( filePtr );

    // Make sure we read everything correctly
    if( freadResult != CODE_LENGTH ) {
        fprintf( stderr, "Error while reading the file: %s\n", filename );
        exit( EXIT_FAILURE );
    }

    // Verify that the bytes we read are indeed ASCII 0-9 since that indicates
    // we read a good unlock code
    int i;
    for( i = 0; i < CODE_LENGTH; i++ ) {
        if( DEBUG == TRUE ) {
            printf( "0x%02x: %c\n", unlockCode[i], unlockCode[i] );
        }

        // We only want to analyze the ASCII code, continue until we reach the
        // offset and have valid ASCII digits
        if( i < CODE_OFFSET ) {
            continue;
        }

        if( unlockCode[i] < ASCII_0 || unlockCode[i] > ASCII_9 ) {
            // The character wasn't within the proper range
            isCodeCorrect = FALSE;
            break;
        }
    }

    // The lock status is contained in the first byte
    lockStatus = unlockCode[0];

    // Show either the code or an error message to the user
    if( isCodeCorrect == TRUE ) {
        // Print the unlock code to screen since it's correct
        printf( "Unlock Code: " );
        for( i = CODE_OFFSET; i < CODE_LENGTH; i++ ) {
            printf( "%c", unlockCode[i] );
        }
        printf( "\nLock Status: " );
        if( lockStatus == UNLOCKED ) {
            // Unlocked
            printf( "Unlocked\n" );
        } else if ( lockStatus == LOCKED ) {
            // Locked
            printf( "Locked\n" );
        } else {
            // Unknown status, most likely not a valid nv_data.bin file
            printf( "Unknown\n" );
        }

    } else {
        printf("There was an error reading your unlock code\n" );
        exit( EXIT_FAILURE );
    }
}

int main( int argc, const char* argv[] ) {
    programPath = (void *) argv; // Used to print program path in usage message

    // Check to see if the user specified a different filename than the default
    if( argc != 2 ) {
        // No custom filename specified, look for nv_data.bin in default path
        readUnlockCode( NV_DATA_PATH );
    } else {
        // Use custom filename to search for unlock code
        readUnlockCode( argv[1] );
    }

    return 0;
}
