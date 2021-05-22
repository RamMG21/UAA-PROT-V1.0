import os
import shutil


def execute(data):

    dirname = 'decompress'
    source = os.getcwd()
    os.chdir(source.rstrip(dirname))
    source = os.getcwd()


    destination = source + '/' + dirname
    os.chdir(destination.rstrip(dirname))

    #os.system('mv *.sh ' + str(destination))

    print('Executing makeblast')

    os.chdir(destination)
    os.system('chmod 755 *.sh')
    os.system('bash makeblast.sh')

    print('makeblast executed')

    print('Executing blatp.sh')
    os.system('bash blastp.sh')

    print('blastp executed')
