#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>

using namespace std;

void Create(char* FileName, int N, int min, int max) {
	FILE* f;
	if ((f = fopen(FileName, "wb")) == NULL) {
		cerr << "File open fails" << endl;
		exit(1);
	}
	int a;
	for (int i = 0; i < N; i++) {
		a = min + rand() % (max - min + 1);
		fwrite(&a, sizeof(int), 1, f);
	}
	cout << endl;
	fclose(f);
}

void Process(char* FileName, char* OddFileName, char* EvenFileName) {
	FILE* file, * file_odd, * file_even;
	if ((file = fopen(FileName, "rb")) == NULL) {
		cerr << "Can not open file " << FileName << endl;
		exit(1);
	}
	if ((file_odd = fopen(OddFileName, "wb")) == NULL) {
		cerr << "Can not open file " << OddFileName << endl;
		exit(1);
	}
	if ((file_even = fopen(EvenFileName, "wb")) == NULL) {
		cerr << "Can not open file " << EvenFileName << endl;
		exit(1);
	}
	int a = 0;

	while (!feof(file)) {
		fread(&a, sizeof(int), 1, file);
		if (a % 2 == 0) {
			fwrite(&a, sizeof(int), 1, file_odd);
		}
		else {
			fwrite(&a, sizeof(int), 1, file_even);
		}
	}
	fclose(file);
	fclose(file_odd);
	fclose(file_even);
}

void Print(char* FileName) {
	FILE* f;
	if ((f = fopen(FileName, "rb")) == NULL) {
		cerr << "File open fails" << endl;
		exit(1);
	}
	cout << "File name: " << FileName << endl;
	int a;
	while (!feof(f)) {
		fread(&a, sizeof(int), 1, f);
		cout << a << " ";
	}
	cout << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand((unsigned)time(NULL));
	int N = 20, min = 5, max = 100;
	char FileName[] = "input.txt";
	char OddFileName[] = "odd.txt";
	char EvenFileName[] = "even.txt";
	Create(FileName, N, min, max);
	Process(FileName, OddFileName, EvenFileName);
	Print(FileName);
	Print(OddFileName);
	Print(EvenFileName);
}
