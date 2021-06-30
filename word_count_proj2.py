import string

def puncTableGen():
    """문자부호 제거/구점을 온점으로 변경/두점 제거"""
    map_D=dict()
    for i in string.punctuation:
        map_D[i]=''
    map_D['-']=' ';map_D['!']='.';map_D['?']='.';map_D['~']='.';map_D['.']='.'
    table=str.maketrans(map_D)
    return table

def preprocess(book_name, in_file_path, out_file_path, startTag, lastTag):
    """소설책 데이터 전처리"""
    with open(in_file_path,'r') as f_r:
        with open(out_file_path, 'w') as f_w:
            sent=''

            #전반부 제거
            for line in f_r:
                if line.startswith(startTag)==True:
                    break


            #불완전한 문장 제거 - 목차리스트
            for line in f_r:
                if line.startswith(book_name):
                    break
                contentList=[]
                if line=='\n':
                    pass
                else:
                    con=line.split('.')[1]
                    con=con.replace('  ','');con=con.replace('\n','')
                    contentList=contentList.append(con)

                
            for line in f_r:
                #후반부 제거
                if line.startswith(lastTag)==True:
                    break
                
                #불완전한 문장 제거
                if line=='\n':
                    line=line.replace('\n','')

                if len(line.split())==1 or line in contentList:
                    line=''

                    
                #'s 또는 'S 제거
                line=line.replace("'s",'');line=line.replace("'S",'')
                
                #.이 포함되는 표현 변경
                line=line.replace("Mr.","Mr");line=line.replace("Mrs.","Mrs")
                line=line.replace("Ms.","Ms");line=line.replace("Dr.","Dr")

                #문자부호 제거/구점을 온점으로 변경/두점 제거
                line=line.translate(puncTableGen())

                #소문자 변환
                line=line.lower()

                idx=line.find(".")
                while idx!=-1:
                    sent+=line[:idx]
                    sent+=" ."
                    line=line[idx+1:].strip()
                    idx=line.find(".")
                    f_w.write(sent+"\n")
                    sent=""
                sent+=line+" "
    
    return out_file_path
                    

def countBigrams(preprocessed_book_path):
    """전처리된 데이터를 이용해 bigram을 count"""
    with open(preprocessed_book_path,'r') as f_r:
        bigram=dict()
        
        for line in f_r:
            line='<s> '+line;line=line.replace('.','</s>')
            word=line.split()
            for i in range(len(word)-1):
                bigram[word[i]+' '+word[i+1]]=bigram.get(word[i]+' '+word[i+1],0)+1
    return bigram


def my_sort(Dict):
    """입력 Dict: 사전 {단어:사용횟수} / 출력 List: 정렬된 리스트[(사용횟수,단어)] - 내림차순 정렬"""
    List=[]
    for key, value in Dict.items():
        List.append((value,key))
        
    #내림차순 정렬
    for i in range(len(List)-1):
        for j in range(i,len(List)):
            if List[j][0]>List[i][0]:
                List[i],List[j]=List[j],List[i]
    
    return List

def outBigramsStat(bi_gram):
    """학습한 bigram LM의 통계를 출력"""
    bigram=my_sort(bi_gram)
    
    print("사용된 bigram의 총 개수:",len(bi_gram))
    print("bigram별 사용횟수 상위 1% (내림차순)")
    for i in range(len(bigram)//100):
        print("{:<20s} {:<20d}" .format(bigram[i][1], bigram[i][0]))


def outShannonVisualization(bi_gram):
    """학습한 bigram LM Shannon Visualization 결과를 출력"""
    w='<s>';bigram=my_sort(bi_gram);wStartList=[]
    while w!='</s>':
        for bg in bigram:
            if bg[1].startswith(w)==True:
                w=bg[1].split()[1]
                wStartList.append(w)
                bigram.remove(bg)
                break
    wStartList[0]=wStartList[0].title();wStartList.remove('</s>')
    for w in wStartList:
        print(w, end=' ')


# main
book_name="A Little Princess";file_name="Little_Princess.txt"
in_file_path="Little_Princess.txt"
out_file_path="preprocessed_Little_Princess.txt"

startTag="CONTENTS"
lastTag="End of Project"

print(f"전자서적 이름: {file_name}\n")

# Preprocessing
preprocessed_book_path=preprocess(book_name, in_file_path, out_file_path, startTag, lastTag)

# Bigram Count
bi_gram=countBigrams(preprocessed_book_path)
outBigramsStat(bi_gram)

# Shannon Visualization
print("\n%s의 Shannon Visualization: " %file_name)
outShannonVisualization(bi_gram)
