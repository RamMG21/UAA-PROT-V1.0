def menu():
    print(f'Type the following info to download.')
    sourcefilename = input('Insert the .csv file with the info \n')
    directory = input('Insert the destination directory name \n')
    secuence=int(input(f'Choose the sequence to download\n 1...Genome\n 2...Protein\n'))
    if secuence == 1:
        complement = '_genomic.fna.gz'
        filextension = '.fna'
    elif secuence == 2:
        complement = '_protein.faa.gz'
        filextension = '.faa'

    database = int(input(f'Choose the type of sequence to download\n 1...RefSeq\n 2...GenBank\n'))

    if database == 1:
        typedatabase = 14
    elif database == 2:
        typedatabase = 13

    return sourcefilename, directory, complement, filextension, typedatabase