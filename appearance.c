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
void writeLines(char *path, char *extra, int writeTo, char *arr[]);
void makePost(char *title, char *timestamp, char *content, char *arr[]);

int main(void) {

    char *main[getLines(MAIN)];
    char *posts[getLines(POSTS)];
    
    readLines(MAIN, main, 0);
    readLines(POSTS, posts, 2);
    //makePost("fuck", "tits", "hooker-fucker", posts);
    /*
    for(size_t x = 0; x < getLines(POSTS) - 2; x++) {
        printf("%s", posts[x]);
    }
    */

    writeLines(MAIN, "", 0, main);
    writeLines(POSTS, "\t}\n]", 2, posts);

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

void writeLines(char *path, char *extra, int writeTo, char *arr[]) {

    int lines = getLines(path);
    FILE *fptr;
    fptr = fopen(path, "w");
    for(size_t x = 0; x < lines - writeTo; x++) {
        printf("%d\n", x);
        fputs(arr[x], fptr);
        printf("%s", arr[x]);
    }
    if(extra != 4197980) {
        fputs(extra, fptr); 
    }
    fclose(fptr);

}

void makePost(char *title, char *timestamp, char *content, char *arr[]) {

    int lines = getLines(POSTS);
    char *post;
    char *titleLine;
    char *timestampLine;
    char *contentLine;
    sprintf(titleLine, "\t\t\"title\":\"%s\",\n", title);
    printf("%s", titleLine);
    sprintf(timestampLine, "\t\t\"timestamp\":\"%s\",\n", timestamp);
    puts("yeet");
    sprintf(contentLine, "\t\t\"content\":\"%s\",\n", content);
    arr[lines - 2] = "\t},\n";
    arr[lines - 1] = "\t{\n";
    arr[lines] = titleLine;
    arr[lines + 1] = timestampLine;
    arr[lines + 2] = contentLine;
    arr[lines + 3] = "\t}\n";
    arr[lines + 4] = "]";

}