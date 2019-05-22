#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <wchar.h>


#define setx x = h * i;  // x
#define sett t = v * i; // t
#define setu u[0][i] = -2 * pow(x, 2) + 11.85 + 0.3 * x; // 0 ряд
#define setg1 g1[i] = 0.2 * cos(t) + 0.1; // G1
#define setg2 g2[i] = 0.1 * atan(t) + 0.1; //G2
#define setf (-x + 3) * t - 0.2 * sin(t) * x + 0.1 / (1 + pow(t, 2)) - 2.5 * (-0.2 * sin(t)) // f
#define c1 -4 //-a^2/h^2
#define c2 -2 //-r1/h
#define c3 0 // -r2/h
#define a 1
#define s1 0
#define s2 1
#define r1 1
#define r2 0
#define v 0.1 // Тау
#define h 0.5 // Горизонталь
#define getf u[j][0] = u[j][1] - h * g1[j]; //attention 1
#define gets u[j][5] = g2[j];   //attention 2

int main() {
    double x = 0, f, g1[6], g2[6], t = 0, u[6][6]; //  v - тау 
    for (int i = 0; i <= 5; i++) {
        setx
        setu
        sett
        setg1
        setg2
    }
    /*
     * 2 Способ
     *
     *
     *
     *
     */
    printf("2 method: \n");
    for (int j = 1; j <= 5; j++) {
        for (int i = 1; i < 5; i++) {
            setx
            t = v * (j-1);
            f = setf;
            u[j][i] = u[j - 1][i] + (v / pow(h, 2)) * (u[j - 1][i - 1] - 2 * u[j - 1][i] + u[j - 1][i + 1]) + v * f;
        }
        getf 
        gets
    }
    for (int i = 5; i >= 0; i--) {
        for (int j = 0; j <= 5; j++) {
            printf("%10.7g ", u[i][j]);
        }
        printf("\n");
    }

    printf("%c%c%c",'\n','\n','\n');

    /*
     *
     *
     * 3 Способ
     *
     *
     *
     */
     
    int Gauss(double A[6][7], int M, int N)
    {
        for (int i=0; i<M-1; i++)
        {
                for (int j=i+1; j<M;j++)
                {
                        if (A[i][i]==0)
                                exit(22);
                        double K = A[j][i] / A[i][i];
                        for (int k=i; k<N; k++)
                        {
                                A[j][k] -= A[i][k]*K;
                                if (A[j][k] == -0) A[j][k] = +0;
                        }
                }
        }
        return 0;
	}
    double temp[6][7],sub1 = c1,sub2 = c2,sub3 = c3;
    
    
    for (int j = 1; j <= 5; j++) {
    		temp[0][0] = r1/h+s1;
    		temp[0][1] = sub2;
    		for (int i = 1; i < 5; i++)
    		{
    			temp[i][i-1] = temp[i][i+1] = sub1;
    			temp[i][i] = 1/v + 2*(pow(a,2)/pow(h,2));
   			}
    		temp[5][5] = r2/h+s2;
    		temp[5][4] = sub3;
        	temp[0][6]= g1[j];
        	for (int i = 1; i < 5; i++) {
            	setx
            	t = v;
            	temp[i][6]=
                    setf + u[j - 1][i] / v;
        	}
        	temp[5][6] = g2[j];
        	Gauss(temp, 6, 7);
        	u[j][5] = temp[5][6] / temp[5][5];
        	for (int i = 4; i >=0; i--)
        	{
        		u[j][i] = (temp[i][6] - temp[i][i+1]*u[j][i+1])/temp[i][i];
        	}
    }
    
    for (int i = 5; i >= 0; i--) {
        for (int j = 0; j <= 5; j++) {
            printf("%10.7g ", u[i][j]);
        }
        printf("\n");
    }
}

