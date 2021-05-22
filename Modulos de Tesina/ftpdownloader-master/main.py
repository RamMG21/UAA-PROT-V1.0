
import blastp
import downloader
import makeblast
import menu
import execution
import testblastp
import renamer


if __name__ == '__main__':
    data = menu.menu()
    downloader.download(data)
    renamer.rename()
    makeblast.create_makeblast_file(data)
    blastp.create_blastp_file(data)
    execution.execute(data)
    testblastp.test_blosum()


