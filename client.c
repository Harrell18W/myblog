#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 9002

#define LINE_CHAR_LIMIT 1000
#define TITLE_MOTD_CHAR_LIMIT 256
#define POST_CHAR_LIMIT 1000

int main(int argc, char *argv[]) {

    if(argc != 2) {
        puts("Please give the server IP address as your first argument. For localhost, use \"lh\"");
        return 0;
    }
    int command = -1;
    puts("What would you like to do?");
    while(command < 0 || command > 3) {
        puts("0: Change the blog's title");
        puts("1: Change the blog's message of the day");
        puts("2: Change the blog's background color");
        puts("3: Make a new post");
        scanf("%d", &command);
        if(command < 0 || command > 3) {
            puts("Invalid command");
        }
    }

    int networkSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    if(strcmp(argv[1], "lh"))
        serverAddress.sin_addr.s_addr = INADDR_ANY;
    else
        serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
    int connectionStatus = connect(networkSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if(connectionStatus < 0) {
        puts("There was an error connecting to the server");
        return 0;
    }

    if(command == 0) {
        puts("What would you like the new title to be? Max size is 256 characters");
        char *title = malloc(sizeof(char) * TITLE_MOTD_CHAR_LIMIT);
        fgets(title, TITLE_MOTD_CHAR_LIMIT, stdin);
        fgets(title, TITLE_MOTD_CHAR_LIMIT, stdin);
        strtok(title, "\n");
        send(networkSocket, &command, sizeof(command), 0);
        send(networkSocket, title, sizeof(char) * TITLE_MOTD_CHAR_LIMIT, 0);
        free(title);
    } else if(command == 1) {
        puts("What would you like the new message of the day to be? Max size is 256 characters");
        char *motd = malloc(sizeof(char) * TITLE_MOTD_CHAR_LIMIT);
        fgets(motd, TITLE_MOTD_CHAR_LIMIT, stdin);
        fgets(motd, TITLE_MOTD_CHAR_LIMIT, stdin);
        strtok(motd, "\n");
        send(networkSocket, &command, sizeof(command), 0);
        send(networkSocket, motd, sizeof(char) * TITLE_MOTD_CHAR_LIMIT, 0);
        free(motd);
    } else if(command == 2) {
        puts("What would you like the new background color to be? Please enter your color in hexadecimal format, e.g. #00FF00");
        char *rgb = malloc(sizeof(char) * TITLE_MOTD_CHAR_LIMIT);
        fgets(rgb, TITLE_MOTD_CHAR_LIMIT, stdin);
        fgets(rgb, TITLE_MOTD_CHAR_LIMIT, stdin);
        strtok(rgb, "\n");
        send(networkSocket, &command, sizeof(command), 0);
        send(networkSocket, rgb, sizeof(char) * TITLE_MOTD_CHAR_LIMIT, 0);
        free(rgb);
    } else if(command == 3) {
        puts("What would you like the title of your post to be? Max size is 256 characters");
        char *postTitle = malloc(sizeof(char) * TITLE_MOTD_CHAR_LIMIT);
        fgets(postTitle, TITLE_MOTD_CHAR_LIMIT, stdin);
        fgets(postTitle, TITLE_MOTD_CHAR_LIMIT, stdin);
        strtok(postTitle, "\n");
        puts("Please enter the text of your post. Max size is 1000 characters");
        char *postContent = malloc(sizeof(char) * LINE_CHAR_LIMIT);
        fgets(postContent, LINE_CHAR_LIMIT, stdin);
        strtok(postContent, "\n");
        send(networkSocket, &command, sizeof(command), 0);
        send(networkSocket, postTitle, sizeof(char) * TITLE_MOTD_CHAR_LIMIT, 0);
        send(networkSocket, postContent, sizeof(char) * LINE_CHAR_LIMIT, 0);
        free(postTitle);
        free(postContent);
    }

    close(networkSocket);

}