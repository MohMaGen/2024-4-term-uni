#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


struct dynamic_array { void *data; size_t len, cap; };

void _da_push(void *gen_self, void *value, size_t elemsizeof)
{
    struct dynamic_array *self = (struct dynamic_array*)gen_self;
    if (self->len >= self->cap) {
        self->cap  = !self->cap ? 16 : self->cap * 2;
        self->data = realloc(self->data, self->cap * elemsizeof);
    }
    memcpy(self->data + self->len++ * elemsizeof, value, elemsizeof);
}
#define da_push(da, value) (_da_push(da, &value, sizeof value))


struct row { float C, I, U_R, U_L, U_C; };
struct table {
    struct row *rows;
    size_t len, cap;
};

void read_table(FILE *csv, struct table *table)
{
    struct row curr = { 0 };
    while (fscanf(csv, "%f, %f, %f, %f, %f", &curr.C, &curr.I, &curr.U_R, &curr.U_L, &curr.U_C) == 5) {
        da_push(table, curr);
    }
}

struct result_row {
    float C, I, U_R, U_L, U_C, R, X_L, X_C, Z, X, P, Q, S, phi;
};

struct result_table {
    struct result_row *rows;
    size_t len, cap;
};


int main(int argc, char** argv)
{
    struct table table = { 0 };

    FILE *csv = fopen("./measured_data.csv", "r");
    read_table(csv, &table);
    fclose(csv);

    printf("       ----< MEASURED VALUES >----  \n"); //30
    for (size_t i = 0; i < table.len; i++) printf("   %6.1f %6.1f %6.1f %6.1f %6.1f\n",
        table.rows[i].C, table.rows[i].I, table.rows[i].U_R,
        table.rows[i].U_L, table.rows[i].U_C);
    puts("\n");

    float U = 220;


    struct result_table result_table = { 0 };
    for (size_t i = 0; i < table.len; i++) {

        struct row row = table.rows[i];

        // C, I, U_R, U_L, U_C, R, X_L, X_C, Z, X, P, Q, S, phi
        struct result_row curr = { 
            .C   = row.C,
            .I   = row.I,

            .U_R = row.U_R,
            .U_L = row.U_L,
            .U_C = row.U_C,

            .R   = row.U_R / row.I,
            .X_L = row.U_L / row.I,
            .X_C = row.U_C / row.I,
            .X   = row.U_L / row.I - row.U_C / row.I,
            .Z   = U / row.I,

            .P   = row.U_R * row.I,
            .Q   = (row.U_L - row.U_C) * row.I,
            .S   = U * row.I,

            .phi = atanf((row.U_L / row.I - row.U_C / row.I) / row.U_R * row.I)
        };

        da_push(&result_table, curr);
    }

    printf("                                     ---< RESULT TABLE >---\n");
    printf(" %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s\n",
        "C", "I", "U_R", "U_L", "U_C", "R", "X_L", "X_C", "Z", "X", "P", "Q", "S", "phi");

    for (size_t i = 0; i < result_table.len; ++i) {
        printf(" %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f\n",
               result_table.rows[i].C,
               result_table.rows[i].I,
               result_table.rows[i].U_R,
               result_table.rows[i].U_L,
               result_table.rows[i].U_C,
               result_table.rows[i].R,
               result_table.rows[i].X_L,
               result_table.rows[i].X_C,
               result_table.rows[i].Z,
               result_table.rows[i].X,
               result_table.rows[i].P,
               result_table.rows[i].Q,
               result_table.rows[i].S,
               result_table.rows[i].phi);
	}

    FILE *output = fopen("output.csv", "w");
    for (size_t i = 0; i  < result_table.len; i++) {
        fprintf(output, "%6f, %6f, %6f, %6f, %6f, %6f, %6f, %6f, %6f, %6f, %6f, %6f, %6f, %6f\n",
                result_table.rows[i].C,
                result_table.rows[i].I,
                result_table.rows[i].U_R,
                result_table.rows[i].U_L,
                result_table.rows[i].U_C,
                result_table.rows[i].R,
                result_table.rows[i].X_L,
                result_table.rows[i].X_C,
                result_table.rows[i].Z,
                result_table.rows[i].X,
                result_table.rows[i].P,
                result_table.rows[i].Q,
                result_table.rows[i].S,
                result_table.rows[i].phi);
    }
    fclose(output);

    return 0;
}