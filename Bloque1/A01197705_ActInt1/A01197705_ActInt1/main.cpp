// Actividad Integradora 1

// Jose Emilio Alvear Cantu - A01024944
// Andrea Catalina Fernandez Mena - A01197750
// Carlos Milano - A01383102


/*
Instrucciones 
1.- Correr el código 
2.- Revisar .txt de nombre "output" para revisar casos de prueba deseados. 

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 3003

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//PARTE 1 ACTIVIDA INTEGRADORA 

// Complejidad O(n)
//-------------ALGORITMO LOSNGEST PROPER PREFIX -----------------

vector<int> longestProperPrefix(string patron) {
    int n = patron.length();
    //Longest proper prefix también cuenta con función de sufijo
    vector<int> longestProperPrefixVec(n, 0);             
    int j = 0, i = 1;
    while (i < n){
        if (patron[i] == patron[j]) {    // Patrones coinciden
            longestProperPrefixVec[i] = j + 1;
            i++;
            j++;
        }
        else {                        
            // Si no hay patrones que coincidan
            if (j == 0) {     
                //           
                longestProperPrefixVec[i] = 0;
                i++;
            }
            else {                       
                //Regresa un índice 
                j = longestProperPrefixVec[j-1];
            }
        }
    }
    return longestProperPrefixVec;
}

// ------ ALGORITMO Knuth-Morris-Pratt -----RECONOCER PATRONES 
// Complejidad: O(n)
pair<int,vector<int>> kmp (string &transmission, string code){
    int found = 0;                             // veces que codigo es encontrado
    vector<int> positionsMatching;             // indices de donde el codigo es encontrado
    vector<int> longestProperPrefixVec = longestProperPrefix(code);
    int j = 0, i = 0;
    int t = transmission.length();
    int p = code.length();

    while (i < t){
        if (transmission[i] == code[j]){
            i++;
            j++;
            if (j == p) {                        
                positionsMatching.push_back(i-p);  
                j = longestProperPrefixVec[j-1];
                found++;                        
            }
        }
        else {
            if (j == 0) {
                i++;
            }
            else {
                j = longestProperPrefixVec[j-1];
            }
        }
    }

    return {found, positionsMatching};
}

// Complejidad: O(n*m)
void codeFoundOutput (ofstream &outputResult, vector<string> &transmisiones, vector<string> &codigosMaliciosos){
    if (outputResult.is_open()) {
        for (int i = 0; i < codigosMaliciosos.size(); i++) {
            for (int j = 0; j < transmisiones.size(); j++) {
                pair<int,vector<int>> foundCodes = kmp(transmisiones[j], codigosMaliciosos[i]);
                if (foundCodes.first > 0) {
                    outputResult << "true ";
                    for (int k = 0; k < foundCodes.second.size(); k++) {
                        outputResult << foundCodes.second[k] << " ";
                    }
                } else {
                    outputResult << "false";
                }
                outputResult << endl;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//PARTE 2 ACT INTEGRADORA 
//------------------------------ENCONTRAR CÓDIGO CON MALWARE -----------------------------------------------

//----------------------------Utilizamos manacher para identificar fragmentos de código espejeados 

// Complejidad: O(n)

pair<string, pair<int, int>> manacher(string text) {
	string T = "";                                  // Nuevo string auxiliar
	int n = text.length();
	for (int i=0; i<n; i++){
		T += "|";                                   // Se agrega "|" entre cada caracter
		T += text[i];
	}
	T += "|";
	n = T.length();                                 // Nueva longitud
	vector<int> L(n);
	L[0] = 0;
	L[1] = 1;
	int maxLong = 0, maxCenter = 0;
	bool exp;
	for (int c=1, li=0, ri=2; ri<n; ri++){
		li = c-(ri-c);
		exp = false;
		if (c-maxLong <= ri && ri >= c+maxLong){
			if (L[li] < (c+L[c]-ri)){
				L[ri] = L[li];
			}
			else if(L[li] == (c + L[c]) - ri && (c + L[c]) == 2*n){
				L[ri] = L[li];
			}
			else if(L[li] == (c + L[c]) - ri && (c + L[c]) < 2*n){
				L[ri] = L[li];
				exp = true;
			}
			else if(L[li] > (c + L[c]) - ri && (c + L[c]) < 2*n){
				L[ri] = (c+L[c]) - ri;
				exp = true;
			}
		}
		else {
			L[ri] = 0;
			exp = true;
		}
		if (exp) {
			while((ri + L[ri] < n) && (ri - L[ri] > 0) && (T[ri - L[ri] - 1] == T[ri + L[ri] + 1])){
				L[ri]++;
			}
		}
		c = ri;
		if (L[ri] > maxLong) {
	    	maxLong = L[ri];
	    	maxCenter = ri;
	    }
	}
	int start = (maxCenter - maxLong) / 2;
    int end = start + maxLong - 1;
	string exit = "";
	for (int i = start; i < (start + maxLong); i++){
		exit += text[i];
	}

	return {exit, {start, end}}; // Regresa palindromo, posicion inicial y posicion final.
}

//---------------------ACUMULAR CÓDIGO MALICIOSO -------------
//Malware se encuentra a manera de palindromes

// Complejidad: O(n)
void findPalindrome(ofstream &outputResult, vector<string> &transmisiones) {
    vector<pair<string,pair<int, int>>> palindromes;
    for (int i = 0; i < transmisiones.size(); i++) {                
        palindromes.push_back(manacher(transmisiones[i]));
    }

    if (outputResult.is_open()) {
        for (int i = 0; i < transmisiones.size(); i++) {
            outputResult << palindromes[i].second.first << " " << palindromes[i].second.second << " " << palindromes[i].first << endl;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//PARTE 3 ACT INTEGRADORA

//--------------------------ENCONTRAR EL Longest Common Substring -------------------------------------- 

// Complejidad: O(n*m)

pair<string, pair<int, int>> LCSS(string st1, string st2) {
    vector<vector<int>> suffix(st1.length() + 1, vector<int>(st2.length() + 1));
    int lengthLCSS = 0;
    int end = -1;

    for (int i = 0; i <= st1.length(); i++) {
        for (int j = 0; j <= st2.length(); j++) {
            if (i == 0 || j == 0) {
                suffix[i][j] = 0;
            } else if (st1[i - 1] == st2[j - 1]) {
                suffix[i][j] = suffix[i - 1][j - 1] + 1;
                if (lengthLCSS < suffix[i][j]) {
                    lengthLCSS = suffix[i][j];
                    end = i;
                }
            } else {
                suffix[i][j] = 0;
            }
        }
    }

    return {st1.substr(end - lengthLCSS, lengthLCSS), {end - lengthLCSS, end - 1}};
}

// Complejidad: O(1)
void getLongestSubstring (ofstream &outputResult, vector<string> transmisiones) {
    if (outputResult.is_open()) {
        pair<string,pair<int,int>> LCSSData = LCSS(transmisiones[0], transmisiones[1]);
        outputResult << LCSSData.second.first << " " << LCSSData.second.second << " " << LCSSData.first << endl;
    }
}


/* ----------------------------------------------------------------
   ---------------------------------------------------------------- */

int main()
{
    // Variables para transición y revisión de cada caso de prueba
    string mcode1, mcode2, mcode3, t1, t2, t3;
    vector<string> codigosMaliciosos;
    vector<string> transmisiones;            

    // Leer archivos
    ifstream archivoCodigoMalicioso1("mcode1.txt");
    ifstream archivoCodigoMalicioso2("mcode2.txt");
    ifstream archivoCodigoMalicioso3("mcode3.txt");
    ifstream archivoTransmission1("transmission1.txt");
    ifstream archivoTransmission2("transmission2.txt");
    //ifstream transmission3("transmission3.txt");
    ofstream outputResult("output.txt");

    // Leer y guardar codigos maliciosos en el vector
    getline(archivoCodigoMalicioso1, mcode1);                     
    getline(archivoCodigoMalicioso2, mcode2);
    getline(archivoCodigoMalicioso3, mcode3);
    codigosMaliciosos.push_back(mcode1);
    codigosMaliciosos.push_back(mcode2);
    codigosMaliciosos.push_back(mcode3);

    // Leer y guardar transmisiones en el vector
    getline(archivoTransmission1, t1);                     
    getline(archivoTransmission2, t2);
    //getline(transmission3, t3);
    transmisiones.push_back(t1);                    
    transmisiones.push_back(t2);
    //transmisiones.push_back(t3);

    outputResult << "Parte 1" << endl;
    codeFoundOutput(outputResult, transmisiones, codigosMaliciosos);

    outputResult << "Parte 2" << endl;
    findPalindrome(outputResult, transmisiones);

    outputResult << "Parte 3" << endl;
    getLongestSubstring(outputResult, transmisiones);

    return 0;
}