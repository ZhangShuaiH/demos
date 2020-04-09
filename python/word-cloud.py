# coding=utf-8
import matplotlib.pyplot as plt
import argparse
from wordcloud import WordCloud as wc
import jieba
from scipy.misc import imread


def func(bgfile, input, output):
    f = open(input)
    text = f.read()
    f.close()
    words = jieba.cut(text)
    text = " ".join(words)

    # 生成词云
    bg = imread(bgfile)
    mywc = wc(mask=bg, font_path="simfang.ttf", width=1920, height=1080)
    print 'generating...'
    cloud = mywc.generate(text)
    mywc.to_file(output)

    # 在 plt 中显示
    # plt.imshow(cloud, interpolation='bilinear')
    # plt.axis('off')
    # plt.show()


def args_manage():
    parse = argparse.ArgumentParser()
    parse.add_argument('-bg', help='the name of background file, who is a image file with a white background color')
    parse.add_argument('-i', help='the name of a input file, who is a text file')
    parse.add_argument('-o', default='image.jpg', help='the name of a output file, who is a image file')

    args = parse.parse_args()
    bg = args.bg
    input = args.i
    output = args.o
    return bg, input, output


if __name__ == '__main__':
    bg, input, output = args_manage()
    func(bg, input, output)
