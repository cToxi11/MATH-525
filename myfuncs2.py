"""
New my functions file for Lecture 04
"""



def sqrt(x, kmax=100, initial_guess=1.0, tol = 1e-14, printshow=1):
    """
    Compute the square root of a number using Newton's method
    Input: x: real number
           kmax: integer, the maximum number of iterations, default is 100
           initial_guess: the initial guess
           tol: tolerence of accuracy
           printshow: positive number if want to show the calculating process, default is 1
    """


    # convert input to float
    x = 1.0*x
    # check if input makes sense
    if x == 0.0:
       return 0.0
    elif x < 0.0:
       print("**ERROR: input x must non-negative**")
       return -1.0
    # main loop
    s = initial_guess
    for k in range(kmax):
        if printshow > 0:
           print("Before iteration %2d, s = %20.15f" % (k,s))
        sold = s
        s = 0.5*(s + x/s)
        if (abs((s-sold)/x) < tol):
            break
    print("After %2d iterations, s = %20.15f" % (k+1,s))
    return s





