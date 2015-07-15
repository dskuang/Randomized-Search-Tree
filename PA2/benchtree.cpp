/****************************************************************************
                                                       Dominic Kuang
                                                       CSE 100, Winter 2015
                                                       cs100wdy
						       2/5/15
                                                       
                            Assignment Two

File Name:      benchtree.cpp
Description:    The program benchmarks the performance of a RST 
		implementation, an ordinary BST implementation, and the 
                C++ STL std::set structure (red-black tree). It  shows 
                how many comparisons were required to do a successful 
                find operation, in the average case".
****************************************************************************/

#include "RST.hpp"
#include "countint.hpp"
#include "BST.hpp"
#include <set>
#include <random>
#include <algorithm>

using namespace std;


/***************************************************************************
% Routine Name : dataStructTester(string tester, int num, string orderType)
% File :         benchtree.cpp
% 
% Description :  This function an insert and find into either a rst, bst,
		 or set. It keeps track of the count and returns that
		 as a double type to the main method
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% tester        a string of the data structure being tested
% num           an int to the current amount of N
% orderType	a string determining shuffled or sorted
% <return>      a double type           
***************************************************************************/
double dataStructTester(string tester, int num, string orderType) {
	
	int N = num;
	string order = orderType;
	string test = tester;

	std::vector<countint> v;
	v.clear(); 
 	
	for (int i = 0; i < N ; ++i) {
		v.push_back(i);
	}
	//checks if order is shuffled
	if (order == "shuffled") {
         	random_shuffle(v.begin(), v.end());
	}

	std::vector<countint>::iterator vit = v.begin();
	std::vector<countint>::iterator ven = v.end();
	//checks if tester is rst
	if(test == "rst"){
		RST<countint> r;	
		for(vit = v.begin(); vit != ven; ++vit){
			r.insert(*vit);
		}
		countint::clearcount();
		for(vit = v.begin(); vit != ven; ++vit) {
			r.find(*vit);
		}

	}
	//checks if tester is bst
	else if(test == "bst"){
		BST<countint> b;
		for(vit = v.begin(); vit != ven; ++vit){
			b.insert(*vit);
		}
		countint::clearcount();
		for(vit = v.begin(); vit != ven; ++vit) {
			b.find(*vit);
		}

	}
	//checks if tester is set
	else if(test ==  "set"){
		set<countint> s;
		for(vit = v.begin(); vit != ven; ++vit){
			s.insert(*vit);
		}
		countint::clearcount();
		for(vit = v.begin(); vit != ven; ++vit) {
			s.find(*vit);
		}
	}
	return countint::getcount();

}		




int main(int argc, char**argv){
	
	if(argc != 5){
		cout<<"Incorrect # of arguments"<<endl;
		return 1;
	}
		
	string test = argv[1];
	string order = argv[2];
	int maxSize = atoi(argv[3]);
	double numRuns = atoi(argv[4]);


	srand(static_cast<unsigned int>(time(NULL)));
	
	cout << 
      "# Benchmarking average number of comparisons for successful find"<< endl;
	cout << "# Data structure: "<< test << endl;
	cout << "# Data: "<< order<< endl;
	cout << "# N is powers of 2, minus 1, from 1 to "<<maxSize<< endl;
	cout << "# Averaging over "<< numRuns<<" for each N"<<endl;
	cout << "# "<<endl;
	cout << setw(6) << right << "# N" << "\t" <<  setw(16) << right << 
  		"avgComps" << setw(16) << right << 
		setiosflags(ios::fixed) << setprecision(6) << "stdev" << endl;
	
		//loops through maxsize
		for (int k = 1, N = 1; N <= maxSize; N = pow(2,++k)-1) {

			double avgComps = 0;
			double totalAvg = 0;
			double stdev = 0;
			double variance = 0;

			for (int z = 0; z < numRuns; z++) {  
				double compare = dataStructTester(test,N,order);
				avgComps += compare/(double)N;
				totalAvg += pow(compare/(double)N,2);
							
			}
			
			//calculates stdev 
			avgComps = avgComps/numRuns;
			totalAvg = totalAvg/numRuns;
			variance = abs(totalAvg - pow(avgComps,2));
			stdev = sqrt(variance);

			
			cout << setw(6) << right << N << "\t" <<  setw(16) << 
			right << avgComps << setw(16) << right << 
			setiosflags(ios::fixed) << setprecision(6) 
			<< stdev << endl;		
		}

	return 0;
}
