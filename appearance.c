#include <stdio.h>
#include <stdlib.h>

#define LINE_CHAR_LIMIT 150

int getLines(char *path);
void readLines(char *path, char *arr[]);
void changeTitle(char *title, char *arr[]);
void changeMotd(char *motd, char *arr[]);
void changeBgColor(char *color, char *arr[]);
void writeLines(char *path, char *arr[]);

int main(void) {

    char *main[getLines("website/main.json")];
    
    readLines("website/main.json", main);
    for(size_t x = 0; x < getLines("website/main.json"); x++) {
        printf("%s", main[x]);
    }

    writeLines("website/main.json", main);

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

void readLines(char *path, char *arr[]) {

    int lines = getLines(path);
    FILE *fptr;
    fptr = fopen(path, "r");
    for(size_t x = 0; x < lines; x++) {
        arr[x] = malloc(sizeof(char) * LINE_CHAR_LIMIT);
        fgets(arr[x], LINE_CHAR_LIMIT, fptr);
    }
    fclose(fptr);
    
}

void changeTitle(char *title, char *arr[]) {
    sprintf(arr[1], "\t\"title\":\"%s\",\n", title);
}

void changeMotd(char *motd, char *arr[]) {
    sprintf(arr[2], "\t\"motd\":\"%s\",\n", motd);
}

void changeBgColor(char *color, char *arr[]) {
    sprintf(arr[3], "\t\"bgColor\":\"%s\"\n", color);
}

void writeLines(char *path, char *arr[]) {

    int lines = getLines(path);
    FILE *fptr;
    fptr = fopen(path, "w");
    for(size_t x = 0; x < lines; x++) {
        fputs(arr[x], fptr);
    }
    fclose(fptr);

}