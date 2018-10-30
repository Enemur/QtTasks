from copy import copy

from src.Polynom import Polynom
from src.PolynomException.PolynomExceptionBase import PolynomExceptionBase

if __name__ == '__main__':
    try:
        polynom1 = Polynom({2: 1, 1: 2, 0: -1})
        polynom2 = Polynom({1: 2, 0: 3})
        polynom3 = Polynom({3: 2, 2: 3})
        polynom4 = Polynom({3: 1, 2: -12, 0: -42})
        polynom5 = Polynom({1: 1, 0: -3})

        print(polynom4, polynom5)
        print(polynom4 / polynom5)
        print(polynom4 % polynom5)

        print(f'polynom1: {polynom1}')
        print(f'polynom2: {polynom2}')
        print(f'polynom3: {polynom3}')

        print(f'len: {len(polynom1)}')
        print(f'len: {len(polynom3)}')
        print(f'pow: {pow(polynom3, 2)}')
        print(f'superposition 1->2: {Polynom.superposition(polynom1, polynom2)}')
        print(f'superposition 2->1: {Polynom.superposition(polynom2, polynom1)}')

        print(f'polynom1 + polynom2: {polynom1 + polynom2}')
        print(f'polynom1 - polynom2: {polynom1 - polynom2}')
        print(f'polynom1 * polynom2: {polynom1 * polynom2}')
        print(f'polynom1 * 3: {polynom1 * 3}')
        print(f'differential polynom1: {polynom1.differential}')
        print(f'integral polynom1: {polynom1.integral}')
    except PolynomExceptionBase as error:
        print(error.message)
    except Exception as error:
        print(error)
