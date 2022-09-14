/*
--Actividad 2.2 Implementación de un Suffix Array--
--Integrantes de Equipo:
	* Jose Emilio Alvear Cantu - A01024944
	* Andrea Catalina Fernandez Mena - A01197750
	* Carlos Milano - A01383102
*/

// Escribe un programa en C++ que dado un string, se calcule el arreglo de substrings y lo muestre ordenado alfabéticamente 

// Algoritmo Suffix Array basado en algoritmo metodo 2 de: https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/ 

// Instrucciones: 
// Ingresar desde bash de linux g++ -g main.cpp
// Despues proceder a escribir ./a.out <test00.txt

// Otra manera de imprimirlo sin mostrar la parte de la palabra restante es: 
// Ingresar desde cmd y colocar la instrucción main.exe < test00.txt > nombreParaOutput.txt  
    // Nota este método unicamente ejecuta las coordenas de órden alfabético


#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
	string palabra;
	cin >> palabra;
	int n = palabra.length();
	map<string, int> Map;
	int suffix[n];

//Single for implemented
//Complejidad: O(n)
	string sub = "";
	for (int i = n - 1; i >= 0; i--)
	{
		sub = palabra[i] + sub;
		Map[sub] = i;
	}

//Se implementa un for sensillo 
//Complejidad: O(n)
	int j = 0;
	for (auto x : Map)
	{
		suffix[j] = x.second;
		j++;
	}

//Se implementa un for anidado para arreglo de sufijos
//Complejidad: O(n^2)
	cout << "El arreglo de sufijos para " << palabra << " es el siguiente:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << suffix[i] << " ";

		int partialWord = suffix[i];
		for (int j = partialWord; j < palabra.length(); j++)
		{
			cout << palabra[j] << " ";
		}

		cout << endl;
	}

	return 0;
}