#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 4096

int cleanup(int infd, int outfd, int ret_code, const char* outfile) {
    if (infd >= 0) {
        close(infd);
    }
    if (outfd >= 0) {
        close(outfd);
    }
    if (ret_code != 0 && outfd >= 0) {
        unlink(outfile);
    }

    return ret_code;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return 1;
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];

    int infd = -1, outfd = -1;
    struct stat st;
    mode_t mode;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    infd = open(infile, O_RDONLY);
    if (infd < 0) {
        perror("Error opening input file");
        return cleanup(infd, outfd, 1, outfile);
    }

    if (fstat(infd, &st) < 0) {
        perror("Error getting input file permissions");
        return cleanup(infd, outfd, 2, outfile);
    }
    mode = st.st_mode & 0777;

    outfd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (outfd < 0) {
        perror("Error opening/creating output file");
        return cleanup(infd, outfd, 3, outfile);
    }

    while ((bytes_read = read(infd, buffer, BUFFER_SIZE)) > 0) {
        char *out_ptr = buffer;
        ssize_t remaining = bytes_read;
        while (remaining > 0) {
            bytes_written = write(outfd, out_ptr, remaining);
            if (bytes_written <= 0) {
                perror("Error writing to output file");
                return cleanup(infd, outfd, 4, outfile);
            }
            remaining -= bytes_written;
            out_ptr += bytes_written;
        }
    }

    if (bytes_read < 0) {
        perror("Error reading from input file");
        return cleanup(infd, outfd, 5, outfile);
    }

    if (close(infd) < 0) {
        perror("Error closing input file");
        return cleanup(infd, outfd, 6, outfile);
    }
    infd = -1;

    if (close(outfd) < 0) {
        return cleanup(infd, outfd, 7, outfile);
    }
    outfd = -1;

    if (unlink(infile) < 0) {
        perror("Error deleting input file");
        return cleanup(infd, outfd, 8, outfile);
    }

    return cleanup(infd, outfd, 0, outfile);
}
