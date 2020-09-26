# 200 input hashes ; 10|20|15|8 ; Adam(learning_rate=0.001) ; 100 epochs -> accuracy: 0.9055 ; rmse: 0.0180269
# 200 input hashes ; 10|20|15|10|8 ; Adam(learning_rate=0.00105) ; 100 epochs -> accuracy: 0.9213 ; rmse: 0.0232368
# 200 input hashes ; 10|20|15|10|8 ; Adam(learning_rate=0.0011) ; 1000 epochs -> accuracy: 0.9665 ; rmse: 0.0138343 
# 200 input hashes ; 10|15|20|15|10|8 ; Adam(learning_rate=0.0011) ; 1000 epochs -> accuracy: 0.9709 ; rmse: 0.0091305
# 200 input hashes ; 10|13|16|20|17|14|11|8 ; Adam(learning_rate=0.0011) ; 1000 epochs -> accuracy: 0.9747 ; rmse: 0.0099129
import math
import pandas_datareader.data as web
import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential, load_model
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras.layers import Dense, Dropout, LSTM, BatchNormalization
from tensorflow.keras.callbacks import TensorBoard
from tensorflow.keras.callbacks import ModelCheckpoint, ModelCheckpoint
from sklearn.metrics import accuracy_score
import time
import sys

tf.random.set_seed(9950866220)

# Input 10 features, output 8 targets
data = np.genfromtxt('data.csv', delimiter=',')
scaled_data = data / 4294967295  # 2^32 - 1
training_data_len = math.ceil(len(scaled_data) * 0.8)

x = scaled_data[:, :10]
y = scaled_data[:, 10:]

x_train = x[:training_data_len]
y_train = y[:training_data_len]

x_test = x[training_data_len:]
y_test = y[training_data_len:]

# Build model
model = Sequential()
model.add(Dense(13, input_dim=10, activation='sigmoid'))
model.add(Dense(16, activation='sigmoid'))
model.add(Dense(20, activation='sigmoid'))
model.add(Dense(17, activation='sigmoid'))
model.add(Dense(14, activation='sigmoid'))
model.add(Dense(11, activation='sigmoid'))
model.add(Dense(8))

opt = tf.keras.optimizers.Adam(learning_rate=0.0011)

# Compile the model
model.compile(optimizer=opt, loss='mean_squared_error',
              metrics=['accuracy'])

# Train the model
model.fit(x_train, y_train, batch_size=1, epochs=1000)

y_pred = model.predict(x_test)
# print(y_pred)

rmse = np.sqrt(np.mean(((y_pred - y_test)**2)))
print('rmse:', rmse, '\n')
