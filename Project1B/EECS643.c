#include <stdio.h>
#include <time.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#define NbrPlanes 64
#define NbrRows 1024
#define NbrCols 1024
#define NbrIterations 100

int32_t Data[NbrPlanes][NbrRows][NbrCols];

int main (int argc, const char * argv[]) {
	
	FILE *f = fopen("file.txt", "w");
	int32_t*  elemAddr;
	
	
	if (f == NULL){
		printf("Error opening file");
		exit(1);
	}
	int32_t I,J,K = 0;
	int32_t	L = NbrIterations;
	int32_t X = 0;
	
	time_t StartTime, EndTime;

	printf(">>CacheBenchmark: Starting.\n");

	time( &StartTime );
	printf( ">>CacheBenchmark: Start: Time = %d \n", StartTime, ctime (&StartTime) );

	printf( ">>Size of int: %ld; Size of long int: %ld; size of time_t: %ld\n", sizeof(int), sizeof(long int), sizeof(time_t));

	
	//	Step throug data to see if its in main mem

	for( I =0; I<NbrPlanes; I++) {
		for(J = 0; J < NbrRows; J++){
			for(K = 0; K< NbrCols; K++){
				X = Data[I][J][K];
			}
		}
	}

	
	// sleep(1);

	// time(&StartTime);
	// for (L = 0;L< NbrIterations; L++){
		// for(I=0;I<NbrPlanes;I++){
			// for(J=0;J<NbrRows; J++){
				// for(K=0;K<NbrCols;K++){
					// X = Data[I][J][K];
				// }
			// }
		// }	
	// }
	time( &EndTime);
	
	elemAddr = *Data[0][0][0];
	fprintf(f, elemAddr);
	
	printf(">>>>X: %d\n", X);

	printf(">>CacheBenchmark: Start: %d; End: %d; Delta: %d\n", StartTime, EndTime, (EndTime-StartTime));

	sleep(1);
	time(&StartTime);
	// for (L = 0; L< NbrIterations; L++){
		// for(K=0; K<NbrCols; K++){
			// for(J=0; J<NbrRows; J++){
				// for(I=0;I<NbrPlanes;I++){
					// X = Data[I][J][K];
				// }
			// }
		// }	
	// }
	
	time (&EndTime);
	
	printf(">>>>X: %d\n", X);

	printf(">>CacheBenchmark: Start: %d; End: %d; Delta: %d\n", StartTime, EndTime, (EndTime-StartTime));

	return(1);
}

