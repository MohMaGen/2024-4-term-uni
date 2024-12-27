#include <stdio.h>

int main(void)
{
    FILE *input = fopen("./data.csv", "r");
    FILE *output = fopen("./result.csv", "w");


    float R, U_1, I_1, P_1, U_2, I_2, P_2, cos_phi, eta;

    for (size_t i = 0; i < 5; ++i) {
        fscanf(input, "%f, %f, %f, %f, %f, %f",
                &R, &U_1, &I_1, &P_1, &U_2, &I_2);

        P_2 = I_2 * U_2;
        cos_phi = P_1 / U_1 / I_1;
        eta = P_2 / P_1 * 100;

        fprintf(output, "%f, %f, %f, %f, %f, %f, %f, %f, %f\n",
                R, U_1, I_1, P_1, U_2, I_2, P_2, cos_phi, eta); 
    }

    fclose(input);
    fclose(output);

    return 0;
}

