/*
 * individual.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: sushil
 */

#include <individual.h>
#include <stdlib.h>
#include <random.h>
#include <assert.h>
#include <cstdlib> 
#include <ctime> 
using namespace std;
using namespace ga;

// Rui modified
Individual::Individual(){
	length    = 0;
	// base on time to change seed
	srand((unsigned)time(0));
	setup();
}

Individual::Individual(int len){
	length = len;
	setup();
}

void Individual::setup(){
	for(int i = 0; i < length; i++){
		this->chrom[i] = -1;
	}
}

// Rui modify this function to generate possible combo for TSP
bool Individual::check_repeat(int temp, int cur_pos){
	for(int i = 0; i < length; i++){
		if(temp == this->chrom[i]){
			return true;
		}
	}
	return false;
}

void Individual::init(int len){
	assert(len <= MAX_CHROM_LENGTH);
	length = len;

	int temp;
	for(int i = 0; i < length; i++){
		// this->chrom[i] = flip(0.5);
		temp = rand()%len;
		while(this->check_repeat(temp,i) == true){
			temp = rand()%len;
		}
		
		this->chrom[i] = temp;	
	}
}



void Individual::mutate(float prob){
	for(int i = 0; i < length; i++){
		if(flip(prob) == 1)
			chrom[i] = 1 - chrom[i];
	}
}

void Individual::copy(Individual *ip){
	assert(ip->length <= MAX_CHROM_LENGTH);
	this->length = ip->length;
	for(int i = 0; i < length; i++){
		this->chrom[i] = ip->chrom[i];
	}
	for(int i = 0; i < MAX_CRITERIA; i++){
		this->fitness[i] = ip->fitness[i];
		this->objectives[i] = ip->objectives[i];
	}
	this->fit = ip->fit;
	this->scaledFit = ip->scaledFit;
}

