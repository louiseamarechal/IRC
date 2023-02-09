#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

#define PORT "9034"   // Port we're listening on

// Get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) // AF_INET = domaine de communication pour IPv4,
    {
        return &(((struct sockaddr_in*)sa)->sin_addr); //sockaddr_in = structure pour stocker info detaillees des adresses ipv4
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr); // sockaddr_in6 = structure pour stocker infos detailles des ipv6
}

// Return a listening socket
int get_listener_socket(void)
{
    int listener;     // Listening socket descriptor
    int yes=1;        // For setsockopt() SO_REUSEADDR, below
    int rv;

    struct addrinfo hints, *ai, *p; // structure utilise pour representer une adresse socket

    // Get us a socket and bind it
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // address family (IPv4 IPv6) is not specified,
    hints.ai_socktype = SOCK_STREAM; // stream socket
    hints.ai_flags = AI_PASSIVE;
    // AI_PASSIVE : This option specifies that the socket should be bound to a wildcard address (INADDR_ANY for IPv4, IN6ADDR_ANY_INIT for IPv6), allowing the socket to accept connections from any address. This can be useful, for example, when the local host is acting as a server and should be able to accept incoming connections from any client.
    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) // si echec : la liste des ports et adresses n'est pas stocke dans ai
    {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }
    
    for(p = ai; p != NULL; p = p->ai_next) {
        // listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        listener = socket(p->ai_family, p->ai_socktype, 0);
        if (listener < 0) { 
            continue;
        }
        
        // Lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        // SOL_SOCKET pour les options générales de socket
        // Si optval est défini sur 1, cela signifie que l'option spécifiée sera activée. La valeur exacte de l'option dépend de la valeur de l'argument optname. Par exemple, si optname est défini sur SO_REUSEADDR, optval est défini sur 1 pour activer l'option de réutilisation de l'adresse. Cela permet à une autre socket de se lier à l'adresse utilisée par une socket précédemment fermée, même si le timeout de libération de l'adresse n'est pas encore écoulé.
        // SO_REUSEADDR pour autoriser l'utilisation d'une adresse IP et d'un port déjà utilisés par un autre socket
        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        } // cas d'erreur

        break;
    }

    freeaddrinfo(ai); // All done with this

    // If we got here, it means we didn't get bound
    if (p == NULL) {
        return -1;
    }

    // Listen
    if (listen(listener, 10) == -1) {
        return -1;
    }

    return listener;
}

// Add a new file descriptor to the set
void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
    // If we don't have room, add more space in the pfds array
    // if (*fd_count == *fd_size) {
    //     *fd_size *= 2; // Double it

    //     // *pfds = realloc(*pfds, sizeof(**pfds) * (*fd_size));
    //     *pfds = new struct pollfd[*fd_size];
    // }

    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN; // Check ready-to-read

    (*fd_count)++;
}

// Remove an index from the set
void del_from_pfds(struct pollfd pfds[], int i, int *fd_count)
{
    // Copy the one from the end over this one
    pfds[i] = pfds[*fd_count-1];

    (*fd_count)--;
}

// Main
int main(void)
{
    int listener;     // Listening socket descriptor

    int newfd;        // Newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // Client address
    socklen_t addrlen; // variable qui contient la taille de la structure sockaddr

    char buf[256];    // Buffer for client data

    char remoteIP[INET6_ADDRSTRLEN];
    // NET6_ADDRSTRLEN est une constante définie dans les en-têtes de réseau. Il spécifie la longueur maximale d'une chaîne de caractères qui peut être utilisée pour représenter une adresse IPv6.


    // Start off with room for 5 connections
    // (We'll realloc as necessary)
    int fd_count = 0;
    int fd_size = 5;
    // struct pollfd *pfds = ( struct pollfd *)malloc(sizeof *pfds * fd_size);
    struct pollfd *pfds =  new struct pollfd[fd_size];

    // Set up and get a listening socket
    listener = get_listener_socket();

    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n");
        exit(1);
    }

    // Add the listener to set
    pfds[0].fd = listener;
    pfds[0].events = POLLIN; // Report ready to read on incoming connection

    fd_count = 1; // For the listener

    // Main loop
    for(;;) {
        int poll_count = poll(pfds, fd_count, -1); // poll() retourne le nombre de files d'I/O qui sont prêtes à être lues ou écrites, ou 0 si aucun file n'est prête avant que le délai d'attente ne soit écoulé, ou -1 si une erreur se produit.

        if (poll_count == -1) {
            perror("poll");
            exit(1);
        }

        // Run through the existing connections looking for data to read
        for(int i = 0; i < fd_count; i++) {

            // Check if someone's ready to read
            if (pfds[i].revents & POLLIN) { // We got one!!

                if (pfds[i].fd == listener) {
                    // If listener is ready to read, handle new connection

                    addrlen = sizeof remoteaddr;
                    newfd = accept(listener,
                        (struct sockaddr *)&remoteaddr,
                        &addrlen);

                    // Lorsqu'une connexion est reçue et acceptee, accept() retourne un nouveau descripteur de socket pour le client, ou un entier négatif en cas d'erreur.

                    if (newfd == -1) {
                        perror("accept");
                    } else {
                        add_to_pfds(&pfds, newfd, &fd_count, &fd_size);

                        printf("pollserver: new connection from %s on "
                            "socket %d\n",
                            inet_ntop(remoteaddr.ss_family,
                                get_in_addr((struct sockaddr*)&remoteaddr),
                                remoteIP, INET6_ADDRSTRLEN),
                            newfd);
                            // fonction similaire a inet_ntoa qu'on a le droit d'utiliser
                    }
                } else {
                    // If not the listener, we're just a regular client
                    int nbytes = recv(pfds[i].fd, buf, sizeof buf, 0);

                    int sender_fd = pfds[i].fd;

                    if (nbytes <= 0) {
                        // Got error or connection closed by client
                        if (nbytes == 0) {
                            // Connection closed
                            printf("pollserver: socket %d hung up\n", sender_fd);
                        } else {
                            perror("recv");
                        }

                        close(pfds[i].fd); // Bye!

                        del_from_pfds(pfds, i, &fd_count);

                    } else {
                        // We got some good data from a client

                        for(int j = 0; j < fd_count; j++) {
                            // Send to everyone!
                            int dest_fd = pfds[j].fd;

                            // Except the listener and ourselves
                            if (dest_fd != listener && dest_fd != sender_fd) {
                                if (send(dest_fd, buf, nbytes, 0) == -1) {
                                    perror("send");
                                }
                            }
                        }
                    }
                } // END handle data from client
            } // END got ready-to-read from poll()
        } // END looping through file descriptors
    } // END for(;;)--and you thought it would never end!
    
    return 0;
}