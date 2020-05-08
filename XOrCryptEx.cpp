// XOrCryptEx.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <Windows.h>
#include <malloc.h>
#include "XOrCrypt.h"

// Random Generator for seeding and providing random data
static uint64_t s[5];
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
	uint64_t z = (s[4] += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

// #define MB 32036
#define MB 1048576
#define MUL 512


int main() {
	/* Seed Xoshiro //////// Used for debuging / tesing *///////////////////////////////
	s[4] = 18357827323532641321;
	for (int i = 0; i < 4; i++)
		s[i] = nextsm();

	// Random data stream
	void* data = (char*)malloc(MB * MUL);
	for (int i = 0; i < (MB * MUL) / 8; i++)
		((uint64_t*)data)[i] = next();

	// Copy for comparing
	void* data2 = (char*)malloc(MB * MUL);
	memcpy(data2, data, MB * MUL);

	/* Key *////////////////////////////////////////////////////////////////////////////
	void* key = (char*)malloc(256);
	memcpy(key, "dfawuziijdhag76cdv 2ubcaol25627b1necmnhbuw7a8bc9dw6v9w0adwrbc32657onrr"
		"g67c3b8oamnre6c3cobw672c gr5ohiabco682erc8b6t37c6377rlcwvk09ä0öv,ceg763nm9n8bw"
		"nad8wn6a7o823,8rm7923bv8r376bc7267n8rzxbga78nb28c6r8cnj2edcbbgm8,9l09xa9owcavn"
		"z2vrm87cgqm,xe9chi8vw3cr3vcted", 256);

	// Stream encryption
	for (int i = 0; i < MB / (1 << ((sizeof(_XC_DT) * 8) - 1)); i++)
		fnXOrEncrypt((void*)((uint32_t)data + (i * (1 << ((sizeof(_XC_DT) * 8) - 1)))),
			(1 << ((sizeof(_XC_DT) * 8) - 1)), key);
	fnXOrEncrypt((void*)((uint32_t)data + ((MB / (1 << ((sizeof(_XC_DT) * 8) - 1)))
		* (1 << ((sizeof(_XC_DT) * 8) - 1)))), MB % (1 << ((sizeof(_XC_DT) * 8) - 1)), key);

	// Encrypt and reset key
//	fnXOrEncrypt(data, MB * MUL, key);
	memcpy(key, "dfawuziijdhag76cdv 2ubcaol25627b1necmnhbuw7a8bc9dw6v9w0adwrbc32657onrr"
		"g67c3b8oamnre6c3cobw672c gr5ohiabco682erc8b6t37c6377rlcwvk09ä0öv,ceg763nm9n8bw"
		"nad8wn6a7o823,8rm7923bv8r376bc7267n8rzxbga78nb28c6r8cnj2edcbbgm8,9l09xa9owcavn"
		"z2vrm87cgqm,xe9chi8vw3cr3vcted", 256);

	// Decrypt
	for (int i = 0; i < MB / (1 << ((sizeof(_XC_DT) * 8) - 1)); i++)
		fnXOrDecrypt((void*)((uint32_t)data + (i * (1 << ((sizeof(_XC_DT) * 8) - 1)))),
			(1 << ((sizeof(_XC_DT) * 8) - 1)), key);
	fnXOrDecrypt((void*)((uint32_t)data + ((MB / (1 << ((sizeof(_XC_DT) * 8) - 1)))
		* (1 << ((sizeof(_XC_DT) * 8) - 1)))), MB % (1 << ((sizeof(_XC_DT) * 8) - 1)), key);

//	fnXOrDecrypt(data, MB * MUL, key);
	int a = memcmp(data, data2, MB * MUL);

	free(data);
	free(data2);
	free(key);

	return a;
}