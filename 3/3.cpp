#include <Windows.h>
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;
CRITICAL_SECTION cs;
HANDLE event1, event2;
struct Array {
	char* array;
	int n;
	int k;
	int sum = 0;
};
DWORD WINAPI SumElement(LPVOID _array)
{
	EnterCriticalSection(&cs);
	WaitForSingleObject(event2, INFINITE);
	Array* array = (Array*)_array;
	for (int i = 0; i < array->k; i++) {
		array->sum += (int)array->array[i];
	}
	array->sum /= array->k;
	LeaveCriticalSection(&cs);
	return 0;
}
DWORD WINAPI work(LPVOID _array)
{
	cout << "Input sleep time"<<endl;
	int s;
	cin >> s;
	Array* array = (Array*)_array;
	for (int id = 0; id < array->k; id++) {
		char temp = array->array[0];
		for (int ind = id + 1; ind < array->n; ind++) {
			if (array->array[id] > array->array[ind]) {
				temp = array->array[id];
				array->array[id] = array->array[ind];
				array->array[ind] = temp;
			}
		}
		Sleep(s);
	}
	SetEvent(event1);
	return 0;
}
int main() {
	event1 = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (event1 == NULL) {
		return GetLastError();
	}
	event2 = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (event2 == NULL) {
		return GetLastError();
	}
	InitializeCriticalSection(&cs);
	HANDLE hThread;
	DWORD IDThread;
	HANDLE hThread2;
	DWORD IDThread2;
	cout << "Input n:" << endl;
	int n;
	cin >> n;
	cout << "Input array:" << endl;
	char* arr = new char[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << "Size of the source array: " << n << endl;
	cout << "Elements of the source array: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << "Codes of the source array: ";
	for (int i = 0; i < n; i++) {
		cout << (int)arr[i] << " ";
	}
	cout << endl;
	int k;
	cout << "Input k" << endl;
	cin >> k;
	Array* array = new Array();
	array->array = arr;
	array->n = n;
	array->k = k;
	hThread = CreateThread(NULL, 0, work, (void*)array, 0, &IDThread);
	if (hThread == NULL) {
		return GetLastError();
	}
	hThread2 = CreateThread(NULL, 0, SumElement, (void*)array, 0, &IDThread2);
	if (hThread2 == NULL) {
		return GetLastError();
	}
	WaitForSingleObject(event1, INFINITE);
	cout << "New array up to k position:" << endl;
	for (int i = 0; i < array->k; i++) {
		cout << array->array[i] << " ";
	}
	cout << endl;
	SetEvent(event2);
	EnterCriticalSection(&cs);
	cout << "Arithmetic mean of character codes: ";
	cout << array->sum << endl;
	LeaveCriticalSection(&cs);
	WaitForSingleObject(hThread2, INFINITE);
	DeleteCriticalSection(&cs);
	cout << "Array elements starting from k position:" << endl;
	for (int i = k; i < array->n; i++) {
		cout << array->array[i] << " ";
	}
	cout << endl;
	CloseHandle(hThread);
	CloseHandle(hThread2);
}