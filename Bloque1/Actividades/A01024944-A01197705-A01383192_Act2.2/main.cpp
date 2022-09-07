/*
--Actividad 2.2 Implementación de un Suffix Array--

--Integrantes de Equipo:
* Jose Emilio Alvear Cantu - A01024944
* Andrea Catalina Fernandez Mena - A01197750
* Carlos Milano - A01383102
*/

//Escribe un programa en C++ que dado un string, se calcule el arreglo de substrings y lo muestre ordenado alfabéticamente 

//Algoritmo Suffix Array basado en algoritmo de: https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/ 

//Instrucciones: 
//Ingresar desde bash de linux g++ -g main.cpp
//Despues proceder a escribir ./a.out <text00.txt

//Otra manera de imprimirlo sin mostrar la parte de la palabra restante es: 
//Ingresar desde cmd y colocar la instrucción main.exe < text00.txt > nombreParaOutput.txt  



#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

// Structure to store information of a suffix
struct suffix
{
	int index; 
	int level[2]; //Guardar organización en pares además del índice
};


int valuesComparisson(struct suffix a, struct suffix b)
{
	return (a.level[0] == b.level[0])? (a.level[1] < b.level[1] ?1: 0):
			(a.level[0] < b.level[0] ?1: 0);
}


int *buildSuffixArray(string txt, int n)
{
	// Struct para gurdar sufijos e indices
	struct suffix suffixes[n];
	// Organización de manera alfabética y revisar sus indices mientras se organizan.
	for (int i = 0; i < n; i++)
	{
		// Acomodar suffixesutilizando comparación
		suffixes[i].index = i;
		suffixes[i].level[0] = txt[i] - 'a';
		suffixes[i].level[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
	}

	sort(suffixes, suffixes+n, valuesComparisson);
	int suffixIndex[n]; 

//Funcion para asignar nivel de jerarquía a identifiacar sufijos 

	for (int k = 4; k < 2*n; k = k*2)
	{
		int level = 0;
		int prev_level = suffixes[0].level[0];
		suffixes[0].level[0] = level;
		suffixIndex[suffixes[0].index] = 0;

//Iteración para crear rank en los sufijos
		for (int i = 1; i < n; i++)
		{
			if (suffixes[i].level[0] == prev_level &&
					suffixes[i].level[1] == suffixes[i-1].level[1])
			{
				prev_level = suffixes[i].level[0];
				suffixes[i].level[0] = level;
			}
			else 
			{
				prev_level = suffixes[i].level[0];
				suffixes[i].level[0] = ++level;
			}
			suffixIndex[suffixes[i].index] = i;
		}

		for (int i = 0; i < n; i++)
		{
			int nextindex = suffixes[i].index + k/2;
			suffixes[i].level[1] = (nextindex < n)?
								suffixes[suffixIndex[nextindex]].level[0]: -1;
		}

		sort(suffixes, suffixes+n, valuesComparisson);
	}

	//Guardar el arreglo todos los prefijos trabajados

	int *suffixArr = new int[n];
	for (int i = 0; i < n; i++)
		suffixArr[i] = suffixes[i].index;
	return suffixArr;
}


void print(int arr[], int n, string wordChosen)
{
	for (int i = 0; i < n; i++){
		int partialWord = arr[i];
		cout << arr[i] << " ";
		//Segudo indice revisa el arreglo 
		for(int j = partialWord; j<wordChosen.length(); j++){
			cout << wordChosen[j] << " ";
		}
	
	cout << endl;
	}
}

int main(){
    string wordChosen;
    cin>>wordChosen;
    // char txt[] ="wordChosen";   //No se si sea la manera correcta de aceptar los casos de prueba
	// int n = strlen(txt);
    int n = wordChosen.length();
	int *suffixArr = buildSuffixArray(wordChosen, n);
	cout << "El siguiente arreglo de sufijos en orden alfabético para " << wordChosen << " es:"<<endl;
	print(suffixArr,n, wordChosen);
	return 0;
}