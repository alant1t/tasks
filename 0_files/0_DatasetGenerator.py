#!/usr/bin/env python
# coding: utf-8

# In[5]:


with open('D:\\text.txt', 'w') as ouf:
  ouf.write('Some text\n')
  ouf.write(str(25))


# In[6]:


from sklearn import datasets
n_samples = 1500
noisy_circles = datasets.make_circles(n_samples=n_samples, factor=.5,
                                      noise=.05)


# In[11]:


n_samples = 1500
noisy_circles = datasets.make_circles(n_samples=n_samples, factor=.5,
                                      noise=.05)
X, y = noisy_circles
with open('D:\\noisy_circles.txt', 'w') as ouf:
    for element in X:
        ouf.write(str(element))
        ouf.write('\n')


# In[12]:


n_samples = 1500
noisy_moons = datasets.make_moons(n_samples=n_samples, noise=.05)
X, y = noisy_circles
with open('D:\\noisy_moons.txt', 'w') as ouf:
    for element in X:
        ouf.write(str(element))
        ouf.write('\n')


# In[13]:


n_samples = 1500
blobs = datasets.make_blobs(n_samples=n_samples, random_state=8)
with open('D:\\blobs.txt', 'w') as ouf:
    for element in X:
        ouf.write(str(element))
        ouf.write('\n')


# In[15]:


import numpy as np
n_samples = 1500
no_structure = np.random.rand(n_samples, 2), None
with open('D:\\no_structure.txt', 'w') as ouf:
    for element in X:
        ouf.write(str(element))
        ouf.write('\n')


# In[16]:


import numpy as np
n_samples = 1500
random_state = 170
X, y = datasets.make_blobs(n_samples=n_samples, random_state=random_state)
transformation = [[0.6, -0.6], [-0.4, 0.8]]
X_aniso = np.dot(X, transformation)
aniso = (X_aniso, y)
with open('D:\\aniso.txt', 'w') as ouf:
    for element in X_aniso:
        ouf.write(str(element))
        ouf.write('\n')


# In[17]:


n_samples = 1500
random_state = 170
varied = datasets.make_blobs(n_samples=n_samples,
                             cluster_std=[1.0, 2.5, 0.5],
                             random_state=random_state)
with open('D:\\varied.txt', 'w') as ouf:
    for element in X:
        ouf.write(str(element))
        ouf.write('\n')


# In[ ]:




