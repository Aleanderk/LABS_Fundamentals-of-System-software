#pragma warning(disable : 4996) 
#include <iostream>
#include <fstream>
using std::cin;
using std::ofstream;
struct employee
{
	int num; // идентификационный номер сотрудника
	char name[10]; // имя сотрудника
	double hours; // количество отработанных часов
};
int main(int argc, char** argv) {	
	int n = strtol(argv[2], nullptr, 10);
	employee* arr = new employee[n];	
	for (int i = 0; i < n; i++) {
		employee temp;
		cin >> temp.num;
		cin >> temp.name;
		cin >> temp.hours;
		arr[i] = temp;
	}
	ofstream out;
	out.open(argv[1], ofstream::binary);
	for (int i = 0; i < n; i++) {
		out.write((const char*)&arr[i], sizeof(employee));
	}
	delete[] arr;
	return 0;
}