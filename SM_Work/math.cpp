#include <iostream>
using namespace std;


int circles[8] = {0}; 
int result = -1; //решение не найденно

const int numbers[] = {1, 2, 3, 4, 6, 8, 9}; //числа будут перемноженны
bool used[10] = {false};

bool check() {
    int p1 = circles[1] * circles[2] * circles[3];
    int p2 = circles[3] * circles[4] * circles[5];
    int p3 = circles[5] * circles[6] * circles[7];
    
    return (p1 == p2 && p2 == p3);  // Возвращаем true, если все три произведения равны
}

void findSolution(int pos) { //текущая позиция перебираем кружочки функция
//  явлеятся реурсивной(вызывает саму себя для решения более мелких задач)
    if (pos == 8) { 
        if (check()) {
            result = circles[4]; //центральный кружочек
            cout << "Решение: ";
            for (int i = 1; i <= 7; i++) {
                cout << circles[i] << " ";
            }
            cout << " | Произведение = " << (circles[1] * circles[2] * circles[3]) << endl;
        }
        return;
    }
    
    for (int i = 0; i < 7; i++) {
        int num = numbers[i];
        if (!used[num]) {
            used[num] = true;
            circles[pos] = num;
            findSolution(pos + 1);
            used[num] = false;
        }
    }
}