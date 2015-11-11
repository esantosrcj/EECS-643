// Authors: Hayden Kaustinen, Dylan Dreiling, Eduardo Santos
// Title: Project 1B

#include <stdio.h>
#include <time.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

// Change nway to say what kind of cache you have
#define nway 8
#define NbrPlanes 64
#define NbrRows 1024
#define NbrCols 1024
#define NbrIterations 100

#define NbrDataBits 6
#define sizeData (1 << NbrDataBits)
#define MaskDataBits (sizeData - 1)

#define cacheExp 15
#define addrExp 32

#define sizeCache (1 << cacheExp)
#define NbrIndexBits (cacheExp - NbrDataBits) - (nway/2)
#define sizeIndex (sizeCache/sizeData)/nway
#define MaskIndexBits (sizeIndex - 1)

#define sizeLine (1 << addrExp)
#define NbrTagBits (addr - NbrDataBits - NbrIndexBits)
#define tagOffset (addrExp - NbrTagBits)
#define sizeTag (sizeLine/sizeCahe)
#define MaskTagBits (sizeTag - 1)

typedef int bool;
#define true 1
#define false 0

int32_t Data[NbrPlanes][NbrRows][NbrCols];
int32_t Addr[NbrPlanes][NbrRows][NbrCols];
int32_t Addr2[NbrCols][NbrRows][NbrPlanes];

// 2D arrays
int32_t line[sizeIndex][nway];
bool valid[sizeIndex][nway];
int32_t replace[sizeIndex];

int main (int argc, const char * argv[])
{
	int32_t I,J,K = 0;
	int32_t	L = NbrIterations;
	int32_t X = 0;
  
  int tag, index, offset;

	int32_t *elemAddr = NULL;
  int32_t *baseAddr = NULL;
  int32_t binAddr;

	time_t StartTime, EndTime;
  
  int32_t hit = 0;
  int32_t miss = 0;
  int32_t *streamAddress;
  int32_t streamData;
  int32_t loop = 0;
  
  FILE *f = fopen("Cols.bin", "w");
  FILE *p = fopen("Planes.bin", "w");
		
	if (f == NULL)
  {
		printf("Error opening file");
		exit(1);
	}

  for (int = 0; i <sizeIndex; i++)
  {
    for (int j = 0; j < nway; j++)
    {
      valid[i][j] = 0;
    }
    replace[i] = 0;
  }
	printf(">>CacheBenchmark: Starting.\n");
	
  time(&StartTime);
	printf(">>CacheBenchmark: Start: Time = %d \n", StartTime, ctime(&StartTime));
	printf(">>Size of int: %ld; Size of long int: %ld; size of time_t: %ld\n", sizeof(int), sizeof(long int), sizeof(time_t));

  //
  // Step through data
  //
  baseAddr = &Data[0][0][0];
	for (I = 0; I < NbrPlanes; I++)
  {
		for (J = 0; J < NbrRows; J++)
    {
			for (K = 0; K < NbrCols; K++)
      {
				X = Data[I][J][K];
			}
		}
	}
  sleep(1);

  //
  // Cols(outside) index iterating fastest
  //
  time(&StartTime);
	for (I = 0; I < NbrPlanes; I++)
  {
		for (J = 0; J < NbrRows; J++)
    {
			for (K = 0; K < NbrCols; K++)
      {
				X = Data[I][J][K];
        Addr[I][J][K] = (&Data[I][J][K] - baseAddr) * 4;
			}
		}
	}
  time(&EndTime);

  fwrite(Addr, 4, I * J * K, f);
	printf(">>>>X: %d\n", X);
	printf(">>CacheBenchmark: Start: %d; End: %d; Delta: %d\n", StartTime, EndTime, (EndTime - StartTime));

  //
  // Planes(inside) index iterating fastest
  //
	sleep(1);
	time(&StartTime);
	for (K = 0; K < NbrCols; K++)
  {
		for (J = 0; J < NbrRows; J++)
    {
			for (I = 0; I < NbrPlanes; I++)
      {
				X = Data[I][J][K];
        Addr2[K][J][I] = (&Data[I][J][K] - baseAddr) * 4;
			}
		}
	}
	time (&EndTime);

  fwrite(Addr2, 4, I * J * K, p);
	printf(">>>>X: %d\n", X);
	printf(">>CacheBenchmark: Start: %d; End: %d; Delta: %d\n", StartTime, EndTime, (EndTime - StartTime));
  fclose(f);
  fclose(p);

  f = fopen("Cols.bin", "r");
  f = fopen("Planes.bin", "r");

  int32_t hit = 0;
  int32_t miss = 0;
  int32_t *streamAddress;
  int32_t streamData;
  int32_t loop = 0;

	return(1);
}

