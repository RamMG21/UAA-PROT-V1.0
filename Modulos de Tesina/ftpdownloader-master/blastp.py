import os


def create_blastp_file(data):
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

    for _ in range(len(lines)-1):
        count += 1
        with open('blastp.sh', 'a') as blast_p_file:

            blast_p_file.write(
                "echo {} {}".format(count, ' virus \n'))

            for j in range(len(lines) - count):

                try:
                    blast_p_file.write('blastp -db ')
                    blast_p_file.write(
                        lines[count - 1].rstrip(data[3]+'\n') + ' -query ' + lines[count + j].rstrip('\n') + ' -out ' +
                        lines[count + j].rstrip(data[3]+'\n') + '_vs_' + lines[count - 1].rstrip(data[3]+'\n')
                        + '.txt &\n')
                    blast_p_file.write('blastp -db ')
                    blast_p_file.write(
                        lines[count + j].rstrip(data[3]+'\n') + ' -query ' + lines[count - 1].rstrip('\n') + ' -out ' +
                        lines[count - 1].rstrip(
                            data[3]+'\n') + '_vs_' + lines[count + j].rstrip(data[3]+'\n') + '.txt &\n')

                except IndexError:
                    pass
                continue

        blast_p_file.close()
