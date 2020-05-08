#include "XOrCrypt.h"

static inline void fnRoAL(void* pKey) {
	uint8_t bX = ((_XC_DT*)pKey)[0] >> ((sizeof(_XC_DT) * 8) - 1);
	for (uint8_t i = 0; i < (((_XC_KEYSIZE / 8) / sizeof(_XC_DT)) - 1); i++) {
		((_XC_DT*)pKey)[i] <<= 1;
		((_XC_DT*)pKey)[i] |= ((_XC_DT*)pKey)[i + 1] >> ((sizeof(_XC_DT) * 8) - 1);
	}

	((_XC_DT*)pKey)[((_XC_KEYSIZE / 8) / sizeof(_XC_DT)) - 1] <<= 1;
	((_XC_DT*)pKey)[((_XC_KEYSIZE / 8) / sizeof(_XC_DT)) - 1] |= bX;
}

void fnXOrEncrypt(void* pData, _XC_DT nDataLen, void* pKey) {
	for (_XC_DT i = 0; i < (nDataLen / sizeof(_XC_DT)); i++) {
		_XC_DT nX = ((_XC_DT*)pData)[i];
		((_XC_DT*)pData)[i] ^= ((_XC_DT*)pKey)[i % ((_XC_KEYSIZE / 8) / sizeof(_XC_DT))];
		((_XC_DT*)pKey)[i % ((_XC_KEYSIZE / 8) / sizeof(_XC_DT))] ^= nX;
		fnRoAL(pKey);
	}
}
void fnXOrDecrypt(void* pData, _XC_DT nDataLen, void* pKey) {
	for (_XC_DT i = 0; i < nDataLen / sizeof(_XC_DT); i++) {
		((_XC_DT*)pData)[i] ^= ((_XC_DT*)pKey)[i % ((_XC_KEYSIZE / 8) / sizeof(_XC_DT))];
		((_XC_DT*)pKey)[i % ((_XC_KEYSIZE / 8) / sizeof(_XC_DT))] ^= ((_XC_DT*)pData)[i];
		fnRoAL(pKey);
	}
}