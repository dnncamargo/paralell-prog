#include <stdio.h>
#include <math.h>
#include "main.h"

/* Função recebe um valor e returna 1 se for positivo ou 0 caso contrário */
int isgreaterthan0 (int input) { return input > 0; }

/* Função recebe um valor e retorna 0 se for nulo ou 1 caso contrário */
int isnotnull (char * input) { return input != NULL; }

/* Função recebe três valores, 'a', 'b' e 'c', que são os coeficientes de uma equação do
segundo grau e retorna o valor do delta, que é dado por 'b² – 4ac'. */
double delta(double a, double b, double c) { return (pow(b, 2) - 4 * a * c); }

/* Usando as 3 funções acima, crie um programa que calcula as raízes de uma equação do 2o grau:
ax² + bx + c=0. Para ela existir, o coeficiente 'a' deve ser diferente de zero. Caso o delta seja maior
ou igual a zero, as raízes serão reais. Caso o delta seja negativo, as raízes serão complexas e da
forma: x + iy */
double fquad(double a, double b, double c) {
    if (isgreaterthan0(a)) {
        double d = delta(a, b, c);
        double f1 = (-b + sqrt(d)) / 2 * a;
        double f2 = (-b - sqrt(d)) / 2 * a;
        printf("Real roots : x1 = %f; x2 = %f", f1, f2);
    } else {
        double d = delta(-a, b, c);
        double f1 = (-b + sqrt(d)) / 2 * a;
        double f2 = (-b - sqrt(d)) / 2 * a;
        printf("Complex roots : x1 = %f i; x2 = %f i", f1, f2);
    }
}