#include <stdio.h>
#include <math.h>

typedef short int Int16;

typedef struct
{
    float real;
    float imag;
} COMPLEX;

#define BUFFSIZE 1000

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#define N 100		// N-Point DFT

#define NUMBER_OF_PRINTED_ELEMENTS 10

void dft(Int16 *inbuf, Int16 length);

Int16 res_dft[BUFFSIZE];
Int16 res_idft[BUFFSIZE];

int main()
{
    Int16 input[1000] = {[0] = 21, [1] = 523, [2] = 12};
    dft(input, BUFFSIZE);
    
    Int16 i;
    printf("Input = \n");
    for(i=0;i<NUMBER_OF_PRINTED_ELEMENTS;i++)
        printf("%d ", input[i]);
    printf("\n");
    
    printf("Absolute of DFT = \n");
    for(i=0;i<NUMBER_OF_PRINTED_ELEMENTS;i++)
        printf("%d ", res_dft[i]);
    printf("\n");
    
    printf("Absoulte of IDFT = \n");
    for(i=0;i<NUMBER_OF_PRINTED_ELEMENTS;i++)
        printf("%d ", res_idft[i]);

    return 0;
}

void dft(Int16 *inbuf, Int16 length)
{
	COMPLEX result[BUFFSIZE];
	COMPLEX res_inv[BUFFSIZE];
	Int16 k, n;
	
	for (k = 0; k < length; k++)
	{ 
        	result[k].real = 0.0;    
		result[k].imag = 0.0;
		
		for (n = 0; n < N; n++)
	    	{
			//result[k].real += inbuf[n].real*cos(2*M_PI*k*n/N) + inbuf[n].imag*sin(2*M_PI*k*n/N); 
			result[k].real += inbuf[n] * cos(2*M_PI*k*n/N);
			
			//result[k].imag += inbuf[n].imag*cos(2*M_PI*k*n/N) - inbuf[n].real*sin(2*M_PI*k*n/N);  
			result[k].imag -= inbuf[n] * sin(2*M_PI*k*n/N);
		}
		
		res_dft[k] = roundf(sqrt(result[k].real*result[k].real + result[k].imag*result[k].imag));
	}
		
	for (n = 0; n < length; n++)
    	{
        	res_inv[n].real = 0.0;    
		res_inv[n].imag = 0.0;
		
		for (k = 0; k < N; k++)
	    	{
			res_inv[n].real += (result[k].real * cos(2*M_PI*k*n/N) - result[k].imag * sin(2*M_PI*k*n/N)) / N;
			
			res_inv[n].imag += (result[k].real * sin(2*M_PI*k*n/N) + result[k].imag * cos(2*M_PI*k*n/N)) / N; 			 
		}
		
		res_idft[n] = roundf(sqrt(res_inv[n].real*res_inv[n].real + res_inv[n].imag*res_inv[n].imag));
	}
}
