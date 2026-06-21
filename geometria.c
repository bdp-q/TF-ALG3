#include "geometria.h"

// utiliza o valor absoluto do determinante da matriz com os 3 pontos dividido por 2
float area_triangulo(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float area;

    area = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2;

    return (area < 0.0) ? -area : area;
}

/*  considerando a equação: area = (base * altura) / 2
 * elevando ao quadrado: area^2 = (base^2 * altura^2) / 4
 * reorganizando:      altura^2 = 4 * area^2 / base^2
 */
float altura2_triangulo(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float area, dx, dy;

    area = area_triangulo(x1, y1, x2, y2, x3, y3);
    dx = x3 - x1;
    dy = y3 - y1;

    return 4 * (area * area) / (dx * dx + dy * dy);
}