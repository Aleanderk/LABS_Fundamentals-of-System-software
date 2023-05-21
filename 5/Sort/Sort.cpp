#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	HANDLE hWritePipe, hReadPipe;
	HANDLE hRead2;
	hRead2 = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Read2");
	hWritePipe = (HANDLE)atoi(argv[1]);
	hReadPipe = (HANDLE)atoi(argv[2]);
	int n;
	DWORD dwBytesRead;
	if (!ReadFile(hReadPipe, &n, sizeof(n), &dwBytesRead, NULL))
	{
		_cputs("Read from the pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	__int8* arr = new __int8[n];
	if (!ReadFile(hReadPipe, arr, sizeof(__int8)*n, &dwBytesRead, NULL)) {
		_cputs("Read from the pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}	
	DWORD dwBytesWritten;
	//Сортировка выбором
	for (int id = 0; id < n; id++) {
		__int8 temp = arr[0];
		for (int ind = id + 1; ind < n; ind++) {
			if (arr[id] > arr[ind]) {
				temp = arr[id];
				arr[id] = arr[ind];
				arr[ind] = temp;
			}
		}
	}
	cout << "Sorted array:" << endl;
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
		if (!WriteFile(hWritePipe, &arr[i], sizeof(__int8), &dwBytesWritten, NULL))
		{
			_cputs("Write to file failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
	}
	cout << endl;
	SetEvent(hRead2);
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hRead2);
	system("pause");
	return 0;
}