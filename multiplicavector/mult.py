#!/usr/bin/env python

import multiplica
import numpy as np

l = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])

print("Array original: ")
print(l)

multiplica.multiplica(l)

print("Array despues de multiplicar todas sus componentes por 2: ")
print(l)
