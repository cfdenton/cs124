import sys
import random
from datetime import datetime
import numpy as np
import math

maxnum = 100
maxiter = 1000


def kk(arr):
    n = len(arr)
    nonzero = 0
    for i in range(n):
        if arr[i] > 0:
            nonzero += 1
    
    while nonzero > 1:
        i = random.randint(0, n-1)
        j = random.randint(0, n-1)
        if i == j:
            continue

        if arr[i] > arr[j]:
            if arr[j] != 0:
                nonzero += -1
            if arr[j] == arr[i] and arr[j] != 0:
                nonzero += -1

            arr[i] = arr[i] - arr[j]
            arr[j] = 0
        else:
            if arr[i] != 0:
                nonzero += -1
            if arr[j] == arr[i] and arr[j] != 0:
                nonzero += -1
    
            arr[j] = arr[j] - arr[i]
            arr[i] = 0
    res = 0
    for i in arr:
        if i > res:
            res = i
    print("KK algorithm residue: " + str(res))
    return res


def repeated_random(arr):
    n = len(arr)
    s = rand_sol(n)

    for i in range(maxiter):
        sprime = rand_sol(n)
        if residue(arr, sprime) < residue(arr, s):
            s = sprime[:]

    print("repeated random residue: " + str(residue(arr, s)))
    return s
        

def hill_climbing(arr):
    n = len(arr)
    s = rand_sol(n)

    #print("s: " + str(s) + " residue: " + str(residue(s, arr)))
    
    for i in range(maxiter):
        sprime = rand_neighbor(s)
        
        if residue(arr, sprime) < residue(arr, s):
            s = sprime[:]

    print("hill climbing residue: " + str(residue(arr, s)))
    return s

def simulated_annealing(arr):
    n = len(arr)
    s = rand_sol(n)
    spp = s[:]
    for i in range(maxiter):
        sp = rand_neighbor(s)
        if residue(arr, sp) < residue(arr, s):
            s = sp[:]
        elif random.random() < anneal(arr, s, sp, i):
            s = sp[:]

        if residue(arr, s) < residue(arr, spp):
            spp = s[:]

    print("simulated annealing residue: " + str(residue(arr, spp)))
    return spp
        
def anneal(arr, s, sp, i):
    def temp(i):
        return pow(10, 10)*pow(0.8, math.floor(i/300))
    return math.exp(-(residue(arr, sp) - residue(arr, s))/temp(i))

def rand_sol(n):
    arr = []
    for i in range(n):
        if random.random() > 0.5:
            arr.append(1)
        else:
            arr.append(-1)
    return arr

def rand_neighbor(sol):
    n = len(sol)
    sprime = sol[:]

    if random.random() < 0.5:
        j = random.randint(0, n-1)
        sprime[j] *= -1
    else:
        j = random.randint(0, n-1)
        k = random.randint(0, n-2)
        if k >= j:
            k += 1
        sprime[j] *= -1
        sprime[k] *= -1
    return sprime
   



def residue(arr, sol):
    res = 0
    for i in range(len(arr)):
        res += arr[i] * sol[i]
    return abs(res)


def generate_random(n):
    arr = []
    for i in range(n):
        arr.append(random.randint(0, maxnum))
    return arr




def many_random(size, num):
    arrs = []
    for i in range(num):
        arrs.append(generate_random(size))
    return arrs
        


def main(args):
    random.seed(datetime.now())

    size = 100 
    num = 10
    arr = generate_random(size)
    print("array: " + str(arr))
    repeated_random(arr)
    # hill_climbing(arr)
    # simulated_annealing(arr)
    # kk(arr)


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
