#include <bits/stdc++.h>
#include <stdint.h>
#include "MD5.h"
#include "RSA.h"
#include "SHAMIR.h"

int main() {
	printf("\n-------------------- CONG TY TAO KHOA (RSA) --------------------\n");
	int n, e, d;
	crKeysRSA(&n, &e, &d);
	printf("\n\t=> KHOA CONG KHAI: n = %d, d = %d\n", n, d);
	printf("\t=> KHOA BI MAT: n = %d, e = %d\n", n, e);
	
	printf("\n-------------------- MA HOA KHOA BI MAT (SHAMIR) --------------------\n");
	int l = 5, k = 3, N[2][100], E[2][100];
	printf("\n- So lan chia nho: %d\n", l);
	printf("- Nguong giai ma: %d\n", k);
	enSHAMIR(n, l, k, N);
	
	enSHAMIR(e, l, k, E);
	printf("\n=> KHOA BI MAT:\n", n, e);
	printf("\tn = \n");
	for (int i = 0; i < l; i++) {
			printf("\t\t%d %d\n", N[0][i], N[1][i]);
	}
	printf("\te = \n");
	for (int i = 0; i < l; i++) {
			printf("\t\t%d %d\n", E[0][i], E[1][i]);
	}
	
	printf("\n-------------------- MA HOA THONG TIN HOP DONG (MD5) --------------------\n");
	const char *mess = "Ma hoa nguong";
	uint8_t hashCode[16];
	printf("\n- Noi dung hop dong: \"");
	for (int i = 0; i < strlen(mess); i++)
		printf("%c", *(mess+i));
	printf("\"\n");
	md5_hash((uint8_t *)mess, strlen(mess), hashCode);
	printf("\n\t=> MA BAM: \"");
	for (int i = 0; i < 16; i++)
        printf("%02x", hashCode[i]);
    printf("\"\n");
    
    printf("\n-------------------- GIAI MA KHOA RIENG TU (SHAMIR) --------------------\n");
    int g = 4; 
	double S_n, S_e;
	printf("\n- So luong cac phan da biet: %d\n", g);
	printf("\tn = \n");
	for (int i = 0; i < g; i++) {
			printf("\t\t%d %d\n", N[0][i], N[1][i]);
	}
	printf("\te = \n");
	for (int i = 0; i < g; i++) {
			printf("\t\t%d %d\n", E[0][i], E[1][i]);
	}
	deSHAMIR(g, N, S_n);
	deSHAMIR(g, E, S_e);
	printf("\n\t=> KHOA BI MAT: n = %.0f, e = %.0f\n", S_n, S_e);
	
	printf("\n-------------------- MA HOA MA BAM THONG TIN HOP DONG (RSA) --------------------\n");
	int R_hashCode[16];
	printf("\n- Khoa bi mat: n = %.0f, e = %.0f\n", S_n, S_e);
	printf("- Ma Bam: \"");
	for (int i = 0; i < 16; i++)
        printf("%02x", hashCode[i]);
    printf("\"\n");
    printf("\n\t=> RSA: \"");
	for (int i = 0; i < 16; i++) {
		R_hashCode[i] = enRSA(S_n, S_e, (int)hashCode[i]);
		printf("%d", R_hashCode[i]);
	}
	printf("\"\n");
	
	printf("\n-------------------- GIAI MA MA RSA THONG TIN HOP DONG (RSA) --------------------\n");
	uint8_t D_hashCode[16];
	printf("\n- Khoa cong khai: n = %d, d = %d\n", n, d);
	printf("- RSA: \"");
	for (int i = 0; i < 16; i++) {
		R_hashCode[i] = enRSA(S_n, S_e, (int)hashCode[i]);
		printf("%d", R_hashCode[i]);
	}
	printf("\"\n");
	printf("\n\t=> MA BAM (1): \"");
	for (int i = 0; i < 16; i++) {
		D_hashCode[i] = deRSA(n, d, R_hashCode[i]);
		printf("%02x", D_hashCode[i]);
	}
	printf("\"\n");
	return 0;
}
