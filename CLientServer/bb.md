Хорошо, сделаю минимально, но с выполнением всех требований.

## Математическая модель

Объём шара x² + y² + z² ≤ 1 вычисляется методом Монте-Карло. Точки генерируются в кубе [-1,1]³ объёмом 8. Отношение точек внутри сферы к общему числу равно отношению объёма сферы к объёму куба: V = (k/n) * 8. Теоретический объём: V = 4/3 * π ≈ 4.18879.

---

## Структура проекта

```
math_server/
├── math_lib.h
├── math_lib.cpp
├── server.cpp
├── client.cpp
├── help.txt
├── Makefile
```

---

## 1. `math_lib.h`

```cpp
#ifndef MATH_LIB_H
#define MATH_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

struct MonteResult {
    double volume;
    int points_inside;
    double time;
};

const char* get_version();
const char* get_author();
double calc_sphere(int n, MonteResult* res);

#ifdef __cplusplus
}
#endif

#endif
```

---

## 2. `math_lib.cpp`

```cpp
#include "math_lib.h"
#include <cstdlib>
#include <ctime>
#include <chrono>

const char* get_version() {
    return "1.0";
}

const char* get_author() {
    return "Ivan Ivanov";
}

double calc_sphere(int n, MonteResult* res) {
    auto start = std::chrono::high_resolution_clock::now();
    
    srand(time(NULL));
    int k = 0;
    
    for (int i = 0; i < n; i++) {
        double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double z = (double)rand() / RAND_MAX * 2.0 - 1.0;
        
        if (x*x + y*y + z*z <= 1) k++;
    }
    
    double volume = (double)k / n * 8.0;
    
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration<double>(end - start).count();
    
    if (res) {
        res->volume = volume;
        res->points_inside = k;
        res->time = elapsed;
    }
    
    return volume;
}
```

---

## 3. `server.cpp`

```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

const int PORT = 8080;
const int BUF = 1024;

int main() {
    void* lib = dlopen("./libmath.so", RTLD_LAZY);
    if (!lib) {
        cerr << "lib error\n";
        return 1;
    }
    
    auto getv = (const char*(*)())dlsym(lib, "get_version");
    auto geta = (const char*(*)())dlsym(lib, "get_author");
    auto calc = (double(*)(int, void*))dlsym(lib, "calc_sphere");
    
    if (!getv || !geta || !calc) {
        cerr << "symbols error\n";
        dlclose(lib);
        return 1;
    }
    
    ifstream hf("help.txt");
    string help;
    if (hf.is_open()) {
        stringstream ss;
        ss << hf.rdbuf();
        help = ss.str();
        hf.close();
    }
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    
    bind(sock, (sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);
    cout << "Server on port " << PORT << endl;
    
    socklen_t len = sizeof(addr);
    int client = accept(sock, (sockaddr*)&addr, &len);
    cout << "Client connected\n";
    
    char buf[BUF];
    while (true) {
        memset(buf, 0, BUF);
        recv(client, buf, BUF, 0);
        string msg(buf);
        
        if (msg == "exit") break;
        else if (msg == "--help" || msg == "-h")
            send(client, help.c_str(), help.length(), 0);
        else if (msg == "--version" || msg == "-v") {
            string v = string(getv()) + "\n" + string(geta()) + "\n";
            send(client, v.c_str(), v.length(), 0);
        }
        else if (msg.substr(0,6) == "sphere") {
            int n = stoi(msg.substr(7));
            MonteResult res;
            double vol = calc(n, &res);
            stringstream out;
            out << "Volume: " << vol << "\n";
            out << "Inside: " << res.points_inside << "/" << n << "\n";
            out << "Time: " << res.time << "s\n";
            send(client, out.str().c_str(), out.str().length(), 0);
        }
        else
            send(client, "Unknown\n", 8, 0);
    }
    
    close(client);
    close(sock);
    dlclose(lib);
    return 0;
}
```

---

## 4. `client.cpp`

```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    
    connect(sock, (sockaddr*)&addr, sizeof(addr));
    cout << "Connected\n";
    
    string input;
    while (true) {
        cout << "> ";
        getline(cin, input);
        send(sock, input.c_str(), input.length(), 0);
        
        if (input == "exit") break;
        
        char buf[1024];
        memset(buf, 0, 1024);
        recv(sock, buf, 1024, 0);
        cout << buf;
    }
    
    close(sock);
    return 0;
}
```

---

## 5. `help.txt`

```
Math Server v1.0
Author: Ivan Ivanov

Commands:
  --help, -h     - this help
  --version, -v  - version info
  sphere N       - volume by N points
  exit           - quit

Sphere: x^2 + y^2 + z^2 = 1
Method: Monte Carlo
Volume = (points_inside / N) * 8
```

---

## 6. `Makefile`

```makefile
all: libmath.so server client

libmath.so: math_lib.cpp math_lib.h
	g++ -fPIC -shared -o libmath.so math_lib.cpp

server: server.cpp
	g++ -o server server.cpp -ldl

client: client.cpp
	g++ -o client client.cpp

clean:
	rm -f libmath.so server client
```

---

## 7. Doxygen

Создать `Doxyfile`:

```bash
doxygen -g
```

Правим параметры:

```
PROJECT_NAME = "Math Server"
INPUT = ./
FILE_PATTERNS = *.h *.cpp
EXTRACT_ALL = YES
```

Запуск:

```bash
doxygen Doxyfile
```

---

## Сборка и запуск

```bash
make
./server          # терминал 1
./client          # терминал 2
```

В клиенте:
```
> sphere 1000000
> --help
> --version
> exit
```

Всё! Минимальный код, но с полной функциональностью: библиотека, сервер, клиент, справка из файла, doxygen.