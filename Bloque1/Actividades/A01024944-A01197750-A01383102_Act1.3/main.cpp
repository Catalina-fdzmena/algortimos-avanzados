// Actividad 1.3
// Jose Emilio Alvear Cantu - A01024944
// Andrea Catalina Fernandez Mena - A01197750
// Carlos Milano - A01383102

// Profesor Eduardo: ertello@tec.mx

//Instrucciones: 
//Ingresar desde cmd y colocar la instrucción main.exe < casoDePrueba.txt > nombreParaOutput.txt  


// Algoritmo de backtracking basado en el algoritmo de https://www.geeksforgeeks.org/rat-in-a-maze-backtracking-2/

// Algoritmo Laberinto Branch and Bound basado en: https://ocw.snu.ac.kr/sites/default/files/NOTE/498.pdf

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

void imprimirVector(vector<vector<int> > &vec, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << vec[i][j];
            cout << " ";
        }
        cout << endl;
    }
}

// Complejidad  O(2^(n^2))
bool resolverLaberintoBacktracing(vector<vector<int> > &laberinto, vector<vector<int> > &solucion_backtracking, int _M, int _N, int posicionRata_i, int posicionRata_j)
{
    // Caso en el que se llega a la meta del laberinto
    if (posicionRata_i == _M - 1 && posicionRata_j == _N - 1 && laberinto[posicionRata_i][posicionRata_j] == 1)
    {
        solucion_backtracking[posicionRata_i][posicionRata_j] = 1;
        return true;
    }

    // Si esta dentro del laberinto y se puede avanzar, seguir con la busqueda
    if (posicionRata_i < _M && posicionRata_j < _N && laberinto[posicionRata_i][posicionRata_j] == 1)
    {
        // Ya se checó esa casilla, no hay por qué volver a checar
        if (solucion_backtracking[posicionRata_i][posicionRata_j] == 1)
            return false;

        // Marcamos la casilla actual como posible solución
        solucion_backtracking[posicionRata_i][posicionRata_j] = 1;

        // Se revisa la casilla de la derecha
        if (resolverLaberintoBacktracing(laberinto, solucion_backtracking, _M, _N, posicionRata_i + 1, posicionRata_j))
            return true;

        // Se revisa la casilla de abajo si moverse a la derecha no funcionó
        if (resolverLaberintoBacktracing(laberinto, solucion_backtracking, _M, _N, posicionRata_i, posicionRata_j + 1))
            return true;

        // Se marca como cero de nuevo, no hay solucion desde este punto
        solucion_backtracking[posicionRata_i][posicionRata_j] = 0;
        return false;
    }

    return false;
}

// Definir límites de la matriz para revisar shortest path
bool safeBoundaries(vector<vector<int> > &laberinto, int x, int y)
{
    // Condicionales del laberinto que se genera con M y N
    if (x >= 0 && x < laberinto[0].size() && y >= 0 && y < laberinto[0].size() && laberinto[x][y] == 1)
        return true;
    return false;
}

// Complejidad O(n^2)
void resolverBranchAndBound(vector<vector<int> > laberinto, vector<vector<int> > &path, int M, int N)
{
    vector<vector<int> > bestPath(M, vector<int>(N));

    if (!safeBoundaries(laberinto, 0, 0))
    {
        cout << "SIN SOLUCION BRANCH AND BOUND" << endl;
    }
    else
    {
        int i = 0;
        int j = 0;

        while (i < M && j < N)
        {
            bestPath[i][j] = 1;
            if (i == M - 1 && j == N - 1)
            {
                break;
            }
            if (i == M - 1)
            {
                if (laberinto[i][j + 1] == 1)
                {
                    j++;
                }
            }
             else if (j == N - 1)
            {
                if (laberinto[i + 1][j] == 1)
                {
                    i++;
                }
            }
            if(i != M - 1 && j != N - 1)
            {
                if (laberinto[i + 1][j] == 1)
                {
                    i++;
                }
                else if (laberinto[i][j + 1] == 1)
                {
                    j++;
                }
                else
                {
                    i++;
                    j++;
                }
            }
        }
    }

    path = bestPath;
}

int main()
{
    int M, N;
    cin >> M >> N;

    vector<vector<int> > laberinto(M, vector<int>(N, -1));
    vector<vector<int> > solucion_backtracking(M, vector<int>(N, 0));
    vector<vector<int> > bestPath(M, vector<int>(N, 0));

    // Leer laberinto
    int valorBooleano;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> valorBooleano;
            laberinto[i][j] = valorBooleano;
            bestPath[i][j] = 0;
        }
    }

    // Solucionar con backtracking
    if (resolverLaberintoBacktracing(laberinto, solucion_backtracking, M, N, 0, 0))
        imprimirVector(solucion_backtracking, M, N);
    else
        cout << "SIN SOLUCION BACKTRACKING" << endl;

    cout << endl;

    // Solución Branch and Bound
    resolverBranchAndBound(laberinto, bestPath, M, N);


    // Solución Branch and Bound
    try
    {
        imprimirVector(bestPath, M, N);
    }
    catch (invalid_argument)
    {
        cout << "SIN SOLUCIÓN BRANCH AND BOUND" << endl;

        cout << endl;
    }

    return 0;
}