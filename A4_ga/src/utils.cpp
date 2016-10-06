/*
 * utils.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: sushil
 */

#include <random.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <sstream>
#include <vector>

void swap(int *x, int i, int j){
	int tmp = x[i];
	x[i] = x[j];
	x[j] = tmp;
}

void shuffle(int *array, int size){
	for(int i = 0; i < size; i++){
		array[i] = i;
	}
	int a, b;
	for(int i = 0; i < size/2; i++){
		a = intInRange(0, size);
		b = intInRange(0, size);
		swap(array, a, b);
	}
}

void printIntArray(int *x, int size){
	for(int i = 0; i < size; i++){
		std::cout << x[i] << " ";
	}
	std::cout << std::endl;
}

void writeBufToFile(std::string buf, std::string filename){
	std::ofstream ofs(filename, std::ofstream::app);
	if(ofs.good()){
		ofs << buf;
	}
	ofs.flush();
	ofs.close();
}

void chromToString(int *chrom, int len, char *s){
	for(int i = 0; i < len; i++){
		s[i] = (chrom[i] == 0 ? '0' : '1');
	}
	s[len] = '\0';
	assert(strlen(s) == (unsigned int) len);
}

void stringToChrom(char *chromChar, int len, int *chromInt){
	for(int i = 0; i < len; i++){
		chromInt[i] = (chromChar[i] == '0' ? 0 : 1);
	}
}

float decode (int *chrom, int start, int end, float min, float max){
	int sum = 0;
	int powerOfTwo = 0;
	for(int i = start; i < end; i++){
		sum += (chrom[i] == 1 ? pow(2.0, powerOfTwo) : 0);
		powerOfTwo++;
	}
	float precision = (max - min)/pow(2.0, (double)(end-start));
	return min + (precision * sum);
}

float decode(const char* chrom, int start, int end, float min, float max){
	int sum = 0;
	for(int i = 0; i < end - start; i++){
		sum += (chrom[start + i] == '0' ? 0 : pow(2.0, (double) i));
	}
	float precision = (max - min)/pow(2.0, (double)(end-start));
	return min + (precision * sum);
}


// Rui check if the number is in the array, array[xp1:xp2] will not be checked
// coz the crossover part will be changed for sure
// return -1 if not in the array, return positive number means the position
int if_number_in_array(int* array, int num, int len){
	// std::cout<<"The array is:"<<std::endl;
	// for(int i=0; i<len; i++){
	// 	std::cout<<array[i];
	// }
	// std::cout<<std::endl;

	for(int i=0; i<len; i++){
		if(array[i] == num)
		{
			// // test
			// std::cout<<"repeat in array:"<<array[i]<<std::endl;
			// // std::cout<<"repeat in child:"<<num<<std::endl;
			// std::cout<<"---------------position:"<<i<<std::endl;
			// // test ends
			return i;
		}
	}
	return -1;
}

// Rui, I cannot handle c++ really.
// This function removes the duplicate elements and add the missing one
void remove_duplicate_element_in_array(int* array, int len){

	int* temp = new int[len];

	for(int k=0; k<len; k++){
		temp[k] = k;
	}
	for(int i=0; i<len; i++){

		for(int j=0; j<i; j++){
			temp[array[i]] = -1;
			if(array[i]==array[j])
			{
				for(int m=0; m<len; m++){
					if(temp[m]!=-1){
						array[i] = temp[m];
						temp[m] = -1;
						break;
					}
				}
				
			}
		}
	}

	delete [] temp;
}



// Rui this function is used to parse the tsp file
// the idea is from http://stackoverflow.com/questions/7868936/read-file-line-by-line
// len represents the city number
void parse_tsp_file(char* filename, float dist_info[52][2]){
	std::ifstream infile(filename);
	std::string line;

	// remove meta data lines
	int meta_data_length = 6;
	for(int i=0; i<meta_data_length; i++){
		std::getline(infile, line);
	}

	int count = 0;
	while(std::getline(infile, line)){
		// std::cout<<"+++++++++++++++++++++++++++++++++++"<<std::endl;
		std::istringstream iss(line);
		// std::istringstream iss(line);
		// int city_id;
		float city_id ,x, y;
		if(!(iss>>city_id>>x>>y))
		{
			// std::cout<<"------------------------------"<<std::endl;
			// this means reaching "EOF" line
			break;
		}
		dist_info[count][0] = x;
		dist_info[count][1] = y;
		// std::cout<<"city id:"<<city_id<<"; x:"<<x<<"; y:"<<y<<std::endl;
		count = count + 1;
	}

}

