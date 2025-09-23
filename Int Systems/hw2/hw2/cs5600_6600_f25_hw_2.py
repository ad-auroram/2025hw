#!/usr/bin/python

#########################################
# module: cs5600_6600_f25_hw_2.py
# YOUR A#: 02343790
# YOUR NAME: Roxanne Seeley
#########################################

import numpy as np
import pickle
from cs5600_6600_f25_hw_2_data import *

# sigmoid function
def sigmoid(x, deriv=False):
    # your code here
    # in my implement when deriv=True, the function computes the
    # derivative of sigmoid.
    sig = 1 / (1 + np.exp(-x))
    if deriv:
        return sig * (1 - sig)
    return sig
    

# save() function to save the trained network to a file
def save(obj, file_name):
    with open(file_name, 'wb') as fp:
        pickle.dump(obj, fp)

# restore() function to restore the file
def load(file_name):
    with open(file_name, 'rb') as fp:
        obj = pickle.load(fp)
    return obj

def build_nn_wmats(mat_dims):
    wwmats = tuple(
        np.random.randn(mat_dims[i], mat_dims[i + 1])
        for i in range(len(mat_dims) - 1)
    )
    
    return wwmats
    
def build_121_nn():
    return build_nn_wmats((1, 2, 1))

def build_231_nn():
    return build_nn_wmats((2, 3, 1))
    
def build_2331_nn():
    return build_nn_wmats((2, 3, 3, 1))
    
def build_4221_nn():
    return build_nn_wmats((4, 2, 2, 1))
    
def build_421_nn():
    return build_nn_wmats((4, 2, 1))

def build_1331_nn():
    return build_nn_wmats((1,3,3,1))

## Training 3-layer neural net.
## X is the matrix of inputs
## y is the matrix of ground truths.
## build is a nn builder function.

def train_3_layer_nn(numIters, X, y, build):
    W1, W2 = build()
    for j in range(numIters):
        
        Z2 = np.dot(X, W1)
        a2 = sigmoid(Z2)
        Z3 = np.dot(a2, W2)
        yHat = sigmoid(Z3)
        
        yHat_error = y - yHat
        yHat_delta = yHat_error * sigmoid(yHat, deriv=True)
        a2_error = yHat_delta.dot(W2.T)
        a2_delta = a2_error * sigmoid(a2, deriv=True)

        W2 += a2.T.dot(yHat_delta)
        W1 += X.T.dot(a2_delta)
    return (W1, W2)

def train_4_layer_nn(numIters, X, y, build):
    W1, W2, W3 = build()

    for j in range(numIters):
        Z2 = np.dot(X, W1)
        a2 = sigmoid(Z2)
        Z3 = np.dot(a2, W2)
        a3 = sigmoid(Z3)
        Z4 = np.dot(a3, W3)
        yHat = sigmoid(Z4)

        yHat_error = y - yHat
        yHat_delta = yHat_error * yHat * (1 - yHat)
        a3_error = yHat_delta.dot(W3.T)
        a3_delta = a3_error * a3 * (1 - a3)
        a2_error = a3_delta.dot(W2.T)
        a2_delta = a2_error * a2 * (1 - a2)

        W3 += a3.T.dot(yHat_delta)
        W2 += a2.T.dot(a3_delta)
        W1 += X.T.dot(a2_delta)
    return (W1, W2, W3)

def test_3_layer_nn(x, wmats, thresh=0.4, thresh_flag=False):
    W1, W2 = wmats

    Z2 = np.dot(x, W1)
    a2 = sigmoid(Z2)

    Z3 = np.dot(a2, W2)
    yHat = sigmoid(Z3)

    if thresh_flag:
        return (yHat > thresh).astype(int)
    else:
        return yHat
    
def test_4_layer_nn(x, wmats, thresh=0.4, thresh_flag=False):
    W1, W2, W3 = wmats

    Z2 = np.dot(x, W1)
    a2 = sigmoid(Z2)

    Z3 = np.dot(a2, W2)
    a3 = sigmoid(Z3)

    Z4 = np.dot(a3, W3)
    yHat = sigmoid(Z4)

    if thresh_flag:
        return (yHat > thresh).astype(int)
    else:
        return yHat


def fit_3_layer_nn(x, wmats, thresh=0.4, thresh_flag=False):
    return test_3_layer_nn(x, wmats, thresh=thresh, thresh_flag=thresh_flag)


def fit_4_layer_nn(x, wmats, thresh=0.4, thresh_flag=False):
    return test_4_layer_nn(x, wmats, thresh=thresh, thresh_flag=thresh_flag)

# and_3_layer: 500 iterations, 2x3x1
# and_4_layer: 500 iterations, 2x3x3x1
# or_3_layer: 500 iterations, 2x3x1
# or_4_layer: 300 iterations, 2x3x3x1
# not_3_layer: 300 iterations, 1x2x1
# not_4_layer: 300 iterations, 1x3x3x1
# xor_3_layer: 800 iterations, 2x3x1
# xor_4_layer: 700 iterations, 2x3x3x1
#bool_3_layer: 800 iterations, 4x2x1
#bool_4_layer: 500 iterations, 4x2x2x1
