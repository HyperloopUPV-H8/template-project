import re

file = open('err.txt', 'r')
for line in file.readlines():
    line = line.replace("cc1:", "")
    line = line.replace("C++/ObjC++", "C++")
    line = line.replace("command-line option", "option")
    line = re.sub("\/.*\/ST-LIB", "ST-LIB", line)
    line = re.sub("\/.*\/template-project", "template-project", line)
    line = re.sub(".*In function.*", "", line)

    if line.strip() != "":
        print(line)
    
    
file.close()

