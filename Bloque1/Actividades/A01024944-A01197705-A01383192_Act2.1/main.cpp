/*
--Actividad 2.1 Implementación de un Hash String--

--Integrantes de Equipo:
* Jose Emilio Alvear Cantu - A01024944
* Andrea Catalina Fernandez Mena - A01197750
* Carlos Milano - A01383102
*/

//Add preprocessors
#include <iostream>
//#include <cmath>    -aplicable sólo para versión 1
#include <sstream>
#include <fstream>
#include <cstdio>
#include <vector>

using namespace std;

//Falta implementas ASCII y lesctura dentro del mismo

/*
long long prhf(string S){
    int n = S.length();
    int p = 64;   //Ya que n es un entero múltiplo de 4 y  (16 <= n <=64)
    int m = 1e9 + 9;
    long long hashValue  = 0;
    long long power = 1;
    for (int i = 0; i < n ; i++){
        //Definir como obtener el valor a partir de la hashing string
        hashValue = (hashValue + (S[i] - 'a' + 1) * power) % m;
        //Definir como obtener el valor de potencia para función hashing
        power = (power * p) % m;
    }
    return hashValue;

}
*/

main(){
    /*
    int n {};
    cin>>n;
    long long prhf(string S);
    return 0;
    */
    //-------------------------------------------------------------------------------------------------------------
   //Segunda versión de implementación de hash string
    string palabra;
    int n;
	cin >> palabra;
    cin >> n;
    
    ifstream inputfile(palabra);
    if(!inputfile.is_open())
    {
        cout << "Error file: "<<palabra<<" not found"<<endl;
        exit(EXIT_FAILURE);
    }
    if (((n % 4) != 0) || n < 4 || n > 64)
    {
        cout << "RANGE ERROR_ N value: "<<palabra<<" is not matching  must be multiple of 4 within a range of 4 and 64 "<<endl;
        exit(EXIT_FAILURE);

    }

    return 0;

}