#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Feb  2 12:05:21 2023

@author: yanbinc
"""

import numpy as np


def gauss_elimination(A, b):
    AA = np.copy(A)
    bb = np.copy(b)
    num_rows = AA.shape(0)
    num_cols = AA.shape(1)
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
    x= np.zeros(3)
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



A = np.array([[-2.0, 0, 1.0], [-1.0, 7.0, 1.0], [5.0, -1.0, 1.0]])
b = np.array([-4.0, -50.0, -26.0])

gauss_elimination(A, b)