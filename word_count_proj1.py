import string

def puncTableGen():
    """문자부호 제거"""
    map_D=dict()
    for i in string.punctuation:
        map_D[i]=''
    map_D['-']=' '
    table=str.maketrans(map_D)
    return table

def countWords(inFName, puncTable, startTag, lastTag):
    """단어의 사용 횟수 계산"""
    Fp=open(inFName,'r',encoding="utf-8")

    for s in Fp:
        if s.startswith(startTag)==True:
            break

    wDict=dict()

    for s in Fp:
        if s.startswith(lastTag)==True:
            break
        s=s.replace("'s",'');s=s.replace("'S",'')
        s=s.translate(puncTable)

        for w in s.split():   
            w=w.lower()
            wDict[w]=wDict.get(w,0)+1

    Fp.close()
    return wDict


def sortWords(wDict):
    """입력 wDict: 사전 {단어:사용횟수}
출력 wList: 정렬된 리스트[(사용횟수,단어)]"""
    wList=[]
    for key, value in wDict.items():
        wList.append((value,key))
    wList.sort()
    return wList

def countLeastWds(wList):
    """단어들의 개수를 구하는 함수"""
    leastUsed=wList[0][0]
    cnt=0
    for i in wList:
        if i[0]!=leastUsed:
            break
        else:
            cnt+=1
    return leastUsed, cnt

def outWordStat(wDict, outFName, inFName):
    """단어의 사용 횟수 출력"""
    wList=sortWords(wDict)
    leastUsed, wCnt=countLeastWds(wList)
    
    print("전자서적 이름 : %s\n" %outFName)
    print("사용된 단어의 개수 : %d\n" %len(wList))
    print("사용횟수가 가장 작은 단어 통계")
    print("사용횟수: %d, 단어수: %d, 백분율: %d%%\n" \
          %(leastUsed, wCnt, wCnt/len(wList)*100))
    print("단어별 사용횟수(내림차순)")
    wList.sort(reverse=True)
    for i in range(len(wList)):
        print("{:<15s} {:<15d}" .format(wList[i][1], wList[i][0]))


import time

inFName="Little_Princess.txt"
outFName="Little_Princess.txt"
startTag="Produced by"
lastTag="End of Project"

startTime=time.time()

puncTable=puncTableGen()
wordsDict=countWords(inFName, puncTable, startTag, lastTag)
outWordStat(wordsDict, outFName, inFName)

execTime=time.time()-startTime
print("\n실행 완료(소요 시간 = %.2f초)" %execTime)
