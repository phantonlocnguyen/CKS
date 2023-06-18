int arrayContains(int array[][100], int size, int value) {
  for (int i = 0; i < size; i++) {
    if (array[0][i] == value) {
      return 1;
    }
    srand((unsigned int)time(NULL));
  }
  return 0;
}

long pow(int a, int b) {
	if (b == 0) return 1;
	return a*pow(a, b-1);
}

void CalcY(int A[], int B[][100], int k, int n) {
	int temp = A[0];
	for (int i = 1; i < k; i++)
		temp+=pow(B[0][n], i)*A[i];
	B[1][n] = temp;
}

void enSHAMIR(int S, int l, int k, int B[][100]) {
	srand((unsigned int)time(NULL));
	int A[k];
	A[0] = S;
	for (int i = 1; i < k; i++)
		A[i] = rand()%100 + 1;
	for (int i = 0; i < l; i++) {
		int randN = rand()%(l+10) + 1;
		do {
			randN = rand()%(l+10) + 1;
		} while (arrayContains(B, i, randN));
		B[0][i] = randN;
		CalcY(A, B, k, i);
	}
}

void deSHAMIR(int k, int B[][100], double &S) {
	double L[k];
	
	for (int i = 0; i < k; i++) {
		L[i] = B[1][i];
	}
	
	//Chay tim so bi mat bang Lagrange
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++)
			if (j != i) {
				//Tinh L(i)=y(i)*l(i)
				L[i] = (-L[i]*B[0][j])/(B[0][i] - B[0][j]);
			}
		//Tinh so bi mat
		S+=L[i];
	}
}
