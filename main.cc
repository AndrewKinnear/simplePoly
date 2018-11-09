/* Andrew Kinnear
   300176911
   Lab 3, Polynomials
*/

#include <iostream>
#include <fstream>
using namespace std;

struct node{
  int coef;
  int exp;
  node * next;
};

void print(node * list){
  while(list){
    cout << list->coef << "    " << list->exp << "     " << list->next<< endl;
    list = list->next;
  }
}

node* addNode(node * list, int coef, int exp){
  node * temp = new node;
  temp->coef = coef;
  temp->exp = exp;
  temp->next = list;
  list = temp;
  return list;
}
//Practice for your Midterm returns the list reversed.
node* reverseList(node * list, node * acc){
  if(list == NULL)
    return acc;
  else{
    node * nodeCopy = new node();
    nodeCopy->coef = list->coef;
    nodeCopy->exp = list->exp;
    if(acc == NULL)
      nodeCopy->next = NULL;
    else
      nodeCopy->next = acc;
    list = list->next;
    return reverseList(list, nodeCopy);
  }
}
//Writes to specified file
void printFile(node* list,string fileName){
  ofstream outFile;
  outFile.open(fileName.c_str());
  while(list){
    outFile << list->coef << endl;
    outFile << list->exp << endl;
    list =  list->next;
  }
  outFile.close();
}
//Creates my lists
node* buildList(node * list, string fileName){//Needs to take in file name;
  ifstream infile;
  infile.open(fileName.c_str());
  int inCoef;
  int inExp;
  while(infile >> inCoef){
    inExp = 0;
    infile >> inExp;
    list = addNode(list, inCoef, inExp);
  }
  return list;
}

//Tail recursivly gets my answer
node * getAnswer(node * listOne, node * listTwo, node * ansList){
  if(listOne == NULL && listTwo == NULL){
      return ansList;
  }else{
    if(listTwo == NULL){
      ansList = addNode(ansList, listOne->coef, listOne->exp);
      return getAnswer(listOne->next, listTwo, ansList);
    }
    if(listOne == NULL){
      ansList = addNode(ansList, listTwo->coef, listTwo->exp);
      return getAnswer(listOne, listTwo->next, ansList);
    }
    if(listOne->exp == listTwo->exp){
      ansList = addNode(ansList, listOne->coef+listTwo->coef, listOne->exp);
      return getAnswer(listOne->next, listTwo->next, ansList);
    }
    if(listOne->exp < listTwo->exp){
      ansList = addNode(ansList, listOne->coef, listOne->exp);
      return getAnswer(listOne->next, listTwo, ansList);
    }
    if(listOne->exp > listTwo->exp){
      ansList = addNode(ansList, listTwo->coef, listTwo->exp);
      return getAnswer(listOne, listTwo->next, ansList);
    }
  }
}

int main(int argc, char * argv[]){

  if(argc < 4){
    cout << "Please have two input files, and one output file."<< endl;
    return 1;
  }

  node * listOne;
  node * listTwo;
  node * ansList;

  listOne = buildList(listOne, argv[1]);
  listTwo = buildList(listTwo, argv[2]);

  ansList = getAnswer(listOne, listTwo,ansList);

  printFile(ansList, argv[3]);
  return 0;
}
