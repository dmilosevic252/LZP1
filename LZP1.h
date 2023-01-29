#pragma once
class LZP1
{
private:
	const int HASH_POW = 12;
	const int HASH_SIZE = 1 << HASH_POW;
	int getHash(int x) { return ((x >> 11) ^ x) & 0xFFF; }
	char table[1<<12];
public:
	void encode(const char* loadPath, const char* savePath);
	void decode(const char* loadPath, const char* savePath);
};