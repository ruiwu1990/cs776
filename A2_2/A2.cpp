#include <iostream>
#include <math.h>
#include <cstdlib> 
#include <ctime> 
#include <algorithm>
using namespace std;

double eval(int *pj);

void print_vec(int* vec){
	cout << "vector is: ";
	for(int i=0; i<150; i++){
		cout << vec[i];
	}
	cout<<endl;
}

void generate_random_vec(int vec[100][150], int population_num){
	// random generate population
	// TODO input vec[100][150], should be ** but I am not too familiar with pointer
	srand((unsigned)time(0));
	for(int m=0; m<population_num; m++){
		for(int i=0; i<150; i++){
			vec[m][i] = rand()%2;
		}	
		// print_vec(vec[m]);
		// cout << "fitness = " << eval(vec[m]) << endl;
	}
	
}

void get_fitness(int vec[100][150], int fitness_vec[100], int population_num, int* cur_max){
	for(int m=0; m<population_num; m++){
		fitness_vec[m] = eval(vec[m]);
		
		if(eval(vec[m])>cur_max[0]){
			cur_max[0] = eval(vec[m]);
			cout<< "temp best vec:";
			print_vec(vec[m]);
			cout << "fitness = " << eval(vec[m]) << endl;
		}
		
		
	}
}

void cross_over(int vec1[150], int vec2[150], int cross_possiblility){
	// the function is used to do cross over between two vectors
	// the cross possibility is cross_possiblility, the cross position is cross_pos
	int temp_random = rand()%100;
	int cross_pos = (rand()%150) - 1;
	int temp;
	// print_vec(vec1);
	// print_vec(vec2);
	if(temp_random <= cross_possiblility){
		for(int i=0; i<cross_pos; i++){
			temp = vec1[i];
			vec1[i] = vec2[i];
			vec2[i] = temp;
		}
		// cout<< "cross over happened"<<endl;
	}
	// cout<<"cross over and pos"<<cross_pos<<endl;
	// print_vec(vec1);
	// print_vec(vec2);

}

void mutation(int vec[150], int mutation_rate){
	// print_vec(vec);
	int temp_mutation;
	for(int i=0; i<150; i++){
		temp_mutation = rand()%1000;
		if(vec[i]!=0 && vec[i]!=1){
			cout<<"here is something wrong!!!!"<<1-vec[i]<<"aaaa"<<vec[i]<<endl;
			print_vec(vec);
		}
		if(temp_mutation<=mutation_rate)
		{
			// if 1 then change into 0, else 0
			vec[i] = 1 - vec[i];
		}
		if(vec[i]!=0 && vec[i]!=1){
			cout<<"here is something wrong????"<<endl;
			print_vec(vec);
			throw std::exception();
		}
	}
	// print_vec(vec);
}

void selection(int* fitness_vec, int vec[100][150], int* chosen_vec_index){
	
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
  generate_random_vec(population_vec,100);
  get_fitness(population_vec,fitness_vec,100,cur_max);
  srand((unsigned)time(0));
  // cross_over(population_vec[0],population_vec[1], cross_possiblility);
  // mutation(population_vec[0],mutation_rate);
  while(true){
  	selection(fitness_vec, population_vec, chosen_vec_index);
  	for(int i=0; i<100; i=i+2){
  		cross_over(population_vec[chosen_vec_index[i]],population_vec[chosen_vec_index[i+1]], cross_possiblility);
  		mutation(population_vec[chosen_vec_index[i]],mutation_rate);
  		mutation(population_vec[chosen_vec_index[i+1]],mutation_rate);
  	}
  	// first pair
  	// cross_over(population_vec[chosen_vec_index[0]],population_vec[chosen_vec_index[1]], cross_possiblility);
  	// mutation(population_vec[chosen_vec_index[0]],mutation_rate);
  	// mutation(population_vec[chosen_vec_index[1]],mutation_rate);
  	// // second pair
  	// cross_over(population_vec[chosen_vec_index[2]],population_vec[chosen_vec_index[3]], cross_possiblility);
  	// mutation(population_vec[chosen_vec_index[2]],mutation_rate);
  	// mutation(population_vec[chosen_vec_index[3]],mutation_rate);

  	get_fitness(population_vec,fitness_vec,100,cur_max);
  	// cout<<"111"<<endl;
  }


}