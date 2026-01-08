#include <stdlib.h>
#include <stdio.h>

#define VERSION_MAX 0
#define VERSION_MIN 1

#define BUF_SIZE 256

typedef enum {
    ERR_22 = 22,
} CurlError;

void LogError(int err) {
    const char* msg;
    switch (err) {
        case ERR_22: { msg = "HTTP page not retrieved"; } break;

        default: { msg = "Unknown error"; } break;
    }

    printf("Curl request failed\n"
           "Error code: %i\n"
           "Message: %s\n", 
           err,
           msg);
}

int main(int argc, const char** argv) {
    // TODO
    // - use my bnkstring.h instead
    // - would like to have a cache or at least track previous files I have grabbed, this is so I could just do 'bnkget stb_image.h' etc
    // - its currently way too fragile, need to implement some proper error handling
    // - add support for branches, if we do not add one then default to main/master
    // - find a way to check the branch, one approach is to use the GitHub API and then check the branch. Another is to send a request to master and if its an error try main.
    // - be able to create custom "bundles" or something like that where you can basically grab multiple files, maybe something like 'bnkget {bundle}'
    // - need a way to sort out versioning

    printf("bnkget v%i.%i\n", VERSION_MAX, VERSION_MIN);

    if (argc != 4) {
        printf("Arguments must be provided in this format:\n"
               "'bnkget {author/repo} {file} {branch}'\n");

        return -1;
    }

    char buf[BUF_SIZE] = {0};

    const char* url = "https://raw.githubusercontent.com";
    int len = snprintf(buf, BUF_SIZE, "curl -s -f -L -o %s %s/%s/%s/%s", argv[2], url, argv[1], argv[3], argv[2]);

    int err = system(buf);
    printf("%i\n", err);
    if (err != 0) {
        LogError(err);
        return -1;
    }
}
