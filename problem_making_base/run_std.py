import os
import time
from sys import argv

def getListFiles(path):
    ret = []
    for root, dirs, files in os.walk(path):
    	for file in files:
    		if (file.startswith("data") and file.endswith(".in")):
    			ret.append(os.path.splitext(file)[0])
    return ret;
if __name__ == '__main__':
	#ret = getListFiles("./")
	ret = os.listdir('./')
	data = 'data'
	exec = './std'
	if (len(argv) > 1):
		data = argv[1]
	if (len(argv) > 2):
		exec = argv[2];
	for file in ret:
		if (file.endswith('.in') and file.startswith(data)):
			file = os.path.splitext(file)[0];
			print ("running " + file + '.in...')
			start = time.clock();
			os.system(exec+' < ' + file + '.in' + ' > ' + file + '.out')
			end = time.clock();
			print ("total execute time: %.3fs" % (end - start))
