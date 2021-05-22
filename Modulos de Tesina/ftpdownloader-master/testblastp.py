import os
import shutil


def test_blosum():
    os.mkdir('blastoutputs')
    os.system('find . -type f -name "*_vs_*" > file.log')
    os.system("sed 's/.\///g' file.log > lista.txt")
    lista = open('lista.txt', 'r')
    filelista = lista.readlines()
    lista.close()
    for item in filelista:
        os.system('mv ' + str(item).rstrip('\n') + ' ' + str(os.getcwd() + '/blastoutputs'))

    os.system('mv lista.txt ' + str(os.getcwd() + '/blastoutputs'))
    os.remove('file.log')
    # for file in os.getcwd():
    #     if file.endswith('.txt'):
    #         shutil.move(file,str(os.getcwd() + '/blastoutputs'))
    #         os.system('mv ' + str(file) + ' ' + str(os.getcwd() + '/blastoutputs'))
    os.system('find . -type f -name "*.txt" -exec mv {} blastoutputs > /dev/null \; > /dev/null')
    os.chdir(os.getcwd() + str('/blastoutputs'))

    print('Test for BLOSUM is beginning')

    for file in os.listdir(os.getcwd()):

        #os.system('grep -w "BLOSUM" ' + str(file) + ' > test.txt')
        os.system('tail -n 4 '+str(file) + ' > test.txt')
        test = open('test.txt', 'r')
        filetest = test.readlines()
        if "Matrix: BLOSUM62\n" in filetest:
            with open('done.log', 'a') as done:
                done.write(str(file + '\n'))
            done.close()
        else:
            with open('error.log', 'a') as error:
                error.write(str(file + '\n'))
            error.close()
        test.close()
    os.remove('test.txt')

    os.system('find . -type f -name "*_vs_*" > file.log')
    os.system("sed 's/.\///g' file.log > lista.txt")
    os.remove('file.log')
    print('Test has been finished, look for output file')
