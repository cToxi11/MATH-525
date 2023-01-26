"""
Module for my defined functions
Try1: newton method for sqrt(x) by solving f(s) = s^2-x = 0
"""

def sqrt(x,kmax):
    # convert input to float
    x=1.0*x
    # check if input makes sense
    if x==0.0:
       return 0.0
    elif x<0.0:
       print("**ERROR: input x must non-negative**")
       return -1.0

    # main loop
    s = 1.0
    for k in range(kmax):
        #print("Before iteration %2d, s = %20.15f" % (k,s))
        sold = s
        s = 0.5*(s + x/s)
        if (abs((s-sold)/x) < 1.0e-14):
            break
        #print("After %2d iterations, s = %20.15f" % (k+1,s))

    return s;
    
