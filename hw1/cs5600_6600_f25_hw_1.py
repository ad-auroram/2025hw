
####################################################
# CS 5600/6600 F25: HW 1: Problems 2 & 3
# starter code for hw 1.
# bugs to vladimir kulyukin in canvas.
#####################################################

import numpy as np

class and_percep:

    def __init__(self):
        self.weight = 0
        self.bias = 0

    def output(self, x):
        self.weight = x[0]+x[1]
        if self.weight == 2:
            return 1
        else:
            return 0

class or_percep:
    def __init__(self):
        self.weight = 0
        self.bias = 0

    def output(self, x):
        self.weight = x[0]+x[1]
        if self.weight == 1 or self.weight == 2:
            return 1
        else:
            return 0

class not_percep:
    def __init__(self):
        self.weight = 0
        self.bias = -1

    def output(self, x):
        self.weight = x[0] + self.bias
        if self.weight == 0:
            return 0
        else:
            return 1

class xor_percep:
    
    def __init__(self):
        self.weight = 0
        self.bias = 0

    def output(self, x):
        andp = and_percep()
        orp = or_percep()
        notp = not_percep()

        self.weight = andp.output(np.array([orp.output(x),notp.output(np.array([andp.output(x)]))]))

        return self.weight

class xor_percep2:
    def __init__(self):
        self.weight = 0
        self.bias = -1

    def output(self, x):
        self.weight = x[0]+x[1]+self.bias
        if self.weight == 0:
            return np.array([1])
        else:
            return np.array([0])

class percep_net:
    
    def __init__(self):
        self.weight = 0
        self.bias = 0

    def output(self, x):
        assert len(x) == 4
       	### your code here
        #(x0 or x1) and not x2) or x3
        andp = and_percep()
        orp = or_percep()
        notp = not_percep()
        zeroOrOne = orp.output(np.array(([x[0], x[1]])))
        notTwo = notp.output(np.array([x[2]]))
        firstAnd = andp.output(np.array([zeroOrOne, notTwo]))
        self.weight = orp.output(np.array([firstAnd, x[3]]))

        return self.weight

class percep_net2:
    
    def __init__(self):
        self.weight = 0
        self.bias = 0

    def output(self, x):
        assert len(x) == 4
        ### x0 xor x1) and not x2) xor x3
        andp = and_percep()
        xorp = xor_percep()
        notp = not_percep()
        zeroOrOne = xorp.output(np.array(([x[0], x[1]])))
        notTwo = notp.output(np.array([x[2]]))
        firstAnd = andp.output(np.array([zeroOrOne, notTwo]))
        self.weight = xorp.output(np.array([firstAnd, x[3]]))
        print(self.weight)

        return self.weight
    




