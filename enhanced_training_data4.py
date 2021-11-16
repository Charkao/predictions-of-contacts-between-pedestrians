# -*- coding: utf-8 -*-
"""
Created on Tue Jul 13 18:30:27 2021

@author: saadc
"""


# import pandas module 
import numpy as np
import pandas as pd 
    
# making dataframe 
df = pd.read_csv("enhanced_training_data4.csv",sep=';') #conversion du data csv au Dataframe
enh_data=df.to_numpy() #conversion to a matrix

n=int(enh_data.shape[0]/4)
m=int(enh_data.shape[1]*4)

c=4 #répartition des données apr

def split(enh_data,i):
    l=np.zeros((n,4))
    for k in range(n):
            l[k]=[enh_data[k,i],enh_data[k+1,i],enh_data[k+2,i],enh_data[k+3,i]]
    return l


def convert_data(enh_data):
    l_1=[]
    for k in range(0,11):
        l=split(enh_data,k)
        l_1=l_1+[l]
        
    return l_1

m=convert_data(enh_data)
m1=np.concatenate(m,axis=1)
    
    
def create_label(enh_data):
    l = np.zeros(enh_data.shape[0])
    
    for i in range(0,30):
                l[i]=0 
                
    for i in range(30,133):
                l[i]=1
        
    for i in range(133,161):
                l[i]=0
                
    for i in range(161,177):
                l[i]=1
                
    for i in range(171,288):
                l[i]=1
                
    for i in range(288,384):
                l[i]=2
                
    for i in range(384,468):
                l[i]=3
          
    return l


def create_label1(enh_data):
    l=np.zeros(n)
    for i in range(0,8):
                l[i]=0
                
    for i in range(8,34):
                l[i]=1
        
    for i in range(34,41):
                l[i]=0
    for i in range(41,45):
                l[i]=1
                
    for i in range(45,73):
                l[i]=1
                
    for i in range(73,96):
                l[i]=2
                
    for i in range(96,117):
                l[i]=3
          
    return l
    

def create_label(enh_data):
    
    l = np.zeros(enh_data.shape[0])
    
    for i in range(0,30):
                l[i]=0 
                
    for i in range(30,133):
                l[i]=1
        
    for i in range(133,161):
                l[i]=0
    for i in range(161,177):
                l[i]=1
                
    for i in range(171,288):
                l[i]=1
                
    for i in range(288,384):
                l[i]=2
                
    for i in range(384,468):
                l[i]=3
          
    return l




labels = create_label1(enh_data)


from sklearn.model_selection import train_test_split

#split the data into test and training data
x_train, x_test, y_train, y_test = train_test_split(m1, labels, test_size=0.33, random_state=42)

from sklearn.neural_network import MLPClassifier
from sklearn.metrics import accuracy_score, confusion_matrix
import seaborn as sn
import matplotlib.pyplot as plt

clf = MLPClassifier(solver='lbfgs', alpha=1e-4,hidden_layer_sizes=(20,20, 4), random_state=1,activation='tanh')

clf.fit(x_train, y_train)       #training of the model 

output=clf.predict(x_train)    #prediction des labels 
acc=accuracy_score(output,y_train)   #tester l'accuracy du model par rapport à sa "training_data"


#testing the model

output_test=clf.predict(x_test) #on utilise le classifier déjà entrainé
acc_test=accuracy_score(output_test,y_test) #on calcul l'accuracy par rapport au "testing data"

print("accuracy_test (multiclasses) - MLP class :" , acc_test *100 ,'%') 

#confusion matrix
plt.figure(1)
cm=confusion_matrix(output_test,y_test)
sn.heatmap(cm,annot=True)
plt.title("confusion matrix")
plt.xlabel("predicted")
plt.ylabel("expected")



        
    




