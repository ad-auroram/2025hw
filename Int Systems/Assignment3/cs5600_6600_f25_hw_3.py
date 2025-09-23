#/usr/bin/python

############################################
# module: cs5600_6600_f25_hw_3.py
# starter code for CS5600/6600 F25: HW 3
# bugs to vladimir kulyukin in canvas.
############################################

'''
Problem 3: 1-layer NN
------------------------
Eta/HLS | 10 | 25 | 50 |
------------------------
0.5     |  8965  |  9265  |  8594  |
------------------------
0.25    |  8649  |  9084  |  9184  |
------------------------
0.125   |  8291  |  8924  |  6562  |
------------------------

Problem 3: two-hidden layer NNs
h1 = 10
------------------------
Eta/h2  | 10 | 25 | 50 |
------------------------
0.5     |  9010  |  9063  |  8427  |
------------------------
0.25    |  8844  |  8995  |  8892  |
------------------------
0.125   |  8181  |  8715  |  8637  |
------------------------

h1 = 25
------------------------
Eta/h2  | 10 | 25 | 50 |
------------------------
0.5     |  9189  |  9251  |  9293  |
------------------------
0.25    |  9009  |  9121  |  9149  |
------------------------
0.125   |  8736  |  8876  |  9017  |
------------------------

h1 = 50
------------------------
Eta/h2  | 10 | 25 | 50 |
------------------------
0.5     |  9258  |  9325  |  9368  |
------------------------
0.25    |  9110  |  9191  |  9203  |
------------------------
0.125   |  8723  |  8954  |  8975  |
------------------------
'''

from ann import ann
from mnist_loader import load_data_wrapper

train_d, valid_d, test_d = load_data_wrapper()

HLS = [10, 25, 50]
ETA = [0.5, 0.25, 0.125]
def train_1_hidden_layer_anns(hls=HLS, eta=ETA, mini_batch_size=10, num_epochs=10):
    training_data, _, test_data = load_data_wrapper()
    for h in hls:
        for lr in eta:
            print(f"*** Training 784x{h}x10 ANN with eta={lr}")
            net = ann([784, h, 10])
            net.mini_batch_sgd(
                training_data=training_data,
                epochs=num_epochs,
                mini_batch_size=mini_batch_size,
                eta=lr,
                test_data=test_data
            )
            print(f"*** Training 784x{h}x10 ANN DONE...\n")


def train_2_hidden_layer_anns(hls=HLS, eta=ETA, mini_batch_size=10, num_epochs=10):
    training_data, _, test_data = load_data_wrapper()
    for h1 in hls:
        for h2 in hls:
            for lr in eta:
                print(f"*** Training 784x{h1}x{h2}x10 ANN with eta={lr}")
                net = ann([784, h1, h2, 10])
                net.mini_batch_sgd(
                    training_data=training_data,
                    epochs=num_epochs,
                    mini_batch_size=mini_batch_size,
                    eta=lr,
                    test_data=test_data
                )
                print(f"*** Training 784x{h1}x{h2}x10 ANN DONE...\n")

### Uncomment to run
if __name__ == '__main__':
    #train_1_hidden_layer_anns(hls=HLS, eta=ETA, mini_batch_size=10, num_epochs=10)
    #train_2_hidden_layer_anns(hls=HLS, eta=ETA, mini_batch_size=10, num_epochs=10)
    pass
