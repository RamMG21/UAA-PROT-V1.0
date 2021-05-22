from ftplib import FTP
import csv23
import numpy as np
import os
import gzip
import shutil


def leercsv(sourcefile):
    reader = csv23.open_reader(sourcefile[0])
    listado = []
    ftp_temp2 = []
    with reader as reader:
        for row in reader:
            listado.append(row)
    lista = np.array(listado, dtype=str)

    ftplist_temp = lista[:, sourcefile[4]]

    for ftpitem in ftplist_temp:
        if ftpitem != '':
            ftp_temp2.append(ftpitem)
    ftplist = np.array(ftp_temp2, dtype=str)
    return ftplist


def download(data):
    ftplist = leercsv(data)
    dirname = data[1]
    print(createdir(dirname))
    os.chdir(dirname)
    ftp = FTP("ftp.ncbi.nlm.nih.gov")
    ftp.login()
    ftplist = ftplist[1:]
    for item in ftplist:

        ftp.cwd(item.replace('ftp://ftp.ncbi.nlm.nih.gov', ''))

        filename = (item[item.find('_') - 3:]) + data[2]
        lf = open(filename, 'wb')

        try:
            ftp.retrbinary('RETR ' + filename, lf.write, 8 * 1024)
        except Exception as e:
            with open('error', 'a') as e_f:
                e_f.write(str(e))
                e_f.write('\n')
            e_f.close()
            lf.close()
        finally:

            lf.close()
        with gzip.open(filename, 'rb') as f_in:
            with open(filename.replace('.gz', ''), 'wb') as f_out:
                shutil.copyfileobj(f_in, f_out)

    ftp.quit()
    print(f'Directory {dirname} has been filled')
    splitfiles(data[3])


def createdir(dirname):
    v = 1
    try:
        os.mkdir(dirname)
    except FileExistsError:
        v += 1
        dirname + v
        createdir(dirname)
    finally:
        return f'Directory {dirname} has been created'


def splitfiles(data):
    print("Directory is being decompressed")
    dirname = 'decompress'
    createdir(dirname)
    source = os.getcwd()
    destination = source + '/' + dirname
    source = os.listdir(source)

    for files in source:
        if files.endswith(data):
            with open('lista.txt', 'a') as l_e:
                l_e.write(str(files + '\n'))
            shutil.move(files, destination)

            l_e.close()

    print('Data has been decompressed')
