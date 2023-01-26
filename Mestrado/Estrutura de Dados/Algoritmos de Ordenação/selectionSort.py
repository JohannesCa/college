import numpy as np


class SelectionSorter:
    def __init__(self, array):
        self.unordered = list(array)
        self.ordered = list(array)

    def swap(self, i, j):
        aux = self.ordered[i]
        self.ordered[i] = self.ordered[j]
        self.ordered[j] = aux

    def sort(self):
        for j in range(len(self.unordered) - 1):
            min = j

            for i in range(j+1, len(self.unordered)):
                if self.ordered[i] < self.ordered[min]:
                    min = i

            self.swap(min, j)

        return np.array(self.ordered)
