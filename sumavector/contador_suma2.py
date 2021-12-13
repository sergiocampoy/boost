import numpy as np
import contador_suma

valores = np.array([1,2,3,4])

suma, contador = contador_suma.contador_sumador(valores.astype(np.double))

print("La suma es",suma,"con",contador,"elementos")


"""
def python_contador_sumador(x):
	return np.sum(x), len(x)

"""