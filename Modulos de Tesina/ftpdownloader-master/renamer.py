import os
import shutil

def rename():
    os.chdir('decompress')

    for files in os.listdir(os.getcwd()):
        if files.endswith('.faa'):
            os.system('head -n 1 ' + str(files) + ' > newname')
            file = open('newname', 'r')
            filename = file.readline()
            filename = filename.replace(' ', '_').replace('/', '_').replace('-', '_').replace('.', '_')
            filename = filename[(filename.find('[') + 1):(len(filename) - 2)]
            if filename in os.listdir(os.getcwd()):
                filename = filename + '_v1'
            os.renames(files, filename)

    os.remove('newname')

    for files in os.listdir(os.getcwd()):
        os.renames(files, files+'.faa')

    for files in os.listdir(os.getcwd()):
        with open('lista.txt', 'a') as l_e:
            l_e.write(str(files + '\n'))
        l_e.close()
    #os.system('cd..')
    #os.system('mv all_list.txt '+str(os.getcwd().replace('/decompress')))
