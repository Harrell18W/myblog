#include <stdio.h>
#include <stdlib.h>

#define LINE_CHAR_LIMIT 150

int getLines(char *path);

int main(void) {

    int lines = getLines("website/main.json");
    printf("%d\n", lines);

    char *main[lines];
    FILE *fptr;
    fptr = fopen("website/main.json", "r");
    for(size_t x = 0; x < lines; x++) {
        main[x] = malloc(sizeof(char) * LINE_CHAR_LIMIT);
        fgets(main[x], LINE_CHAR_LIMIT, fptr);
        printf("%s", main[x]);
    }
    fclose(fptr);

    return 0;

}

int getLines(char *file) {
    
    FILE *fp;
    fp = fopen(file, "r");
    int lines = 0;
    char singleLine[LINE_CHAR_LIMIT];
    while(!feof(fp)) {
        fgets(singleLine, LINE_CHAR_LIMIT, fp);
        lines++;
    }
    fclose(fp);

    return lines;

}