#include <stdio.h>
#include "float_alt.h"

int main(void)
{
	char outbuf[1024];

	float vf1 = 3.456;
	float vf2 = 7.6945;

	float_dt v1, v2, v3;

	if (!fa_from_float(vf1, 3, &v1))
	{
		printf("float conversion error\n");
	}
	if (!fa_from_float(vf2, 4, &v2))
	{
		printf("float conversion error\n");
	}

	fa_print(v1, outbuf);
	printf("v1: %s\n", outbuf);

	fa_print(v2, outbuf);
	printf("v1: %s\n", outbuf);

	memset(&v3, 0, sizeof(v3));

	if (!fa_sub(v1, v2, &v3))
	{
		printf("float add error\n");
	}
	
	fa_print(v3, outbuf);
	printf("v3: %s\n", outbuf);

	return 0;
}