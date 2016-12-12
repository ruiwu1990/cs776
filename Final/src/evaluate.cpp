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
#include <sstream>
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

void rmse_eval(ga::Individual *ent){
	double x0 = (decode_local(ent->chrom, 0, 11) - 1024)/100;
	double x1 = (decode_local(ent->chrom, 11, 22) - 1024)/100;
	double x2 = (decode_local(ent->chrom, 22, 33) - 1024)/100;
	double x3 = (decode_local(ent->chrom, 33, 44) - 1024)/100;
	double x4 = (decode_local(ent->chrom, 44, 55) - 1024)/100;
	double x5 = (decode_local(ent->chrom, 55, 66) - 1024)/100;
	double x6 = (decode_local(ent->chrom, 66, 77) - 1024)/100;
	double x7 = (decode_local(ent->chrom, 77, 88) - 1024)/100;
	double x8 = (decode_local(ent->chrom, 88, 99) - 1024)/100;
	double x9 = (decode_local(ent->chrom, 99, 110) - 1024)/100;
	double x10 = (decode_local(ent->chrom, 110, 121) - 1024)/100;
	double x11 = (decode_local(ent->chrom, 121, 132) - 1024)/100;
	// cout<<"temp x1:"<<x1<<"temp x2:"<<x2<<"temp x3:"<<x3<<endl;
	// process the file and get rmse
	ifstream infile("data.csv");
	string line;
	float temp_arr [13];
	int count = 0;
	float predicted_NO3 = 0;
	
	float pi = 3.14159265359;
	float sum = 0;
	int total_line_num = 0;
	float dtime = 0;
	float decimal_time = 0;
	float center_decimal_time = 0 ;
	// remove the header
	getline(infile, line);
	// cout<<line<<endl;
	while (getline(infile, line))
	{
		total_line_num++;
	    istringstream ss(line);
	    string token;
	    string::size_type sz;
	    count  = 0;
	    // [0] TP, [1] OP, [2] ON, [3] temperature
	    // [4] Q, [5] DO, [6] PH, [7] day, [8] month, 
	    // [9] year, [10] hour, [11] minute, [12] NO3
	    while(std::getline(ss, token, ',')) {
		    // cout << token<<"////";
		    // convert string into float
		    temp_arr[count] = stof (token,&sz);
		    // convert negtive and 0 predictions into positive
		    // or some functions like log will not work
		    if(temp_arr[count]<=0){
		    	temp_arr[count] = 0.00001;
		    }
		    // cout << temp_arr[count]<<"////";
		    count++;
		}

		//month temp_arr[7]
		//day temp_arr[8]

        double decimal_time_date=0,decimal_time_time=0;

        decimal_time_date = ((temp_arr[7]*30)+temp_arr[8])/365;
        decimal_time_time = ((temp_arr[10]*60)+temp_arr[11])/(365*24*60);
        decimal_time =  decimal_time_date + decimal_time_time + temp_arr[9]; //with YEAR
        //decimal_time =  decimal_time_date + decimal_time_time; //without YEAR
        center_decimal_time = 2005.249334; //with YEAR
        //center_decimal_time = 0.497174658; //without YEAR
   
        dtime = decimal_time - center_decimal_time;

		//dtime = 1;

		predicted_NO3 = x0+x1*log(temp_arr[4])+x2*log(temp_arr[4]*temp_arr[4])+x3*sin(2*pi*dtime)+
			x4*cos(2*pi*dtime)+x5*dtime+x6*dtime*dtime/1e11+x7*temp_arr[5]+x8*temp_arr[3]+x9*temp_arr[2]+
			x10*temp_arr[1]+x11*temp_arr[0];

		// predicted_NO3 = x0+x1*log(temp_arr[4])+x2*log(temp_arr[4]*temp_arr[4])+x3*sin(2*pi*dtime)+
		// 	x4*cos(2*pi*dtime)+x5*dtime+x7*temp_arr[5]+x8*temp_arr[3]+x9*temp_arr[2]+
		// 	x10*temp_arr[1]+x11*temp_arr[0];

		// predicted_NO3 = x0 + x1*temp_arr[0] + x2*temp_arr[0]*temp_arr[0] +
		// 				x3 + x1*temp_arr[1] + x2*temp_arr[0]*temp_arr[0] +
		// 				x0 + x1*temp_arr[2] + x2*temp_arr[0]*temp_arr[0] +
		// 				x0 + x1*temp_arr[3] + x2*temp_arr[0]*temp_arr[0] +
		// 				x0 + x1*temp_arr[4] + x2*temp_arr[0]*temp_arr[0] +
		// 				x0 + x1*temp_arr[5] + x2*temp_arr[0]*temp_arr[0] +
		// 				x0 + x1*temp_arr[6] + x2*temp_arr[0]*temp_arr[0] +
		// 				x0 + x1*temp_arr[7] + x2*temp_arr[0]*temp_arr[0] +
		// 				x0 + x1*temp_arr[8] + x2*temp_arr[0]*temp_arr[0] +
		// 				x0 + x1*temp_arr[9] + x2*temp_arr[0]*temp_arr[0] +
		// 				x0 + x1*temp_arr[10] + x2*temp_arr[0]*temp_arr[0] +
		// 				x0 + x1*temp_arr[11] + x2*temp_arr[0]*temp_arr[0] +
		// 				x0 + x1*temp_arr[12] + x2*temp_arr[0]*temp_arr[0];
		


		sum = (temp_arr[12] - predicted_NO3)*(temp_arr[12] - predicted_NO3) + sum;

		// cout<<temp_arr[12]<<":---:"<< predicted_NO3<<endl;
		// // test
		// float temp = (temp_arr[12] - predicted_NO3)*(temp_arr[12] - predicted_NO3);
		// if(isnan(temp)){
		// 	cout<<temp_arr[12]<<"---"<< predicted_NO3<<endl;
		// 	cout<<temp_arr[0]<<"--"<<temp_arr[1]<<"--"<<temp_arr[2]<<"--"<<temp_arr[3]<<"--"<<temp_arr[4]<<"--"<<temp_arr[5]<<"--"<<temp_arr[6]<<endl;
		// 	cout<<x1*log(temp_arr[4])<<"---:"<<temp_arr[4]<<"---:"<<log(temp_arr[4])<<endl;

		// 	break;
		// }
        
		// cout<<"\n sin_pi_time: "<<sin(2*pi*dtime)<<"\t cos_pi_time: "<<cos(2*pi*dtime)<<"\n";
		// cout<<"\n sin_pi_timexxxx: "<<x3*sin(2*pi*dtime)<<"\t cos_pi_timexxxxx: "<<x4*cos(2*pi*dtime)<<"\n";
		// cout<<"jose is panda:"<<x6*dtime*dtime/1e11<<endl;
		// cout<<"\n predicted_NO3: "<<predicted_NO3<<"\n";
		// cout<<"\n aaaaa: "<<(temp_arr[12] - predicted_NO3)*(temp_arr[12] - predicted_NO3)<<"\n";
		//cout<<"\n sum: "<<sum;
		
	}
	// 1/rmse
	//cout<<(sqrt(sum/total_line_num))<<endl;
	ent->fit = 1.0/(sqrt(sum/total_line_num));
	//cout<<"\n ent->fit : "<< ent->fit ;

}

// void first_de_jong(ga::Individual *ent) {
// 	double x1 = (decode_local(ent->chrom, 0, 10) - 512)/100;
// 	double x2 = (decode_local(ent->chrom, 10, 20) - 512)/100;
// 	double x3 = (decode_local(ent->chrom, 20, 30) - 512)/100;
// 	ent->fit = 1/ ((x1*x1) + (x2*x2) + (x3*x3));
// 	// cout<<"temp x1:"<<x1<<"temp x2:"<<x2<<"temp x3:"<<x3<<endl;
// 	return;
// }

// void second_de_jong(ga::Individual *ent) {
// 	double x1 = (decode_local(ent->chrom, 0, 12) - 2048)/1000;
// 	double x2 = (decode_local(ent->chrom, 12, 24) - 2048)/1000;
// 	ent->fit = 1/(x1*x1-x2)*(x1*x1-x2) + (1-x1)*(1-x1);
// 	// cout<<"temp x1:"<<x1<<"temp x2:"<<x2<<endl;
// 	return;	
// }

// void third_de_jong(ga::Individual *ent) {
// 	double x1 = (decode_local(ent->chrom, 0, 10) - 512)/100;
// 	double x2 = (decode_local(ent->chrom, 10, 20) - 512)/100;
// 	double x3 = (decode_local(ent->chrom, 20, 30) - 512)/100;
// 	double x4 = (decode_local(ent->chrom, 30, 40) - 512)/100;
// 	double x5 = (decode_local(ent->chrom, 40, 50) - 512)/100;

// 	if((float)(int(x1)+int(x2)+int(x3)+int(x4)+int(x5)) == 0)
// 	{
// 		ent->fit = pow(2,32);
// 	}
// 	else
// 	{
// 		ent->fit = 1.0/(float)(int(x1)+int(x2)+int(x3)+int(x4)+int(x5));
// 	}
	
// 	// cout<<"temp x1:"<<x1<<" temp x2:"<<x2<<" temp x3:"<<x3<<" temp x4:"<<x4<<" temp x5:"<<x5<<endl;
// 	// cout<<"temp:"<<(float)(int(x1)+int(x2)+int(x3)+int(x4)+int(x5))<<endl;
// 	return;	
// }


// void fourth_de_jong(ga::Individual *ent) {
// 	double x[30];
// 	double pi = 3.1415926;
// 	for(int i=0; i<30; i++){
// 		x[i] = (decode_local(ent->chrom, 8*i, 8*(i+1)) - 128)/100;
// 	}

// 	ent->fit = 0;
// 	for(int i=0; i<30; i++){
// 		ent->fit = ent->fit + (1/(x[i]*x[i]*x[i]*x[i]*(i+1)+((exp(-1*x[i]*x[i]/2))/(sqrt(2*pi)))));
// 	}
// 	return;

// }