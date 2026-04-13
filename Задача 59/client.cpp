#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr = {AF_INET, htons(8080)};
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if (connect(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) { //подкючение
        cout << "Ошибка коннекта!" << endl;
        return 1;
    }
    cout << "УРА! коннект!!!" << endl;

    string n;
    cout << "Сколько крупиц кинуть? "; cin >> n;
    send(s, n.c_str(), n.size(), 0);

    char buffer[1024] = {0};
    int bytes = recv(s, buffer, 1024, 0);
    if (bytes > 0) {
        cout << "ОТВЕТ СЕРВЕРА: " << buffer << endl;
    }

    close(s);
    return 0;
}