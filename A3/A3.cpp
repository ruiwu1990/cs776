#include <iostream>
#include <math.h>
#include <cstdlib> 
#include <ctime> 
#include <algorithm>
using namespace std;

double eval(int *pj);

void print_vec(int* vec, int arr_size){
	cout << "vector is: ";
	for(int i=0; i<arr_size; i++){
		cout << vec[i];
	}
	cout<<endl;
}

void generate_random_vec(int* vec[100], int population_num, int arr_size){
	// random generate population
	// TODO input vec[100][arr_size], should be ** but I am not too familiar with pointer
	srand((unsigned)time(0));
	for(int m=0; m<population_num; m++){
		for(int i=0; i<arr_size; i++){
			vec[m][i] = rand()%2;
		}	

	}
	
}

void get_fitness(int* vec[100], int fitness_vec[100], int population_num, int* cur_max, int arr_size){
	for(int m=0; m<population_num; m++){
		fitness_vec[m] = eval(vec[m]);
		
		if(eval(vec[m])>cur_max[0]){
			cur_max[0] = eval(vec[m]);
			cout<< "temp best vec:";
			print_vec(vec[m],arr_size);
			cout << "fitness = " << eval(vec[m]) << endl;
		}
		
		
	}
}

void cross_over(int* vec1, int* vec2, int cross_possiblility, int arr_size){
	// the function is used to do cross over between two vectors
	// the cross possibility is cross_possiblility, the cross position is cross_pos
	int temp_random = rand()%100;
	int cross_pos = (rand()%arr_size) - 1;
	int temp;
	
	if(temp_random <= cross_possiblility){
		for(int i=0; i<cross_pos; i++){
			temp = vec1[i];
			vec1[i] = vec2[i];
			vec2[i] = temp;
		}
		// cout<< "cross over happened"<<endl;
	}


}

void mutation(int* vec, int mutation_rate, int arr_size){
	int temp_mutation;
	for(int i=0; i<arr_size; i++){
		temp_mutation = rand()%1000;
		if(temp_mutation<=mutation_rate)
		{
			// if 1 then change into 0, else 0
			vec[i] = 1 - vec[i];
		}
	}
}

void selection(int* fitness_vec, int* vec[100], int* chosen_vec_index, int arr_size){
	
	int sum_fitness = 0;
	for(int i=0; i<100; i++){
		// ordered_fitness[i] = fitness_vec[i];
		sum_fitness = fitness_vec[i] + sum_fitness;
	}
	for(int m=0; m<100; m++){
		int aim_pos = rand()%sum_fitness;
		int temp_pos = 0;
		
		for(int i=0; i<100; i++){
			temp_pos = temp_pos + fitness_vec[i];
			if(temp_pos>=aim_pos){
				chosen_vec_index[m] = i;
				break;
			}
		}
	}

	// for(int i=0; i<100; i++){
	// 	cout<<"chosen_vec:"<<chosen_vec_index[i]<<endl;
	// }

}

int main()
{
  int arr_size = 150;
  int vec[150];
  int population_vec[100][150];
  int fitness_vec[100];
  int cur_max[1];
  int cross_possiblility = 80;
  //  this means  1% to mutate
  int mutation_rate = 1; 

  int chosen_vec_index[100];
  for(int i=0; i<100; i++){
  	chosen_vec_index[i] = -1;
  }

  cur_max[0] = 0;
  // for current version, I do not check duplicated elements
  generate_random_vec(population_vec,100,150);
  get_fitness(population_vec,fitness_vec,100,cur_max, arr_size);
  srand((unsigned)time(0));
  // cross_over(population_vec[0],population_vec[1], cross_possiblility);
  // mutation(population_vec[0],mutation_rate);
  while(true){
  	selection(fitness_vec, population_vec, chosen_vec_index);
  	for(int i=0; i<100; i=i+2){
  		cross_over(population_vec[chosen_vec_index[i]],population_vec[chosen_vec_index[i+1]], cross_possiblility,arr_size);
  		mutation(population_vec[chosen_vec_index[i]],mutation_rate,arr_size);
  		mutation(population_vec[chosen_vec_index[i+1]],mutation_rate,arr_size);
  	}

  	get_fitness(population_vec,fitness_vec,100,cur_max,arr_size);
  	// cout<<"111"<<endl;
  }


}