def check_possible(n,cur_stat):
	'''
	this function check if the missionaries are alive
	'''
	bank_b = [n-cur_stat[0],n-cur_stat[1]]
	if cur_stat[0]>=0 and cur_stat[1]>=0 and bank_b[0]>=0 and bank_b[1]>=0:
		# only possible when more missionaries or no missionaries
		if (cur_stat[0]>=cur_stat[1] or cur_stat[0]==0) and (bank_b[0]>=bank_b[1] or bank_b[0]==0):
			return True
		else:
			return False
	else:
		return False

def m_c(n,boat_seat_count, cur_stat, result_list):
	'''
	river has two banks A and B, at start all people are on bank A
	cur_stat contains 3 numbers (first number means how many missionaries on one side of river 
	bank A and second number means how many cannibal on the bank A, the last element is for boat: 1 means 
	boat on bank A and 0 means boat on bank B), n people are missionaries and n are cannibals
	start state are [n,n,1] and final state are [0,0,0], let's assume there is at least a solution for all
	the problems
	'''
	if cur_stat == [0,0,0]:
		print 'Finished. Result is:'
		print result_list+[[0,0,0]]

	result_list.append(cur_stat[:])


	for people_in_boat in range(1,boat_seat_count+1):
		for m_in_boat in range(people_in_boat+1):
			c_in_boat = people_in_boat - m_in_boat
			# change boat position
			temp_stat = [None]*3
			if cur_stat[-1] == 0:
				temp_stat[-1] = 1
				# bank A will have more people
				temp_stat[0] = cur_stat[0] + m_in_boat
				temp_stat[1] = cur_stat[1] + c_in_boat
			else:
				temp_stat[-1] = 0
				# bank A will have less people
				temp_stat[0] = cur_stat[0] - m_in_boat
				temp_stat[1] = cur_stat[1] - c_in_boat

			if check_possible(n,temp_stat) == True and temp_stat not in result_list:
				m_c(n,boat_seat_count,temp_stat,result_list)

	# if the program can reach here, it means we should not push cur_stat
	result_list.pop()



if __name__ == "__main__":
	print 'Input the boat seat number'
	boat_seat_count = int(raw_input())
	m_c(3,boat_seat_count,[3,3,1],[])


