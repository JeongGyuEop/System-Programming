#include <stdarg.h>
int add(int args, ...)
{
	int sum = 0;
	va_list ap;
	va_start(ap, args);
	for (int i =0; i < args; i++)
	{
		int num = va_arg(ap, int);
		sum += num;
	}
	va_end(ap);
	return sum;
}

int subtract(int args, ...)
{
	int sum = 0;
	va_list ap;
	va_start(ap, args);
	for(int i = 0; i < args; i++)
	{
		int num = va_arg(ap, int);
		if(i==0)
			sum = num;
		else
			sum -= num;
	}
	va_end(ap);
	return sum;
}

int multiply(int args, ...)
{
	int sum = 0;
	va_list ap;
	va_start(ap, args);
	for(int i = 0; i < args; i++)
	{
		int num = va_arg(ap, int);
		if(i==0)
			sum = num;
		else
			sum *= num;
	}
	va_end(ap);
	return sum;
}

int divide(int args, ...)
{
	int sum = 0;
	va_list ap;
	va_start(ap, args);
	for(int i = 0; i < args; i++)
	{
		int num = va_arg(ap, int);
		if(i==0)
			sum = num;
		else
			sum /= num;
	}
	va_end(ap);
	return sum;
}

