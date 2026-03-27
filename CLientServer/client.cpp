#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const char* SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 8080;
const int BUFFER_SIZE = 1024;

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Ошибка сокета"; return 1;
    }
    std::cout << "Сокет создан";
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        close(clientSocket);
        return 2;
    }
    std::cout << "УРА! коннект!!!";
    for (int i = 0; i <= 4; i++) {
        std::string message = "ping";
        send(clientSocket, message.c_str(), message.length(), 0);
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
        int bytesRecieved = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
        if (bytesRecieved > 0) {
            std::cout << buffer << std::endl;
        }
    }
    send(clientSocket, "exit", 4, 0);
    close(clientSocket);
    return 0;
}
