#include <iostream>
#include <vector>
#include "Punto.h"

double getClosestPairOfPoints(std::vector<Punto> &points) {
    return 0;
}

int main() {

    int numeroDePuntos;
    std::cin >> numeroDePuntos;

    int x, y;
    std::vector<Punto> puntos(numeroDePuntos);
    for (int i = 0; i < numeroDePuntos; i++) {
        std::cin >> x >> y;
        puntos[i] = Punto(x, y);
    }

    double distancia = getClosestPairOfPoints(puntos);
    std::cout << "La distancia mas corta es: " << distancia;

    return 0;
}