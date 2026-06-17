#ifndef GEOMETRIA_H
#define GEOMETRIA_H

/*
 * Calcula a área do triângulo formado pelos pontos (x1,y1), (x2,y2) e (x3,y3)
 *
 * Retorno: Área do triângulo
 */
float area_triangulo(float x1, float y1, float x2, float y2, float x3, float y3);

/*
 * Calcula a altura do triângulo elevada ao quadrado, sendo a altura a distância
 * entre (x2,y2) e a base do triangulo (x1,y1)~(x3,y3)
 *
 * Retorno: Altura ao quadrado do triângulo
 */
float altura2_triangulo(float x1, float y1, float x2, float y2, float x3, float y3);

#endif