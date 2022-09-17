/*
--Actividad 2.1 Implementación de un Hash String--

--Integrantes de Equipo:
* Jose Emilio Alvear Cantu - A01024944
* Andrea Catalina Fernandez Mena - A01197750
* Carlos Milano - A01383102
*/

//Instrucciones: 
//Ingresar desde cmd y colocar la instrucción main.exe < casoDePrueba.txt > nombreParaOutput.txt  

//Add preprocessors
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// Complejidad: O(n)
int main(){
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
    vector<vector<char>> bytesReader;
    vector<char> rowChecker;

    char letter = 0;
    while (inputfile.get(letter))
    {
        rowChecker.push_back(letter);

        if ((rowChecker.size() % n) == 0){
            bytesReader.push_back(rowChecker);
            rowChecker.clear();
        }
    }

    if (rowChecker.size() < n){
        int missing = n - rowChecker.size();

        for (int i = 0 ; i < missing ; i ++){
            char letter = 'a';

            rowChecker.push_back(letter);
        }
        bytesReader.push_back(rowChecker);
    }
    std::string matrixResult;
    for(int i = 0; i < bytesReader.size(); i++){
        int sum = 0;
        for (int j = 0; j < n ; j++){
            sum += bytesReader[i][j];
        }
        std::stringstream ss;
        ss << setfill('0')<<setw(2)<<right<<std::hex<<(sum % 256);
        string tmp = ss.str();
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);

        matrixResult = matrixResult + (tmp);
    }
    cout << matrixResult <<endl;
    inputfile.close();
    return EXIT_SUCCESS;

    return 0;

}