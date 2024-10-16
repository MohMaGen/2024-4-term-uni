#ifndef calc_h_INCLUDED
#define calc_h_INCLUDED
#include <stddef.h>

typedef struct {
    double *data; size_t width, height;
} Matrix;

#define M_FOREACH(m, name_curr, body){                             \
    Matrix __m = (m);                                              \
    for (size_t y = 0; y < __m.height; y++) {                      \
        for (size_t x = 0; x < __m.width; x++) {                   \
            double *name_curr = __m.data + x + y * __m.width;      \
            { body }                                               \
        }                                                          \
    }                                                              \
}                                                                  \

#define M_FORROW(m, name_curr, body){          \
    Matrix __m = (m);                          \
    for (size_t y = 0; y < __m.height; y++) {  \
        Matrix name_curr = mget_row(__m, y);   \
        { body }                               \
    }                                          \
}                                              \

Matrix mk_vectorw(size_t width, double *values);
Matrix mk_vectorh(size_t height, double *values);
Matrix mk_matrix(size_t widht, size_t height, double *values);
Matrix mget_rowcp(Matrix m, size_t row_id);
Matrix mget_row(Matrix m, size_t row_id);
double* mat(Matrix m, size_t x, size_t y);
Matrix mget_columncp(Matrix m, size_t column_id);
Matrix solve_sle(Matrix sle);
void display_matrix(Matrix sle);

#endif // calc_h_INCLUDED

#ifdef IML_CALC
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void display_matrix(Matrix sle) {
    printf("\n");
    M_FORROW(sle, row, {
        printf("\t");
        M_FOREACH(row, curr, { printf("%7.2lf", *curr); }) 
        printf("\n");
    }) 
}

Matrix solve_sle(Matrix sle) {
    M_FORROW(sle, row, {
        double yy = *mat(sle, y, y);
        M_FOREACH(row, elem, {  *elem /= yy; })
        size_t y_c = y;

        M_FORROW(sle, row, {
            if (y == y_c) continue;
            double v = *mat(sle, y_c, y);

            M_FOREACH(row, elem, { 
                *elem -= v * *mat(sle, x, y_c);
            })
        }) 
    })
    return mget_columncp(sle, sle.width-1); 
}

Matrix mget_columncp(Matrix m, size_t column_id) {
    Matrix column = (Matrix){ (double*)malloc(m.height * sizeof(double)), 1, m.height };
    M_FORROW(m, row, {
        *mat(column, 0, y) = *mat(row, column_id, 0);
    }) 
    return column;
}

double* mat(Matrix m, size_t x, size_t y) {
    return m.data + x + m.width * y;
}
Matrix mget_row(Matrix m, size_t row_id) {
    return (Matrix){ m.data + row_id * m.width, m.width, 1 };
}
Matrix mget_rowcp(Matrix m, size_t row_id) {
    return mk_vectorw(m.width, m.data + row_id * m.width);
}

Matrix mk_vectorw(size_t width, double *values) {
    Matrix m = (Matrix){ (double*)malloc(width * sizeof(double)), width, 1 };
    memcpy(m.data, values, width * sizeof(double)); 
    return m;
}
Matrix mk_vectorh(size_t height, double *values) {
    Matrix m = (Matrix){ (double*)malloc(height * sizeof(double)), 1, height };
    memcpy(m.data, values, height * sizeof(double)); 
    return m;
}

Matrix mk_matrix(size_t width, size_t height, double *values) {
    Matrix m = (Matrix){ (double*)malloc(width * height * sizeof(double)), width, height };
    memcpy(m.data, values, width * height * sizeof(double)); 
    return m;
}
#endif
