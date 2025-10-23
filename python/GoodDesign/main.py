from abc import ABC, abstractmethod


class DiscountStrategy(ABC):
    @abstractmethod
    def calcute_discount(self, amount):
        ...


class DiscountVip(DiscountStrategy):
    def calcute_discount(self, amount):
        return amount * 0.8


class DiscountReg(DiscountStrategy):
    def calcute_discount(self, amount):
        return amount * 0.5



class Discount:
    def __init__(self, strategy: DiscountStrategy) -> None:
        self.strategy = strategy

    def calculate(self, amount):
        return self.strategy.calcute_discount(amount)


d = Discount(DiscountReg())
print(d.calculate(100))
