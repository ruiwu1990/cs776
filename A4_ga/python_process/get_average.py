def get_average_file(folder_location,output_file, model_run_num):
	filename = folder_location+'/outfile_'
	fp = open(output_file,'wb')
	temp_filename = []
	for i in range(model_run_num):
		temp_filename.append(open(filename + str(i),'r'))

	gen = -1;
	for line in temp_filename[0]:
		#  the last line is empty
		if line.strip() != '':
			gen = gen + 1
			temp_min = float(line.strip().split(' 	 ')[1])
			temp_avg = float(line.strip().split(' 	 ')[2])
			temp_max = float(line.strip().split(' 	 ')[3])
			for m in range(1,model_run_num):
				temp_line = temp_filename[m].readline()
				temp_min = temp_min + float(temp_line.strip().split(' 	 ')[1])
				temp_avg = temp_avg + float(temp_line.strip().split(' 	 ')[2])
				temp_max = temp_max + float(temp_line.strip().split(' 	 ')[3])

			temp_min = temp_min/model_run_num
			temp_avg = temp_avg/model_run_num
			temp_max = temp_max/model_run_num

			fp.write(','.join([str(gen),str(temp_min),str(temp_avg),str(temp_max)])+'\n')

	fp.close()



# get_average_file('temp','result.csv',2)
get_average_file('../A3_result/1_1','result1_1.csv',30)
get_average_file('../A3_result/1_2','result1_2.csv',30)
get_average_file('../A3_result/1_3','result1_3.csv',30)

get_average_file('../A3_result/2_1','result2_1.csv',30)
get_average_file('../A3_result/2_2','result2_2.csv',30)
get_average_file('../A3_result/2_3','result2_3.csv',30)

get_average_file('../A3_result/3_1','result3_1.csv',30)
get_average_file('../A3_result/3_2','result3_2.csv',30)
get_average_file('../A3_result/3_3','result3_3.csv',30)

get_average_file('../A3_result/4_1','result4_1.csv',30)
get_average_file('../A3_result/4_2','result4_2.csv',30)
get_average_file('../A3_result/4_3','result4_3.csv',30)