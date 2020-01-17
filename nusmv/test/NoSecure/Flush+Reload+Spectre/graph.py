#!/usr/bin/python
# -*- coding: UTF-8 -*-
import re;
import sys;
import os;
import copy;

class Trace:
    def __init__(self):  
        self.trace_index=0;
        self.trace_state_index=0;
        self.trace_state_dic=[];
        self.filled_trace_state_dic=[];
        self.phase="";

# class MultipleCounterexample:
#     def __init__(self):  
#         self.list = []     

	# r_time = 0
	# w_time = 0
	# attacker.cmd = branch
	# attacker.rw_addr = SC_addr
	# victim.cmd = nop
	# cache.ExistStateSC = TRUE
	# cache.ExistStateOT = TRUE
	# predictor.Predict = nop
	# cpu.state = normal
	# evict = FALSE
	# cache.evict = FALSE
black_list=["attacker.cmd","victim.cmd"]
white_list=["cache.ExistStateOT","cpu.state","predictor.Predict","cache.ExistStateSC","cache.ExistStateOT","r_time","w_time","cache.evict","cpu.isflush"]
# white_list=["cache.ExistStateOT","cpu.state","predictor.Predict","cache.ExistStateSC","cache.ExistStateOT","r_time","w_time","cache.evict","cpu.isflush"]
# white_list=["cpu.state","predictor.Predict","cache.ExistStateSC","w_time","cache.evict","cpu.isflush"]
# phase_evict={"victim.cmd":"flush","cpu.state":"evict"}

phase_n=[0,0,1]
phase_key=["attacker.cmd","victim.cmd","cpu.state"]
phase_value=["flush","flush","squash"]

phase_target_key=["cache.ExistStateSC","cache.ExistStateSC","cache.ExistStateSC"];
phase_target_value=["0","0","1"];

# phase_evict_index=[-1,-1,-1,-1]


# white_list=["cpu.state"]

def file2list(fdir):
	files = os.listdir(fdir)

	# fdir="."
	# files=["F00.smv.ce"]

	cnt=0
	multi_counterexample_path_list=[]
	for fpath in files:
		f = open(fdir+'/'+ fpath, 'r')
		multi_counterexample=f.read().replace('\n',' ').replace('\t','')
		# print(multi_counterexample)
		pattern = re.compile(r'-> State: ([0-9]*).([0-9]*) <-([\s|_|.|=|0-9A-Za-z]*)')
		results=re.findall(pattern,multi_counterexample)
		# print(results)

		path = re.compile(r'([\S]*) = ([\S]*)')


		index_last=1
		index_current=1;
		counterexample=[]

		for i in range(len(results)):
			# print(results[i])
			trace = Trace()
			index_current= int(results[i][0])
			trace.trace_index =cnt
			trace.trace_state_index=results[i][1]
			states={}
			tmp_states=re.findall(path,results[i][2])
			# print(tmp_states)
			for j in range(len(tmp_states)):
				states[tmp_states[j][0]]=tmp_states[j][1];
			# print(states)
			trace.trace_state_dic=states


            #从这里下手 将缺少的状态填充完毕
			if(index_current!=index_last):
				multi_counterexample_path_list.append(counterexample);
				# print(len(counterexample))
				counterexample=[];
				index_last=index_current;
				cnt=cnt+1
				trace.trace_index=cnt

				for path_fill_i in range(int(trace.trace_state_index)-1):
					fill_trace = Trace()
					fill_trace.trace_index=cnt
					fill_trace.trace_state_index=path_fill_i+1
					fill_trace.trace_state_dic=multi_counterexample_path_list[-1][path_fill_i].trace_state_dic.copy()
					counterexample.append(fill_trace)

			counterexample.append(trace)
		if(len(counterexample)>0):
			multi_counterexample_path_list.append(counterexample);
		cnt=cnt+1

	multi_counterexample_path_list.sort(key=len)
	return multi_counterexample_path_list

def fill_states(multi_counterexample_path_list):
	# print(multi_counterexample_path_list)
	phase_evict_index=-1;
	for i in range(len(multi_counterexample_path_list)):
		# every counterexample
		items=[]
		phase_evict_index=[-1,-1];
		phase_str=["",""];

		for j in range(len(multi_counterexample_path_list[i])):
			if(j==0):
				items=list(multi_counterexample_path_list[i][j].trace_state_dic.keys());
				multi_counterexample_path_list[i][j].filled_trace_state_dic=multi_counterexample_path_list[i][j].trace_state_dic.copy()
				for x in range(len(items)):
					if(items[x] not in white_list and items[x] not in black_list):   #除了黑名单和白名单外的item都删除掉;
						multi_counterexample_path_list[i][j].filled_trace_state_dic.pop(items[x])
				items=list(multi_counterexample_path_list[i][j].filled_trace_state_dic.keys());

			else:
				# items=list(multi_counterexample_path_list[i][j-1].filled_trace_state_dic.keys());
				multi_counterexample_path_list[i][j].filled_trace_state_dic={};#multi_counterexample_path_list[i][j].trace_state_dic.copy();
				for k in range(len(items)):
					if(not ( items[k] in multi_counterexample_path_list[i][j].trace_state_dic)):  #item不存在本trace中则从上一个trace中取值
						multi_counterexample_path_list[i][j].filled_trace_state_dic[items[k]]=multi_counterexample_path_list[i][j-1].filled_trace_state_dic[items[k]]
					else:																		  #否则从本trace中取值
						multi_counterexample_path_list[i][j].filled_trace_state_dic[items[k]]=multi_counterexample_path_list[i][j].trace_state_dic[items[k]]

				# phase_items=list(phase_evict.keys())
				# target_items=list(phase_target.keys())
				for pi in range(len(phase_key)):
					key=phase_key[pi];
					target_key=phase_target_key[pi];
					target_value=phase_target_value[pi];
					if(j< len(multi_counterexample_path_list[i]) and multi_counterexample_path_list[i][j-1].filled_trace_state_dic[key]==phase_value[pi] and multi_counterexample_path_list[i][j].filled_trace_state_dic[target_key]==target_value):
						# print(key)
						# print(phase_evict[key])
						# print("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")
						phase_evict_index[phase_n[pi]]=j-1
						phase_str[phase_n[pi]]=phase_value[pi];
						# break;
		for pn in range(len(phase_n)):
			if(phase_evict_index[phase_n[pn]]>=0):
				multi_counterexample_path_list[i][phase_evict_index[phase_n[pn]]].phase=phase_str[phase_n[pn]]
			# print(i)
			# print(phase_evict_index);
			# print(multi_counterexample_path_list[i][phase_evict_index].phase)
			# print("sssssss")



				# for x in range(len(items)):
				# 	if(items[x] not in white_list and items[x] not in black_list):
				# 		multi_counterexample_path_list[i][j].filled_trace_state_dic.pop(items[x])
				#
				# for k in range(len(items)):
				# 	if(not ( items[k] in multi_counterexample_path_list[i][j].filled_trace_state_dic) and  (items[k] in white_list  or items[k] in black_list or items[k] in black_list)):
				# 		multi_counterexample_path_list[i][j].filled_trace_state_dic[items[k]]=multi_counterexample_path_list[i][j-1].filled_trace_state_dic[items[k]]


	return multi_counterexample_path_list;


def generate_graph(multi_counterexample_path_list,length):
	print(" strict digraph prof {\n")
	print("    node [fontname=\"Arial\"];\n")
	# print("    splines=line;\n")
	# phase_items=list(phase_evict.keys())
	for i in range(len(phase_key)):
		print("\"\n%s\n\" [style=filled,fillcolor=yellow,shape=box,width=5]\n" %(phase_value[i]))

	# if(length>len(multi_counterexample_path_list)):
	# 	length=len(multi_counterexample_path_list)



	for i in range(len(multi_counterexample_path_list)):
		# every counterexample
		len_j=len(multi_counterexample_path_list[i])
		if(len_j>length):
			print(len_j);
			print(length)
			break;
		phase_id=1
		for j in range(len_j):
			list_str=""
			print("\"");
			if(j==0):
				print("start");
			else:
				items=list(multi_counterexample_path_list[i][j-1].filled_trace_state_dic.items())
				for k in range(len(items)):
					if (items[k][0] in black_list):
						list_str=list_str + ("%s = %s\n" %(items[k][0],items[k][1]))
						continue;
					print('%d:%d:%s = %s\n' % (phase_id,len_j,items[k][0],items[k][1]))
					# print('%d:%d:%s = %s\n' % (i,j-1,items[k][0],items[k][1]))
				# print(multi_counterexample_path_list[i][j-1].trace_index)
				# print(".")
				# print(multi_counterexample_path_list[i][j-1].trace_state_index)

			print("\" -> \"");
			# if(j==2):
			# 	print("222222")
			# 	print(multi_counterexample_path_list[i][j-1].phase)
			if(multi_counterexample_path_list[i][j-1].phase != ""):
				# print("aaaaaaaaa");
				print(multi_counterexample_path_list[i][j-1].phase);
				print("\"   -> \"");
				phase_id=phase_id+1;



			# if(j==len(multi_counterexample_path_list[i])-1):
			# 	print("Accept:\n")
			items=list(multi_counterexample_path_list[i][j].filled_trace_state_dic.items())
			for k in range(len(items)):
				if (items[k][0] in black_list ):
					continue;
				print('%d:%d:%s = %s\n' % (phase_id,len_j,items[k][0],items[k][1]))
				# print('%d:%d:%s = %s\n' % (i,j,items[k][0],items[k][1]))
			# print(multi_counterexample_path_list[i][j].trace_index)
			# print(".")
			# print(multi_counterexample_path_list[i][j].trace_state_index)

			print("\"");
			print("[ label=\"%s\" ]" % list_str)


			if(j==len_j-1):
				print("\"");
				for k in range(len(items)):
					if (items[k][0] in black_list ):
						continue;
					print('%d:%d:%s = %s\n' % (phase_id,len_j,items[k][0],items[k][1]))
					# print('%d:%d:%s = %s\n' % (i,j,items[k][0],items[k][1]))

				print("\" -> \"Danger\"");






	print("}")


	





def main(argv):
	multi_counterexample_path_list=file2list('ce')
	# for i in range(2):
	# 	print(len(multi_counterexample_path_list[i]))
	# 	for j in range(len(multi_counterexample_path_list[i])):
	# 		print(multi_counterexample_path_list[i][j].trace_state_dic);



	if(len(multi_counterexample_path_list)==0):
		print("PASS\n");
		return;
	multi_counterexample_path_list=fill_states(multi_counterexample_path_list);
	# for i in range(2):
	# 	print(len(multi_counterexample_path_list[i]))
	# 	for j in range(len(multi_counterexample_path_list[i])):
	# 		print(multi_counterexample_path_list[i][j].trace_state_dic);
	# print(multi_counterexample_path_list[0][0]);
	generate_graph(multi_counterexample_path_list,9)



	# for i in range(100):
	# 	print(len(multi_counterexample_path_list[i]))
	# 	for j in range(len(multi_counterexample_path_list[0])):
	# 		print(multi_counterexample_path_list[0][j].filled_trace_state_dic);




if __name__ == "__main__":
   main(sys.argv[1:])
