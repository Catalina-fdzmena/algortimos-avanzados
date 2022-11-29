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
**    g++ -g main.exe main.cpp
** Ejemplo de ejecucion:
**     ./a.out < test01.txt
**    
*/

#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>

using namespace std;

bool regexNumber(string numb) { 
  const regex expReg("^[1-9]|10$");
  return regex_match(numb, expReg);
}

bool regexHat(string numb) { 
  const regex expReg("^([1-9]|[1-9][0-9]|100)$");
  return regex_match(numb, expReg);
}

bool validHatChoice (vector<int> currentComb, int currentHat) {
  for (auto hat : currentComb) {
    if (hat == currentHat) return false;
  }
  return true;
}

//Complejidad: O(2^N)
void findHatCombinations (int currentPerson, vector<vector<int> > hatsPerPerson, vector<bool> assignedHats, vector<int> currentCombination, vector<vector<int> > &hatsCombination) {
  if (all_of(assignedHats.begin(), assignedHats.end(), [](int i){return i == 1;})) {
    hatsCombination.push_back(currentCombination);
    return;
  }

  for (int person = currentPerson; person < hatsPerPerson.size(); person++) {
    if (!assignedHats[person]) { 
      for (int hat = 0; hat < hatsPerPerson[person].size(); hat++) {
          int currentHat = hatsPerPerson[person][hat];
          if (validHatChoice(currentCombination, currentHat)) {
            currentCombination.push_back(hatsPerPerson[person][hat]);
            assignedHats[person] = true;

            findHatCombinations(currentPerson + 1, hatsPerPerson, assignedHats, currentCombination, hatsCombination);

            currentCombination.pop_back();
            assignedHats[person] = false;
          }
      }
    }
  }
};

int main () {
  string inputNumberPersons;
  vector<vector<int> > hatsPerPerson;
  vector<bool> assignedHats;
  vector<vector<int> > hatsCombination;
  vector<int> currentCombination;

  cin >> inputNumberPersons;

  cin.ignore();
  for (int person = 0; person < stoi(inputNumberPersons); person++) {
    string inputHat;
    vector<int> hatsList;
    getline(cin, inputHat);
    
    stringstream ss(inputHat);
    for (string i; ss >> i;) {
      if (regexHat(i)) {
        hatsList.push_back(stoi(i));
      } else {
        exit(0);
      }
    }

    hatsPerPerson.push_back(hatsList);
    assignedHats.push_back(0);
  }

  findHatCombinations(0, hatsPerPerson, assignedHats, currentCombination, hatsCombination);

  cout << hatsCombination.size() << endl;
  for (int person = 0; person < hatsCombination.size(); person++) {
    cout << "(";
    for (int hat = 0; hat < hatsCombination[person].size(); hat++) {
      cout << hatsCombination[person][hat];
      if(hat < hatsCombination[person].size() - 1){
        cout << ",";
      }
      else{}
    }
    cout << ")\n";
  }
};