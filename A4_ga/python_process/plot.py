import matplotlib.pyplot as plt
import numpy as np

def plot(save_folder,input_file):
	fp = open(input_file,'r')
	y1 = []
	y2 = []
	y3 = []
	x = []

	for line in fp:
		temp_list = line.strip().split(',')
		x.append(temp_list[0])
		y1.append(temp_list[1])
		y2.append(temp_list[2])
		y3.append(temp_list[3])

	fig, ax = plt.subplots()
	ax.plot(x,y1, '-',linewidth=2, label=input_file+'_min')
	ax.plot(x,y2, '--',linewidth=2, label=input_file+'_avg')
	ax.plot(x,y3, ':',linewidth=2, label=input_file+'_max')
	legend = ax.legend(loc='center right', shadow=True)
	# legend = ax.legend(bbox_to_anchor=(0., 0.0, 1.0, .050), loc=3, ncol=1, mode="expand", borderaxespad=0.)

	plt.xlabel('generation')
	plt.ylabel('fitness')
	plt.title(input_file)
	# plt.show()
	fig.savefig(save_folder+input_file+'.png')

	fig, ax = plt.subplots()
	ax.plot(x,y1, '-',linewidth=2, label=input_file+'_min')
	legend = ax.legend(loc='lower right', shadow=True)
	plt.xlabel('generation')
	plt.ylabel('fitness')
	plt.title(input_file)
	fig.savefig(save_folder+input_file+'_min.png')	

	fig, ax = plt.subplots()
	ax.plot(x,y2, '--',linewidth=2, label=input_file+'_avg')
	legend = ax.legend(loc='lower right', shadow=True)
	plt.xlabel('generation')
	plt.ylabel('fitness')
	plt.title(input_file)
	fig.savefig(save_folder+input_file+'_avg.png')	

	fig, ax = plt.subplots()
	ax.plot(x,y3, ':',linewidth=2, label=input_file+'_max')
	legend = ax.legend(loc='lower right', shadow=True)
	plt.xlabel('generation')
	plt.ylabel('fitness')
	plt.title(input_file)
	fig.savefig(save_folder+input_file+'_max.png')	
	fp.close()

# plot('pic//','eil51.csv')
plot('pic//','berlin52.csv')
