# XOrCrypt
XOrCrypt is a lightweight Xorcrypt algorithm that uses chaining and bitwise array rotation.\
It was designed to be extremly light on resources and has little to no overhead,
as well as being very fast.\
It is also nativly compatible with 8-, 16-, 32- and 64-Bit CPU's

## How it works
-> Xor Plaintext-Block with Key-Block (return Ciphertext)
-> Xor Key-Block with Paintext-Block (using temporary copy of Plaintext-Block)
-> Bitwise array rotate Key
-> repeate until done

## Comment
I don't really know how good the protection/encryption exactly is (in statistical means),
but it should be pretty strong for an Xorcrypt algorithm and for the amount of code it requires.\
Because the Key gets xored with the Plaintext,
it's constantly chaning meaning that every Big Block of the Plain gets it's on pseudoKey.\
The rotation just add's an additional layer of protection by making it harder to reverse engineer
the Key using part of the Plaintext (if it is known or can be predicted),
this is achived by introducing an "offset" in the key.
