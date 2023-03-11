#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "choice.hpp"

class Story{
  private:
    size_t page_num;
    char page_type;
    const char * page_filename;
    bool referenced;
    std::vector<Choice *> choices;
    std::vector<std::pair<std::string,long int> > variables;
    
  public:
    //constructor
    Story(): page_num(0), page_type('N'), page_filename(NULL), referenced(false){}
    Story(size_t pn, char pt, const char * pfn): page_num(pn), page_type(pt), page_filename(pfn), referenced(false){}
    //destructor
    ~Story(){
      std::vector<Choice *>::iterator it = choices.begin();
      while(it!=choices.end()){
        delete *it;
        ++it;
      }
      delete[] page_filename;
    }
    //copy constructor
    Story(const Story & rhs): page_num(rhs.page_num), page_type(rhs.page_type), page_filename(NULL), referenced(rhs.referenced){
      char * pfn = new char[strlen(rhs.page_filename)+1];
      strcpy(pfn,rhs.page_filename);
      page_filename = pfn;
      choices = rhs.choices;
      variables = rhs.variables;
    }
    //assignment operator
    Story & operator=(const Story & rhs){
      if(this != &rhs){
        std::vector<Choice *> tmp1;
        tmp1 = rhs.choices;
        for(size_t i = 0;i<choices.size();++i){
          delete choices[i];
        }
        choices.clear();
        choices = tmp1;
        for(size_t i = 0;i<tmp1.size();++i){
          delete tmp1[i];
        }
        tmp1.clear();
        std::vector<std::pair<std::string,long int> > tmp2;
        tmp2 = rhs.variables;
        variables.clear();
        variables = tmp2;
        tmp2.clear();
        char * temp = new char[strlen(rhs.page_filename)+1];
        strcpy(temp,rhs.page_filename);
        delete[] page_filename;
        page_filename = temp;
        page_num = rhs.page_num;
        page_type = rhs.page_type;
      }
      return *this;
    }
    //This method adds choice to the page
    void addChoice(size_t pn, size_t jpn, std::string cc, std::string name, long int value){
      Choice * c = new Choice(pn, choices.size()+1, jpn, cc);
      c->addCondition(name,value);
      choices.push_back(c);
    }
    //This method adds variable to the page
    void addVariable(std::string name, long int value){
      std::vector<std::pair<std::string,long int> >::iterator it = variables.begin();
      while(it!=variables.end()){
        if((*it).first.compare(name)==0){
          (*it).second = value;
          return;
        }
        ++it;
      }
      variables.push_back(make_pair(name,value));
    }
    //This method sets the variables of the page to the user's inventory
    void setVariables(std::vector<std::pair<std::string,long int> > & inventory){
      std::vector<std::pair<std::string,long int> >::iterator it = variables.begin();
      while(it!=variables.end()){
        std::vector<std::pair<std::string,long int> >::iterator ivt = inventory.begin();
        while(ivt!=inventory.end()){
          if((*it).first.compare((*ivt).first)==0){
            (*ivt).second = (*it).second;
            break;
          }
          ++ivt;
        }
        if(ivt==inventory.end()){
          inventory.push_back(make_pair((*it).first,(*it).second));
        }
        ++it;
      }
      return;
    }
    //This method prints the content and choices of one page
    void printOnePage(std::vector<std::pair<std::string,long int> > & inventory, int mode){
      if(mode == 1){
        std::cout<<"Page "<<page_num<<std::endl;
        std::cout<<"=========="<<std::endl;
      }
      std::ifstream ifs;
      ifs.open(page_filename,std::ios::in);
      if(!ifs.is_open()){
        std::cerr<<"Can't open the page:"<<page_filename<<std::endl;
        exit(EXIT_FAILURE);
      }
      std::string buf;
      while(getline(ifs,buf)){
        std::cout<<buf<<std::endl;
      }
      ifs.close();
      //prints choice or ending statement based on the page type
      if(page_type=='W'){
        std::cout<<"\nCongratulations! You have won. Hooray!"<<std::endl;
      }else if(page_type=='L'){
        std::cout<<"\nSorry, you have lost. Better luck next time!"<<std::endl;
      }else{
        std::cout<<"\nWhat would you like to do?\n"<<std::endl;
        std::vector<Choice *>::iterator it = choices.begin();
        while(it != choices.end()){
          (*it)->printChoice(inventory);
          ++it;
        }
      }
      return;
    }
    //This method checks the type of the page ('N','W','L') and makes sure the WIN and LOSE pages do not have any choice
    int checkOnePage(){
      if(page_type=='W'){
        if(choices.size()!=0){
          std::cerr<<"Win pages MUST NOT have any choices!"<<std::endl;
          exit(EXIT_FAILURE);
        }
        return 1;
      }else if(page_type=='L'){
        if(choices.size()!=0){
          std::cerr<<"Lose pages MUST NOT have any choices!"<<std::endl;
          exit(EXIT_FAILURE);
        }
        return -1;
      }
      return 0;
    }
    //This method returns all the page numbers that all the choices in that page refer to
    std::vector<size_t> getAllChoiceReferences(){
      std::vector<size_t> refs;
      std::vector<Choice *>::iterator it = choices.begin();
      while(it != choices.end()){
        if(page_num!=(*it)->getJumpPageNum()){
          refs.push_back((*it)->getJumpPageNum());
        }
        ++it;
      }
      return refs;
    }
    //This method returns the reference of the selected choice
    size_t findTheChoiceReference(size_t input){
      std::vector<Choice *>::iterator it = choices.begin();
      for(size_t i = 0; i < input-1; i++){
        ++it;
      }
      return (*it)->getJumpPageNum();
    }
    //This method returns a boolean that means whether a choice is accessable according to the user's inventory
    bool checkTheChoiceValidation(size_t input){
      std::vector<Choice *>::iterator it = choices.begin();
      for(size_t i = 0; i < input-1; i++){
        ++it;
      }
      return (*it)->getValidationOfChoice();
    }
    //The following methods return the value of private variables in Story class
    size_t getPageNum(){
      return page_num;
    }
    char getPageType(){
      return page_type;
    }
    bool getReferenced(){
      return referenced;
    }
    size_t getSizeOfChoices(){
      return choices.size();
    }
    void setReferencedTrue(){
      referenced = true;
    }
};