#!/usr/bin/env python2
import timeit
import fast

import numpy as np
import sys

def matmul(a, b):
    """
    Funcion que multiplica 2 matrices de numpy
    """
    if a.shape[1] == b.shape[0]:
        # Se puede realizar la multiplicacion
        # Crea la matriz resultado
        r = np.zeros((a.shape[0], b.shape[1]))

        # Realiza la multiplicacion
        for i in range(r.shape[0]):
            for j in range(r.shape[1]):
                for k in range(a.shape[1]):
                    r[i][j] += a[i][k]*b[k][j]

        return r


if __name__ == '__main__':
    a = np.array([[1, 2, 3], [4, 5, 6]], dtype=np.float64)
    b = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]], dtype=np.float64)

    a = np.array([[1, 1, 1]], dtype=np.float64)
    b = np.array([[1, 2, 3], [1, 2, 3], [1, 2, 3]], dtype=np.float64)

    # Crea una matriz 3x3 aleatoria
    N_EJEC = int(sys.argv[1])
    TAM = int(sys.argv[2])
    a = np.random.rand(TAM, TAM)
    b = np.random.rand(TAM, TAM)

    # Comprueba que las matrices resultado son iguales y no hay errores
    if np.matmul(a, b).all() == matmul(a, b).all() and \
       np.matmul(a, b).all() == fast.matmul(a, b).any():
        print("Las matrices son iguales, realizando benchmark:\n")

        # Ejecuta 10 veces cada funcion y muestra el tiempo de ejecucion
        t1 = timeit.timeit(lambda: matmul(a, b), number=N_EJEC)
        t2 = timeit.timeit(lambda: fast.matmul(a, b), number=N_EJEC)
        t3 = timeit.timeit(lambda: np.matmul(a, b), number=N_EJEC)

        print('| Version | N. Ejecuciones | Tam Matriz | Tiempo (s)')
        print('| Python | %d | %d | %f |'%(N_EJEC, TAM, t1))
        print('| C++    | %d | %d | %f |'%(N_EJEC, TAM, t2))
        print('| Numpy  | %d | %d | %f |'%(N_EJEC, TAM, t3))
    else:
        print("Error: las matrices no coinciden")
