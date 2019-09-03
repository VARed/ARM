import numpy as np
import cv2
from keras.datasets import cifar10
from keras.models import load_model
from keras.utils import np_utils
from keras import backend
import matplotlib.pyplot as plt
backend.set_image_data_format('channels_first')


def change_size(binary_image):

    x = binary_image.shape[0]
    print("高度x=", x)
    y = binary_image.shape[1]
    print("宽度y=", y)
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

# 设定随机种子
seed = 7
np.random.seed(seed=seed)

path = 'C:/Users/Administrator/Desktop/test/011.bmp'
img = cv2.imread(path)
for i in range(3):
   np.savetxt('C:/Users/Administrator/Desktop/test/011'+str(i)+'.txt', img[:, :, i],fmt='%03d')
GrayImage = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
plt.imshow(GrayImage)
plt.show()
ret, th2 = cv2.threshold(GrayImage, 50, 1, cv2.THRESH_BINARY)
th2=change_size(th2)

th2 = cv2.resize(th2, (28, 28),interpolation=cv2.INTER_CUBIC)

#r, g, b = [img[:, :, i] for i in range(3)]
#img_gray = r*0.299+g*0.587+b*0.114



#r = img[:, :, 2]

input_img = th2.reshape(1, 784)
#input_img = input_img/255.0
model = load_model('mnist_mlp2.h5')

y = model.predict(input_img)
print("result:", y)
arr = np.array(y)
r = np.argmax(arr)
print(r)







