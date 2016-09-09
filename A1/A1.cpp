#include <iostream>
#include <math.h>

using namespace std;

double eval(int *pj);

int* modify(int* input_vec){

	for(int i=0; i<100; i++)
	{
		if(i%2 == 0)
		{
			input_vec[i] = 0;
		}
		else{
			input_vec[i] = 1;
		}			
		
	}
	return input_vec;
}

void add_one(int* input_vec, int pos){
	// this function change vec by add one
	if(input_vec[pos] == 0 && pos<100){
		input_vec[pos] = 1;
	}
	else if(input_vec[pos] == 1 && pos<100){
		input_vec[pos] = 0;	
		add_one(input_vec,pos+1);
	}
	else if(input_vec[pos] == 1 && pos==100){
		input_vec[pos] = 0;	
	}
	else if(input_vec[pos] == 0 && pos==100){
		input_vec[pos] = 1;	
	}
}

void minus_one(int* input_vec, int pos){
	// this function change vec by add one
	if(input_vec[pos] == 1 && pos<=100){
		input_vec[pos] = 0;
	}
	else if(input_vec[pos] == 0 && pos<100){
		input_vec[pos] = 1;	
		minus_one(input_vec,pos+1);
	}
	else if(input_vec[pos] == 0 && pos==100){
		input_vec[pos] = 1;	
	}
}

void duplicate_vec(int* old_vec, int* new_vec){
	for(int i=0; i<100; i++){
		new_vec[i] = old_vec[i];
	}
}

void print_vec(int* vec){
	cout << "vector is: ";
	for(int i=0; i<100; i++){
		cout << vec[i];
	}
	cout<<endl;
}

int main()
{
  int vec[100];
  int new_vec[100];

  int climb_step = pow(2,10);
  // this will be consumed if the current direction is changed
  int change_direction_times = 100;

  int i;
  // initial inputs here
  // the inital value is the middle of all the values
  // first 50 are 1 and next 50 are 0
  for(i = 0; i < 100; i++){
  	if(i<=50){
  		vec[i] = 1;	
  	}
  	else{
  		vec[i] = 0;	
  	}
    
  }

  double fitness;

  
  // temp
  int max = eval(vec);
  duplicate_vec(vec,new_vec);
  for(int m=0; m<1024; m++){
		add_one(new_vec,0);
  }


  int temp_fitness;

  // print_vec(vec);
  // print_vec(new_vec);
  // cout<<"temp max"<< eval(new_vec) <<endl;
  // cout<<"max"<< max <<endl;

  while(change_direction_times>=0){

  	temp_fitness = eval(new_vec);
  	cout << "temp fitness = " << temp_fitness << endl;
  	cout << "max = " << max << endl;
  	print_vec(new_vec);
  	if(temp_fitness>max){
  		max = temp_fitness;
  		// back up new_vec
  		duplicate_vec(vec,new_vec);
  		// if bigger ahead, then keep climbing
  		for(int m=0; m<climb_step; m++){
			add_one(new_vec,0);
 		}
 		cout<<"climb forward"<<endl;
  	}
  	else{
  		// if bigger behind, then climb back and the climb_step should be 
  		// half of previous climb step
  		climb_step = climb_step/2;
  		duplicate_vec(new_vec,vec);
  		for(int m=0; m<climb_step; m++){
			minus_one(new_vec,0);
 		}

 		change_direction_times = change_direction_times - 1;
 		cout<<"climb back"<<endl;
  	}
  	

  }

  

  cout << "fitness = " << max << endl;

  
}