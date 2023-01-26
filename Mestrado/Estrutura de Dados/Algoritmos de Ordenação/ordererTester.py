#!/usr/bin/python3

import re
import sys
import argparse
import numpy as np
import inquirer as inq
from pprint import pprint as prt

from insetionSort import InsertionSorter
from selectionSort import SelectionSorter


questions = [
    inq.List('sorter',
             message="Qual algoritmo de ordenação deseja testar?",
             choices=["Insertion Sort", "Selection Sort"]
             ),
    inq.Text('arraySize',
             message="Qual o tamanho para o array?",
             validate=lambda _, x: re.match('^[0-9]*[0-9]$', x)
             ),
    inq.Text('maxValue',
             message="Qual o MAIOR valor possível para os números do array?",
             validate=lambda _, x: re.match('^[0-9]*[0-9]$', x)
             ),
    inq.List('numTests',
             message="Quantos testes fazer?",
             choices=[1, 10, 100, 1000]
             ),
    inq.List('verbose',
             message="Verbose?",
             choices=['Não', 'Sim']
             )
]


def fileReader(filename):
    with open(filename, 'r') as file:
        lines = [int(x.split('\n')[0]) for x in list(file.readlines())]
        return lines


def test(options):
    for i in range(options['numTests']):
        testArray = np.random.randint(
            int(options['maxValue']), size=int(options['arraySize']))

        if options['sorter'] == "Insertion Sort":
            mySorter = InsertionSorter(testArray)

        else:
            mySorter = SelectionSorter(testArray)

        res = mySorter.sort()
        ref = np.sort(testArray)

        if options['verbose'] == "Sim":
            print('')
            print(' --- Generated array:')
            prt(testArray)

            print(' --- My sort result:')
            prt(res)

            print(' --- Expected result:')
            prt(ref)

        if (np.array_equal(res, ref)):
            print('[ Test ' + str(i+1) + ' ] PASSED!')

        else:
            print('[ Test ' + str(i+1) + ' ] FAILED!')
            exit(-1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--selection', help='Use selection sorter.', action='store_true')
    parser.add_argument(
        '--insertion', help='Use insertion sorter.', action='store_true')
    parser.add_argument(
        '-f', '--file', help='Select a file with a list of numbers.')

    args = parser.parse_args()

    if args.file:
        testArray = fileReader(args.file)

        if args.selection:
            print(' --- Running Selecion Sort')
            mySorter = SelectionSorter(testArray)
            res = mySorter.sort()
            ref = np.sort(testArray)

            if np.array_equal(res, ref):
                print(' --- Selection Sort is Correct!')
                print(' +++ Sorted Array:')
                prt(res)
                print('')
            else:
                print(' --- Selection Sort is WRONG!')

        if args.insertion:
            print(' --- Running Insertion Sort')
            mySorter = InsertionSorter(testArray)
            res = mySorter.sort()
            ref = np.sort(testArray)

            if np.array_equal(res, ref):
                print(' --- Insertion Sort is Correct!')
                print(' +++ Sorted Array:')
                prt(res)
                print('')
            else:
                print(' --- Insertion Sort is WRONG!')

    elif not (args.selection or args.insertion):
        options = inq.prompt(questions)
        test(options)

    else:
        parser.print_help(sys.stderr)
        sys.exit(-1)
