#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int SERVER_PORT = 8080;
const int BUFFER_SIZE = 1024;

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);
    if(bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Ошибка bind";
        close(server_socket);
        return 2;
    }
    if(listen(server_socket, 3) < 0) {
        std::cerr << "Ошибка listen"; close(server_socket);
        return 3;
    }
    std::cout << "Слушаю порт " << SERVER_PORT << std::endl;
    std::cout << "Ожидание клиента...";
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(server_socket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if(clientSocket < 0) {
        close(server_socket);
        return 4;
    }
    char buffer[BUFFER_SIZE];
    while(true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if(bytesReceived <= 0)

         break;
    }
    
}
