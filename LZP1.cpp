#include "LZP1.h"
#include <fstream>
using namespace std;
void LZP1::encode(const char* loadPath, const char* savePath)
{
    int mask, i, j;
    char buf[8];
    unsigned int hash = 0;
    unsigned int triPrethodna = 0;
    char c;
    ifstream f;
    ofstream s;
    f.open(loadPath);
    s.open(savePath);
    if (!f.is_open()) return;
    if (!s.is_open()) return;
    while (!f.eof()) {
        j = 0;
        mask = 0;
        for (i = 0; i < 8 && !f.eof(); i++) {
            f.get(c);
            if (c == table[hash]) 
                mask |= 1 << i;
            else {
                table[hash] = c;
                buf[j++] = c;
            }
            triPrethodna = triPrethodna & 0x00FFFF;
            triPrethodna = triPrethodna << 8;
            triPrethodna += (int)c;
            hash = getHash(triPrethodna);
        }
        if (i > 0) {
            s.put((char)mask);
            for (int k = 0; k<j; k++)
                s.put(buf[k]);
        }
    }
    f.close();
    s.close();
}

void LZP1::decode(const char* loadPath,const char* savePath)
{
    int mask, i, j;
    char buf[8];
    unsigned int hash = 0;
    unsigned int triPrethodna = 0;
    char c;
    ifstream f;
    ofstream s;
    f.open(loadPath);
    s.open(savePath);
    if (!f.is_open()) return;
    if (!s.is_open()) return;
    while (!f.eof()) {
        j = 0;
        f.get(c);
        mask = (int)c;
        for (i = 0; i < 8 && !f.eof(); i++) {
            if ((mask & (1 << i)) != 0) 
                c = table[hash];
            else {
                f.get(c);
                table[hash] = c;
            }
            buf[j++]=c;
            triPrethodna = triPrethodna & 0x00FFFF;
            triPrethodna = triPrethodna << 8;
            triPrethodna += (int)c;
            hash = getHash(triPrethodna);
        }
        if (j > 0) {
            for (int k = 0; k < j; k++)
                s.put(buf[k]);
        }
    }
    f.close();
    s.close();
}
