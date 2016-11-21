//============================================================================
// Name        : ga.cpp
// Author      : Sushil J Louis
// Version     :
// Copyright   : Copyright University of Nevada, Reno
// Description : GA in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <utils.h>
#include <population.h>
#include <ga.h>
#include <random.h>
#include <cstdlib> 
#include <ctime> 

using namespace std;
using namespace ga;

int main(int argc, char *argv[]) {

	srand((unsigned)time(0));
	for(int i=0; i<30; i++){
		GA ga = GA(argc, argv,i);

		ga.init();
		ga.run();
		ga.report();	
	}
	

	return 0;
}

GA::GA(int argc, char *argv[]){

	setupOptions(argc, argv, 0);
	srandom(options.randomSeed);
	ofstream ofs(options.outfile, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	ofstream pofs(options.phenotypeFile, std::ofstream::out | std::ofstream::trunc);
	pofs.close();
	maxFitGen = 0;
	this->bestIndividualSoFar = new Individual(options.chromLength);
	bestFitnessSoFar = -1;


}

GA::GA(int argc, char *argv[], int loop_count){

	setupOptions(argc, argv, loop_count);
	srandom(options.randomSeed);
	ofstream ofs(options.outfile, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	ofstream pofs(options.phenotypeFile, std::ofstream::out | std::ofstream::trunc);
	pofs.close();
	maxFitGen = 0;
	this->bestIndividualSoFar = new Individual(options.chromLength);
	bestFitnessSoFar = -1;


}


void GA::init(){
	parent = new Population(options);
	child  = new Population(options);
	parent->initialize(); // evaluates, stats, and reports on initial population
	updateProgress(0, parent);
//	cout << "initialized" << endl;
}



//
//void GA::CHC(Population *p, Population *c){
//}

void GA::run(){//chc

	Population *tmp;
	for (unsigned int i = 1; i < options.maxgens; i++){
	  //		parent->chc(child);
	        parent->generation(child);
		child->statistics();
		child->report(i);

		updateProgress(i, child);

		tmp = parent;
		parent = child;
		child = tmp;
		//cout << "Generation: " << i << endl;
	}

}

/**
 * Update and save the best ever individual
 */
void GA::updateProgress(unsigned int gen, Population *p){

  if (p->max > bestFitnessSoFar){
    bestFitnessSoFar = p->max;
    maxFitGen = gen;
    bestIndividualSoFar->copy(p->pop[p->maxi]);
    
    char printbuf[1024];
    char chromString[MAX_CHROM_LENGTH+1];
    chromToString(bestIndividualSoFar->chrom, bestIndividualSoFar->length, chromString);
    sprintf(printbuf, "%4i \t %f \t %s\n", maxFitGen, bestFitnessSoFar, chromString);
    writeBufToFile(printbuf, options.phenotypeFile);
  }
  
}


void GA::report(){
  //parent->report(options.maxgens);
  cout << *(parent->pop[parent->maxi]) << endl;
}

void GA::configure(){
	ifstream ifs(options.infile);
	if(ifs.good()){
		ifs >> options.popSize;
		ifs >> options.chromLength;
		ifs >> options.maxgens;
		ifs >> options.px;
		ifs >> options.pm;
		ifs >> options.scaler;
		ifs >> options.lambda;
	}
	ifs.close();
}

void GA::setupOptions(int argc, char *argv[], int loop_count){

	// base on time to change seed
	// srand((unsigned)time(0));
	// options.randomSeed = rand()%200;	
	options.randomSeed = 90 + 10 * loop_count;


	// options.randomSeed = 189;
	options.infile = string("infile");
	options.outfile = string("../results/outfile_")+to_string(loop_count);// append randomseed to output file names

	options.popSize = 100;
	// for first it should be 30, coz each x should be 10, from -5.12 to 5.12
	// for second it should be 24, coz each x should be 12, from -2.048 to 2.048
	// for third it should be 50, coz each x should be 10, from -5.12 to 5.12
	// for fourth it should be 240, coz each x should be 8, from -1.23 to 1.28
	options.chromLength = 132;
	options.maxgens = 100;
	options.px = 0.67f;
	options.pm = 0.001f;
	options.scaler = 1.05;
	options.lambda = 2;
	options.nCriteria = 1;

	options.mutator = Mutator::Flip;
	options.xover = Xover::UX;
	options.selector = Selector::Proportionate;

	if(argc == 4){
		options.infile = string(argv[1]);
		options.outfile = string(argv[2]);
		options.randomSeed = atoi(argv[3]);
		configure();
	}
	//derived values go after configure() above
	options.phenotypeFile   = string(options.outfile + ".pheno"); //derived from options.outfile
	//options.maxgens = options.popSize * 1.5;


}


