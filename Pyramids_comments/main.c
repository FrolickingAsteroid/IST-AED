#include "projectHeader.h"

/**
 * @brief main
 */
int main(int argc, char *argv[])
{
    char extention[] = ".in", *dot = strrchr(argv[1], '.');

    if (dot == NULL)
        exit(EXIT_FAILURE);

    if (strcmp(dot, extention) != 0)
        exit(EXIT_FAILURE);

    file_reader(argv[1]);

    exit(0);
}
