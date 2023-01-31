'''
Gaussian Elimination 
'''
import numpy as np
from numpy.linalg import norm
from numpy.linalg import solve


A = np.array([[-2, 0, 1], [-1, 7, 1], [5, -1, 1]])
b = np.array([[-4], [-50], [-26]])

A_new = np.append(A, b, axis = 1)
A_new = A_new.astype(float)
#make a21, a31 to 0
A_new[1, :] = A_new[1, :] - A_new[1,0]/A_new[0,0]*A_new[0, :]
A_new[2, :] = A_new[2, :] - A_new[2,0]/A_new[0,0]*A_new[0, :]

#make a32 to 0
A_new[2, :] = A_new[2, :] - A_new[2,1]/A_new[1,1]*A_new[1, :]

#Now we have a Ux=b_new, we can easily comput the x solution

x3 = A_new[2,3]/A_new[2,2]
x2 = (A_new[1,3]-A_new[1,2]*x3)/A_new[1,1]
x1 = (A_new[0,3]-A_new[0,2]*x3-A_new[0,1]*x2)/A_new[0,0] 

x = np.array([[x1], [x2], [x3]])
solution = solve(A, b)

print("difference between numpy.linalg.solve and this function:   "+str(norm(x-solution)))



























