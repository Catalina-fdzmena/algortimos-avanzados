// Actividad 1.2
// Jose Emilio Alvear Cantu - A01024944
// Andrea Catalina Fernandez Medina - A01197750
// Carlos 

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

void imprimirVector(std::vector<int> &vec, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << vec[i] << std::endl;
    }
}

void leerDenominaciones(std::vector<int> &denominaciones, int noDenominaciones)
{
    int denominacion;
    for (int i = 0; i < noDenominaciones; i++)
    {
        std::cin >> denominacion;
        denominaciones.push_back(denominacion);
    }
}

void ordenarVectorAscendiente(std::vector<int> &vec)
{
    std::sort(vec.begin(),vec.end());
}

void calcularMonedas_algoritmoAvaro(std::vector<int> &denominaciones, std::vector<int> &monedas_a_regresar_avaro, int _cambio, int noDenominaciones)
{
    // Se traversa restando puesto a que las denominaciones están en orden ascendiente
    int j = 0; 
    for (int i = noDenominaciones - 1; i >= 0; i--)
    {
        monedas_a_regresar_avaro[j] = _cambio / denominaciones[i];
        _cambio = _cambio % denominaciones[i];
        j++;
    }

    
    if (_cambio == 0)
        imprimirVector(monedas_a_regresar_avaro, noDenominaciones);
    else
        std::cout << "SIN SOLUCION" << std::endl;
}

void calcularMonedas_algoritmoDinamico(std::vector<int> &denominaciones, std::vector<int> &monedas_a_regresar_dinamico, int _cambio, int noDenominaciones)
{
    if (denominaciones[0] != 1)
    {
        std::cout << denominaciones[0];
        std::cout << "NO SE PUEDE RESOLVER CON PROGRAMACION DINAMICA" << std::endl;
        return;
    }

    std::vector<int> F(_cambio + 1, INT_MAX);
    F[0] = 0;

    for (int i = 1; i <= _cambio; i++)
    {
        int temp = INT_MAX;
        int j = 0;

        while (j < noDenominaciones && i >= denominaciones[j])
        {
            temp = std::min(F[i - denominaciones[j]], temp);
            j++;
        }

        F[i] = temp + 1;
    }
    
    // Calcular la cantidad de monedas de cada denominacion
    while (_cambio > 0)
    {
        int temp = INT_MAX;
        int minIndex = -1;

        for (int j = 0; j < noDenominaciones; j++)
        {
            if ((_cambio - denominaciones[j]) >= 0 && F[_cambio - denominaciones[j]] < temp)
            {
                temp = F[_cambio - denominaciones[j]];
                minIndex = j;
            }
        }

        monedas_a_regresar_dinamico[noDenominaciones - minIndex - 1] += 1; // Se debe guardar hasta el final porque el resultado va de mayor a menor. 
        _cambio -= denominaciones[minIndex];
    }

    imprimirVector(monedas_a_regresar_dinamico, noDenominaciones);
}

int main()
{
    int N, P, Q;
    std::vector<int> denominaciones;

    // Leer denominaciones
    std::cin >> N;
    leerDenominaciones(denominaciones, N);
    ordenarVectorAscendiente(denominaciones);
    
    std::cin >> P;         // Leer el precio del producto
    std::cin >> Q;         // Leer billete con el que se hace el pago
    int cambio = Q - P;    // Calcular cambio a devolver

    // ALGORITMO DINAMICO
    std::vector<int> monedas_a_regresar_dinamico(N, 0); // Inicializar vector de monedas a regresar
    calcularMonedas_algoritmoDinamico(denominaciones, monedas_a_regresar_dinamico, cambio, N);

    // ALGORITMO AVARO
    std::vector<int> monedas_a_regresar_avaro(N, 0);
    calcularMonedas_algoritmoAvaro(denominaciones, monedas_a_regresar_avaro, cambio, N);
    
    return 0;
}