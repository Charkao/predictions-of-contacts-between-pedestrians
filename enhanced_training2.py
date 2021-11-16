# -*- coding: utf-8 -*-
"""
Created on Wed Jul  7 10:26:07 2021

@author: saadc
"""

# -*- coding: utf-8 -*-
"""
Created on Thu Jun 24 12:20:10 2021

@author: saadc
"""

# import pandas module 
import numpy as np
import pandas as pd 
    
# making dataframe 
df = pd.read_csv("enhanced_training_datat2.csv",sep=';') #conversion du data csv au Dataframe
enh_data=df.to_numpy() #conversion to a matrix


def create_label(enh_data):
    l = np.zeros(enh_data.shape[0])
    
    for i in range(0,556):
        for j in range(1,enh_data.shape[1]):
            if(enh_data[i,j]!=0):
                l[i]=1
                
    for i in range(556,1262):
        for j in range(1,enh_data.shape[1]):
            if(enh_data[i,j]!=0):
                l[i]=2
                
    for i in range(1262,1732):
        for j in range(1,enh_data.shape[1]):
            if(enh_data[i,j]!=0):
                l[i]=3
    return l


labels = create_label(enh_data)


from sklearn.model_selection import train_test_split

#split the data into test and training data
x_train, x_test, y_train, y_test = train_test_split(enh_data, labels, test_size=0.33, random_state=42)

from sklearn.neural_network import MLPClassifier
from sklearn.metrics import accuracy_score, confusion_matrix
import seaborn as sn
import matplotlib.pyplot as plt

clf = MLPClassifier(solver='lbfgs', alpha=1e-4,hidden_layer_sizes=(20, 4), random_state=1)

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



        
    

