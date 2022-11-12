#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Punto.h"

void swap(Punto *a, Punto *b)
{
    Punto t = *a;
    *a = *b;
    *b = t;
}

int partition(std::vector<Punto> &vec, int low, int high)
{
    double pivot = vec[high].x; // pivot
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (vec[j].x < pivot) {
            i++; // increment index of smaller element
            swap(&vec[i], &vec[j]);
        }
    }
    swap(&vec[i + 1], &vec[high]);
    return (i + 1);
}

// Quicksort implementado para ordenar clase Punto
void quickSort(std::vector<Punto> &points, int low, int high) {
    if (low < high) {
        int pi = partition(points, low, high);
        quickSort(points, low, pi - 1);
        quickSort(points, pi + 1, high);
    }
}


// Calcula la distancia entre dos puntos
double calculateDistance(Punto a, Punto b) {
    double dist = std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    return dist;
}

// Complejidad de tiempo: O(nlog(n))
// Complejidad de espacio: O(nlog(n))
double getClosestPairOfPoints(std::vector<Punto> sortedX, std::vector<Punto> sortedY) {

    int n = sortedX.size();
    if (n == 2) {
        return calculateDistance(sortedX[0], sortedX[1]);
    }
    if (n == 3) {
        return std::min({calculateDistance(sortedX[0], sortedX[1]),
                         calculateDistance(sortedX[1], sortedX[2]),
                         calculateDistance(sortedX[0], sortedX[2])});
    }

    int mid = n / 2;

    // Crear vector con la primera mitad del arreglo y encontrar distancia minima
    std::vector<Punto>::const_iterator first = sortedX.begin();
    std::vector<Punto>::const_iterator last = sortedX.begin() + mid;
    std::vector<Punto> primeraMitad(first, last);
    double dl = getClosestPairOfPoints(primeraMitad, sortedY);

    // Crear vector con la segunda mitad del arreglo y encontrar distancia minima
    first = sortedX.begin() + mid;
    last = sortedX.end();
    std::vector<Punto> segundaMitad(first, last);
    double dr = getClosestPairOfPoints(segundaMitad, sortedY);

    double distance = std::min(dl, dr);

    // Crear arreglo con los puntos que estén dentro del rango [mid.x - distancia, mid.x + distancia]
    std::vector<Punto> s;
    for (int i = 0; i < sortedY.size(); i++) {
        if (sortedY[i].x >= sortedX[mid].x - distance && sortedY[i].x <= sortedX[mid].x + distance) {
            s.push_back(sortedY[i]);
        }
    }

    // Encontrar si hay alguna distancia más corta entre los puntos del rango anterior
    for (int i = 0; i < s.size(); i++) {
        for (int j = i + 1; j < s.size() && (s[j].y - s[i].y) < distance; j++) {
            distance = std::min(distance, calculateDistance(s[i], s[i + j]));
        }
    }

    return distance;
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

    std::vector<Punto> puntosOrdenadosPorX = puntos;
    quickSort(puntosOrdenadosPorX, 0, numeroDePuntos - 1);

    for (int i = 0; i < numeroDePuntos; i++) { puntos[i].swapXandY(); }
    std::vector<Punto> puntosOrdenadosPorY = puntos;
    quickSort(puntosOrdenadosPorY, 0, numeroDePuntos - 1);
    for (int i = 0; i < numeroDePuntos; i++) { puntosOrdenadosPorY[i].swapXandY(); }

    double distancia = getClosestPairOfPoints(puntosOrdenadosPorX, puntosOrdenadosPorY);
    std::cout << "La distancia mas corta es: " << distancia;

    return 0;
}