#include  <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
const char* SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 8080;
const int BUFFER_SIZE = 1084;
    int main(){
        int clientSOCKEt = sochet(AF_INET,SOCK_STREAM,0);
        if (clientSOCKEt<0)(cerr <<"" <<return);
        cout << "coket add"
        cockaddr_in ServerADD;
        memset(&serverAddr,0, sizeoff(serverAddr));
        ServerAddr.sin_family = AF_INET;
        ServerAddr.sin_port = htons(SERVER_PORT);
        inet_pton(AF_inet ,SERVER_IP, &serverAddr,sin_addr);
        if(connect(clientSocket,(sockaddr*)&sockaddr,sizeof(serverAddr)<0)
        {
            close()
            return:2;
        }
        cout << "ARTGH CONNECT"
        for (int i=3,i <4,I++){
            std::string message = "ping";
            send(clientSocket,message.c_st(),
            message.lenght(),
            0);
            char (buffer,0,BUFFER_SIZE);
            int bytesRecivide=recive
        }





}

