# accuracy: 0.9624, rmse: 0.36074939 ; 88|476|8, epochs=30,learning_rate=0.001
# accuracy: 0.9880, rmse: 0.42458802 ; 24|450|8, epochs=30,learning_rate=0.001
# accuracy: 0.9833, rmse: 0.39933591 ; 24|35|48|35|15|8, epochs=30,learning_rate=0.001
# accuracy: 0.9836, rmse: 0.43026822 ; 24|30|50|50|25|8, epochs=100,learning_rate=0.001
# accuracy: 0.9785, rmse: 0.54449450 ; 24|48|8, epochs=30,learning_rate=0.001
# accuracy: 0.9540, rmse: 0.44320928 ; 24|500|300|8, epochs=100,learning_rate=0.001
# accuracy: 0.8292, rmse: 0.45744228 ; 24|35|48|100|48|35|15|8, epochs=100,learning_rate=0.001
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

# Input 88 features, output 8 targets
data = np.genfromtxt('data.csv', delimiter=',')
features = 24
scaled_data = data / 4294967295  # 2^32 - 1
training_data_len = math.ceil(len(scaled_data) * 0.8)

x = scaled_data[:, :features]
y = scaled_data[:, features:]

x_train = x[:training_data_len]
y_train = y[:training_data_len]

x_test = x[training_data_len:]
y_test = y[training_data_len:]

# Build model
model = Sequential()
model.add(Dense(476, input_dim=features, activation='sigmoid'))
model.add(Dense(8))

opt = tf.keras.optimizers.Adam(learning_rate=0.001)

# Compile the model
model.compile(optimizer=opt, loss='mean_squared_error',
              metrics=['accuracy'])

# Train the model
model.fit(x_train, y_train, batch_size=1, epochs=30)

y_pred = model.predict(x_test)
# print(y_pred)

rmse = np.sqrt(np.mean(((y_pred - y_test)**2)))
print('rmse:', rmse, '\n')
