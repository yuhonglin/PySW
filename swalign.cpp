/**
 * @file   swalign.cpp
 * @author yuhonglin <yuhonglin1986@gmail.com>
 * @date   Sat Jun  1 18:59:04 2013
 * 
 * @brief  The implementation of Smith-Waterman Algorithm
 * 
 * 
 */
#include "swalign.h"
#include <iostream>


CSWAlign::CSWAlign(){
  result = new std::list<int>;
  direct = new std::list<char>;
  score_of_match = 1;
  score_of_mismatch = -1;
  score_of_gap = 0;
  foostr = NULL;
  barstr = NULL;
  foolen = 0;
  barlen = 0;
  scorematrix = NULL;
  directmatrix = NULL;
  matchstr = NULL;
  matchlength = 0;
  foomatchindex = NULL;
  barmatchindex = NULL;
}

CSWAlign::~CSWAlign(){
  if(result!=NULL)
    delete result;
  if(direct!=NULL)
    delete direct;
  if(scorematrix!=NULL)
    delete scorematrix;
  if(directmatrix!=NULL)
    delete directmatrix;
  
}

void CSWAlign::setScore(int mat, int mis, int gap){
  score_of_match = mat;
  score_of_mismatch = mis;
  score_of_gap = gap;
}

void CSWAlign::setfoo(int* str, int len){
  if(foostr!=NULL)
    delete foostr;
  foostr = new int[len];
  for(int i=0; i<len; i++){
    foostr[i] = str[i];
  }
  foolen = len;

}

void CSWAlign::setbar(int* str, int len){
  if(barstr!=NULL)
      delete barstr;
  barstr = new int[len];
  for(int i=0; i<len; i++){
    barstr[i] = str[i];
  }
  barlen = len;
}

int CSWAlign::getMaxIndex(int *m, int length){
  int max = m[0];
  int index = 0;
  int i = 1;
  for(; i<length; i++){
    if(m[i]>=max){
      max = m[i];
      index = i;
    }
  }
  
  return index;
}

/*                           bar
       -------------------------------------------------
       |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
       |0
foo    |0
       |0
       |0
       |0
       -------------------------------------------------

  F[1] F[2]
  F[0]

  direct = 't' means coming from top
  direct = 'l' means coming from left
  direct = 'c' means coming from the corner
  direct = 'n' means NULL
 */
void CSWAlign::calculate(){
  if(foolen==0||barlen==0){
    std::cerr<<"void CSWAlign::SWcalculate() can not calculate without strings assigned.\n";
    return;
  }

  result->clear();
  direct->clear();
  matchlength = 0;
  
  foolen++;
  barlen++;

  if(scorematrix!=NULL)
    delete scorematrix;
  scorematrix = new int[foolen*barlen];
  if(directmatrix!=NULL)
    delete directmatrix;
  directmatrix = new char[foolen*barlen];
  int i = 0, j = 0;
  int F[3] = {0,0,0};
  int maxindex = 0;
  for(; i<foolen; i++){
    for(j=0; j<barlen; j++){
      if(!i){
	scorematrix[j] = 0;
	directmatrix[j] = 'n';
	continue;
      }
      if(!j){
	scorematrix[i*barlen] = 0;
	directmatrix[i*barlen] = 'n';
	continue;
      }
      F[0] = scorematrix[i*barlen+j-1] +  score_of_gap;
      F[2] = scorematrix[(i-1)*barlen+j] +  score_of_gap;
      if(foostr[i-1]==barstr[j-1])
	F[1] = scorematrix[(i-1)*barlen+j-1] + score_of_match;
      else
	F[1] =  scorematrix[(i-1)*barlen+j-1] + score_of_mismatch;
      
      maxindex = getMaxIndex(F, 3);
      scorematrix[i*barlen+j] = F[maxindex];
      if(maxindex==0){;
	directmatrix[i*barlen+j] = 'l';
      }else if(maxindex==1){
	directmatrix[i*barlen+j] = 'c';
      }else{
	directmatrix[i*barlen+j] = 't';
      }
    }
  }

  maxindex = getMaxIndex(scorematrix, foolen*barlen);
  int w = maxindex%barlen;
  int h = maxindex/barlen;

  char t = 'n';
  while(w>0&&h>0){
    t = directmatrix[h*barlen+w];
    if(t=='l'){
      direct->push_back('f');
      w--;
    }else if(t=='t'){
      direct->push_back('b');
      h--;
    }else if(t=='c'){
      direct->push_back('m');
      matchlength++;
      w--;
      h--;
    }
  }
  if(h==0){
    while(w>0){
      direct->push_back('f');
      w--;
    }
  }else{
    while(h>0){
      direct->push_back('b');
      h--;
    }
  }

  int fooindex = 0;
  int barindex = 0;
  int matchindex = 0;
  std::list<char>::iterator iter = direct->end();
  if(matchstr!=NULL)
    delete matchstr;
  if(foomatchindex!=NULL)
    delete foomatchindex;
  if(barmatchindex!=NULL)
    delete barmatchindex;
  matchstr = new int[matchlength];
  foomatchindex = new int[matchlength];
  barmatchindex = new int[matchlength];
  for(;; iter--){
    if((*iter)=='m'){
      matchstr[matchindex] = foostr[fooindex];
      foomatchindex[matchindex] = fooindex;
      barmatchindex[matchindex] = barindex;
      fooindex++;
      barindex++;
      matchindex++;
    }else if((*iter)=='f'){
      barindex++;
    }else if((*iter)=='b'){
      fooindex++;
    }
    if(iter==direct->begin())
      break;
  }
  

  foolen--;
  barlen--;
 
}

void CSWAlign::dump(){
   /*display*/
  if(direct->empty()){
    std::cerr<<"Nothing to display\n";
    return;
  }
  
  std::cout<<"Matched string:\n";
  for(int i=0; i<matchlength; i++){
    std::cout<<matchstr[i]<<'\t';
  }

  std::cout<<"\nMatched index:\nfoo\tbar\n";
  for(int i=0; i<matchlength; i++){
    std::cout<<foomatchindex[i]<<'\t'<<barmatchindex[i]<<'\n';
  }
  
  std::cout<<"\nThe two strings:\nfoo\tbar\n";
  int fooindex = 0;
  int barindex = 0;  
  std::list<char>::iterator iter = direct->end();
  for(;; iter--){
    if((*iter)=='m'){
      std::cout<<foostr[fooindex]<<"\t"<<barstr[barindex]<<std::endl;
      fooindex++;
      barindex++;
    }else if((*iter)=='f'){
      std::cout<<"-"<<"\t"<<barstr[barindex]<<std::endl;
      barindex++;
    }else if((*iter)=='b'){
      std::cout<<foostr[fooindex]<<"\t"<<"-"<<std::endl;
      fooindex++;
    }
    if(iter==direct->begin())
      break;
  }
  
  std::cout<<"\nScore Matrix:\n";
  for(int di=0; di<foolen+1; di++){
    for(int dj=0; dj<barlen+1; dj++){
      std::cout<<scorematrix[di*(barlen+1)+dj]<<'\t';
    }
    std::cout<<'\n';
  }
  
  std::cout<<"\nDirect Matrix:\n";
  for(int di=0; di<foolen+1; di++){
    for(int dj=0; dj<barlen+1; dj++){
      std::cout<<directmatrix[di*(barlen+1)+dj]<<'\t';
    }
    std::cout<<'\n';
  }
  
}


int CSWAlign::getmatchlength(){
  return matchlength;
}
