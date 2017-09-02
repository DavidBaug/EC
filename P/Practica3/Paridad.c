#define TEST 0
#define COPY_PASTE_CALC 0

#if ! TEST
#define NBITS 20
#define SIZE (1<<NBITS)
unsigned lista[SIZE];
#define RESULT 10485760
#else
#define SIZE 8
unsigned lista[SIZE] = {0x80000000, 0x00100000, 0x00000800, 0x00000001};
unsigned lista[SIZE] = {0x7fffffff, 0xffefffff, 0xfffff7ff, 0xfffffffe, 0x01000024,
	0x00356700, 0x8900ac00, 0x00bd00ef};
#endif

#include <stdio.h>      // para printf()
#include <stdlib.h>     // para exit()
#include <sys/time.h>   // para gettimeofday(), struct timeval
#define WSIZE 8*sizeof(int)
#define SIZE (1<<20)  // tamaño suficiente para tiempo apreciable
unsigned lista[SIZE]; // = { 0x01010101 }; // 0x00000003, 0x00000003};
int resultado = 0;

int paridad1(unsigned* array, int len)
{
	int i, j;
	int paridad;
	unsigned entero;
	int result = 0;

	for (i = 0; i < len; i++) {
		paridad = 0;
		entero = array[i];
		for (j = 0; j < WSIZE; j++) {
			paridad ^= (entero & 1);
			entero >>= 1;
		}
		result += paridad & 0x01;
	}
	return result;
}

int paridad2(unsigned* array, int len) {
	int i;
	int paridad;
	unsigned entero;
	int result = 0;

	for (i = 0; i < len; i++) {
		paridad = 0;
		entero = array[i];
		while (entero) {
			paridad ^= (entero & 1);
			entero >>= 1;
		}
		result += paridad & 0x1;
	}
	return result;
}

/*
 * Versión C de CS:APP Ejercicio 3.22
 */
int paridad3(unsigned* array, int len) {

	int val = 0;
	int i;
	unsigned x;
	int result = 0;
	for (i = 0; i < len; i++) {
		x = array[i];
		while (x) {
			val ^= x;
			x >>= 1;
		}
		result += val & 0x1;
	}
	return result;

}

/*
 * Versión C de CS:APP Ejercicio 3.22 (Traduciendo while)
 */
int paridad4(unsigned* array, int len) {

	int val;
	int i;
	unsigned x;
	int result = 0;

	for (i = 0; i < len; i++) {
		x = array[i];
		val = 0;
		asm(
				"ini3:						\n\t"
				"xor %[x], %[v]			\n\t"
				"shr $1, %[x]			\n\t"
				"test %[x], %[x]        \n\t"
				"jnz ini3				\n\t"
				: [v]"+r"(val)
				: [x]"r"(x)
		);
		result += val & 0x1;
	}
	return result;

}

/**
 * Sumando en árbol
 */
int paridad5(unsigned* array, int len) {

	int i, k;
	int result = 0;
	unsigned x;
	for (i = 0; i < len; i++) {
		x = array[i];
		for (k = 16; k == 1; k /= 2)
			x ^= x >> k;
		result += (x & 0x01);
	}
	return result;

}

int paridad6(unsigned* array, int len) {
	int j;
	unsigned entero = 0;


	int resultado = 0;

	for (j = 0; j < len; j++)
	{
		entero = array[j]; 
		asm(
				"mov	%[x], 	%%edx		\n\t"
				"shr	$16,	%%edx		\n\t"
				"xor	%[x],	%%edx		\n\t"
				"xor	%%dh,	%%dl		\n\t"
				"setpo  %%dl				\n\t"
				"movzx	%%dl,	%[x]		\n\t"
				: [x] "+r" (entero) // input
				:
				: "edx"//Clobber
		);
		resultado += entero;
	}
	return resultado;
}

void crono(int (*func)(), char* msg) {
	struct timeval tv1, tv2;
	long tv_usecs;

	gettimeofday(&tv1, NULL);
	resultado = func(lista, SIZE);
	gettimeofday(&tv2, NULL);

	tv_usecs = (tv2.tv_sec - tv1.tv_sec) * 1E6 + (tv2.tv_usec - tv1.tv_usec);
#if ! COPY_PASTE_CALC
	printf("resultado = %d\t", resultado);
	printf("%s:%9ld us\n", msg, tv_usecs);
#else
	printf("%9ld us\n", tv_usecs);
#endif
}

int main() {
#if ! TEST
	int i;
	for (i = 0; i < SIZE; i++)
		lista[i] = i;
#endif
	int j=0;
	for(j; j<11; j++){
	crono(paridad1, "Paridad1 (    en lenguaje C for  )");
	crono(paridad2, "Paridad2 (    en lenguaje C whi  )");
	crono(paridad3, "Paridad3 (Ejemplo CS:APP Ej: 3.22)");
	crono(paridad4, "Paridad4 (Traducción bucle While )");
	crono(paridad5, "Paridad5 (      Suma en árbol    )");
	crono(paridad6, "Paridad6 (Bucle interno con setpe)");
	}exit(0);
}
