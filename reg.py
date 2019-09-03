
from keras.models import Sequential

from keras.layers import Dense
#import matplotlib.pyplot as plt
import numpy as np

np.random.seed(1337)

# 生成数据
X = np.linspace(-1, 1, 300)  # 在返回（-1, 1）范围内的等差序列
np.random.shuffle(X)  # 打乱顺序
Y = 0.5 * X + 2 + np.random.normal(0, 0.1, 300)  # 生成Y并添加噪声


X_train, Y_train = X[:200], Y[:200]  # 前160组数据为训练数据集
X_test, Y_test = X[200:], Y[200:]  # 后40组数据为测试数据集

# 构建神经网络模型
model = Sequential()
model.add(Dense(input_dim=1, units=1))

# 选定loss函数和优化器
model.compile(loss='mse', optimizer='sgd')

# 训练过程
print('Training -----------')
for step in range(501):
    cost = model.train_on_batch(X_train, Y_train)
    if step % 50 == 0:
        print("After %d trainings, the cost: %f" % (step, cost))
W, b = model.layers[0].get_weights()
# 测试过程
print('\nTesting ------------')
cost = model.evaluate(X_test, Y_test, batch_size=40)
print('test cost:', cost)

print('Weights=', W, '\nbiases=', b)
model.save('my_model.h5')

