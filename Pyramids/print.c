#include "projectHeader.h"

/**
 * @brief Create a file name object
 * 
 * @return char* 
 */
char *create_file_name(char *file_name)
{
    char *dot = NULL, extension[] = ".sol1";

    dot = strrchr(file_name, '.');
    strcpy(dot, extension);

    return file_name;
}

/**
 * @brief 
 *
 * @param result 
 */
void print_to_file(int result, char *file_name)
{
    FILE *fptr = NULL;
    char *file = create_file_name(file_name);
    static bool name_is_made = false;

    if(!name_is_made){
        fclose(fopen(file, "w"));
        name_is_made = true;
    }

    if ((fptr = fopen(file, "a")) == NULL) /* "a" permite continuar a escrita, sem overwrite*/
        exit(EXIT_FAILURE);

    fprintf(fptr, "%d\n\n", result);

    fclose(fptr);
}