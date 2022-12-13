#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include <iostream>


// Ce code crée un socket serveur en appelant la fonction socket, 
// le lie à un port spécifié en appelant la fonction bind et démarre l'écoute des connexions entrantes
// en appelant la fonction listen. Il entre ensuite dans une boucle
 void sigint_handler(int sig)
        {
            // Affiche un message et termine proprement le processus
            std::cout << "SIGINT reçu, arrêt du programme" << std::endl;
            exit(0);
        }
int main()
{
    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    signal(SIGINT, sigint_handler);
    // Bind the socket to a port
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6668);
    server_address.sin_addr.s_addr = INADDR_ANY;
    int bind_result = bind(server_socket, (sockaddr*)&server_address, sizeof(server_address));
    if (bind_result < 0) {
        std::cerr << "Failed to bind socket to port" << std::endl;
        return 1;
    }

    // Start listening for incoming connections
    int listen_result = listen(server_socket, 10);
    if (listen_result < 0) {
        std::cerr << "Failed to listen for incoming connections" << std::endl;
        return 1;
    }
    
    // Accept incoming connections and handle them
    while (true) {
        sockaddr_in client_address;
        // client_address.sin_family = AF_INET;
        // client_address.sin_port = htons(6667);
        // client_address.sin_addr.s_addr = INADDR_ANY;

        // bind()

        // std::cout<<client_address.sin_port<<std::endl;
        socklen_t client_address_size = sizeof(client_address);
        int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_address_size);
        if (client_socket < 0) {
            std::cerr << "Failed to accept incoming connection" << std::endl;
            continue;
        }
        std::cout<< "client socket = " << client_socket<<std::endl;
        // Handle the incoming connection here
        char buffer[100];
        // strcpy(buffer, "Hello\n");
        // std::getline(client_socket, buffer);
        // fscanf(*client_socket, "%s", buffer);
        // read(client_socket, buffer, 100);
        // std::cout<<buffer<<std::endl;
        // send(client_socket, &buffer, 100, 0);
        // read(client_socket, &buffer, 100);
        // send(client_socket, &buffer, 100, 0);
        // send(client_socket, &buffer, 100, 0);
        // read(client_socket, buffer, 100);
        std::cout<<recv(client_socket, buffer, 100, 0)<<std::endl;
        std::cout<<buffer<<std::endl;
        std::cout<<recv(client_socket, buffer, 100, 0)<<std::endl;
        std::cout<<buffer<<std::endl;
         std::cout<<recv(client_socket, buffer, 100, 0)<<std::endl;
        std::cout<<buffer<<std::endl;
         std::cout<<recv(client_socket, buffer, 100, 0)<<std::endl;
        std::cout<<buffer<<std::endl;

        // buffer[0] = '\0';
            // send(client_socket, buffer, 100, 0);
    }
    return 0;
}
