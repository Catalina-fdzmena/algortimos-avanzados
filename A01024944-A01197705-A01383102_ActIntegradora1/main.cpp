// Actividad Integradora 1

// Jose Emilio Alvear Cantu - A01024944
// Andrea Catalina Fernandez Mena - A01197750
// Carlos Milano - A01383102

/*

Input
     nada, solamente deben existir los 5 archivos en la misma ruta donde se ejecuta el programa    

Output
  Parte 1
     (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode1.txt, un espacio y la posición    
     (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode1.txt, un espacio y la posición
     (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode2.txt, un espacio y la posición
     (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode2.txt, un espacio y la posición
     (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode3.txt, un espacio y la posición
     (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode3.txt, un espacio y la posición
  Parte2
     posiciónInicial posiciónFinal (para archivo de transmisión1) códigoMalicioso
     posiciónInicial posiciónFinal (para archivo de transmisión2) códigoMalicioso
  Parte3
      posiciónInicial posiciónFinal (de substring común más largo entre archivos de transmisión 1 y 2) longitudSubstringComún substringComún

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

//Output must be generated
/*
    (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode1.txt, un espacio y la posición    
     (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode1.txt, un espacio y la posición
     (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode2.txt, un espacio y la posición
     (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode2.txt, un espacio y la posición
     (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode3.txt, un espacio y la posición
     (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode3.txt, un espacio y la posición
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//PARTE 2 ACT INTEGRADORA 
//------------------------------ENCONTRAR CÓDIGO CON MALWARE -----------------------------------------------

//----------------------------Utilizamos manacher para identificr fragmentos de código espejeados 

// Complejidad: O(n)

pair<string, int> manacher(string text){
	string T = "";                                  // new aux string
	int n = text.length();
	for (int i=0; i<n; i++){
		T += "|";                                   // adding "|" between each charatcter
		T += text[i];
	}
	T += "|";
	n = T.length();                                 // new length
	vector<int> L(n);
	L[0] = 0;
	L[1] = 1;
	int maxLong=0, maxCenter=0;
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
		else{
			L[ri] = 0;
			exp = true;
		}
		if (exp){
			while((ri + L[ri] < n) && (ri - L[ri] > 0) && (T[ri - L[ri] - 1] == T[ri + L[ri] + 1])){
				L[ri]++;
			}
		}
		c = ri;
		if (L[ri] > maxLong){
	    	maxLong = L[ri];
	    	maxCenter = ri;
	    }
	}
	int start = (maxCenter - maxLong) / 2;
	string exit = "";
	for (int i=start; i<(start+maxLong); i++){
		exit+=text[i];
	}
	return {exit, start};      // REGRESA PALINDROME Y POSICIÓN 
    //missing this structure: 

    //posiciónInicial posiciónFinal (para archivo de transmisión2) códigoMalicioso
}

//---------------------ACUMULAR CÓDIGO MALICIOSO -------------
//Malware se encuentra a manera de palindromes

// Complejidad: O(n)
void findPalindrome(ofstream &outputResult, vector<string> &transmissionN){
    vector< pair<string, int> > palindromes;
    for (int i=0; i<transmissionN.size(); i++){                
        palindromes.push_back(manacher(transmissionN[i]));
    }

    if (outputResult.is_open()){
        outputResult << "Palíndromo más grande:" << endl;
        for (int i=0; i<transmissionN.size(); i++){
            outputResult << "\tTransmision" << i+1 << ".txt" << " ==> " << "Posición: " << palindromes[i].second << endl;
            outputResult << "\t" << palindromes[i].first << endl;
            outputResult << "\t----" << endl;
        }
        outputResult << "\n==============\n" << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//PARTE 3 ACT INTEGRADORA

//--------------------------ENCONTRAR EL Longest Common Substring -------------------------------------- 

// Complejidad: O(n*m)
string LCSS(string st1, string st2){
    int longestCommonSS[MAX][MAX];
    int position = 0, length = 0;           

    // first column
    for (int i=0; i<st1.length(); i++){
        if (st1[i] == st2[0]){
            longestCommonSS[i][0] = 1;
            // length = 1;
        }
        else{
            longestCommonSS[i][0] = 0;
        }
    }

//Revisar primer fila
    for (int j=0; j<st2.length(); j++){
        if (st1[0] == st2[j]){
            longestCommonSS[0][j] = 1;
            length = 1;
        }
        else{
            longestCommonSS[0][j] = 0;
        }
    }

//Continuar revisando txt para resto de valores 
    for (int i=1; i<st1.length(); i++){
        for (int j=1; j<st2.length(); j++){
            if (st1[i] == st2[j]){
                longestCommonSS[i][j] = longestCommonSS[i-1][j-1] + 1;
                // length = (longestCommonSS[i][j] > length) ? longestCommonSS[i][j] : length;
                if (longestCommonSS[i][j] > length){
                    length += 1;                                            // update length if it gets surpassed
                    position = i;                                           // store position
                }
            }
            else{
                longestCommonSS[i][j] = 0;
            }
        }
    }
    return st1.substr(position-length+1, length);       // returns the substring from position=position-length+1 and of length=length
}

// Complejidad: O(1)
void getLongestSubstring (ofstream &outputResult, vector<string> transmissionN){
    if (outputResult.is_open()){
        outputResult << "Substring más largo:" << endl;
        
        outputResult << "\tSubstring más largo t1-t2 ==> " << LCSS(transmissionN[0], transmissionN[1]) << endl;
        outputResult << "\tSubstring más largo t1-t3 ==> " << LCSS(transmissionN[0], transmissionN[2]) << endl;
        outputResult << "\tSubstring más largo t2-t3 ==> " << LCSS(transmissionN[1], transmissionN[2]) << endl;
         
        outputResult << "==============\n" << endl;
    }
}


/* ----------------------------------------------------------------
   ---------------------------------------------------------------- */

int main(){
    //Variables para transición y revisión de cada caso de prueba
    string code1, code2, code3, t1, t2, t3;                        

    ifstream codeDoc("mcode1.txt");
    ifstream codeDoc2("mcode2.txt");
    ifstream codeDoc3("mcode3.txt");                      // reading files
    ifstream transmission1("transmission1.txt");
    ifstream transmission2("transmission2.txt");
    ifstream transmission3("transmission3.txt");
    ofstream outputResult("outputResult.txt");

    //Vector que almacena lo detectado como malware
    vector<string> mcodeN;  //Defined with N at the end, cause it has N values

    //Crear vector  para almacenar transmiciones                          
    vector<string> transmissionN;   //Defined with N at the end, cause it has N values               

/*
    //Enviar código hacía MCNODE para almacenar aquel correspondiente
    getline(codeDoc, code1);                     
    getline(codeDoc2, code2);
    getline(codeDoc3, code3);
    //Enviar detecciones de malware a los vectores correspondientes
    codeDoc.push_back(code1);
    codeDoc2.push_back(code2);
    codeDoc3.push_back(code3);*/

//Asignar variables a malware según el archivo así como inclusión a su mismo vector

    if (getline(codeDoc, code1)){
        mcodeN.push_back(code1);
    }else if(getline(codeDoc2, code2)){
        mcodeN.push_back(code2);
    }else if(getline(codeDoc3, code3)){
        mcodeN.push_back(code3);
    }else{
        cout<<"Document is not availabe to read malware"<<endl;
    }

    //Asignar a cada una de las transmisiones una de las variables creadas
    getline(transmission1, t1);                     
    getline(transmission2, t2);
    getline(transmission3, t3);

    //Enviar las transmisiones acumuladas en las vaariables hacía el vector de transmisiones
    transmissionN.push_back(t1);                    
    transmissionN.push_back(t2);
    transmissionN.push_back(t3);

    //findCodes(outputResult, transmissionN, mcodeN);   //FOR PART 1
    findPalindrome(outputResult, transmissionN);        //FOR PART 2
    getLongestSubstring(outputResult, transmissionN);   //FOR PART 3

    return 0;
}
