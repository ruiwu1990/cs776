/*
 * evaluate.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: sushil
 */

#include <evaluate.h>
#include <utils.h>
#include <const.h>

#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

void evaluate(ga::Individual *ent){
//	cout << *ent << endl;
	double sum = 0;
	for(int i = 0; i < ent->length; i++){
		sum += ent->chrom[i];
	}
	ent->fit = sum;
	for(int i = 0; i < ga::MAX_CRITERIA; i++){
		ent->fitness[i] = sum;
	}

//	cout << "----------------------------------------" << endl;

}

double decode(int * chrom, int start, int end){
  double prod = 0;
  for (int i = start; i < end; i++){
    prod += (chrom[i] == 0 ? 0 : pow(2.0, (double) i));
  }
  return prod;
}

double decode_local(int * chrom, int start, int end){
  double prod = 0;
  for (int i = start; i < end; i++){
    prod += (chrom[i] == 0 ? 0 : pow(2.0, (double) (i-start) ));
  }
  return prod;
}

void xSquared(ga::Individual *ent) {
  int value = decode(ent->chrom, 0, ent->length);
  ent->fit = value * value;
  return;

}

// int max_value = pow(2,32);

void first_de_jong(ga::Individual *ent) {
	double x1 = (decode_local(ent->chrom, 0, 10) - 512)/100;
	double x2 = (decode_local(ent->chrom, 10, 20) - 512)/100;
	double x3 = (decode_local(ent->chrom, 20, 30) - 512)/100;
	ent->fit = 1/ ((x1*x1) + (x2*x2) + (x3*x3));
	// cout<<"temp x1:"<<x1<<"temp x2:"<<x2<<"temp x3:"<<x3<<endl;
	return;
}

void second_de_jong(ga::Individual *ent) {
	double x1 = (decode_local(ent->chrom, 0, 12) - 2048)/1000;
	double x2 = (decode_local(ent->chrom, 12, 24) - 2048)/1000;
	ent->fit = 1/(x1*x1-x2)*(x1*x1-x2) + (1-x1)*(1-x1);
	// cout<<"temp x1:"<<x1<<"temp x2:"<<x2<<endl;
	return;	
}

void third_de_jong(ga::Individual *ent) {
	double x1 = (decode_local(ent->chrom, 0, 10) - 512)/100;
	double x2 = (decode_local(ent->chrom, 10, 20) - 512)/100;
	double x3 = (decode_local(ent->chrom, 20, 30) - 512)/100;
	double x4 = (decode_local(ent->chrom, 30, 40) - 512)/100;
	double x5 = (decode_local(ent->chrom, 40, 50) - 512)/100;

	if((float)(int(x1)+int(x2)+int(x3)+int(x4)+int(x5)) == 0)
	{
		ent->fit = pow(2,32);
	}
	else
	{
		ent->fit = 1.0/(float)(int(x1)+int(x2)+int(x3)+int(x4)+int(x5));
	}
	
	// cout<<"temp x1:"<<x1<<" temp x2:"<<x2<<" temp x3:"<<x3<<" temp x4:"<<x4<<" temp x5:"<<x5<<endl;
	// cout<<"temp:"<<(float)(int(x1)+int(x2)+int(x3)+int(x4)+int(x5))<<endl;
	return;	
}


void fourth_de_jong(ga::Individual *ent) {
	double x[30];
	double pi = 3.1415926;
	for(int i=0; i<30; i++){
		x[i] = (decode_local(ent->chrom, 8*i, 8*(i+1)) - 128)/100;
	}

	ent->fit = 0;
	for(int i=0; i<30; i++){
		ent->fit = ent->fit + (1/(x[i]*x[i]*x[i]*x[i]*(i+1)+((exp(-1*x[i]*x[i]/2))/(sqrt(2*pi)))));
	}
	return;

}