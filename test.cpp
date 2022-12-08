// #include <iostream>
// #include <cstdio>
// #include <cstdlib>
// #include <unistd.h>
// #include <sys/types.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// You would need to create a Socket object and specify the port number that you want to use for the server:

// Once the socket is bound to a port, you can start listening for incoming connections by calling the listen() method:

// To accept incoming connections, you can use the accept() method, which will return a new Socket object that you can use to communicate with the client:

// Once you have accepted an incoming connection, you can use the send() and receive() methods to send and receive data with the client. For example:

// int main() {
//   // Create a socket object
//   Socket socket;

//   // Bind the socket to a port
//   socket.bind(8080);

//   // Start listening for incoming connections
//   socket.listen();

//   // Accept an incoming connection
//   Socket client = socket.accept();

//   // Send a message to the client
//   client.send("Hello, client!");

//   // Receive a message from the client
//   std::string message = client.receive();
//   std::cout << "Received message: " << message << std::endl;
// }

int main(void) 
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6666); // bind to port 6666
    serverAddr.sin_addr.s_addr = INADDR_ANY; // bind to any local address
    bind(sockfd, (sockaddr*)&serverAddr, sizeof(serverAddr)); // bind the socket to a specific port
    
    // bind() arguments :
        //  - sockfd = socket descriptor
        //  - (sockaddr*)&serverAddr = pointer to a 'sockaddr_in' structure containing the address and port to bni the socket to
        //  - sizeof(serverAddr) = size of the sockaddr_in structure

    //  listen for incoming connectins using listen(). Takes up to 2 arguments :
        // - socket descriptor
        //  - max peding connections that the server will allow

    listen(sockfd, 10);

    // accept incoming connections with accept(). Fuction takes 3 arguments :
        //  - socket descriptor
        //  - pointer to a sockaddr structure to store the adress of the connecting client
        //  - pointer to an integer to store the size of the sockaddr structure.
    //  The function returns a new socket descriptor for the accepted connection

    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSockfd = accept(sockfd, (sockaddr*)&clientAddr, &clientAddrSize);

    // Once you have accepted the connection, you can send and receive and data using send() and rcv().
    // Both functions take as argument :
        // - socket descriptor
        // - a pointer to a buffer containing the data to send or receive
        // - size of the buffer

    // send data to the client
    char buffer[1024];
    strcpy(buffer, "Hello\n");
    send(clientSockfd, buffer, strlen(buffer), 0);

    // receive data from the client
    recv(clientSockfd, buffer, sizeof(buffer), 0);
}