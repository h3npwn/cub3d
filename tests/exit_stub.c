#include "../headers/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void exit_failure(int code, int isnoexit)
{
    const char *errors[] = {
        "Error\nInvalid number of arguments.\n",
        "Error\nCannot open file OR extension invalid.\n",
        "Error\nInvalid configuration format.\n",
        "Error\nMemory allocation failed.\n",
        "Error\nInvalid map format.\n",
        "Error\nUnknown error occurred.\n"
    };
    int max = sizeof(errors) / sizeof(errors[0]);
    if (code >= 0 && code < max)
        fputs(errors[code], stderr);
    else
        fputs("Error\nUnknown\n", stderr);
    if (isnoexit)
        exit(isnoexit);
}
