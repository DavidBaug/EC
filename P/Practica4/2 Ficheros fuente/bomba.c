#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()/strlen()
#include <sys/time.h>	// para gettimeofday(), struct timeval

char jaje[]={72,72,102,98,116,122};
int  jeja  = 0220;

void jeje(){
	printf("***************\n");
	printf("*** BOOM!!! ***\n");
	printf("***************\n");
	exit(-1);
}

void jaja(){
	jeje();
}

void jiji(){
	printf("*************************\n");
	printf("*** bomba desactivada ***\n");
	printf("*************************\n");
	exit(0);
}

void juji(){
	int x, w, k, p;
	p = 0;
	k =1;

	for (x = 0; x < 30; x++){
		for (w = 0; w < 40; w++){
			k = k*2;
		}
	}

	if(p == 3){
		printf("Esto no hace nada pero es para molestar :D... %d \n",k);
		exit(0);
	}else
		for (k = 2; k < 10; k++){
			k = k+3;
		}
}

void joju(char *c){

	int i;

	for(i=0; i < strlen(c); i++){
		c[i] = c[i] +1;
	}
}


int main(){
#define SIZE 100
	char juja[SIZE];
	int  jijo;
#define TLIM 5
	struct timeval tv1,tv2;	// gettimeofday() secs-usecs

	gettimeofday(&tv1,NULL);

	printf("Introduce la contraseña: ");
	fgets(juja,SIZE,stdin);

	juji();
	joju(juja);

	if (strncmp(juja,jaje,strlen(jaje)))
	    jaja();

	gettimeofday(&tv2,NULL);
	if (tv2.tv_sec - tv1.tv_sec > TLIM)
	    jaja();

	printf("Introduce el código: ");
	scanf("%i",&jijo);
	if (jijo!=jeja) jaja();

	gettimeofday(&tv1,NULL);
	if (tv1.tv_sec - tv2.tv_sec > TLIM)
	    jaja();

	juji();
	jiji();
}
