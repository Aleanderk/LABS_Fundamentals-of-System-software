#pragma warning(disable : 4996)
#include <iostream>
#include <windows.h>
#include <conio.h>
HANDLE B, endChild;
HANDLE hMutex;
using namespace std;
int main(int argc, char* argv[]){
	B = CreateEvent(NULL, FALSE, FALSE, "B");
	if (B == NULL) {
		return GetLastError();
	}
	endChild = CreateEvent(NULL, FALSE, FALSE, "endChild");
	if (endChild == NULL) {
		return GetLastError();
	}
	hMutex = CreateMutex(NULL, FALSE, "MutexChild");
	if (hMutex == NULL) {
		return GetLastError();
	}
	char message;
	WaitForSingleObject(hMutex, INFINITE);
	int num = atoi(argv[1]);
	for (int i = 0; i < num; i++) {
		cout << "Input message for process Child:" << endl;
		cin >> message;
		if (message == 'B') { // Не обрабатывал случай ввода не B, аналогично с A в Parent, т.к. по условию строго сказано, что сообщения состоят из этих букв.
			SetEvent(B);
		}
	}
	ReleaseMutex(hMutex);
	CloseHandle(B);
	WaitForSingleObject(endChild, INFINITE);
	return 0;
}