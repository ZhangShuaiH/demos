#! /usr/bin/env python
#coding=utf-8
# -*- coding: utf-8 -*-

'''the number of train data kinks'''
FNO = 4

'''storing train data using a list of three dimensions,
the first dimension store kinds,
the second dimension store lines in kind,
the third dimension store words in line'''
gTrainData = []

'''create a dictionary whose key is word and value is the no. of word '''
gWordList = {}

'''a two dimension list, storing the number of different words'''
gNo = []

'''a two dimension list, storing the probability value of different words in different kinds'''
gPro = []

'''a two dimension list, storing different Posterior probabilities of line in test data'''
gResult = []

'''calculate variance of different words'''
gS = []

def cutWords( fname ):
    '''
    delete space and table in file and cut file into words
    :param fname:
    :return:
    '''
    import jieba,os

    if os.path.exists( 'cut' + fname ):
        print 'Already exist ' + 'cut' + fname
        return 0
    fi = open(fname)
    fo = open( 'cut' + fname, 'wb' )
    print 'creating file ' + 'cut' + fname + '...'
    line = fi.readline()
    ii = 0
    while line:
        tempLine = ''
        for c in line:
            if c != ' ' and c != '\t':  # delete space and table
                tempLine += c
        line = tempLine
        cuto = jieba.cut( line[:-1] )
        str = ' '.join(cuto).encode('utf8')
        fo.write( str + '\n' )
        line = fi.readline()
        ii += 1
        if ii%100000 == 0:
            print 'cut line ' + str(ii)
    print 'cut line ' + str(ii)

    fo.close()
    fi.close()
    return 0

def dealTrainData():
    '''
    deal train data to establish gTrainDate, a three dimensions list and establish gWordList
    :return:
    '''
    print 'establishing gTrainDate, a three dimensions list and gWordList, a dictionary'
    i = 0
    for m in range( FNO ):
        gTrainData.append([])
        cutWords( 'train' + str(m) )
        fi = open( 'cuttrain' + str(m) )
        lines = fi.readlines()
        fi.close()
        for n in range( len(lines) ):
            gTrainData[m].append([])
            words = lines[n][:-1].split( ' ' )
            for w in words:
                if gWordList.has_key( w ):
                    gTrainData[m][n].append( gWordList[w] )
                else:
                    gWordList[w] = i
                    i += 1
                    gTrainData[m][n].append(gWordList[w])
    return 0

def setGNo():
    '''
    read gTrainData to establish gNo
    :return:
    '''
    print 'reading gTrainData to establish gNo...'
    wln = len(gWordList) + 1 # the number of different words + 1
    kn = FNO # the number of kinds
    for m in range( kn ):
        gNo.append( [0] * wln )
        total = 0
        for line in gTrainData[m]:
            for w in line:
                gNo[m][w] += 1
                total += 1
        gNo[m][-1] = total

    gNo.append([0] * wln)
    for m in range(wln):
        total = 0
        for n in range(kn):
            total += gNo[n][m]
        gNo[kn][m] = total

    gNo.append( [0] * (kn + 1) )
    total = 0
    for n in range( kn ):
        gNo[kn + 1][n] = len( gTrainData[n] )
        total += gNo[kn + 1][n]
    gNo[kn + 1][kn] = total
    return 0

def setGPro():
    '''
    read gNo to establish gPro
    :return:
    '''
    print 'reading gNo to establish gPro'
    wln = len(gWordList) + 1  # the number of different words + 1
    kn = FNO  # the number of kinds
    for m in range(kn + 1):
        gPro.append( [0] * wln )
        for n in range(wln-1):
            gPro[m][n] = gNo[m][n]/float(gNo[m][-1])
        gPro[m][-1] = gNo[-1][m]/float(gNo[-1][-1])
    return 0

def calculate():
    '''
    read gPro to establish gResult
    :return:
    '''
    cutWords( 'test' )
    print 'reading gPro to establish gResult'
    fi = open('cuttest')
    line = fi.readline()
    ii = 0
    while line:
        words = line[:-1].split(' ')
        ll = []
        for w in words:
            if gWordList.has_key(w):
                ll.append( gWordList[w] )
        if len(ll) != 0:
            res = [line]
            proa = 1
            for i in range( FNO ):
                prob = 1
                for l in ll:
                    prob *= gPro[i][l]
                    if i==0:
                        proa *= gPro[-1][l]
                prob *= gPro[i][-1]
                prob /= proa
                res.append(prob)
            gResult.append( res )
        line = fi.readline()
        ii += 1
        if ii % 100000 == 0:
            print 'calculate line ' + str(ii)
    print 'calculate line ' + str(ii)

    fi.close()
    return 0

def getResult(n):
    '''
    create result file
    :param n:
    :return:
    '''
    res = []
    for r in gResult:
        res.append( [r[n+1], r[0]] )
    res.sort()
    res.reverse()
    fo = open('reusult' + str(n), 'wb')
    print 'creating file ' + 'reusult' + str(n)
    for r in res:
        fo.write( str(r[0]) + '\t' + r[1] )
    fo.close()

def setGS():
    '''
    calculate variance of different words to establish gS
    :return:
    '''
    import math
    print 'reading gPro to establish gS'
    wn = len(gWordList)
    kn = FNO
    for w in range(wn):
        average = 0
        for k in range(kn):
            average += gPro[k][w]
        average /= kn
        s2 = 0
        for k in range(kn):
            s2 += (gPro[k][w] - average)**2
        s2 /= kn
        s2 = math.sqrt(s2)
        gS.append( [s2,w] )
    return 0

def getGS():
    '''
    establish s.txt
    :return:
    '''
    print 'establishing s.txt...'
    dictnw = {} #number of a word and word
    words = gWordList.keys()
    for w in words:
        dictnw[ gWordList[w] ] = w
    gS.sort()
    fo = open( 's.txt','wb' )
    for s in gS:
        fo.write( str(s[0]) + '\t' + dictnw[s[1]] + '\n' )
    fo.close()
    return 0

def main():
    dealTrainData()
    setGNo()
    setGPro()
    calculate()
    setGS()
    getGS()
    # for r in range(FNO):
    #     getResult(r)
main()

