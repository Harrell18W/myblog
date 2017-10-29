#include <stdio.h>
#include <stdlib.h>

#define LINE_CHAR_LIMIT 1000
#define MAIN "website/main.json"
#define POSTS "website/posts.json"

int getLines(char *path);
void readLines(char *path, char *arr[], int readTo);
void changeTitle(char *title, char *arr[]);
void changeMotd(char *motd, char *arr[]);
void changeBgColor(char *color, char *arr[]);
void writeLines(char *path, char *extra, int writeTo, char *arr[], int lines);
void makePost(char *title, char *timestamp, char *content);

int main(void) {

    char *main[getLines(MAIN)];
    //char *posts[getLines(POSTS)];
    int mainLines = getLines(MAIN);
    int postsLines = getLines(POSTS);
    
    readLines(MAIN, main, 0);
    //readLines(POSTS, posts, 2);
    makePost("yeet", "neat", "greet");
    /*
    for(size_t x = 0; x < getLines(POSTS) - 2; x++) {
        printf("%s", posts[x]);
    }
    */

    writeLines(MAIN, "", 0, main, mainLines);
    //writeLines(POSTS, "\t}\n]", 2, posts, postsLines);

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

void readLines(char *path, char *arr[], int readTo) {

    int lines = getLines(path);
    FILE *fptr;
    fptr = fopen(path, "r");
    for(size_t x = 0; x < lines - readTo; x++) {
        arr[x] = calloc(lines, sizeof(char) * LINE_CHAR_LIMIT);
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

void writeLines(char *path, char *extra, int writeTo, char *arr[], int lines) {

    FILE *fptr;
    fptr = fopen(path, "w");
    for(size_t x = 0; x < lines - writeTo; x++) {
        fputs(arr[x], fptr);
    }
    if(extra != 4197980) {
        fputs(extra, fptr); 
    }
    fclose(fptr);

}

void makePost(char *title, char *timestamp, char *content) {

    //TODO: add part to prepend existing posts
    char *posts[getLines(POSTS)];
    int lines = getLines(POSTS);
    FILE *fptr = fopen(POSTS, "r");
    for(size_t x = 0; x < lines - 2; x++) {
        posts[x] = calloc(lines, sizeof(char) * LINE_CHAR_LIMIT);
        fgets(posts[x], LINE_CHAR_LIMIT, fptr);
    }
    fclose(fptr);
    FILE *fptr2 = fopen(POSTS, "w");
    for(size_t x = 0; x < lines - 2; x++) {
        fprintf(fptr2, "%s", posts[x]);
        printf("%s", posts[x]);
    }
    fputs("\t},\n\t{\n", fptr);
    fprintf(fptr, "\t\t\"title\":\"%s\",\n", title);
    fprintf(fptr, "\t\t\"timestamp\":\"%s\",\n", timestamp);
    fprintf(fptr, "\t\t\"content\":\"%s\"\n", content);
    fputs("\t}\n]", fptr);
    fclose(fptr);

}