// Actividad 1.2
// Jose Emilio Alvear Cantu - A01024944
// 

#include <iostream>
#include <vector>

int main()
{
    int N, P, Q;
    std::vector<int> denominaciones;
    std::vector<int> monedas_a_regresar;

    // Leer numero de denominaciones
    std::cin >> N;

    // Leer denominaciones
    int denominacion;
    for (int i = 0; i < N; i++)
    {
        std::cin >> denominacion;
        denominaciones.push_back(denominacion);
        monedas_a_regresar.push_back(0); // Inicializar el vector de las monedas a regresar
    }

    // Leer el precio del producto
    std::cin >> P;

    // Leer billete con el que se hace el pago
    std::cin >> Q;

    // Cambio a devolver
    int cambio = Q - P;

    // Calcular el numero de monedas a regresar
    for (int i = 0; i < N; i++)
    {
        monedas_a_regresar[i] = cambio / denominaciones[i];
        cambio = cambio % denominaciones[i];
    }

    // Imprimir el numero de monedas a regresar de cada denominacion
    for (int i = 0; i < N; i++)
    {
        std::cout << monedas_a_regresar[i] << std::endl;
    }

    return 0;
}