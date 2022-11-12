import os
import sys
import codecs
import chardet
import sys

#将路径下面的所有文件，从原来的格式变为UTF-8的格式
def convert(file, in_enc="GBK", out_enc="UTF-8"):
    """
    该程序用于将目录下的文件从指定格式转换到指定格式，默认的是GBK转到utf-8
    :param file:    文件路径
    :param in_enc:  输入文件格式
    :param out_enc: 输出文件格式
    :return:
    """
    in_enc = in_enc.upper()
    out_enc = out_enc.upper()
    try:
        print("convert [ " + file.split('\\')[-1] + " ].....From " + in_enc + " --> " + out_enc )
        f = codecs.open(file, 'r', in_enc)
        new_content = f.read()
        codecs.open(file, 'w', out_enc).write(new_content)
    # print (f.read())
    except IOError as err:
        print("I/O error: {0}".format(err))

def list_folders_files(path):
    """
    返回 "文件夹" 和 "文件" 名字

    :param path: "文件夹"和"文件"所在的路径
    :return:  (list_folders, list_files)
            :list_folders: 文件夹
            :list_files: 文件
    """
    list_folders = []
    list_files = []
    for file in os.listdir(path):
        file_path = os.path.join(path, file)
        if os.path.isdir(file_path):
            list_folders.append(file)
        else:
            list_files.append(file)
    return (list_folders, list_files)

if __name__ == "__main__":

    path = sys.argv[1]
    (list_folders, list_files) = list_folders_files(path)

    print("Path: " + path)
    for fileName in list_files:
        filePath = path + '\\' + fileName
        if '.c' in fileName or '.h' in fileName or '.asm' in fileName:
            with open(filePath, "rb") as f:
                data = f.read()
                codeType = chardet.detect(data)['encoding']
                convert(filePath, codeType, 'UTF-8')