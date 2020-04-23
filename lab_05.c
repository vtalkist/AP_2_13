#include <stdio.h>
#include <stdarg.h>

//#define my_va_start(list, param) (list = (((va_list)&param) + sizeof(param)))
//#define my_va_arg(list, type) (*(type *)((list += sizeof(type)) - sizeof(type)))

double sum1(int n, ...);
//double sum2(double first, ...);
double sum3(double num, ...);
double sum4(char *type, ...);

double sum1(int n, ...)
{
	int *p = &n;
	double even_sum = 1, odd_sum = 1, *pp = (double *)++p;
	for (int i = 1; n--; i++, pp++)
	{
		if (i & 1)
			odd_sum *= (*pp);
		else
			even_sum *= (*pp);
	}

	return odd_sum - even_sum;
}

//double sum2(double first, ...)
//{
//	double even_sum = 1, odd_sum = 1, *pp = &first;
//	for (int i = 1; (int)*pp; i++, pp++)
//	{
//		if (i & 1)
//			odd_sum *= (*pp);
//		else
//			even_sum *= (*pp);
//	}
//	return odd_sum - even_sum;
//}

double sum3(double num, ...)
{
	double even_sum = 1, odd_sum = 1;
	va_list args;
	va_start(args, num);
	for (int i = 1; num--; i++)
	{
		if (i & 1)
			odd_sum *= va_arg(args, double);
		else
			even_sum *= va_arg(args, double);
	}
	va_end(args);
	return odd_sum - even_sum;
}


double sum4(char *type, ...)
{
	char * type_pointer = (char*)&type;
	double even_sum = 1, odd_sum = 1;
	type_pointer += 4;
	for (int i = 1; *(char*)type != 0; i++, type++)
	{
		switch (*(char*)type)
		{
		case 'i':
			if (i & 1)
				odd_sum *= *(int*)type_pointer;
			else
				even_sum *= *(int*)type_pointer;
			type_pointer += sizeof(int);
			break;
		case 'd':
			if (i & 1)
				odd_sum *= *(double*)type_pointer;
			else
				even_sum *= *(double*)type_pointer;
			type_pointer += sizeof(double);
			break;
		}
	}
	return odd_sum - even_sum;
}

//double sum5(double num, ...)
//{
//	double even_sum = 1, odd_sum = 1;
//	va_list args;
//	my_va_start(args, num);
//	for (int i = 1; num--; i++)
//	{
//		if (i & 1)
//			odd_sum *= my_va_arg(args, double);
//		else
//			even_sum *= my_va_arg(args, double);
//	}
//	va_end(args);
//	return odd_sum - even_sum;
//}

void main() {
	printf("summ = %lf\n", sum1(5, 1.25, 2.35, 3.44, 4.75, 5.85));
	//printf("summ = %lf\n", sum2(1.25, 2.35, 3.44, 4.75, 5.85, 0));
	printf("summ = %lf\n", sum1(5, 1.25, 2.35, 3.44, 4.75, 5.85));
	printf("summ = %lf\n", sum4("ddddd", 1.25, 2.35, 3.44, 4.75, 5.85));
	system("pause");
}
