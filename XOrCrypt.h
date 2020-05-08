#ifndef _XC_HIG
#define _XC_HIG

/* Header Files needed for XOrCrypt+ */
#include <stdint.h>

/*
    Defines the size of the Key in BITS.
    Has to be atleast a multiple of the current selected DataType size.
    e.g. on x64 (8-Bytes) : atleast KEY_SIZE = 64
            x86 (4-Bytes) :         KEY_SIZE = 32

    KEY_SIZE is limited to a maximum size of (((2^8) * 8) * (BlockSize / 8))
    e.g. on x64 (8-Bytes) : atmost KEY_SIZE = 16.384
            x86 (4-Bytes) :        KEY_SIZE =  8.192
*/
#define _XC_KEYSIZE 2048

/*
    Defines the size of a single Block in BITS.
    This option defines what DataType to use depending on the choosen BlockSize.
    You should match this to the size of your target architecture.
    e.g. on x64 (8-Bytes) : BLOCK_SIZE = 64
            x86 (4-Bytes) : BLOCK_SIZE = 32
*/
#define _XC_BLOCKSIZE 8

/////////////////////////////////////////////////////////////////////////////////////

#if _XC_BLOCKSIZE == 64
    #define _XC_DT uint64_t
#elif _XC_BLOCKSIZE == 32
    #define _XC_DT uint32_t
#elif _XC_BLOCKSIZE == 16
    #define _XC_DT uint16_t
#elif _XC_BLOCKSIZE == 8
    #define _XC_DT uint8_t
#endif

/////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif
    /* Function Declarations */
    void fnXOrEncrypt(void* pData, _XC_DT nDataLen, void* pKey);
    void fnXOrDecrypt(void* pData, _XC_DT nDataLen, void* pKey);

#ifdef __cplusplus
}
#endif
#endif