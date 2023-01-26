import numpy as np


class InsertionSorter:
    def __init__(self, array):
        self.unordered = list(array)
        self.ordered = list(array)

    def sort(self):
        for i in range(1, len(self.unordered)):
            j = i-1
            pivot = self.ordered[i]

            while (j >= 0) and (pivot < self.ordered[j]):
                self.ordered[j+1] = self.ordered[j]
                j -= 1

            self.ordered[j+1] = pivot

        return np.array(self.ordered)
