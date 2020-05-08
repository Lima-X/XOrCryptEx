// XOrCryptEx.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <Windows.h>
#include <malloc.h>
#include "XOrCrypt.h"

// Random Generator for seeding and providing random data
static uint64_t s[4];
static uint64_t x;
static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}
uint64_t next(void) {
	const uint64_t result = rotl(s[1] * 5, 7) * 9;
	const uint64_t t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];
	s[2] ^= t;
	s[3] = rotl(s[3], 45);

	return result;
}
uint64_t nextsm() {
	uint64_t z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

#define MB 32000
//#define MB 1048576
#define MUL 1

int main() {
	// Seed
	x = 18357827323532641321;
	for (int i = 0; i < 4; i++)
		s[i] = nextsm();

	// Random data stream
	void* data = (char*)malloc(MB * MUL);
	for (int i = 0; i < (MB * MUL) / 8; i++)
		((uint64_t*)data)[i] = next();

	// Copy for comparing
	void* data2 = (char*)malloc(MB * MUL);
	memcpy(data2, data, MB * MUL);

	// Key
	void* key = (char*)malloc(256);
	memcpy(key, "dfawuziijdhag76cdv 2ubcaol25627b1necmnhbuw7a8bc9dw6v9w0adwrbc32657onrr"
		"g67c3b8oamnre6c3cobw672c gr5ohiabco682erc8b6t37c6377rlcwvk09ä0öv,ceg763nm9n8bw"
		"nad8wn6a7o823,8rm7923bv8r376bc7267n8rzxbga78nb28c6r8cnj2edcbbgm8,9l09xa9owcavn"
		"z2vrm87cgqm,xe9chi8vw3cr3vcted", 256);


	for (int i = 0; i < MB / 128; i++) {
		fnXOrEncrypt((void*)((uint64_t)data + (i * 128)), 128, key);
	}
	fnXOrEncrypt((void*)((uint64_t)data + ((MB / 128) * 128)), MB % 128, key);

	// Encrypt and reset key
//	fnXOrEncrypt(data, MB * MUL, key);
	memcpy(key, "dfawuziijdhag76cdv 2ubcaol25627b1necmnhbuw7a8bc9dw6v9w0adwrbc32657onrr"
		"g67c3b8oamnre6c3cobw672c gr5ohiabco682erc8b6t37c6377rlcwvk09ä0öv,ceg763nm9n8bw"
		"nad8wn6a7o823,8rm7923bv8r376bc7267n8rzxbga78nb28c6r8cnj2edcbbgm8,9l09xa9owcavn"
		"z2vrm87cgqm,xe9chi8vw3cr3vcted", 256);

	// Decrypt
	for (int i = 0; i < MB / 128; i++) {
		fnXOrDecrypt((void*)((uint64_t)data + (i * 128)), 128, key);
	}
	fnXOrDecrypt((void*)((uint64_t)data + ((MB / 128) * 128)), MB % 128, key);

//	fnXOrDecrypt(data, MB * MUL, key);

	int a = memcmp(data, data2, MB * MUL);

	free(data);
	free(data2);
	free(key);

	return a;
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