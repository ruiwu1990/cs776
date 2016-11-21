# def get_quality(input_file,num_model):
def get_quality(num_model,opt_num):
	'''
	this function get the quality 
	'''
	input_file = '../A4_result/outfile_'
	average_best = 0
	for i in range(num_model):
		cur_input_file = input_file + str(i) + '.pheno'
		fp = open(cur_input_file,'r')
		for line in fp:
			pass
		last_line = line
		average_best = average_best + float(last_line.strip().split(' 	 ')[1])
		fp.close()

	average_best = average_best/num_model
	print 'average best is:' + str(1/average_best)
	diff = (1/average_best) - opt_num
	print 'quality is:'+ str(100*diff/opt_num)+'%'
	return 1/average_best,str(100*diff/opt_num)+'%'

def get_realiability(num_model,average_best):
	input_file = '../A4_result/outfile_'
	result = 0

	for i in range(num_model):
		cur_input_file = input_file + str(i) + '.pheno'
		fp = open(cur_input_file,'r')
		for line in fp:
			pass
		last_line = line
		# print str((1/float(last_line.strip().split(' 	 ')[1]))-average_best)
		if average_best >= (1/float(last_line.strip().split(' 	 ')[1])):
			result = result + 1
		fp.close()
	# print result
	print 'reliability is:' + str(float(result)/num_model)
	return float(result)/num_model

def get_speed(num_model,average_best):
	'''
	'''
	input_file = '../A4_result/outfile_'
	result = 0

	for i in range(num_model):
		cur_input_file = input_file + str(i) + '.pheno'
		fp = open(cur_input_file,'r')
		for line in fp:
			if average_best >= (1/float(line.strip().split(' 	 ')[1])):
				result = result + float(line.strip().split(' 	 ')[0])
		fp.close()
	# print result
	print 'speed is:' + str(float(result)/num_model)
	return float(result)/num_model

# a,b = get_quality(30, 426)
# print get_realiability(30,a)
# print get_speed(30,a)


a,b = get_quality(30,  7542)
print get_realiability(30,a)
print get_speed(30,a)