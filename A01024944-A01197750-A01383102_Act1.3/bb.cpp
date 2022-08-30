#include <iostream>
#include <limits>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>

using namespace std;

#define TABSIZE 4

void knapsack(float* content, float* cost, float* utility, float maxCost, unsigned int size);
void BranchAndBound(bool* content, float* cost, float* utility, float maxCost, unsigned int size);

/*
 *	MAIN
 */

int main(){

    //Define la matriz
	bool content[TABSIZE] = {
		false,
		false,
		false,
		false
	};

	float utility[TABSIZE]	=	{8.f, 18.f, 20.f, 11.f};
	float cost[TABSIZE]		=	{3.f, 7.f, 9.f, 6.f};

	BranchAndBound(content, cost, utility, 17.f, TABSIZE);

	for(int i = 0; i < TABSIZE; i++){
		std::cout << content[i] << endl;
	}std::cout << '\n';

	float fcost = 0.f;
	for(int i = 0; i < TABSIZE; i++){
		fcost += content[i] * cost[i];
	}std::cout << "Cost = " << fcost << endl;

	return 0;
}

/*
 *	ALGOS
 */

struct uc{
	float ucRatio;
	unsigned int index;
};

int cmp(const void* elm1, const void* elm2){
	int a = ((uc*)elm1)->ucRatio;
	int b = ((uc*)elm2)->ucRatio;
	return a > b ? -1 : a < b;
}

/*
 *	BRANCH & BOUND
 */

struct bbNode{
	unsigned int	lev;
	bool*			set;
	float			benef;
	float			cost;
	float			bound;
};

float calculateBound(bbNode nd, float* cost, float* utility, uc* ucTab, float maxCost, unsigned int size){
	float addCost = 0.f;
	float addBenef = 0.f;

	for(int i = nd.lev; i < size; i++){
		if(nd.cost + addCost + cost[ucTab[i].index] > maxCost){
			//	Partial add of the best c/u object
			float partialBenefit = ((maxCost - addCost) / cost[ucTab[i].index]) * utility[ucTab[i].index];
			return nd.benef + addBenef + partialBenefit;
		}
		addCost += cost[ucTab[i].index];
		addBenef += utility[ucTab[i].index];
	}
	return nd.cost + addCost;
}

float calculateBenefit(bbNode nd, float* utility, unsigned int size){
	float res = 0.f;
	for(int i = 0; i < size; i++)
		if(nd.set[i])
			res+=utility[i];
	return res;
}

void cpyNode(bbNode* dest, bbNode src, unsigned int size){
	*dest = src;
	dest->set = (bool*)malloc(size * sizeof(bool));
	memcpy(dest->set, src.set, size * sizeof(bool));
}

void setNextObject(bbNode* nd, bool val, float* cost, uc* ucTab){
	nd->set[ucTab[nd->lev].index] = val;
	nd->cost += val * cost[ucTab[nd->lev].index];
	nd->lev++;
}

void BranchAndBound(bool* content, float* cost, float* utility, float maxCost, unsigned int size){
	//	Declarations
	uc* ucTab = (uc*)malloc(size * sizeof(uc));
	queue<bbNode> queueNd;

	//	Sorting items by Cost/Utility ratio
	for(int i = 0; i < size; i++){
		ucTab[i].ucRatio = utility[i] / cost[i];
		ucTab[i].index = i;
	}qsort(ucTab, size, sizeof(uc), cmp);

	//	Initializing level, set of items selected etc.
	bbNode bsf;
	
	bsf.lev = 0;
	bsf.set = (bool*)malloc(size * sizeof(bool));
	bsf.benef = - INFINITY;
	bsf.cost = 0.f;
	bsf.bound = 0.f;
	memset(bsf.set, 0, size * sizeof(bool));

	bbNode aNode;
	
	aNode.lev = 0;
	aNode.set = (bool*)malloc(size * sizeof(bool));
	aNode.benef = 0.f;
	aNode.cost = 0.f;
	aNode.bound = calculateBound(bsf, cost, utility, ucTab, maxCost, size);
	memset(aNode.set, 0, size * sizeof(bool));

	//	Enqueuing
	queueNd.push(aNode);

	while(!queueNd.empty()){
		bbNode currNode = queueNd.front();
		queueNd.pop();

		memcpy(content, currNode.set, size * sizeof(bool));

		float _cost = 0.f;
		cout << "Contenu : \n";
		for(int i = 0; i < size; i++){
			_cost += currNode.set[i] * cost[i];
			cout << currNode.set[i] << endl;
		}cout << "Cout : " << _cost << endl << endl;

		if(currNode.bound > bsf.benef){
			//	Create a node nextAdded equal to currNode with the next item added
			bbNode nextAdded;
			cpyNode(&nextAdded, currNode, size);
			delete[] currNode.set;	//	Memory management
			setNextObject(&nextAdded, true, cost, ucTab);
			nextAdded.bound = calculateBound(nextAdded, cost, utility, ucTab, maxCost, size);
			nextAdded.benef = calculateBenefit(nextAdded, utility, size);

			//	if nextAdded's benefit > bestSoFar's benefit
			if(nextAdded.benef > bsf.benef){
				//	set bsf equal to nextAdded
				delete[] bsf.set;
				cpyNode(&bsf, nextAdded, size);
			}

			//	if nextAdded's bound > bestSoFar's benefit
			if(nextAdded.bound > bsf.benef){
				//	enqueue nextAdded
				queueNd.push(nextAdded);
			}
		}

		//	Create a node nextNotAdded equal to currNode without the next item added
		bbNode nextNotAdded;
		cpyNode(&nextNotAdded, currNode, size);
		delete[] currNode.set;	//	Memory management
		setNextObject(&nextNotAdded, false, cost, ucTab);
		
		nextNotAdded.bound = calculateBound(nextNotAdded, cost, utility, ucTab, maxCost, size);
		nextNotAdded.benef = calculateBenefit(nextNotAdded, utility, size);
		
		//	if nextNotAdded's bound > bsf's benef
		if(nextNotAdded.bound > bsf.benef){
			//	enqueue nextNotAdded
			queueNd.push(nextNotAdded);
		}
	}
}


/*
 *	FAYARD PLATEAU
 */


void knapsack(float* content, float* cost, float* utility, float maxCost, unsigned int size){
	//	Tri des couts/utilité
	uc* ucTab = new uc[size];

	for(int i = 0; i < size; i++){
		ucTab[i].ucRatio = utility[i] / cost[i];
		ucTab[i].index = i;
	}

	qsort(ucTab, size, sizeof(uc), cmp);

	//	Ajout des objets dans le sac
	float totalCost = 0.f;
	for(int i = 0; i < size; i++){
		if(cost[ucTab[i].index] <= maxCost - totalCost){	//	Ajout total
			content[ucTab[i].index] = 1.f;
			totalCost += cost[ucTab[i].index];
		}
		else{												//	Ajout partiel
			float ratioAdd = (maxCost - totalCost) / cost[ucTab[i].index];
			content[ucTab[i].index] = ratioAdd;
			totalCost += cost[ucTab[i].index] * ratioAdd;
		}
	}
}