#ifndef SWALIGN_H
#define SWALIGN_H
#include <list>


struct SWPosition{
  int row;
  int column;
};

class CSWAlign{

 public:
  CSWAlign();
  ~CSWAlign();
  
 private:
  int score_of_mismatch;
  int score_of_match;
  int score_of_gap;
  int* foostr;
  int foolen;
  int* barstr;
  int barlen;
  int* scorematrix;
  char* directmatrix;
  std::list<int>* result;
  std::list<char>* direct;

  int* matchstr;
  int matchlength;
  int* foomatchindex;
  int* barmatchindex;
 public:
  void setScore(int match, int mis, int gap);
  /*
    'm' means Match
    'f'  means adding a gap to Foo string
    'b' means adding a gap to Bar string 
  */
  void calculate();
  
  void setfoo(int* str, int len);
  void setbar(int* str, int len);
  int getMaxIndex(int *m, int len);
  void dump();

  const int* getmatchstr(){ return matchstr;};
  const int* getfoomatchindex(){ return foomatchindex;}
  const int* getbarmatchindex(){ return barmatchindex;}
  int getmatchlength();

};
#endif
