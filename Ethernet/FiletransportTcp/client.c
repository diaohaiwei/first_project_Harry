#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT 10000
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

int main(int argc, char** argv){
        if(argc < 2){
                printf("Usage: ./%s ServerIPAddress\n", argv[0]);
                exit(-1);
        }
        int tsock = socket(AF_INET, SOCK_STREAM, 0);
        if(tsock < 0){
                printf("Create socket Failed!\n");
                exit(-1);
        }
        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        if(inet_aton(argv[1], &servaddr.sin_addr) == 0){
                printf("Server IP Address Error!\n");
                exit(-1);
        }
        servaddr.sin_port = htons(SERVER_PORT);
        int len = sizeof(servaddr);
        int ret, num;
        ret = connect(tsock, (struct sockaddr*)&servaddr, sizeof(struct sockaddr));
        if(ret < 0){
                printf("connect Failed!\n");
                exit(-1);
        }
        char file_name[FILE_NAME_MAX_SIZE + 1];
        memset(file_name, '\0', sizeof(file_name));
        printf("Please input file name on server. \t");
        scanf("%s", file_name);
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', sizeof(buffer));
        strncpy(buffer, file_name, strlen(file_name) > BUFFER_SIZE? BUFFER_SIZE : strlen(file_name));
        num = 0;
        num = send(tsock, buffer, BUFFER_SIZE, 0);
//        if(num != strlen(buffer)){
//            printf("Send data Failed!\n");
//            exit(-1);
//        }    
        FILE* fp = fopen(file_name, "w");
        if(fp == NULL){
                printf("File:\t%s Can NOt OPen to write!\n", file_name);
                exit(-1);
        }
        memset(buffer, '\0', sizeof(buffer));
        num = 0;
        while((num = recv(tsock, buffer, BUFFER_SIZE, 0)) != 0){
            if(num < 0){
                printf("Receive data from server %s Failed!\n", argv[1]);
                break;
            }
            int write_len = fwrite(buffer, sizeof(char), num, fp);
            if(write_len != num){
                printf("File:\t %s Write Failed!\n", file_name);
                break;
            }
            memset(buffer, '\0', BUFFER_SIZE);
        }
        printf("Receive FIle:\t %s From Server [%s] Finished!\n", file_name, argv[1]);
        fclose(fp);
        close(tsock);
        return 0;
}
