#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Feb  2 12:05:21 2023

@author: yanbinc

Application of solving polynomial interpolation 
"""



import numpy as np

def gauss_elimination(A, b):
    """
    Gauss elimination (no partial pivoting) 
    solve linear system Ax = b
    compared with numpy solve results
    """
    AA = np.copy(A)
    bb = np.copy(b)
    num_rows = A.shape[0]
    num_cols = A.shape[1]
    #main loop
    print('Gaussian Elimination === ') 
    for col in range(num_cols-1):
        print('Gauss elemination along col=',col,':')
        for row in range(col+1,num_rows):
            m = (A[row][col]/A[col][col])
            A[row][col:] = A[row][col:] - m*A[col][col:]
            b[row] = b[row] - m*b[col]
        print(A) 
        print(b)
    #back substituion
    print('Back substitution === ')
    x= np.zeros(num_rows)
    x[num_rows-1] = b[num_rows-1]/A[num_rows-1][num_cols-1]
    for row in range(num_rows-2,-1,-1):
        x[row] = (b[row] - np.dot(A[row][row+1:],x[row+1:]))/A[row][row]
    print(x)
    #compare with numpy solve
    from numpy import linalg as la
    xx = la.solve(AA,bb)
    print(xx)
    print('Error compuared with numpy solve is ', la.norm(x-xx))
        
    return x



#A = np.array([[-2.0, 0, 1.0], [-1.0, 7.0, 1.0], [5.0, -1.0, 1.0]])
#b = np.array([-4.0, -50.0, -26.0])

#gauss_elimination(A, b)


if __name__ == "__main__":
    import matplotlib.pyplot as plt
    n = 4
    xp = np.array([-0.1, -0.02, 0.02, 0.1])
    A = np.ones((n, n))
    A[:, 0] = xp**3
    A[:, 1] = xp**2
    A[:, 2] = xp
    
    b = np.ones(4)
    b = np.cos(xp)
    
    x = gauss_elimination(A, b)
    
    xgrid = np.linspace(xp[0], xp[-1], 101)
    f = np.cos(xgrid)
    p = np.zeros(101)
    for k in range(n):
        p = p + xgrid**(n-k-1)*x[k]
    
    #for pw in range(n):
    #    p = p + (xgrid**(pw-1))*x[4-pw-1]
    plt.plot(xgrid, f, 'r', xgrid, p, 'o')
    plt.show()
    
    
    
    
    
    
    


























