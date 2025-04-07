#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings
void strip_newline(char *string);


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hashText = md5(plaintext, strlen(plaintext));
    strip_newline(hashText);

    // Open the hash file
    FILE *file = fopen(hashFilename, "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return NULL;
    }
    char *hashLine = malloc(HASH_LEN * sizeof(char));

    // Loop through the hash file, one line at a time.
    while (fgets(hashLine, HASH_LEN, file) != NULL)
    {
        strip_newline(hashLine);
        if (strcmp(hashLine, hashText) == 0)
        {
            fclose(file);
            free(hashLine);
            return hashText;
        }
    }

    // Attempt to match the hash from the file to the
    // hash of the plaintext.

    // If there is a match, you'll return the hash.
    // If not, return NULL.

    // Before returning, do any needed cleanup:
    //   Close files?
    //   Free memory?
    free(hashText);
    free(hashLine);
    fclose(file);

    // Modify this line so it returns the hash
    // that was found, or NULL if not found.
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.
    //char *found = tryWord("hello", "hashes00.txt");
    //printf("%s %s\n", found, "hello");

    int crackedHashes = 0;
    // Open the dictionary file for reading.
    FILE *dict = fopen(argv[2], "r");  
    char *plaintext = malloc(PASS_LEN * sizeof(char));  
    while (fgets(plaintext, PASS_LEN, dict) != NULL)
    {
        strip_newline(plaintext);
        char *found = tryWord(plaintext, argv[1]);
        if (found) 
        {
            printf("%s %s\n", found, plaintext);
            crackedHashes ++;
        }
    }
    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    
    // If we got a match, display the hash and the word. For example:
    //   5d41402abc4b2a76b9719d911017c592 hello
    fclose(dict);
    // Close the dictionary file.

    // Display the number of hashes that were cracked.
    printf("Cracked %d hashes.\n", crackedHashes);
    // Free up any malloc'd memory?
    free(plaintext);
}


void strip_newline(char *string)
{
    int i = 0;
    while (string[i])
    {
        if (string[i] && string[i] == '\n')
        {
            string[i] = '\0';
            break;
        }
        i = i + 1;
    }
}