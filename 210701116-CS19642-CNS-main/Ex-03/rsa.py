#include <math.h>
#include <stdio.h>


long long int power(long long int a, long long int b, long long int P)
{
	if (b == 1)
		return a;
	else
		return (((long long int)pow(a, b)) % P);
}

int main()
{
	long long int P, G, x, a, y, b, ka, kb;

	printf("Enter the value of P [A prime number]: ");
	scanf("%lld", &P);

	printf("Enter the value of G [Primitive root of P] : ");
	scanf("%lld", &G);

	printf("Enter sender's private key : ");
	scanf("%lld", &a);
	x = power(G, a, P);

	printf("Enter recipient's private key : ");
	scanf("%lld", &b);
	y = power(G, b, P);

	ka = power(y, a, P); 
	kb = power(x, b, P);

    if(ka == kb) {
    	printf("The Shared Secret is : %lld\n", ka);
    }

	return 0;
}

