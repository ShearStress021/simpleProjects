from abc import ABC, abstractmethod
from dataclasses import dataclass




class MovieName(ABC):
    @abstractmethod
    def find_num_of_available_seats(self, number):
        pass



@dataclass
class MovieOne(MovieName):
    capacity: int
    def check_if_seats_available(self):
        return self.capacity > 0


    def find_num_of_available_seats(self, number):
        if number <= self.capacity and self.check_if_seats_available():
            self.capacity = self.capacity - number

            print(f"number of seats available is {self.capacity}")
        else:
            
            print("no seat available for Threatre one")





@dataclass
class MovieTwo(MovieName):
    capacity: int
    def check_if_seats_available(self):
        return self.capacity > 0


    def find_num_of_available_seats(self, number):
        if number <= self.capacity and self.check_if_seats_available():
            self.capacity = self.capacity - number

            print(f"number of seats available is {self.capacity}")
        else:
            print("no seat available for Threatre Two")





@dataclass
class Movie:
    movie_name: MovieName


    def calculate(self, number):
        return self.movie_name.find_num_of_available_seats(number)



one = MovieOne(10)

m = Movie(one)
m.calculate(10)


