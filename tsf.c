#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    char serverMessage[1024];
    char clientMessage[1024];
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serveraddr;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(12345);
    bind(socketDescriptor, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(socketDescriptor, 5);
    int clientSD = accept(socketDescriptor, NULL, NULL);
    pid_t cpid;
    cpid = fork();

    if (cpid == 0)
    {
        while (1)
        {

            recv(clientSD, clientMessage, sizeof(clientMessage), 0);
            printf("\nCLIENT:%s", clientMessage);
        }
       
    }
    else
    {
         while (1)
        {
            printf("\nEnter message");
            scanf("%s", serverMessage);
            send(clientSD, serverMessage, sizeof(serverMessage), 0);
        }
    }

    close(socketDescriptor);
    return 0;
}