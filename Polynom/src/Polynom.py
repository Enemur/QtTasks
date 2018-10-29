from src.PolynomException.ValueTypeException import ValueTypeException


class Polynom:

    def __init__(self, nodes: dict = {}):
        if not isinstance(nodes, dict):
            raise ValueTypeException(f'node have type {type(nodes)}, but dict was expected')

        self.nodes = nodes
        self.__simplify()

    def __add__(self, other):
        if not isinstance(other, Polynom):
            raise ValueTypeException(f'Other have type {type(other)}, but Polynom was expected ')

        items = dict(self.nodes)

        for node in other.nodes:
            value = other.nodes[node]

            if node in items:
                items[node] += value
            else:
                items[node] = value

        return Polynom(items)

    def __iadd__(self, other):
        result = self + other
        self.nodes = result.nodes

        return self

    def __sub__(self, other):
        if not isinstance(other, Polynom):
            raise ValueTypeException(f'Other have type {type(other)}, but Polynom was expected ')

        items = dict(self.nodes)

        for node in other.nodes:
            value = other.nodes[node]

            if node in items:
                items[node] -= value
            else:
                items[node] = value

        return Polynom(items)

    def __isub__(self, other):
        result = self - other
        self.nodes = result.nodes

        return self

    def __mul__(self, other):
        if isinstance(other, Polynom):
            result = self.__mulOnPolynom(other)
        else:
            result = self.__mulOnOtherType(other)

        return result

    def __imul__(self, other):
        result = self * other
        self.nodes = result.nodes

        return self

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
            nodes[power + 1] = value / power + 1

        return Polynom(nodes)

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

            if abs(value) != 1:
                result += str(abs(value))

            if power != 0:
                result += f"x^{power}"

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
        self.nodes = result
