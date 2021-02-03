# THIBAULT CHARLET PROJET HTML

SEUL SUR LE PROJET

## EXPLICATION

Cette partie du code permet l'initialisation de la com serveur avec l'adresse IP de mon ordinateur. Egalement la création d'un char contenant une réponse http type.

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
    char buffer_answer[] = "Réponse HTTP type attendue par le serveur"
    int BUFFER_SIZE = 1024;
    

Cette partie permet la création de la socket a partir de la lecture d'info réalisé par sockfd. Si la connexion a lieu correctement, l'info de la socket (buffer) est stocké puis print, la requete est bien receptionnée.Il y alors une requete http envoyé en retour au serveur par une socket write contenant le string de la requete http type. on ferme alors la connexion.
    
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
# Projet_HTML
# Projet_HTML
