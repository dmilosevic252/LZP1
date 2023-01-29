#include <iostream>
#include "LZP1.h"
#include <chrono>
using namespace std;
void main() {
	LZP1* l = new LZP1();
	const char* test[] = { "Lorem.txt","Bible.txt","Pi.txt","Enwik8.txt" };
	const char* comp[] = { "LoremC.txt","BibleC.txt","PiC.txt","Enwik8C.txt" };
	const char* dcmp[] = { "LoremD.txt","BibleD.txt","PiD.txt","Enwik8D.txt" };
	for (int i = 0; i < 4; i++) {
		auto start = chrono::steady_clock::now();
		l->encode(test[i], comp[i]);
		auto end = chrono::steady_clock::now();
		auto startDec = chrono::steady_clock::now();
		l->decode(comp[i], dcmp[i]);
		auto endDec = chrono::steady_clock::now();
		cout << "Vreme kompresovanja: "
			<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
			<< " ms" << endl;
		cout << "Vreme dekompresovanja: "
			<< chrono::duration_cast<chrono::milliseconds>(endDec - startDec).count()
			<< " ms" << endl;
	}
}