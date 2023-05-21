#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;
int main()
{
	int n;
	cout << "Input size of the array:" << endl;
	cin >> n;
	__int8* arr = new __int8[n];
	srand(time(0));
	for (int i = 0; i < n; i++) {
		arr[i] = '0' + rand() % ('z' - '0');
	}
	char lpszComLine[80];
	HANDLE hRead2;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hWritePipe, hReadPipe;
	SECURITY_ATTRIBUTES sa;
	hRead2 = CreateEvent(NULL, FALSE, FALSE, "Read2");
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
	{
		_cputs("Create pipe failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	wsprintf(lpszComLine, "Sort.exe %d %d", (int)hWritePipe, (int)hReadPipe);
	if (!CreateProcess(NULL, lpszComLine, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		_cputs("Create process failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	DWORD dwBytesWritten;
	if (!WriteFile(hWritePipe, &n, sizeof(n), &dwBytesWritten, NULL))
	{
		_cputs("Write to file failed.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	WriteFile(hWritePipe, arr, sizeof(__int8)*n, &dwBytesWritten, NULL);
	__int8* arr1 = new __int8[n];
	DWORD dwBytesRead;
	WaitForSingleObject(hRead2, INFINITE);
	cout << "Transmitted information:" << endl;
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << "Received information:" << endl;
	for (int i = 0; i < n; i++) {
		if (!ReadFile(hReadPipe, &arr1[i], sizeof(__int8), &dwBytesRead, NULL))
		{
			_cputs("Read from the pipe failed.\n");
			_cputs("Press any key to finish.\n");
			_getch();
			return GetLastError();
		}
		cout << arr1[i] << " ";
	}
	cout << endl;
	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	CloseHandle(hRead2);
	return 0;
}