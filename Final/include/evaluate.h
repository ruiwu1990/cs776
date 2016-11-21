/*
 * evaluate.h
 *
 *  Created on: Mar 15, 2016
 *      Author: sushil
 */

#ifndef EVALUATE_H_
#define EVALUATE_H_

#include <individual.h>
#include <cstring>

void evaluate(ga::Individual *ent);
void xSquared(ga::Individual *ent);
// void first_de_jong(ga::Individual *ent);
// void second_de_jong(ga::Individual *ent);
// void third_de_jong(ga::Individual *ent);
// void fourth_de_jong(ga::Individual *ent);
void rmse_eval(ga::Individual *ent);

void convertToString(int *vec, int size, char *chrom);
double decode_local(int * chrom, int start, int end);
#endif /* EVALUATE_H_ */
