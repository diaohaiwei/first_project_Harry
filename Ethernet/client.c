#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>
#define SERVERIP "127.0.0.1"
#define SERVERPORT 10000
int main(){
        int ret, num = 0;
        int tsock;
        double *i = 0;
        i = (double *)malloc(sizeof(double));
        char* j = '\0';
        j = (char *)malloc(sizeof(char));
        double* k = 0;
        k = (double *)malloc(sizeof(double));
        double result = 0;
        char* buffer = "HELP";
        char buf[20];
        struct sockaddr_in servaddr;
        tsock = socket(AF_INET, SOCK_STREAM, 0);
        if(tsock < 0){
        printf("Create Socket Failed!\n");
        exit(-1);
        }
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERVERPORT);
        inet_aton(SERVERIP, &servaddr.sin_addr);
        ret = connect(tsock, (struct sockaddr*)&servaddr, sizeof(struct sockaddr));
        if(ret < 0){
                printf("connet Failed!\n");
                exit(-1);
        }
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERVERPORT);
        inet_aton(SERVERIP, &servaddr.sin_addr);
        ret = connect(tsock, (struct sockaddr*)&servaddr, sizeof(struct sockaddr));
        if(ret < 0){
        num = send(tsock, buffer,strlen(buffer), 0);
        if(num != strlen(buffer)){
        printf("Send Data Failed!\n");
        exit(-1);
        }
        num = 0;
        num = recv(tsock, buf, sizeof(buf), 0);
        if(num < 0)
        {
                printf("Receive Data Failed!\n");
                exit(-1);
        }
        printf("%s\n", buf);
        *i = 1.0;
        *j = '+';
        *k = 2.0;
        num = 0;
        num = send(tsock, i, sizeof(double), 0);
        if(num < 0){
                printf("Send Data Failed!\n");
                exit(-1);
        }
        num = 0;
        num = send(tsock, j, sizeof(char), 0);
        if(num < 0){
                printf("Send Data Failed!\n");
                exit(-1);
        }
        num = 0;
        num = send(tsock, k, sizeof(double), 0);
        if(num < 0){
                printf("Send Data Failed!\n");
                exit(-1);
        }
        num = 0;
        num = recv(tsock, &result, sizeof(double), 0);
        if(num < 0){
                printf("Receive Data Failed!\n");
                exit(-1);
        }
        printf("result : %f\n", result);
close(tsock);
        free(i);
        free(j);
        free(k);
        return 0;


}
