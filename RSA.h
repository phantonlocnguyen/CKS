int checkPrime(int n){
	for(int i = 2; i <= sqrt(n); i++)
		if(n % i == 0) return 0;
	return 1;
}

int GCD(int a, int b) {
	if(b == 0) return a;
	else return GCD(b, a%b);
}

void exEuler(int a, int b, int *x, int *y) {
    int xa = 1, xb = 0, ya = 0, yb = 1;
    int q, r, xr, yr;
    while (b != 0) {
        q = a / b;
        r = a % b;
        a = b;
        b = r;
        xr = xa - q * xb;
        yr = ya - q * yb;
        xa = xb;
        xb = xr;
        ya = yb;
        yb = yr;
    }
    *x = xa;
    *y = ya;
}

int powMod(int x, int n, int m) {
    int p;
	if (n == 0) return 1;
	p = powMod(x, n/2, m);
	if (n%2 == 0) return (p * p) % m;
	else return (p * p * x) % m;
}

void crKeysRSA(int *n, int *e, int *d) {
	srand((unsigned int)time(NULL));
	int p, q, x, y, phi_n;
	do {
		p = rand()%100;
		q = rand()%100;
		*n = p * q;
	} while (!checkPrime(p) || !checkPrime(q) || p == q || *n < 200 || *n > 500);
	printf("\n- p = %d, q = %d\n", p, q);
	printf("- n = p * q = %d\n", *n);
	phi_n = (p - 1) * (q - 1);
	printf("- phi_n = %d\n", phi_n);
	do {
		*e = rand();
	} while( *e <= 1 || *e >= phi_n || GCD(*e, phi_n) != 1);
	exEuler(*e, phi_n, &x, &y);
	if(x < 0)
		x += phi_n;
	*d = x;
	printf("- e = %d, d = %d\n", *e, *d);
}

int enRSA(int n, int e, int m) {
	return powMod(m, e, n);
}

int deRSA(int n, int d, int c) {
	return powMod(c, d, n);
}
