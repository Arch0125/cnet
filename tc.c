#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
    char clientResponse[1024];
    char serverResponse[1024];
    int socketDescriptor;
    struct sockaddr_in serveraddr, clientaddr;

    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(12345);
    serveraddr.sin_family = AF_INET;

    socketDescriptor = socket(AF_INET,SOCK_STREAM,0);

    connect(socketDescriptor, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    while (1)
    {
        recv(socketDescriptor, serverResponse, sizeof(serverResponse), 0);
        printf("\nSERVER:%s", serverResponse);
        printf("\nEnter client response");
        scanf("%s", clientResponse);
        send(socketDescriptor, clientResponse, sizeof(clientResponse), 0);
    }
    close(socketDescriptor);
    return 0;
}