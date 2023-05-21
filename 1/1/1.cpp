#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
struct nArray {
    unsigned int* Arr;
    int n;
    int sleepTime;
};
DWORD WINAPI worker(LPVOID iNum) {
    nArray newArr = *(nArray*)iNum;
    for (int i = 0; i < newArr.n; i++) {
        if (newArr.Arr[i] % 10 == 1) {
            std::cout << newArr.Arr[i] << std::endl;
        }
        Sleep(newArr.sleepTime);
    }
    return 0;
}
int main() {
    HANDLE hThread;
    DWORD IDThread;
    nArray newArr;
    std::cin >> newArr.n;
    newArr.Arr = new unsigned int[newArr.n];
    for (int i = 0; i < newArr.n; i++) {
        std::cin >> newArr.Arr[i];
    }
    newArr.sleepTime = 10;
    hThread = CreateThread(NULL, 0, worker, &newArr, 0, &IDThread);
    if (hThread == NULL) {
        return GetLastError();
    }
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    return 0;
}