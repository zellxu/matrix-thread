#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *matrix_multiplicaiton( void *ptr );

int main(){
	int static const NUM_EPOCHS = 2;
	int static const NUM_THREADS = 10;
	//pthread_t threads[NUM_THREADS];
	int  iret;
	int i, epoch;

	pthread_t *threads = malloc(sizeof(pthread_t) * NUM_THREADS);

	for(epoch=0; epoch<NUM_EPOCHS; epoch++){
		for (i=0; i<NUM_THREADS; i++){
			iret = pthread_create( &threads[i], NULL, matrix_multiplicaiton, &epoch);
			if(iret){
				fprintf(stderr,"Error - pthread_create() return code: %d\n",iret);
				exit(EXIT_FAILURE);
			}
			//printf("thread %d created\n",i);
		}
		for (i=0; i<NUM_THREADS; i++){
			pthread_join( threads[i], NULL);
		}
	}
	exit(EXIT_SUCCESS);
}

void *matrix_multiplicaiton( void* s ){
	int size = *(int*) s + 1;
	int a[size][size];
	int b[size][size];
	int c[size][size];
	int ab[size][size];
	int abc[size][size];
	int i,j,k;
	int sum = 0;

	for (i=0; i<size; i++){
		for(j=0; j<size; j++){
			a[i][j] = 2;
			b[i][j] = 2;
			c[i][j] = 2;
		}
	}

	for (i=0; i<size; i++){
		for(j=0; j<size; j++){
			for(k=0; k<size; k++){
				sum = sum + a[i][k] * b[k][j];
			}
			ab[i][j] = sum;
			sum = 0;
		}
	}

	for (i=0; i<size; i++){
		for(j=0; j<size; j++){
			for(k=0; k<size; k++){
				sum = sum + ab[i][k] * c[k][j];
			}
			abc[i][j] = sum;
			sum = 0;
		}
	}
	/*
	if(size!=1){
		printf("Result:\n%d %d\n%d %d\n", abc[0][0], abc[0][1], abc[1][0], abc[1][1]);
	}
	*/
}