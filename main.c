/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <math.h>

typedef int Int16;

typedef struct
{
    float real;
    float imag;
} COMPLEX;

#define BUFFSIZE 1000
#define PI 3.14159265358979 
#define N 100

void dft(Int16 *inbuf, Int16 length);

Int16 res_dft[BUFFSIZE];
Int16 res_idft[BUFFSIZE];

int main()
{
    Int16 input[1000] = {[0] = 10, [1] = 10, [2] = 10};
    dft(input, BUFFSIZE);
    
    int i;
    for(i=0;i<10;i++)
        printf("%d ", input[i]);
    printf("\n");
    for(i=0;i<10;i++)
        printf("%d ", res_dft[i]);
    printf("\n");
    for(i=0;i<10;i++)
        printf("%d ", res_idft[i]);
    
    //printf("\n%d", res_dft[429]);

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
		    //result[k].real += inbuf[n].real*cos(2*PI*k*n/N) + inbuf[n].imag*sin(2*PI*k*n/N); 
			result[k].real += inbuf[n] * cos(2*PI*k*n/N);
			
			//result[k].imag += inbuf[n].imag*cos(2*PI*k*n/N) - inbuf[n].real*sin(2*PI*k*n/N);  
			result[k].imag -= inbuf[n] * sin(2*PI*k*n/N);
		}
		
		res_dft[k] = sqrt(result[k].real*result[k].real + result[k].imag*result[k].imag);
	}
		
	for (n = 0; n < length; n++)
    {
        res_inv[n].real = 0.0;    
		res_inv[n].imag = 0.0;
		
		for (k = 0; k < N; k++)
	    {
			res_inv[n].real += (result[k].real * cos(2*PI*k*n/N) - result[k].imag * sin(2*PI*k*n/N)) / N;
			
			res_inv[n].imag += (result[k].real * sin(2*PI*k*n/N) + result[k].imag * cos(2*PI*k*n/N)) / N; 			 
		}
		
		res_idft[n] = sqrt(res_inv[n].real*res_inv[n].real + res_inv[n].imag*res_inv[n].imag);
	}
	
	for (k=0; k<10; k++)
	    if (res_inv[k].imag >= 0)
	        printf("%.4f+%.4fj ", res_inv[k].real, res_inv[k].imag);
	    else
	        printf("%.4f%.4fj ", res_inv[k].real, res_inv[k].imag);
	printf("\n");
}
