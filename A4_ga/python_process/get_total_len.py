# 40-44-4-18-16-12-39-37-36-19-14-15-28-42-26-33-2-48-30-17-20-7-45-47-0-41-1-6-32-3-9-10-5-8-11-34-13-22-35-21-38-23-24-25-27-29-31-39-43-46-49-50-
# "../data/berlin52.tsp"
import math

def get_total_len(input_file,city_arr):
	'''
	The function calculates the final total distances
	'''
	fp = open(input_file,'r')
	temp_arr = []
	for line in fp:
		if 'EOF' in line:
			break
		# print line
		temp_arr.append([float(i) for i in line.strip().split(' ')])

	city_order = [int(i) for i in city_arr.split('-')]

	total_len = 0
	arr_len = len(city_order)
	for count in range(arr_len-1):
		total_len = total_len + math.sqrt(pow(temp_arr[city_order[count]][1]-temp_arr[city_order[count+1]][1],2)+pow(temp_arr[city_order[count]][2]-temp_arr[city_order[count+1]][2],2))
	print "total len is:" + str(total_len)

	print  "city arr len:"+str(arr_len)
	fp.close()

def opt_total_len(input_file, opt_file):
	'''
	this function calculates the optimal best length
	'''
	fp = open(input_file,'r')
	
	fp1 = open(opt_file,'r')
	temp_arr = []
	for line in fp:
		if 'EOF' in line:
			break
		# print line
		temp_arr.append([float(i) for i in line.strip().split(' ')])

	city_order = []
	for line in fp1:
		if '-1' in line:
			break
		city_order.append(int(line.strip())-1)

	total_len = 0
	arr_len = len(city_order)
	for count in range(arr_len-1):
		total_len = total_len + math.sqrt(pow(temp_arr[city_order[count]][1]-temp_arr[city_order[count+1]][1],2)+pow(temp_arr[city_order[count]][2]-temp_arr[city_order[count+1]][2],2))
	print "total len is:" + str(total_len)

	print  "opt arr len:"+str(arr_len)
	fp.close()
	fp1.close()

# city_arr = '47-44-17-0-24-32-50-18-1-49-40-36-4-33-21-2-30-29-43-28-42-27-3-34-38-41-5-48-37-6-7-8-9-10-12-13-35-14-15-19-16-20-22-11-25-31-17-23-39-45-46-26'
city_arr = '26-35-24-20-21-19-17-41-44-23-30-1-22-47-48-49-32-14-18-40-4-0-27-25-16-45-38-6-7-2-43-11-12-3-5-8-9-10-13-15-28-31-37-29-39-42-34-33-36-44-50-51'
input_file = "../data/berlin52.tsp"
opt_file = "../data/berlin52.opt.tour"
get_total_len(input_file,city_arr)
opt_total_len(input_file,opt_file)


city_arr = '38-1-35-28-3-17-13-36-0-25-19-34-2-37-49-15-48-10-7-18-46-43-9-29-5-47-16-4-50-31-22-27-6-24-11-12-44-8-14-20-26-21-23-30-32-33-36-41-40-42-45'
input_file = "../data/eil51.tsp"
opt_file = "../data/eil51.opt.tour"
get_total_len(input_file,city_arr)
opt_total_len(input_file,opt_file)
