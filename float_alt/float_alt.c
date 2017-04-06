#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "float_alt.h"

int power(int x, int k)
{
	int i;
	int result = 1;
	for (i = 0; i < k; i++)
	{
		result *= x;
	}
	return result;
}

void fa_print(float_dt value, char *output)
{
	if (!output)
		return false;

	char format[MAX_PRECISION] = { 0 };
	sprintf(format, "%%d.%%0%dd", value.precision);
	sprintf(output, format, value.integer, value.fraction);
}

bool fa_from_float(float value, int precision, float_dt *result)
{
	if (!result)
		return false;

	result->integer = (int)(value);
	result->precision = precision;
	int f1 = (int)(value*power(10, precision));
	int f2 = (int)(((int)value)*power(10, precision));
	result->fraction = (int)(f1 - f2);

	return true;
}

bool fa_add(float_dt a, float_dt b, float_dt *result)
{
	int max_pres = a.precision > b.precision ? a.precision : b.precision;
	int temp_frac = 0;
	int multiplier = pow(10, max_pres);
	if (!result)
		return false;
	
	if (a.precision < b.precision) // 5.43 vs. 5.434
	{
		temp_frac = a.fraction * pow(10, (b.precision - a.precision));
		temp_frac += b.fraction;
		result->precision = b.precision;
	}
	else if (b.precision < a.precision)
	{
		temp_frac = b.fraction * pow(10, (a.precision - b.precision));
		temp_frac += a.fraction;
		result->precision = a.precision;
	}
	
	int carry = (temp_frac / multiplier)*multiplier;

	result->integer = a.integer + b.integer + (temp_frac / multiplier);
	result->fraction = temp_frac - carry;
	
	return true;
}

bool fa_sub(float_dt a, float_dt b, float_dt *result)
{
	int max_pres = a.precision > b.precision ? a.precision : b.precision;
	int multiplier = power(10, max_pres);

	if (!result)
		return false;

	if (a.precision < b.precision) // 5.43 vs. 5.434
	{
		a.fraction = a.fraction * pow(10, (b.precision - a.precision));
		result->precision = b.precision;
	}
	else if (b.precision < a.precision)
	{
		b.fraction = b.fraction * pow(10, (a.precision - b.precision));
		result->precision = a.precision;
	}

	result->integer = 0;
	result->fraction = a.fraction - b.fraction;
	if (result->fraction < 0)
		result->fraction *= -1;

	result->integer += a.integer - b.integer;

	return true;
}


bool fa_sub(float_dt a, float_dt b, float_dt *result)
{
	int max_pres = a.precision > b.precision ? a.precision : b.precision;
	int multiplier = power(10, max_pres);

	if (!result)
		return false;

	if (a.precision < b.precision) // 5.43 vs. 5.434
	{
		a.fraction = a.fraction * pow(10, (b.precision - a.precision));
		result->precision = b.precision;
	}
	else if (b.precision < a.precision)
	{
		b.fraction = b.fraction * pow(10, (a.precision - b.precision));
		result->precision = a.precision;
	}

	result->integer = 0;
	result->fraction = a.fraction - b.fraction;
	if (result->fraction < 0)
		result->fraction *= -1;

	result->integer += a.integer - b.integer;

	return true;
}
