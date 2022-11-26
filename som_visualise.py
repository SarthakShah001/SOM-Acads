import pandas as pd
import numpy as np
import csv
import cv2 as cv
df = pd.read_csv('my_file.csv')
CSV_List = None
# opening the CSV file
with open('my_file.csv', mode ='r')as file:
   
  # reading the CSV file
  csvFile = csv.reader(file)
 
  # displaying the contents of the CSV file
  CSV_List = list(csvFile)
for i in range(100):
  CSV_List[i].pop()
ls = []
for i in CSV_List[0:]:
  t1 = []
  t2 = []
  for j in range(0,300,3):
    t2.append(list(map(np.uint8, i[j:j+3])))
  ls.append(t2)
arr = np.array(ls)
# print(arr.shape)
# print(arr)
cv.imshow('',arr)
cv.waitKey(1000000000)