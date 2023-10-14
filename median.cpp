#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <time.h>
#include <algorithm>
#include <exception>

#define RSIZE(N) pow(N, 0.75)
#define RANDINPUT 0
#define INPUTSIZE 1000

std::vector<int> randElems(const std::vector<int> & input){
    int size = input.size();
    int rsize = RSIZE(size);
    
    std::vector<int> output(rsize);
    std::vector<int>::iterator end = output.end();
    for(std::vector<int>::iterator ite = output.begin(); ite != end; ite++)
	{
		int randelem = rand() % size;
		*ite = input.at(randelem);
	}
	return output; 
}

std::vector<int> computeC(int d, int u, const std::vector<int> & input, int *ld, int *lu){ // not by refernce
	std::vector<int>	output;
	std::vector<int>::const_iterator end = input.end();
    for(std::vector<int>::const_iterator ite = input.begin(); ite != end; ite++)
		if(*ite < d)
			*ld += 1;
		else if (*ite > u)
			*lu += 1;
		else
			output.push_back(*ite);
	return output;
}

int	randomizedMedianAlgorithm(const std::vector<int> & input)
{
	int	ld(0), lu(0), n = input.size(), r;
	
	std::vector<int>    rands = randElems(input);
	r = rands.size();
	std::stable_sort(rands.begin(), rands.end());
	int dpos = floor(RSIZE(n) / 2  - sqrt(n)) - 1 < 0 ? 0 : floor(RSIZE(n) / 2  - sqrt(n)) - 1;
	int upos = ceil((RSIZE(n) / 2  + sqrt(n))) - 1 >= r ? r - 1 : ceil((RSIZE(n) / 2  + sqrt(n))) - 1;
	std::vector<int>	cvector = computeC(rands.at(dpos), rands.at(upos), input, &ld, &lu);
	if ((ld > n / 2 - 1 || lu > n / 2 - 1) || //subtracted 1 to prevent crash
		cvector.size() > 4 * RSIZE(n))
	{
		std::cout << "Algorithm failed, try again." << std::endl;
		return (-1);
	}
	std::stable_sort(cvector.begin(), cvector.end());
	return cvector.at(n / 2 - ld); //without adding 1 because vector starts from 0
}

int main(void){
    std::vector<int>    input;

    srand(time(NULL));
	if(RANDINPUT)
		for(int i = 0; i < INPUTSIZE; i++)
			input.push_back(rand() % INPUTSIZE);
    else
		for(int i = 0; i < INPUTSIZE; i++)
			input.push_back(i);


	std::cout << randomizedMedianAlgorithm(input) << std::endl;
}