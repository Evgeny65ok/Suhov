#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <dlfcn.h>
#include "math_lib.h"

using namespace std;

void print_help() {
    cout << "Программа расчета объема шара методом Монте-Карло (Сервер)\n";
    cout << "Использование: ./server [--help]\n";
    cout << "После запуска сервер ждет подключения клиента на порту 8080.\n";
}

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--help") {
        print_help();
        return 0;
    }

    void* h = dlopen("./libmath.so", RTLD_LAZY);
    if (!h) { cout << "Ошибка библиотеки!" << endl; return 1; }
    auto calc = (void(*)(int, MonteResult*))dlsym(h, "calc_sphere");

    int s = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1; setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    sockaddr_in addr = {AF_INET, htons(8080), INADDR_ANY};
    
    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) return 1;
    listen(s, 1);

    cout << "Сервер готов. Жду клиента..." << endl;
    int c = accept(s, 0, 0);

    char buf[1024];
    while (true) {
        memset(buf, 0, 1024);
        int bytes = recv(c, buf, 1024, 0);
        if (bytes <= 0 || strstr(buf, "exit")) break;

        int n = atoi(buf); 
        if (n <= 0) n = 1000; 

        MonteResult res;
        calc(n, &res);

        string out = "Vol: " + to_string(res.volume) + " Time: " + to_string(res.time) + "s";
        send(c, out.c_str(), out.size(), 0);
    }

    close(c); close(s); dlclose(h);
    return 0;
}
