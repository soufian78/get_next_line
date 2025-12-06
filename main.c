#include "get_next_line.h"
#include <stdio.h>
int main()
{
    int fd = open("text,txt",O_RDWR);
    char *line ;

    while(line = get_next_line(fd))
    {
        printf("%s",line);
        free(line);
    }
}