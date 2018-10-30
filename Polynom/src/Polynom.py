from copy import copy

from src.PolynomException.DivedByZero import DivedByZero
from src.PolynomException.ValueTypeException import ValueTypeException


class Polynom:

    def __init__(self, nodes=None):
        if nodes is None:
            nodes = dict()

        if not isinstance(nodes, dict):
            raise ValueTypeException(f'node have type {type(nodes)}, but dict was expected')

        self.__nodes = dict(nodes)
        self.__simplify()

    def __add__(self, other):
        if not isinstance(other, Polynom):
            raise ValueTypeException(f'Other have type {type(other)}, but Polynom was expected ')

        items = dict(self.nodes)

        for power in other.nodes:
            value = other.nodes[power]

            if power in items:
                items[power] += value
            else:
                items[power] = value

        return Polynom(items)

    def __iadd__(self, other):
        result = self + other
        self.__nodes = result.nodes

        return self

    def __sub__(self, other):
        if not isinstance(other, Polynom):
            raise ValueTypeException(f'Other have type {type(other)}, but Polynom was expected ')

        items = dict(self.nodes)

        for power in other.nodes:
            value = other.nodes[power]

            if power in items:
                items[power] -= value
            else:
                items[power] = -value

        return Polynom(items)

    def __isub__(self, other):
        result = self - other
        self.__nodes = result.nodes

        return self

    def __mul__(self, other):
        if isinstance(other, Polynom):
            result = self.__mulOnPolynom(other)
        else:
            result = self.__mulOnOtherType(other)

        return result

    def __imul__(self, other):
        result = self * other
        self.__nodes = result.nodes

        return self

    def __truediv__(self, other):
        divPart, modPart = Polynom.__divide(self, other)
        return divPart

    def __mod__(self, other):
        divPart, modPart = Polynom.__divide(self, other)
        return modPart

    @staticmethod
    def __divide(left, right):
        if not isinstance(right, Polynom):
            raise ValueTypeException(f'node have type {type(right)}, but Polynom was expected')

        if not isinstance(left, Polynom):
            raise ValueTypeException(f'node have type {type(left)}, but Polynom was expected')

        result: Polynom = Polynom()
        remainder: Polynom = copy(left)

        maxMonomPowerLeft, maxMonomValueLeft = left.__getMaxMonom
        maxMonomPowerRight, maxMonomValueRight = right.__getMaxMonom

        while maxMonomPowerLeft >= maxMonomPowerRight:
            if not maxMonomValueRight:
                raise DivedByZero()

            newPower = maxMonomPowerLeft - maxMonomPowerRight
            newValue = maxMonomValueLeft / maxMonomValueRight

            if not newValue:
                break

            result.__addMonom(newPower, newValue)
            tmpPoly = Polynom({newPower: newValue})

            tmpPoly *= right
            remainder -= tmpPoly

            maxMonomPowerLeft, maxMonomValueLeft = remainder.__getMaxMonom

        return result, remainder

    def __pow__(self, power):
        if power > 0:
            result = Polynom(self.__nodes)
            for i in range(1, power):
                result *= self
        elif power == 0:
            result = Polynom({0: 1})
        else:
            raise Exception('Only power >= 0')

        return result

    @property
    def nodes(self):
        return self.__nodes

    @property
    def differential(self):
        nodes = {}

        for power in self.nodes:
            if power > 0:
                value = self.nodes[power]
                nodes[power - 1] = power * value

        return Polynom(nodes)

    @property
    def integral(self):
        nodes = {}

        for power in self.nodes:
            value = self.nodes[power]
            nodes[power + 1] = value / (power + 1)

        return Polynom(nodes)

    @staticmethod
    def superposition(left, right):
        result = Polynom()

        if not isinstance(right, Polynom):
            raise ValueTypeException(f'node have type {type(right)}, but Polynom was expected')

        if not isinstance(left, Polynom):
            raise ValueTypeException(f'node have type {type(left)}, but Polynom was expected')

        for power in left.nodes:
            value = left.nodes[power]
            result += pow(right, power) * value

        return result

    def __repr__(self):
        result = ''

        for power in self.nodes:
            value = self.nodes[power]
            if result != '' and value >= 0:
                result += '+'
            result += f'{value}x^{power}'

        return result

    def __len__(self):
        if len(self.nodes) != 0:
            maxPower = max(self.nodes.keys())
        else:
            maxPower = 0
        return maxPower

    def __mulOnPolynom(self, other):
        items = {}
        for pow1 in self.nodes:
            for pow2 in other.nodes:
                resultPower = pow1 + pow2
                value = self.nodes[pow1] * other.nodes[pow2]

                if resultPower in items:
                    items[resultPower] += value
                else:
                    items[resultPower] = value
        return Polynom(items)

    def __mulOnOtherType(self, other):
        items = dict(self.nodes)

        for power in items:
            items[power] *= other
        return Polynom(items)

    def __simplify(self):
        result = {}
        for power in self.nodes:
            value = self.nodes[power]
            if value != 0 and power >= 0:
                result[power] = value
        self.__nodes = result

    def __str__(self):
        result = ''

        if len(self.nodes) == 0:
            return "0"

        pows = sorted(self.nodes.keys())[::-1]

        for power in pows:
            value = self.nodes[power]

            if result != '' and value > 0:
                result += "+"
            elif value < 0:
                result += "-"

            if abs(value) != 1 or power < 1:
                result += str(abs(value))

            if power > 0:
                result += "x"
                if power > 1:
                    result += f'^{power}'

        return result

    def __copy__(self):
        nodes = dict(self.__nodes)

        return Polynom(nodes)

    @property
    def __getMaxMonom(self):
        if len(self.__nodes) > 0:
            powers = sorted(self.__nodes.keys())
            power = max(powers)
            value = self.__nodes[power]

            return power, value

        return None

    def __addMonom(self, power, value):
        if power in self.__nodes:
            self.__nodes[power] += value
        else:
            self.__nodes[power] = value
