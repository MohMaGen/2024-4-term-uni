#include <stdio.h>

int main(void)
{
	char buf[256] = { '\0' };

    FILE *input = fopen("./data.csv", "r");
    FILE *output = fopen("./result.csv", "w");
    FILE *o = NULL;

    float R, t, n, I, M;

	int i = 0;
    while (fscanf(input, "%f, %f, %f, %f", &R, &t, &n, &I) == 4) {
        M = I*I;

        if (i % 8 == 0) {
            sprintf(buf, "o%d.csv", i / 8);
            o = fopen(buf, "w");
        }

        fprintf(output, "%f, %f, %f, %f, %f\n", R, t, n, I, M);
        fprintf(o, "%f, %f, %f, %f, %f\n", R, t, n, I, M);

        i++;
    }

    fclose(input);
    fclose(output);

    return 0;
}
