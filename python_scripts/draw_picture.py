from distutils.ccompiler import new_compiler
import matplotlib.pyplot as plt
plt.rcParams['font.sans-serif'] = ['KaiTi', 'SimHei', 'FangSong']
plt.rcParams['font.size'] = 12
plt.rcParams['axes.unicode_minus'] = False
import csv
from sys import argv
import os

def read_csv_file(filepath):
    print(len(argv))
    with open(filepath,'r') as csvfile:
        reader=csv.DictReader(csvfile)
        column0=[float(row['ramanshift']) for row in reader]
    csvfile.close()
    with open(filepath,'r') as csvfile:
        reader=csv.DictReader(csvfile)
        column1=[float(row['data']) for row in reader]
    print('row:ramanshift.length=%d'%(len(column0)))
    print('row:data.length=%d'%(len(column1)))
    print(column1)
    '''
    i=0
    for i in range(1044):
        column0[i]=i
        '''
    i=0
    for i in range(1044):
        print("data %d \t\t = [%s,%s]"%((i+1),column0[i],column1[i]))
        i=i+1
    return column0,column1
    

def release_picture(data_x,data_y,type):
    print(len(argv))
    if type==0:     #直接显示图片
        plt.figure()
        plt.plot(data_x,data_y,color='b',label='拉曼光谱数据')
        plt.xlabel('拉曼偏移量')
        plt.ylabel('光谱强度')
        plt.show()
    if type==1:
        plt.figure()
        plt.plot(data_x,data_y,color='b',label='拉曼光谱数据')
        plt.xlabel('拉曼偏移量')
        plt.ylabel('光谱强度')
        plt.savefig('data.png')
'''
def main(argv):
    print(len(argv))
    '''
def test_file():
    try:
        os.remove("data.png")
    except:
        print('no such file or dictory')



if __name__=='__main__':
    test_file()
    print(argv)
    print(len(argv))
    if(len(argv)!=2):
        print("ERROR invaild input")
    else:
        x,y=read_csv_file(argv[1])
        release_picture(x,y,1)
