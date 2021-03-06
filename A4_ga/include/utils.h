/*
 * utils.h
 *
 *  Created on: Feb 3, 2016
 *      Author: sushil
 */

#ifndef UTILS_H_
#define UTILS_H_

void swap(int *x, int a, int b);
void shuffle(int *x, int size);

void printIntArray(int *x, int size);

void writeBufToFile(std::string buf, std::string filename);
void chromToString(int *x, int len, char *s);
void stringToChrom(char *chromChar, int len, int *chromInt);
float decode (int *chrom, int start, int end, float min, float max);
float decode(const char* chrom, int start, int end, float min, float max);
int if_number_in_array(int* array, int num, int len);
void remove_duplicate_element_in_array(int* array, int len);
// void parse_tsp_file(char* filename, float dist_info[52][2]);
void parse_tsp_file(char* filename, float dist_info[51][2]);

#endif /* UTILS_H_ */
