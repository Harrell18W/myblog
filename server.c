#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 9002

#define LINE_CHAR_LIMIT 1000
#define TITLE_MOTD_CHAR_LIMIT 256
#define POST_CHAR_LIMIT 1000
#define MAIN "website/main.json"
#define POSTS "website/posts.json"

int getLines(char *path);
void readLines(char *path, char *arr[], int readTo);
void changeTitle(char *title, char *arr[]);
void changeMotd(char *motd, char *arr[]);
void changeBgColor(char *color, char *arr[]);
void writeLines(char *path, int writeTo, char *arr[], int lines);
void makePost(char *title, char *timestamp, char *content);

int main(void) {

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    int clientSocket;
    int command;

    while(1) {

        listen(serverSocket, 5);
        clientSocket = accept(serverSocket, NULL, NULL);
        recv(clientSocket, &command, sizeof(command), 0);
        printf("command: %d\n", command);

        char *main[getLines(MAIN)];
        int mainLines = getLines(MAIN);
        
        readLines(MAIN, main, 0);

        if(command == 0) {
            char *title = malloc(sizeof(char) * TITLE_MOTD_CHAR_LIMIT);
            recv(clientSocket, title, sizeof(char) * TITLE_MOTD_CHAR_LIMIT, 0);
            printf("User is changing blog title to: %s\n", title);
            changeTitle(title, main);
            free(title);
        } else if(command == 1) {
            char *motd = malloc(sizeof(char) * TITLE_MOTD_CHAR_LIMIT);
            recv(clientSocket, motd, sizeof(char) * TITLE_MOTD_CHAR_LIMIT, 0);
            printf("User is changing blog motd to: %s\n", motd);
            changeMotd(motd, main);
            free(motd);
        } else if(command == 2) {
            char *rgb = malloc(sizeof(char) * TITLE_MOTD_CHAR_LIMIT);
            recv(clientSocket, rgb, sizeof(char) * TITLE_MOTD_CHAR_LIMIT, 0);
            printf("User is changing blog background color to: %s\n", rgb);
            changeBgColor(rgb, main);
            free(rgb);
        } else if(command == 3) {
            char *postTitle = malloc(sizeof(char) * TITLE_MOTD_CHAR_LIMIT);
            char *postContent = malloc(sizeof(char) * LINE_CHAR_LIMIT);
            time_t currTime = time(NULL);
            char *currTimestamp = asctime(localtime(&currTime));
            sprintf(currTimestamp, "%.*s", 24, currTimestamp);
            recv(clientSocket, postTitle, sizeof(char) * TITLE_MOTD_CHAR_LIMIT, 0);
            recv(clientSocket, postContent, sizeof(char) * LINE_CHAR_LIMIT, 0);
            puts("User is making a new post");
            printf("Title: %s\n", postTitle);
            printf("Content: %s\n", postContent);
            makePost(postTitle, currTimestamp, postContent);
            free(postTitle);
            free(postContent);
        }

        writeLines(MAIN, 0, main, mainLines);

    }

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

void writeLines(char *path, int writeTo, char *arr[], int lines) {

    FILE *fptr;
    fptr = fopen(path, "w");
    for(size_t x = 0; x < lines - writeTo; x++) {
        fputs(arr[x], fptr);
    }
    fclose(fptr);

}

void makePost(char *title, char *timestamp, char *content) {

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
    }
    fputs("\t},\n\t{\n", fptr);
    fprintf(fptr, "\t\t\"title\":\"%s\",\n", title);
    fprintf(fptr, "\t\t\"timestamp\":\"%s\",\n", timestamp);
    fprintf(fptr, "\t\t\"content\":\"%s\"\n", content);
    fputs("\t}\n]", fptr);
    fclose(fptr);

}