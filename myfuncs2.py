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

    #print ("The square root of %2d is,   "%x)
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
        sold = s
        s = 0.5*(s + x/s)
        if printshow > 0:
           print("Before iteration %2d, s = %20.15f" % (k,s))

        if (abs((s-sold)/x) < tol):
            break
    print("After %2d iterations, s = %20.15f" % (k+1,s))
    return s

def test_sqrt():
    print("The square root of %2d is: " % 0)
    print(sqrt(0))
    print("The square root of %2d is: " % -3)
    print(sqrt(-3))
    print("The square root of %2d is: " % 3)
    print(sqrt(3))
    return
    
def factorial(n):
    s = 1
    for k in range(1, n):
        s = s * (k + 1)
    return s

def exp(x, e=2.7182818284590451, kmax=15, printshow=1):
    """
    Exponential function: comput e^x using Tayer series
    Input: x: real number
           e: exponential constant, =2.7182818284590451
           kmax: integer, the maximum number of Taylor series iterations, default is 15
           printshow: positive number if want to show the calculating process, default is 1
    """
    x0 = int(round(x))
    
    z = x - x0
    ex = 0
    for i in range(kmax):
        ex += (e**x0)*(z**i)/factorial(i)

    return ex


''
def ln(x, kmax=100, tol = 1e-14, printshow=1):
    """
    Compute the natural logarithm of a number of iterations
    Input: x: real number
           kmax: integer, the maximum number of Taylor series iterations, default is 15
           tol: tolerence of accuracy

    """
    
    x = 1.0*x
    if x == 0.0:
       return 0.0
    elif x < 0.0:
       print("**ERROR: input value is not non-negative**")
       return -1.0

    s = x
    for k in range(kmax):
        sold = -1.0 + x*exp(-1*s)
        s = s + sold
        if printshow > 0:
            print("Before iteration %2d, s = %20.15f" % (k,s))
           
        if (abs(sold) < tol):
            break
        
    print("After %2d iterations, s = %20.15f" % (k+1,s))
    return s




