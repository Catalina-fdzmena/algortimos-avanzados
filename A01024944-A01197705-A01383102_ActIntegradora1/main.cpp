// Actividad Integradora 1

// Jose Emilio Alvear Cantu - A01024944
// Andrea Catalina Fernandez Mena - A01197750
// Carlos Milano - A01383102

/*

--Instrucciones-- 

En equipos de máximo 3 personas (la entrega es individual), escribe un programa en C++ que lea 5 archivos de texto (de nombre fijo, no se piden al usuario) que contienen exclusivamente caracteres del 0 al 9, caracteres entre A y F y saltos de línea
     transmission1.txt
     transmission2.txt
     mcode1.txt
     mcode2.txt
     mcode3.txt

Los archivos de transmisión contienen caracteres de texto que representan el envío de datos de un dispositivo a otro.
Los archivos mcodeX.txt representan código malicioso que se puede encontrar dentro de una transmisión.

El programa debe analizar si el contenido de los archivos mcode1.txt, mcode2.txt y mcode3.,txt están contenidos en los archivos transmission1.txt y transmission2.txt y desplegar un true o false si es que las secuencias de chars están contenidas o no. En caso de ser true, muestra true, seguido las posiciones (cero basadas) en el archivo de transmissiónX.txt donde inicia el código de mcodeY.txt separadas por un espacio. 

Suponiendo que el código malicioso tiene siempre código "espejeado" (palíndromos de chars), sería buena idea buscar este tipo de código en una transmisión. El programa después debe buscar si hay código "espejeado" dentro de los archivos de transmisión. (palíndromo a nivel chars, no meterse a nivel bits),  muestra en una sola línea separados por un espacio dos enteros correspondientes a la posición (cero basadas) en donde inicia y termina el código "espejeado" más largo (palíndromo) para cada archivo de transmisión y dicho código malicioso. Puede asumirse que siempre se encontrará este tipo de código y es independiente de los códigos en los archivos mcodeX.txt.

Finalmente el programa analiza qué tan similares son los archivos de transmisión, y debe mostrar (separados por un espacio) la posición inicial, la posición final (cero basadas) del primer archivo en donde se encuentra el substring más largo común entre ambos archivos de transmisión, así como dicho substring.

Es indispensable respetar el formato de salida especificado a continuación.

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

#define MAX 1001


/* PART 1*/

// auxiliary function for KMP
// Complexity O(n)
vector<int> lpsvFunc(string patron){
    int n = patron.length();
    vector<int> lpsv(n, 0);             // longest proper prefix lo ponemos como sufijo
    int j=0, i=1;
    while (i < n){
        if (patron[i] == patron[j]){    //si coinciden ambos patrones
            lpsv[i] = j+1;
            i++;
            j++;
        }
        else{                           // Si no coincide
            if (j == 0){                // if it's at the start
                lpsv[i] = 0;
                i++;
            }
            else{                       // move one index back
                j = lpsv[j-1];
            }
        }
    }
    return lpsv;
}