/*
** Integrantes:
**    José Emilio Alvear Cantú - A01024944
**    Andrea Catalina Fernández Mena - A01197705
**    Carlos Milano - A01383102
**
** Actividad:
**    Actividad 5.1 Implementación backtracking con Bitmask
**
** Referencias:
** Revisar un string es un número: https://www.baeldung.com/java-check-string-number 
** Subsets Bitmask approach:  https://www.geeksforgeeks.org/find-distinct-subsets-given-set/ 
**
**
----Instrucciones ----
** Compilacion para ejecucion:
**    g++ -o main.exe main.cpp
** Ejemplo de ejecucion:
-------------forma2----------------
** Compilacion para ejecucion:
** g++ -std=c++17 -O3 -o main *.cpp
** ./main < TestCases/test01.txt
** 
*/

//Preprocesors

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <string.h>

//Función booleanas para definir si un valor es de tipo char o no
bool isChar(unsigned char mask, int pos)
{
  return ((mask & (1 << pos)) != 0);
}

//Función booleanas para definir si un valor es de tipo integer
bool isInt(unsigned int mask, int pos)
{ 
    return ((mask & (1 << pos)) != 0);
}

//Función para guardar con bitmask números enteros


//Función para guardar con bitmask caractéres 


//Función para comprobar si se trata de un número


//Func convertir string a array


//Main func

int main()
{

    return 0; 
}