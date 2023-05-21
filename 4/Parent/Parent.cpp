#pragma warning(disable : 4996)
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
HANDLE A, endParent;
HANDLE hSemaphore;
int main(int argc, char* argv[])
{
	A = CreateEvent(NULL, FALSE, FALSE, "A");
	if (A == NULL) {
		return GetLastError();
	}
	endParent = CreateEvent(NULL, FALSE, FALSE, "endParent");
	if (endParent == NULL) {
		return GetLastError();
	}
	hSemaphore = CreateSemaphore(NULL, 1, 1, "SemaphoreParent");
	if (hSemaphore == NULL) {
		return GetLastError();
	}
	char message;
	WaitForSingleObject(hSemaphore, INFINITE);
	int num = atoi(argv[1]);
	for (int i = 0; i < num; i++) {
		cout << "Input message for process Parent:" << endl;
		cin >> message;
		if (message == 'A') {
			SetEvent(A);
		}
	}
	ReleaseSemaphore(hSemaphore, 1, NULL);
	CloseHandle(A);
	WaitForSingleObject(endParent, INFINITE);
	return 0;
}