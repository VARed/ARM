from keras.datasets import mnist
from matplotlib import pyplot as plt
import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from keras.utils import np_utils
import cv2
def change_size(binary_image):

    x = binary_image.shape[0]
    #print("高度x=", x)
    y = binary_image.shape[1]
    #print("宽度y=", y)
    edges_x = []
    edges_y = []
    for i in range(x):
        for j in range(y):
            if binary_image[i][j] == 0:
                edges_x.append(i)
                edges_y.append(j)

    left = min(edges_x)  # 左边界
    right = max(edges_x)  # 右边界
    width = right - left  # 宽度
    bottom = min(edges_y)  # 底部
    top = max(edges_y)  # 顶部
    height = top - bottom  # 高度

    pre1_picture = binary_image[left:left + width, bottom:bottom + height]  # 图片截取
    return pre1_picture  # 返回图片数据
# 从Keras导入Mnist数据集
(X_train, y_train), (X_validation, y_validation) = mnist.load_data()
X_bufdata=[]
for m in range(60000):
    ret, X_train[m] = cv2.threshold(X_train[m], 50, 1, cv2.THRESH_BINARY_INV)
    X_bufdata=change_size(X_train[m])
    X_train[m] = cv2.resize(X_bufdata, (28, 28), interpolation=cv2.INTER_CUBIC)
for m in range(10000):
    ret, X_validation[m] = cv2.threshold(X_validation[m], 50, 1, cv2.THRESH_BINARY_INV)
    X_bufdata = change_size(X_validation[m])
    X_validation[m] = cv2.resize(X_bufdata, (28, 28), interpolation=cv2.INTER_CUBIC)
# 显示4张手写数字的图片
plt.subplot(221)
plt.imshow(X_train[0], cmap=plt.get_cmap('gray'))

plt.subplot(222)
plt.imshow(X_train[1], cmap=plt.get_cmap('gray'))

plt.subplot(223)
plt.imshow(X_train[2], cmap=plt.get_cmap('gray'))

plt.subplot(224)
plt.imshow(X_train[3], cmap=plt.get_cmap('gray'))

plt.show()

# 设定随机种子
seed = 7
np.random.seed(seed)

num_pixels = X_train.shape[1] * X_train.shape[2]
print(num_pixels)
X_train = X_train.reshape(X_train.shape[0], num_pixels)
X_validation = X_validation.reshape(X_validation.shape[0], num_pixels)

# 格式化数据到0-1之前
#X_train = X_train / 255
#X_validation = X_validation / 255

# one-hot编码
y_train = np_utils.to_categorical(y_train)
y_validation = np_utils.to_categorical(y_validation)
num_classes = y_validation.shape[1]
print(num_classes)

# 定义基准MLP模型
def create_model():
    # 创建模型
    model = Sequential()
    model.add(Dense(units=num_pixels, input_dim=num_pixels, kernel_initializer='normal', activation='relu'))
    model.add(Dense(units=num_classes, kernel_initializer='normal', activation='softmax'))

    # 编译模型
    model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
    return model

model = create_model()
model.fit(X_train, y_train, epochs=10, batch_size=200)

score = model.evaluate(X_validation, y_validation)
model.save('mnist_mlp2.h5')

print('MLP: %.2f%%' % (score[1] * 100))
