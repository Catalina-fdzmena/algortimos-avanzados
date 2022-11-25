/*
** Integrantes:
**    José Emilio Alvear Cantú - A01024944
**    Andrea Catalina Fernández Mena - A01197705
**    Carlos Milano - A01383102
**
** Actividad:
**    Actividad 5.1 Implementación backtracking con Bitmask
**
----Instrucciones ----
**
** Compilacion para ejecucion:
**    g++ -o main.exe main.cpp
** Ejemplo de ejecucion:
**     
**    
*/

#include<iostream>
#include<vector>
#include<stdio.h>
#include<string.h>
#include<sstream> 
#define MOD 1000000007
using namespace std;

vector<int> capTypes[105];
vector<int> oneComb;
vector<vector<int> > combinations; 
int fullBit;

int dp[1025][101];
    
long long int posibleCombHats(int mask, int i)
{

    if (mask == fullBit){
      combinations.push_back(oneComb);
      oneComb = vector<int>(0,0);
      return 1;
    } 
    if (i > 100) return 0;
    if (dp[mask][i] != -1) return dp[mask][i];
  
    long long int ways = posibleCombHats(mask, i+1);
  
    int size = capTypes[i].size();
  
    for (int j = 0; j < size; j++)
    {
        if (mask & (1 << capTypes[i][j])) continue;

        vector<int> tmp = {i,j, mask | (1 << capTypes[i][j])};
        oneComb.push_back(i);
        ways += posibleCombHats(mask | (1 << capTypes[i][j]), i+1);
        ways %= MOD;
    }
    return dp[mask][i] = ways;
}
  
int main(){ 
  int n;  
  string temp, str;
  cin >> n;
  int x;    
  getline(cin, str);  
  for (int i=0; i<n; i++){
    getline(cin, str);
    stringstream ss(str);
    while (ss >> temp){
      stringstream s;
      s << temp;
      s >> x;
      capTypes[x].push_back(i);
    }
  }

  fullBit = (1 << n) - 1;
  

  memset(dp, -1, sizeof dp);
  int cnter =0;
  cout << posibleCombHats(0, 1) << endl;
  return 0;
}