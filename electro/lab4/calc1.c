#include <stdio.h>
#include <string.h>

int main(void)
{
    char buffer[0x100] = { '\0' };

    float U_A, U_B, U_C, U_AB, U_AC, U_BC, I_A, I_B, I_C, P_A, P_B, P_C, P; 
    float R_A, R_B, R_C, R;

    FILE *input, *output;

    output = fopen("./result1-1.csv", "w");

    input  = fopen("./data1-1.csv",   "r");

    (void) fgets(buffer, sizeof buffer, input); // read csv header.

    float I_N;

    fscanf(input, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f",
            &U_A, &U_B, &U_C, &U_AB, &U_AC, &U_BC,
            &I_A, &I_B, &I_C, &I_N);

    P_A = U_A * I_A;
    P_B = U_B * I_B;
    P_C = U_C * I_C;
    P   = P_A + P_B + P_C;

    fprintf(output, "%f, %f, %f, - , %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n",
                    U_A, U_B, U_C, U_AB, U_AC, U_BC,
                    I_A, I_B, I_C, I_N, P_A, P_B, P_C, P);

    fscanf(input, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f",
            &U_A, &U_B, &U_C, &U_AB, &U_AC, &U_BC,
            &I_A, &I_B, &I_C, &I_N);

    P_A = U_A * I_A;
    P_B = U_B * I_B;
    P_C = U_C * I_C;
    P   = P_A + P_B + P_C;

    fprintf(output, "%f, %f, %f, - , %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n",
                    U_A, U_B, U_C, U_AB, U_AC, U_BC,
                    I_A, I_B, I_C, I_N, P_A, P_B, P_C, P);

	fclose(input);
    input  = fopen("./data1-2.csv",   "r");

    (void) fgets(buffer, sizeof buffer, input); // read csv header.

    float U_N;

    fscanf(input, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f",
            &U_A, &U_B, &U_C, &U_N, &U_AB, &U_AC, &U_BC,
            &I_A, &I_B, &I_C);

    P_A = U_A * I_A;
    P_B = U_B * I_B;
    P_C = U_C * I_C;
    P   = P_A + P_B + P_C;

    fprintf(output, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, - , %f, %f, %f,  %f\n",
                    U_A, U_B, U_C, U_N, U_AB, U_AC, U_BC,
                    I_A, I_B, I_C, I_N, P_A, P_B, P_C, P);

    fscanf(input, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f",
            &U_A, &U_B, &U_C, &U_N, &U_AB, &U_AC, &U_BC,
            &I_A, &I_B, &I_C);

    P_A = U_A * I_A;
    P_B = U_B * I_B;
    P_C = U_C * I_C;
    P   = P_A + P_B + P_C;

    fprintf(output, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, - , %f, %f, %f,  %f\n",
                    U_A, U_B, U_C, U_N, U_AB, U_AC, U_BC,
                    I_A, I_B, I_C, I_N, P_A, P_B, P_C, P);

    fclose(input);


    fclose(output);

    return 0;
}
