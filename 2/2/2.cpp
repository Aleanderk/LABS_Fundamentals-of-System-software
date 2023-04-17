#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <process.h>
#include <Windows.h>
#include <conio.h>
#include <fstream>
struct employee
{
	int num; // идентификационный номер сотрудника
	char name[10]; // имя сотрудника
	double hours; // количество отработанных часов
};
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;
using std::fstream;
using std::ifstream;
using std::ofstream;
int main() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	string fileName;
	cout << "Name of the file:" << endl;
	cin >> fileName;
	cout << "Num of notices:" << endl;
	int n;
	cin >> n;
	string fileName1 = fileName + " " + to_string(n);
	string sCreator = "Creator.exe";
	sCreator = sCreator + " " + fileName1;
	const char* Creator = sCreator.c_str();
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, Creator, -1, wString, 4096);
	CreateProcess(NULL, wString, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	ifstream in;
	in.open(fileName, fstream::binary);
	employee* arr = new employee[n];
	for (int i = 0; i < n; i++) {
		in.read((char*)&arr[i], sizeof(employee));
	}
	for (int i = 0; i < n; i++) {
		cout << arr[i].num << " " << arr[i].name << " " << arr[i].hours << endl;
	}
	string fileName2;
	cout << "Input the name of report file:" << endl;
	cin >> fileName2;
	int sum;
	cout << "Input the payment per hour of work:" << endl;
	cin >> sum;
	string sReporter = "Reporter.exe";
	sReporter += " " + fileName + " " + fileName2 + " " + to_string(sum);
	const char* Reporter = sReporter.c_str();
	wchar_t* wString1 = new wchar_t[4096];
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	MultiByteToWideChar(CP_ACP, 0, Reporter, -1, wString1, 4096);
	CreateProcess(NULL, wString1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	ifstream in1;
	in1.open(fileName2);
	string nameofthefile;
	in1 >> nameofthefile;
	cout << nameofthefile << endl;
	for (int i = 0; i < n; i++) {
		employee temp;
		in1 >> temp.num >> temp.name >> temp.hours;
		double salary;
		in1 >> salary;
		cout << temp.num << " " << temp.name << " " << temp.hours << " " << salary << endl;
	}
	delete[] arr;
	delete[] wString;
	return 0;
}