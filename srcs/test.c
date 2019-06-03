#include <stdlib.h>
#include <stdio.h>
#include "../includes/ft_printf.h"
#include <limits.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>


/*int main(void)
{
	long_nbr_t a;
	long_nbr_t b;
	long_nbr_t res;
	a.nbr = malloc(1500 * sizeof(long long));
	b.nbr = malloc(1500 * sizeof(long long));
	int j = 0;
	while (j < 1500)
		a.nbr[j++] = 9;
	j = 0;
	while (j < 1500)
		b.nbr[j++] = 9;
	a.size = 1500;
	b.size = 1500;
	res = karatsuba(a, b);
	int i = res.size - 1;
	while (i >= 0)
		printf("%lld", res.nbr[i--]);
	return (0);
}
*/

void	print_nbr(long_nbr_t a)
{
	int i = a.size - 1;
	while (i >= 0)
		printf("%lld", a.nbr[i--]);
	printf("|||%lld|||\n", a.size);
}

int new = 0;

void		pass_zero(long_nbr_t *a)
{
	int i;

	i = (*a).size - 1;
	while (i >= 0 && (*a).nbr[i--] == 0)
		(*a).size--;
}

void	normalize(long_nbr_t *l)
{
	long long i;
	long long tmp;

	i = 0;
	while (i < ((*l).size - 1)) 
	{
		if ((*l).nbr[i] >= 10)
		{
			tmp = (*l).nbr[i] / 10;
			(*l).nbr[i + 1] += tmp;
			(*l).nbr[i] -= tmp * 10;
		}
		else if ((*l).nbr[i] < 0)
		{
			tmp = (((*l).nbr[i] + 1) / 10) - 1;
			(*l).nbr[i + 1] += tmp;
			(*l).nbr[i] -= tmp * 10;
		}
		++i;
	}
}

long_nbr_t	sum(long_nbr_t a, long_nbr_t b)
{
	long_nbr_t sum;
	int i;

	sum.size = a.size;
	sum.nbr = (long long *)malloc(sizeof(long long) * sum.size);
	ft_bzero(sum.nbr, sizeof(long long) * sum.size);
	printf("first operand\n");
	print_nbr(a);
	printf("second operand\n");
	print_nbr(b);
	if (a.size > b.size)
	{
		sum.size = a.size;
		sum.nbr = (long long *)malloc(sizeof(long long) * sum.size);
		i = -1;
		while (++i < a.size)
			sum.nbr[i] = a.nbr[i] + (i < b.size ? b.nbr[i] : 0);
	}
	else
	{
		sum.size = .size;
		sum.nbr = (long long *)malloc(sizeof(long long) * sum.size);
		i = -1;
		while (++i < b.size)
			sum.nbr[i] = b.nbr[i] + (i < a.size ? a.nbr[i] : 0);
	}
	normalize(&sum);
	return (sum);
}

void		multi(long_nbr_t a, long_nbr_t b, long_nbr_t *res)
{
	int i;
	int j;
	
	i = 0;
	printf("mult: 'a'\n");
	print_nbr(a);
	printf("at the 'b'\n");
	print_nbr(b);
	ft_bzero((*res).nbr, sizeof(long long) * (*res).size);
	while (i < a.size)
	{
		j = 0;
		while (j < b.size)
		{
			(*res).nbr[i + j] += a.nbr[i] * b.nbr[j];
			++j;
		}
		++i;
	}
}

long_nbr_t	*sub(long_nbr_t *a, long_nbr_t b)
{
	int i;

	i = -1;
	while (++i < b.size)
		(*a).nbr[i] -= b.nbr[i];
	return (a);
}

void	restore_parity(long_nbr_t *nbr, int size)
{
	long long *new_nbr;
	int i;
	int j;
	int z;

	new_nbr = (long long *)malloc(sizeof(long long) * ((*nbr).size + size));
	ft_bzero(new_nbr, sizeof(long long) * ((*nbr).size + size));
	i = 0;
	j = size;
	while (j--)
		new_nbr[i++] = 0;
	z = (*nbr).size - 1;
	while (z >= 0 && (*nbr).nbr[z] == 0)
		z--;
	j = 0;
	while (j <= z)
		new_nbr[i++] = (*nbr).nbr[j++];
	//free((*nbr).nbr);
	(*nbr).nbr = new_nbr;
	(*nbr).size += size;
}

void		compensation(long_nbr_t *a, int zero)
{
	long long *new_nbr;
	int i;
	int j;
	int z;

	new_nbr = (long long *)malloc(sizeof(long long) * ((*a).size - zero ));
	i = 0;
	j = 0;
	z = zero;
	while (zero--)
		j++;
	while (j <= (*a).size - 1)
		new_nbr[i++] = (*a).nbr[j++];
	free((*a).nbr);
	(*a).nbr = new_nbr;
	(*a).size -= z;
}

long_nbr_t karatsuba(long_nbr_t a, long_nbr_t b)
{
	long_nbr_t res;
	int zero;
	int flag;
	
	flag = 0;
	res.size = a.size + b.size;
	res.nbr = (long long *)malloc(sizeof(long long) * res.size);
	ft_bzero(res.nbr, sizeof(long long) * res.size);
	if (a.size != b.size && a.size == 20)
	{ 
		if (a.size > b.size)
		{
			zero = a.size - b.size;
			restore_parity(&b, a.size - b.size);
		}
		else
		{
			zero = b.size - a.size;
			restore_parity(&a, b.size - a.size);
		}
	}
	if (a.size < 4 || b.size < 4)
		multi(a, b, &res);
	else
	{
		//printf("hello\n");
		long_nbr_t a_l;
		a_l.nbr = a.nbr;
		a_l.size = (a.size + 1) / 2;
	//	printf("a_l\n");
	//	print_nbr(a_l);
		long_nbr_t a_r;
		a_r.nbr = a.nbr + a_l.size;
		a_r.size = a.size / 2;
	//	printf("a_r\n");
	//	print_nbr(a_r);
		long_nbr_t b_l;
		b_l.nbr = b.nbr;
		b_l.size = (b.size + 1) / 2;
	//	printf("b_l\n");
	//	print_nbr(b_l);
		long_nbr_t b_r;
		b_r.nbr = b.nbr + b_l.size;
		b_r.size = b.size / 2;
	//	printf("b_r\n");
	//	print_nbr(b_r);
		long_nbr_t mul1 = karatsuba(a_r, b_r);
		printf("mul1\n");
		print_nbr(mul1);
		long_nbr_t mul2 = karatsuba(a_l, b_l);
		printf("mul2\n");
		print_nbr(mul2);
		long_nbr_t mul3 = karatsuba(sum(a_l, a_r), sum(b_l, b_r));
		printf("--------\n");
		printf("sum1\n");
		print_nbr(sum(a_l, a_r));
		printf("sum2\n");
		print_nbr(sum(b_l, b_r));
		printf("--------\n");
		printf("mul333before substraction\n");
		print_nbr(mul3);
		sub(sub(&mul3, mul1), mul2);
		normalize(&mul3);
		printf("mul333\n");
		print_nbr(mul3);
		if (a.size == 20)
		{
			restore_parity(&mul1, a.size);
			restore_parity(&mul3, a.size / 2);
		}
	//	printf("mul3\n");
	//	print_nbr(mul3);
	//	printf("mul2\n");
	//	print_nbr(mul2);
	//	printf("mul1\n");
	//	print_nbr(mul1);
		res = sum(mul1, mul3);
		printf("res after first sum\n");
		print_nbr(res);
		res = sum(res, mul2);
		printf("res after second sum\n");
		print_nbr(res);
		if (a.size == 20)
			compensation(&res, zero);
		printf("\nres:\n");
		print_nbr(res);
		free(mul1.nbr);
		free(mul2.nbr);
		free(mul3.nbr);
	}
	normalize(&res);
	return (res);
}

int main(int argc, char **argv)
{
	//long double e;
	//int test;
	long_nbr_t test;
	test.nbr = (long long *)malloc(sizeof(long long) * 12);
	test.size = 12;
	test.nbr[0] = 6;
	test.nbr[1] = 9;
	test.nbr[2] = 2;
	test.nbr[3] = 7;
	test.nbr[4] = 6;
	test.nbr[5] = 9;
	test.nbr[6] = 4;
	test.nbr[7] = 9;
	test.nbr[8] = 2;
	test.nbr[9] = 4;
	test.nbr[10] = 3;
	test.nbr[11] = 4;
	long_nbr_t test2;
	test2.nbr = (long long *)malloc(sizeof(long long) * 20);
	test2.size = 20;
	test2.nbr[0] = 6;
	test2.nbr[1] = 9;
	test2.nbr[2] = 2;
	test2.nbr[3] = 7;
	test2.nbr[4] = 6;
	test2.nbr[5] = 9;
	test2.nbr[6] = 4;
	test2.nbr[7] = 9;
	test2.nbr[8] = 2;
	test2.nbr[9] = 4;
	test2.nbr[10] = 7;
	test2.nbr[11] = 0;
	test2.nbr[12] = 4;
	test2.nbr[13] = 4;
	test2.nbr[14] = 7;
	test2.nbr[15] = 6;
	test2.nbr[16] = 4;
	test2.nbr[17] = 4;
	test2.nbr[18] = 8;
	test2.nbr[19] = 1;
	long_nbr_t res;
	/*int i = test.size - 1;
	while (i >= 0)
		printf("%lld", test.nbr[i--]);
	printf("\n");
	i = test2.size - 1;
	while (i >= 0)
		printf("%lld", test2.nbr[i--]);*/
	printf("\n\n\n\n\n\n\n\n");
	res = karatsuba(test2, test);
	//normalize(&res);
	//int i = res.size - 1;
	//while (i >= 0)
	//	printf("%lld", res.nbr[i--]);
	/*e = 892347580723098457089374509872340895702389745212341234123481093745982374508972039847509827340895789234758072309845708923745098723408957023897452123412341234810937459823745089720398475098273408957892347580723098457089237450987234089570238974521234123412348109374598237450897203984750982734089578923475807230984570892374509872340895702389745212341234123481093745982374508972039847509827340895789234758072309845708923745098723408957023897452123412341234810937459823745089720398475098273408957892347580723098457089237450987234089570238974521234123412348109374598237450897203984750982734089578923475807230984570892374509872340895702389745212341234123481093745982374508972039847509827340895789234758072309845708923745098723408957023897452340895702389745.51L;
	test = ft_printf("{%Lf}", e);
	printf("      >>>>>      bytes = %d\n", test);
	printf("///%ld///", strlen("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));

	//printf("%d\n", count);
	test = printf("{%Lf}", e);
	printf("      >>>>>      bytes = %d\n", test);
	//printf("%d\n", count);*/
	return (0);
}
