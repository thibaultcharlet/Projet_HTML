#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#define MAX 80
#define PORT 8888
#define SA struct sockaddr



int main() 
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET -- IPV4
    //SOCK_STREAM -- TCP
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port  = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int bind_result = bind(sockfd, (struct sockaddr*) &servaddr, sizeof(struct sockaddr_in));
    listen(sockfd, 0);
    int size_socket = sizeof(servaddr);
    // ON ACCEPTE DES CONNEXIONS
    struct sockaddr_in client_addr;
    bzero(&size_socket, sizeof(socklen_t)); // on définit la struct à 0 pour la nettoyer
    char buffer_answer[] = "HTTP/1.1 200 OK\r\nDate: Thu, 11 Jan 2007 14:00:36 GMT\r\nServer: Apache/2.0.54 (Debian GNU/Linux) DAV/2 SVN/1.1.4\r\nConnection: close\r\nTransfer-Encoding: chunked\r\nContent-Type: text/html; charset=ISO-8859-1\r\n\r\n178a1\r\n\r\n<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\r\n<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\">\r\n<head>\r\n<meta http-equiv=\"content-type\" content=\"text/html; charset=ISO-8859-1\" />\r\n<meta http-equiv=\"pragma\" content=\"no-cache\" />\r\n\r\n<title>Accueil - Le Site du Zéro</title>";
    int BUFFER_SIZE = 1024;
    while(1)
    {
        int client_sock = accept(sockfd, (struct sockaddr*) &client_addr, &size_socket);

        printf("New connexion %s\n", inet_ntoa(client_addr.sin_addr));
        int pid = fork();
        if (pid == 0)
        {
            printf("New connexion handled in process %i\n", getpid());
            char *buffer = malloc(BUFFER_SIZE*sizeof(char));
            bzero(buffer, BUFFER_SIZE);

          
            
            int size_lu = read(client_sock, buffer, BUFFER_SIZE);
            if (size_lu <= 0)
            {
                perror("read");
                printf("error : SHUT_RDWRConnexion to %s closed\n", inet_ntoa(client_addr.sin_addr));
                return 0;
            }
            printf("%s",buffer);
            char *chaine = malloc(1024);
            strcpy(chaine,buffer);
            char *suitechaine = malloc(1024);
            suitechaine = strchr(chaine,'/');
            printf("%s",suitechaine);
            write(client_sock, &buffer_answer,sizeof(buffer_answer));
            shutdown(client_sock, SHUT_RDWR);  
            close(client_sock);

            

        }


    }

    
    //free(buffer);
    //close(client_sock);
    //close(sockfd);
}