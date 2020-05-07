// XOrCryptEx.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <Windows.h>
#include <malloc.h>

void XOrCryptE(void* pData, int nDatalen, void* key) {
	char x;
	for (int i = 0; i < nDatalen / 32; i++) {
		for (int j = 0; j < 32; j++) {
			x = ((char*)pData)[(i * 32) + j];
			((char*)pData)[(i * 32) + j] ^= ((char*)key)[j];
			((char*)key)[j] ^= x;
		}
	} for (int j = 0; j < nDatalen % 32; j++) {
		((char*)pData)[((nDatalen / 32) * 32) + j] ^= ((char*)key)[j];
	}
}

void XOrCryptD(void* pData, int nDatalen, void* key) {
	for (int i = 0; i < nDatalen / 32; i++) {
		for (int j = 0; j < 32; j++) {
			((char*)pData)[(i * 32) + j] ^= ((char*)key)[j];
			((char*)key)[j] ^= ((char*)pData)[(i * 32) + j];
		}

	} for (int j = 0; j < nDatalen % 32; j++) {
		((char*)pData)[((nDatalen / 32) * 32) + j] ^= ((char*)key)[j];
	}
}

int main() {
	// Test New 2
	void* data = (char*)malloc(100);
	memcpy(data, "Hello, this is a test to prove a concept of XorCrypt\nIt has now been extendet to test it fully", 95);
	void* key = (char*)malloc(32);
	memcpy(key, "5623321233257612323762163715637", 32);

	XOrCryptE(data, 95, key);
	memcpy(key, "5623321233257612323762163715637", 32);
	XOrCryptD(data, 95, (char*)key);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file