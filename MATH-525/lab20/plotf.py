def func(x):

    import numpy as np

    f = np.exp(-(10.0*x)**2)+np.sin(x)

    return f

def plotf():
    # First, figure out how many intervals there are
    fid = open('quadrature1.data', 'r')
    NumIntervals = 0;
    while True:
        line = fid. readline()
        if not line: break
        NumIntervals = NumIntervals +1
    fid.close()

    import numpy as np; import string as str;
    import matplotlib.pyplot as plt

    col = ['b','r','g','m'] # colors for each thread number

    # Second, read -in all the floats
    rank = np.zeros(NumIntervals, dtype = int)
    a = np.zeros(NumIntervals, dtype = float)
    b = np.zeros(NumIntervals, dtype = float)
    fid = open('quadrature1.data', 'r')
    for k in range (0, NumIntervals ):
        linestring = fid. readline()
        linelist = linestring.split()
        rank[k] = int(linelist[0])
        a[k] = float(linelist[1])
        b[k] = float(linelist[2])
    fid.close()

    # Third , plot the result
    plt.rc("font", size =16);
    plt.figure(1)
    for k in range(0, NumIntervals):
        if rank[k] == 1:
            plt.plot([a[k],b[k]], [-float(k),-float(k)], color = col[0], linewidth = 2);
        else:
            plt.plot([a[k],b[k]], [-float(k),-float(k)], color = col[1], linewidth = 2);
    plt.title ("Subintervals used in adaptive quadrature")
    plt.axis("off")
    plt.savefig('adapt_quad_ser_1(1).png', dpi =400 , bbox_inches ='tight')

    # Fourth plot function with intervals
    xtmp = np.zeros (5 * NumIntervals, dtype = float)
    xs = 0
    for k in range (0, NumIntervals ):
        h = b[k]-a[k]
        xtmp[xs + 0] = a[k]
        xtmp[xs + 1] = a[k]+0.25* h
        xtmp[xs + 2] = a[k]+0.5* h
        xtmp[xs + 3] = a[k]+0.75* h
        xtmp[xs + 4] = b[k]
        xs = xs + 5;
    xsorted = np.unique(xtmp);
    fsorted = func(xsorted);
    xfine = np.linspace(-2.0 ,4.0 ,1001);
    ffine = func(xfine);
    plt.rc("font", size =16);
    plt.figure(0)
    plt.plot(xfine, ffine , color ='b', linewidth = 2);
    plt.plot(xsorted, fsorted ,'o',color ='r', linewidth = 2);
    plt.plot(xsorted, -1.1+0.0* xsorted,'k|', markersize = 10);
    plt.xlim (-2.1 ,4.1)
    plt.ylim (-1.55 ,1.55)
    plt.xticks(np. linspace( -2.0 ,4.0 ,7))
    plt.yticks(np. linspace( -1.5 ,1.5 ,7))
    plt.savefig('adapt_quad_ser_1(2).png', dpi =400 , bbox_inches ='tight')
    plt.show();

if __name__ == "__main__":
    plotf();

