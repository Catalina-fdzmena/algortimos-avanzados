// Actividad 1.2
// Jose Emilio Alvear Cantu - A01024944
// Andrea Catalina Fernandez Medina - A01197750
// Carlos 

#include <iostream>
#include <vector>

int calcularMonedas_algoritmoAvaro(std::vector<int> &denominaciones, std::vector<int> &monedas_a_regresar, int _cambio, int noDenominaciones)
{
    for (int i = 0; i < noDenominaciones; i++)
    {
        monedas_a_regresar[i] = _cambio / denominaciones[i];
        _cambio = _cambio % denominaciones[i];
    }

    return _cambio;
}

void calcularMonedas_algoritmoDinamico()
{
    // TODO
}

void leerDenominaciones(std::vector<int> &denominaciones, int noDenominaciones)
{
    int denominacion;
    for (int i = 0; i < noDenominaciones; i++)
    {
        std::cin >> denominacion;
        denominaciones.insert(denominaciones.begin(), denominacion);
    }
}

// En caso de que las denominaciones vengan de mayor a menor
void ordenarVectorAscendiente(std::vector<int> &denominaciones, int noDenominaciones)
{
    // TODO
}

void imprimirVector(std::vector<int> &vec, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << vec[i] << std::endl;
    }
}

int main()
{
    int N, P, Q;
    std::vector<int> denominaciones;

    // Leer denominaciones
    std::cin >> N;
    leerDenominaciones(denominaciones, N);
    ordenarVectorAscendiente(denominaciones, N);
    
    std::vector<int> monedas_a_regresar(N, 0);      // Inicializar vector de monedas a regresar
    std::cin >> P;                                  // Leer el precio del producto
    std::cin >> Q;                                  // Leer billete con el que se hace el pago
    int cambio = Q - P;                             // Calcular cambio a devolver

    // ALGORITMO DINAMICO

    // ALGORITMO AVARO
    int cambioAvaro = calcularMonedas_algoritmoAvaro(denominaciones, monedas_a_regresar, cambio, N);
    if (cambioAvaro == 0)
        imprimirVector(monedas_a_regresar, N);
    else
        std::cout << "SIN SOLUCION" << std::endl;

    return 0;
}