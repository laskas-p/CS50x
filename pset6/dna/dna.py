import csv
from cs50 import get_string
from sys import argv, exit


def main():

    # initialising the variable to change if person found
    find_person = False

    # check if the command line input arguments are 3
    if len(argv) != 3:
        # if not correct display message for correct usage and exit program with code (1)
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # open cvs file as described in argv[1]
    with open(argv[1]) as csv_file:
        # read from the file with delimiter ','
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            # if this is the first line
            if line_count == 0:
                # create a list
                myindex = []
                # for all the different words - nucleotide of DNA(eg AGAT) starting from the 1 as the 0 is just a description
                for i in range(1, len(row)):
                    # add them in myindex list
                    myindex.append(row[i])
                    # print(f"{myindex[i-1]} ", end="")
                    # use this to finish with the file
                    line_count = 1
                    # print()
    # note that with this: with open(...) file.close is not necessary

    # create a dictionary to store {nucleotide of DNA, max times in sequence}
    myseqdict = {}

    # open seq file as described in argv[2] - DNA sequence file
    with open(argv[2]) as seq:
        # read the sequence - line
        line = seq.readline()
        # print(f"{line}", end ="")
        # for the length of myindex list - different nucleotides of DNA
        for j in range(len(myindex)):
            myseq = myindex[j]
            j = 0
            seqcounter = 1
            max_times = 1
            # for the length of the line (one character at a time)
            for i in range(len(line)):
                # print(f"{myseq[0]} {myindex[j]} {len(myseq)} {len(myindex)}")
                # if the letter at i position of the sequence - line is equal to the first letter of the current nucleotide eg A = A
                if line[i] == myseq[0]:
                    # check if the string starting from position i to the length of the current nucleotide (eg A:GAT) is equal th the string nucleotide
                    if line[i:i+len(myseq)] == myseq:
                        # if this is the case, then check if this is the second in a row string of nuleotide
                        if i == j + len(myseq):
                            # increase the sequencing counter
                            seqcounter += 1
                        else:
                            # other wise reset it to 1
                            seqcounter = 1
                        # if sequencing counter is bigger than maximum times shown in sequence
                        if seqcounter > max_times:
                            # make them equal so max_time always shows the maximum number of times the nucleotide shown in sequence
                            max_times = seqcounter

                        # print(f"{line[i:i+len(myseq)]} {myseq}")
                        # print(f"{line[i]} {line[i:i+len(myseq)]} {myseq}")
                        # print(f"found, {i} counter {seqcounter} maxtimes{max_times}")
                        # reset previous position by storing it to j variable
                        j = i
            # add in dictionary myseqdict the key[myseq] with value max_time eg AGAT, 43
            myseqdict[myseq] = max_times
        # print(myseqdict)
        # note that with this: with open(...) file.close is not necessary

        # open the csv file again to read the lines after the first. The goal is to compare the numbers with the one stored in dictionary.
        # if the sequence is found then the program will print the row[0] value which is the name of the person. This can happen only for one person.
        with open(argv[1]) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            line_count = 0
            for row in csv_reader:
                if line_count == 0:
                    line_count += 1
                else:
                    # create list persons to put the values of the current line starting from 1, as the 0 is the name of the person
                    persons = []
                    found = 1
                    for i in range(1, len(row)):
                        persons.append(row[i])
                        # print(f"{persons[i-1]} ", end="")
                        line_count += 1
                        # in the value_of_dict variable is stored the value of the key myindex[i-1] - eg AGAT. so we have something like 45
                        value_of_dict = myseqdict[myindex[i-1]]
                        # if this value equals the value extracted from the line of the csv file, in integer, then increase found counter
                        if int(persons[i-1]) == value_of_dict:
                            found += 1
                    # if the found counter is equal to the length of the row, which means that for this row-person we found that the maximum
                    # times these nucleotides show in sequence are the same at the sequence.txt file
                    if found == len(row):
                        # print this persons name as this person is found and change the value of find_person to True
                        print(f"{row[0]}")
                        find_person = True
         # note that with this: with open(...) file.close is not necessary

    # if none of these happens then print No match
    if find_person == False:
        print("No match")


main()