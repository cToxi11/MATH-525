# -*- coding: utf-8 -*-
"""
Created on Sun Jan 22 19:01:39 2023

@author: Yanbin
"""
import math

def sqrt(x):
    x = 1.0*x
    kmax = 1000000
    if x == 0.0:
       return 0.0
    elif x < 0.0:
       print("**ERROR: input value is not non-negative**")
       return -1.0

    s = 1.0
    for k in range(kmax):
        sold = s
        s = 0.5*(s + x/s)
        if (abs((s-sold)/x) < 0):
            break

    return s


def exp(x):
    e = 2.7182818284590451
    x0 = int(round(x))
    
    z = x - x0
    ex = 0
    for i in range(10):
        ex += (e**x0)*(z**i)/math.factorial(i)

    return ex



def ln(x):
    x = 1.0*x
    kmax = 1000000
    if x == 0.0:
       return 0.0
    elif x < 0.0:
       print("**ERROR: input value is not non-negative**")
       return -1.0

    s = x
    for k in range(kmax):
        sold = -1.0 + x*exp(-1*s)
        s = s + sold
        if (abs(sold) < 1.0e-14):
            break

    return s
    
















