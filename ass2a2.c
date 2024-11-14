// child.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No arguments provided.\n");
        return 1;
    }

    printf("Reversed array :\n");
    for (int i = argc - 1; i > 0; i--) {
        printf("%d ", atoi(argv[i]));
    }
    printf("\n");

    return 0;
}

