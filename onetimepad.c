#include <stdio.h>

unsigned char rotate(unsigned char c, int count)
{
	int firstbit = c & (1 << 7);  //rememberfirstbit
	c &= ~(1 << 7);  // clearfirstbit

	c = (c >> count) | (c << (7-count));

	if (firstbit)
		c |= 1 << 7;  //setfirstbit
	else
		c &= ~(1 << 7); //clearfirstbit

	return c;
}

int bits(unsigned char c)
{
	int bitCount = 0;
	int i;
	for(i = 0; i < 8; ++i)
		if(c & (1 << i))  // check i-th bit
			++bitCount;
	return bitCount;
}

int main()
{
	unsigned char message[2048], key[2048];
	int messageLength, keyLength;


	int c;
	int i = 0;
	while ((c = getchar()) != 255)
		if (i < 2048)
			message[i++] = c;

	int j = 0;
	while ((c = getchar()) != EOF)
		if(j < 2048)
			key[j++] = c;

	messageLength = i;
	keyLength = j;

	//tiling
	int k;
	for(k = 0; k < messageLength; ++k)
		key[k] = key[k%keyLength];


	//chaining
	int sum = key[messageLength-1]%messageLength;
	int bit = bits(key[messageLength-1]);
	int m;
	for(m = 0; m < messageLength; ++m)
	{
		key[m] = rotate(key[m]^key[sum], bit);

		bit = bits(key[m]);
		sum += key[m];
		sum %= messageLength;
	}

	//xor-ing
	int l;
	for(l = 0; l < messageLength; ++l)
		putchar(message[l] ^ key[l]);

	return 0;
}
