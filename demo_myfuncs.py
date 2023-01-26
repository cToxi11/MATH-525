# -*- coding: utf-8 -*-
"""
Created on Sun Jan 22 19:38:16 2023

@author: Yanbin
"""

import myfuncs as my

import numpy as np

print("comparison of sqrt function: "+ str(np.abs(my.sqrt(3.7)-np.sqrt(3.7))))

print("comparison of exp function: "+ str(np.abs(my.exp(3.7)-np.exp(3.7))))

print("comparison of log function: "+ str(np.abs(my.ln(3.7)-np.log(3.7))))