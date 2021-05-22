import os

def create_makeblast_file(data):
    pwd = os.getcwd()
    sources = pwd
    os.chdir(sources)
    sources = 'lista.txt'
    lines = []
    count = 0

    with open(sources, 'r') as file_list:
        for line in (file_list.readlines()):
            lines.append(line)

    file_list.close()

    for line in lines:
        #count += 1
        with open('makeblast.sh', 'a') as blast_p_file:


                try:
                    blast_p_file.write('makeblastdb -in ')
                    blast_p_file.write(
                        line.rstrip('\n') + ' -dbtype prot -parse_seqids -out ' + line.rstrip(data[3]+'\n') + '\n')

                except IndexError:
                    pass
                continue

        blast_p_file.close()
