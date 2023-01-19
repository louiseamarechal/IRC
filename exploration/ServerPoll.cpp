#include <iostream>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include <fcntl.h>


int main(void){

    int enable = 1;

    // Create Socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }
    else
        std::cout << "Socket created !" << std::endl;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable));
    fcntl(server_socket, F_GETFL, O_NONBLOCK);
    // signal(SIGINT, sigint_handler);

    // Bind Socket to Port
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(55555);
    server_address.sin_addr.s_addr = INADDR_ANY;
    int bind_result = bind(server_socket, (sockaddr*)&server_address, sizeof(server_address));
    if (bind_result < 0) {
        std::cerr << "Failed to bind socket to port" << std::endl;
        return 1;
    }
    else
        std::cout << "Success, socket binded !" << std::endl;

    // Listen for incoming connections
    int listen_result = listen(server_socket, server_address.sin_port);
    if (listen_result < 0) {
        std::cerr << "Failed to listen for incoming connections" << std::endl;
        return 1;
    }
    else
        std::cout << "Listening for incoming connections ..." << std::endl;

    // Accept and handle connections
     while (true) {
        sockaddr_in client_address;
        struct pollfd fds;

        socklen_t client_address_size = sizeof(client_address);
        int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_address_size);
        if (client_socket < 0) {
            std::cerr << "Failed to accept incoming connection" << std::endl;
            continue;
        }
        else {
            std::cout << "Incoming connection detected..." << std::endl;
            std::cout<< "Accepted connection to client socket #" << client_socket <<std::endl;
        }

        fds.fd = client_socket;
        fds.events = POLLIN; 

        int nready = poll(&fds, 1, 100);
        if (nready < 0)
            std::cout << "Poll error" << std::endl;
        char buffer[1024];

        send(client_socket, "001 coucou :Welcome to the JLA.com Network, jbouyer \r\n", 60, 0);

        read(client_socket, buffer, 100);
        send(client_socket, buffer, 100, 0);
    }
}