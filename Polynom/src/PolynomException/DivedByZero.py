from src.PolynomException.PolynomExceptionBase import PolynomExceptionBase


class DivedByZero(PolynomExceptionBase):
    def __init__(self):
        self.message = 'Divided by zero'
