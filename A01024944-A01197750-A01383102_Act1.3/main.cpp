// Actividad 1.3
// Jose Emilio Alvear Cantu - A01024944
// Andrea Catalina Fernandez Medina - A01197750
// Carlos 


#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

void imprimirVector(vector<vector<int>> &vec, int rows, int cols)
{
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << vec[i][j];
            cout << " ";
        }
        cout << endl;
    }
}

int main()
{
    int M, N;
    cin >> M >> N;

    vector<vector<int>> laberinto(M, std::vector<int>(N, -1));
    vector<vector<int>> solucion_backtracking(M, std::vector<int>(N, -1));
    vector<vector<int>> solucion_branchAndBound(M, std::vector<int>(N, -1));

    int valorBooleano;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> valorBooleano;
            laberinto[i][j] = valorBooleano;
        }
    }
    
    return 0;
}