#include "projectHeader.h"

int main(int argc, char* argv[])
{
    int maze;
    if( argc != 3 || strcmp(argv[1], "-s") ) exit(EXIT_FAILURE);

    file_reader(argv[0], maze);

}

/*mode parcer!!*/
/*check if out of bounds for pricell asap*/