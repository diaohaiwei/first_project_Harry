#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT 10000
#define QUEUE 20
#define BUFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

int main(int argc, char** argv){
        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htons(INADDR_ANY);

        servaddr.sin_port = htons(SERVER_PORT);
        int msock = socket(AF_INET, SOCK_STREAM, 0);
        if(msock < 0){
                printf("creat socket Failed!\n");
                exit(-1);
        }
        int ret, num;
        ret = bind(msock, (struct sockaddr*)&servaddr, sizeof(struct sockaddr_in));
        if(ret < 0){
                printf("Server Bind Port: %d Failed!\n", SERVER_PORT);
                exit(-1);
        }
        ret = listen(msock, QUEUE);
        if(ret < 0){
                printf("listen Failed!\n");
                exit(-1);
        }
        while(1){
                struct sockaddr_in clientaddr;
                int len = sizeof(clientaddr);
                int ssock = accept(msock, (struct sockaddr*)&clientaddr, &len);
                if(ssock < 0){
                        printf("accept Failed!\n");
                        break;
                }
                char buffer[BUFER_SIZE];
                memset(buffer, '\0', sizeof(buffer));
                num = 0;
                num = recv(ssock, buffer, BUFER_SIZE, 0);
                if(num < 0){
                        printf("Receive Data Failed!\n");
                        break;
                }
                char file_name[FILE_NAME_MAX_SIZE + 1];
                memset(file_name, '\0', sizeof(file_name));
                strncpy(file_name, buffer, strlen(buffer) > FILE_NAME_MAX_SIZE ? FILE_NAME_MAX_SIZE : strlen(buffer));
                FILE* fp = fopen(file_name, "r");
                if(fp == NULL){
                        printf("File:\t %s Not Found!\n", file_name);
                }
                else{
                        memset(buffer, '\0', BUFER_SIZE);
                        int file_block_length = 0;
                        while((file_block_length = fread(buffer, sizeof(char), BUFER_SIZE, fp)) > 0){
                                printf("file_block_length = %d\n", file_block_length);
                                if(send(ssock, buffer, file_block_length, 0) < 0){
                                        printf("Send File:\t %s Failed!\n", file_name);
                                        break;
                                }
                                memset(buffer, '\0', sizeof(buffer));
                        }
                        fclose(fp);
                        printf("File: \t %s Transfer FInished!\n", file_name);
                }
                close(ssock);
        }
        close(msock);
        return 0;
            

}












