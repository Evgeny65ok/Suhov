#include <iostream>
using namespace std;

extern int circles[8]; //в другом файле
extern int result;    //в другом файле ГЛОБАЛЬНАЯ

void findSolution(int pos);

int main() {
    findSolution(1);
    
    if (result != -1) {
        cout << "Число в закрашенном кружке: " << result << endl;
    } else {
        cout << "Решение не найдено" << endl;
    }
    
    return 0;
}