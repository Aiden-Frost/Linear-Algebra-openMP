import random
fw = open("input.txt","w")
n = int(input("Number of unknown variable:"))
fw.write(str(n)+"\n")
for i in range(n):
    for j in range(n+1):
        fw.write(str(random.randint(-100,100)))
        fw.write(" ")
    fw.write("\n")
fw.close()


    
