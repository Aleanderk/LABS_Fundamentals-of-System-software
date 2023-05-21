#pragma warning(disable : 4996)
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <iostream>
#include <string>
using namespace std;
int main() {
	HANDLE A, B, endParent, endChild;
	A = CreateEvent(NULL, FALSE, FALSE, "A");
	if (A == NULL) {
		return GetLastError();
	}
	B = CreateEvent(NULL, FALSE, FALSE, "B");
	if (B == NULL) {
		return GetLastError();
	}
	endParent = CreateEvent(NULL, FALSE, FALSE, "endParent");
	if (endParent == NULL) {
		return GetLastError();
	}
	endChild = CreateEvent(NULL, FALSE, FALSE, "endChild");
	if (endChild == NULL) {
		return GetLastError();
	}	
	string ParentProcessName = "Parent.exe";
	string ChildProcessName = "Child.exe";
	int numChildProcess, numParentProcess, numMessageChildProcess, numMessageParentProcess;
	cout << "Input num of the Parent processes: ";
	cin >> numParentProcess;
	cout << "Input num of the Child processes: ";
	cin >> numChildProcess;
	cout << "Input num of the messages from Parent processes: ";
	cin >> numMessageParentProcess;
	cout << "Input num of the messages from Child processes: ";
	cin >> numMessageChildProcess;
	HANDLE* Childs = new HANDLE[numChildProcess];
	HANDLE* Parents = new HANDLE[numParentProcess];
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	string connect;
	connect = ParentProcessName + " " + to_string(numMessageParentProcess);
	char* con = new char[connect.size()+1];
	con = strcpy(con, connect.c_str());
	for (int i = 0; i < numParentProcess; i++) {
		if (!CreateProcess(NULL, con, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
		{
			_cputs("The new process is not created.\n"); // Эти три штуки были и в методичках, поэтому решил не менять, но по-большому счету можно заменить к примеру на 
			_cputs("Check a name of the process.\n"); // cout << "Error"; или вообще убрать.
			_cputs("Press any key to finish.\n");
			return 0;
		}
		Parents[i] = piApp.hProcess;
	}
	string connect1;
	connect1 = ChildProcessName + " " + to_string(numMessageChildProcess);
	char* con1 = new char[connect1.size() + 1];
	con1 = strcpy(con, connect1.c_str());
	for (int i = 0; i < numChildProcess; i++) {
		if (!CreateProcess(NULL, con1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
		{
			_cputs("The new process is not created.\n");
			_cputs("Check a name of the process.\n");
			_cputs("Press any key to finish.\n");
			return 0;
		}
		Childs[i] = piApp.hProcess;
	}
	HANDLE mass[] = {A, B};
	for (int i = 0; i < numParentProcess * numMessageParentProcess+numChildProcess*numMessageChildProcess; i++)
	{
		int ind = WaitForMultipleObjects(2, mass, FALSE, INFINITE) - WAIT_OBJECT_0;
		if (ind == 0)
		{
			cout << "Get message A from process Parent." << endl;
		}
		if (ind == 1)
		{
			cout << "Get message B from process Child." << endl;
		}
	}
	for (int i = 0; i < numChildProcess; i++)
	{
		SetEvent(endChild);
	}
	for (int i = 0; i < numParentProcess; i++)
	{
		SetEvent(endParent);
	}
	CloseHandle(A);
	CloseHandle(B);
	CloseHandle(endParent);
	CloseHandle(endChild);
	for (int i = 0; i < numChildProcess; i++)
	{
		CloseHandle(Childs[i]);
	}
	for (int i = 0; i < numParentProcess; i++)
	{
		CloseHandle(Parents[i]);
	}
	return 0;
}