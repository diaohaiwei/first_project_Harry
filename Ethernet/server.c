#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <malloc.h>
#define SERVER_PORT 10000
#define QUEUE 20

int main()  
{
        int msock;
        int ssock;
        int ret, num = 0;
        char buf[1024];
        char* buffer = "ok";
        double* i;
        i = (double*)malloc(sizeof(double));
        char* j;
        j = (char*)malloc(sizeof(char));
        double* k;
        k = (double*)malloc(sizeof(double));
        double result = 0;
        struct sockaddr_in servaddr;
        struct sockaddr_in clientaddr;
        msock = socket(AF_INET, SOCK_STREAM, 0);
        if(msock < 0)
        {
                printf("creat socket failed!\n");
                exit(-1);
        }  
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(SERVER_PORT);
        ret = bind(msock, (struct sockaddr*)&servaddr, sizeof(struct sockaddr_in));
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(SERVER_PORT);
        ret = bind(msock, (struct sockaddr*)&servaddr, sizeof(struct sockaddr_in));
        if(ret < 0){
        if(ret < 0){
                printf("Server Bind Port: %d Failed!\n", SERVER_PORT);
                exit(-1);
        }
        ret = listen(msock, QUEUE);
        if(ret < 0){
                printf("listen Failed!\n");
                exit(-1);
        }
        while(1)
        {
                memset(&clientaddr, 0, sizeof(clientaddr));
                int len = sizeof(clientaddr);
                ssock = accept(msock, (struct sockaddr*)&clientaddr, &len);
                if(ssock < 0)
                {
                        printf("accept Failed!");
                        break;
                }
                memset(buf, '\0', sizeof(buf));
                num = 0;
                num = recv(ssock, buf, sizeof(buf), 0);
                if(num < 0)
                {
                        printf("Receive Data Failed!\n");
                        break;
                }
                printf("%s\n", buf);
                num = 0;
                num = send(ssock, buffer, strlen(buffer), 0);
                if(num != strlen(buffer))
                {
                        printf("Send Data Failed!\n");
                        break;
                }
                num = 0;
                num = recv(ssock, i, sizeof(double), 0);
                if(num < 0)
                {
                        printf("Receive Data Failed!\n");
                        break;
                }
                num = 0;
                num = recv(ssock, j, sizeof(char), 0);
                if(num < 0)
                {
                        printf("Receive Data Failed!\n");
                        break;
                }
                num = 0;
                num = recv(ssock, k, sizeof(double), 0);
                if(num < 0)
                {
                        printf("Receive Data Failed!\n");
                        break;
                }
                printf("Receive customer's data are: i = %f, j = '%c', k = %f \n", *i, *j, *k);
                switch(*j){
                    case '+':
                        result = *i + *k;
                        break;
                    case '-':
                        result = *i - *k;
                        break;
                    case '*':
                        result = (*i)*(*k);
                    default:
                        result = (*i)/(*k);
                        break;
                }
                num = 0;
                num = send(ssock, &result, sizeof(double), 0);
                if(num < 0)
                {
                        printf("Send Data Failed!\n");
                        break;
                }
                close(ssock);
        }
        close(msock);
        return 0;
            
}

