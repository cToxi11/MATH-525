"""
Demo
"""
# -*- coding: utf-8 -*-
"""
Created on Tue Jan 24 12:45:55 2023

@author: Yanbin
"""

###------------------###
#append function
x = [1, 2, 3, 4, 5]
x.append(6)
print(x)

###------------------###
#clear function
y = x.clear()
print(y)

###------------------###
#count function
x = [1, 2, 2, 3, 4, 5]
print(x)
print(x.count(2))

###------------------###
#extend function
y = [5, 4, 3, 2, 1]
y.extend(x)
print(y)

###------------------###
#index function
print(x.index(1))

###------------------###
#insert function
x.insert(3, 4)
print(x)

###------------------###
#pop function 
print(x.pop(3))
print(x)

###------------------###
#remove function
x.remove(2)
print(x)

###------------------###
#reverse function 
x.reverse()

print(x)
###------------------###
#sort function
x.sort()
print(x)




