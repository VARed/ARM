from keras.models import Sequential
from keras.models import load_model
from keras.layers import Dense
#import matplotlib.pyplot as plt
import numpy as np


x = [2, 3]
model = Sequential()

model = load_model('my_model.h5')
Y = model.predict(x)
print("y=", Y)




