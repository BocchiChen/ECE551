#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "story.hpp"

class File{
  private:
    size_t win_pages;
    size_t lose_pages;
    std::vector<Story *> pages;
    std::vector<Story *>::iterator location;
    std::vector<std::pair<std::string,long int> > inventory;
    
  public:
    //constructor
    File(): win_pages(0), lose_pages(0), location(NULL){}
    //destructor
    ~File(){
       std::vector<Story *>::iterator it = pages.begin();
       while(it!=pages.end()){
         delete *it;
         ++it;
       }
    }
    //copy constructor
    File(const File & rhs): win_pages(rhs.win_pages), lose_pages(rhs.lose_pages){
      pages = rhs.pages;
      location = rhs.location;
      inventory = rhs.inventory;
    }
    //assignment operator
    File & operator=(const File & rhs){
      if(this != &rhs){
        std::vector<Story *> tmp1;
        tmp1 = rhs.pages;
        for(size_t i = 0;i<pages.size();++i){
          delete pages[i];
        }
        pages.clear();
        pages = tmp1;
        for(size_t i = 0;i<tmp1.size();++i){
          delete tmp1[i];
        }
        tmp1.clear();
        std::vector<std::pair<std::string,long int> > tmp2;
        tmp2 = rhs.inventory;
        inventory.clear();
        inventory = tmp2;
        win_pages = rhs.win_pages;
        lose_pages = rhs.lose_pages;
        location = rhs.location;
      }
      return *this;
    }
    //step 1 and step 4
    void readFile(char * filename){
      std::string sfn = filename;
      sfn += "/story.txt";
      char * tfn = new char [sfn.size()+1];
      strcpy(tfn,sfn.c_str());
      std::ifstream ifs;
      //open the directory file
      ifs.open(tfn,std::ios::in);
      delete[] tfn;
      if(!ifs.is_open()){
        std::cerr<<"Can't open the directory file:"<<sfn<<std::endl;
        exit(EXIT_FAILURE);
      }
      std::string prefix = sfn.substr(0,sfn.rfind("/")+1);
      std::string buf;
      size_t max_pn = 0;
      while(getline(ifs,buf)){
        //skip any blank line (containing only whitespace)
        if(buf.erase(0,buf.find_first_not_of(" ")).length()==0){
          continue;
        }
        if(buf.find("$")!=std::string::npos){
          //if the string line contains $, which is a type in step4, check the page number first
          checkIsNum(buf.substr(0,buf.find("$")).c_str(),1);
          size_t pn = strtoul(buf.substr(0,buf.find("$")).c_str(),NULL,10);
          //the page number should be less than the maximum page number to prevent anything else related to that page appears before a page declaration
          if(pn >= max_pn){
            std::cerr<<"A page declaration (num@filename) for a given page must appear before anything else related to that page!"<<std::endl;
            exit(EXIT_FAILURE);
          }
          std::string setting = buf.substr(buf.find("$")+1);
          if(setting.find("=")==std::string::npos){
            std::cerr<<"Invalid type of line in the directory: "<< buf <<std::endl;
            exit(EXIT_FAILURE);
          }
          std::string variable_name = setting.substr(0,setting.find("="));
          checkIsNum(setting.substr(setting.find("=")+1).c_str(),2);
          long int variable_value = strtol(setting.substr(setting.find("=")+1).c_str(),NULL,10);
          pages[pn]->addVariable(variable_name,variable_value);
          
        }else if(buf.find("@")!=std::string::npos){
          //if the string line contains @, which is a type in step1
          checkIsNum(buf.substr(0,buf.find("@")).c_str(),1);
          size_t pn = strtoul(buf.substr(0,buf.find("@")).c_str(),NULL,10);
          if(pn != max_pn){
            std::cerr<<"Page declarations must appear in order!"<<std::endl;
            exit(EXIT_FAILURE);
          }
          ++max_pn;
          char pt = buf.substr(buf.find("@")+1,1)[0];
          if(pt!='N'&&pt!='W'&&pt!='L'){
            std::cerr<<"Page type is invalid!"<<std::endl;
            exit(EXIT_FAILURE);
          }
          if(buf.find(":")==std::string::npos){
            std::cerr<<"Invalid type of line in the directory: "<<buf<<std::endl;
            exit(EXIT_FAILURE);
          }
          std::string bufsub = prefix + buf.substr(buf.find(":")+1);
          char * pfn = new char [bufsub.size()+1];
          strcpy(pfn,bufsub.c_str());
          //create a new page and save it in the pages vector
          Story * s = new Story(pn, pt, pfn);
          pages.push_back(s);
          
        }else if(buf.find(":")!=std::string::npos){
          //if the string line contains :, which is a type in step1
          char sep = ':';
          if(buf.find("[")!=std::string::npos){
            sep = '[';
          }
          checkIsNum(buf.substr(0,buf.find(sep)).c_str(),1);
          size_t pn = strtoul(buf.substr(0,buf.find(sep)).c_str(),NULL,10);
          if(pn >= max_pn){
            std::cerr<<"A page declaration (num@filename) for a given page must appear before anything else related to that page!"<<std::endl;
            exit(EXIT_FAILURE);
          }
          
          std::string condition = "";
          std::string name = "";
          long int value = -1;
          
          //if condition exists in a choice
          if(buf.find("[")!=std::string::npos){
            if(buf.find("]")==std::string::npos){
              std::cerr<<"Invalid type of line in the directory: "<<buf<<std::endl;
              exit(EXIT_FAILURE);
            }
            condition = buf.substr(buf.find("[")+1,buf.find("]")-buf.find("[")-1);
            if(condition.find("=")==std::string::npos || condition.length()==1){
              std::cerr<<"Invalid type of line in the directory: "<<buf<<std::endl;
              exit(EXIT_FAILURE);
            }
            name = condition.substr(0,condition.find("="));
            checkIsNum(condition.substr(condition.find("=")+1).c_str(),2);
            value = strtol(condition.substr(condition.find("=")+1).c_str(),NULL,10);
          }
          //split the line to obtain the page number, choice reference and choice content
          std::string su = buf.substr(buf.find(":")+1);
          if(su.find(":")==std::string::npos){
            std::cerr<<"Invalid type of line in the directory: "<< buf <<std::endl;
            exit(EXIT_FAILURE);
          }
          checkIsNum(su.substr(0,su.find(":")).c_str(),1);
          size_t jpn = strtoul(su.substr(0,su.find(":")).c_str(),NULL,10);
          std::string cc = su.substr(su.find(":")+1);
          //add choice to the page
          pages[pn]->addChoice(pn, jpn, cc, name, value);
          
        }else{
          //if no type of line is satisfied, make an error
          std::cerr<<"Invalid type of line in the directory: "<<buf<<std::endl;
          exit(EXIT_FAILURE);
        }
      }
      ifs.close();
    }
    
    //This method prints all the pages 
    void printAllPages(){
      std::vector<Story *>::iterator it = pages.begin();
      while(it!=pages.end()){
        (*it)->printOnePage(inventory, 1);
        ++it;
      }
    }
    
    //This method is used to check whether a string is an valid integer
    void checkIsNum(const char * str, int mode){
      char * ptr_end;
      if(mode == 1){
        strtoul(str,&ptr_end,10);
      }else{
        strtol(str,&ptr_end,10);
      }
      //make sure the page number is made of full integers (except leading whitespaces) and it must have at least one character
      if((*ptr_end)!='\0'||str[0]=='\0'){
        std::cerr<<"Page number must be an integer!"<<std::endl;
        exit(EXIT_FAILURE);
      }
    }
    
    //step 2 and step 4
    //This method checks whether conditions in step 2 are satisfied
    void checkPages(){
      std::vector<Story *>::iterator it = pages.begin();
      while(it!=pages.end()){
        int type = (*it)->checkOnePage();
        //if type is 1, it is a WIN page
        if(type == 1){
          ++win_pages;
        //if type is -1, it is a LOSE page
        }else if(type == -1){
          ++lose_pages;
        }else{
           std::vector<size_t> refs = (*it)->getAllChoiceReferences();
           std::vector<size_t>::iterator rit = refs.begin();
           while(rit!=refs.end()){
             std::vector<Story *>::iterator pit = pages.begin();
             while(pit!=pages.end()){
               if((*pit)->getPageNum()==(*rit)){
                 (*pit)->setReferencedTrue();
                 break;
               }
               ++pit;
             }
             //If no page is found, make an error
             if(pit==pages.end()){
               std::cerr<<"Every page that is referenced by a choice should be valid."<<std::endl;
               exit(EXIT_FAILURE);
             }
             ++rit;
           }
        }
        ++it;
      }
      //check whether the dictionary file has at least one WIN page and one LOSE page 
      if(win_pages==0||lose_pages==0){
        std::cerr<<"At least one page must be a WIN page and at least one page must be a LOSE page."<<std::endl;
        exit(EXIT_FAILURE);
      }
      //iterate through all the pages to find the one who has not been referenced or the normal page who has no choice
      it = pages.begin();
      while(it!=pages.end()){
        if((*it)->getPageNum() != 0 && (*it)->getReferenced() == false){
          std::cerr<<"Every page (except page 0) should be referenced by at least one *other* page's choices."<<std::endl;
          exit(EXIT_FAILURE);
        }
        if((*it)->getPageType() == 'N' && (*it)->getSizeOfChoices() == 0){
          std::cerr<<"Every page (except WIN and LOSE page) should have at least one choice."<<std::endl;
          exit(EXIT_FAILURE);
        }
        ++it;
      }
      return;
    }
    
    //This method prints the content of the first page, jumps and prints the page based on the user's choice
    void startReadingStory(){
      location = pages.begin();
      //iterate until the type of page is 'W' or 'L'
      while((*location)->getPageType()=='N'){
        (*location)->setVariables(inventory);
        (*location)->printOnePage(inventory, 2);
        size_t input = 0;
        size_t sz = (*location)->getSizeOfChoices();
        bool choice_valid = false;
        while(input==0 || input > sz || !choice_valid){
          std::cin >> input;
          if(!std::cin.good()){
            std::cin.clear();
            std::string bin;
            std::cin >> bin;
          }
          //if the input stream reaches the end of the file, while the game is not over
          if(std::cin.eof()){
            std::cerr<<"Insufficient choices to let the game end"<<std::endl;
            exit(EXIT_FAILURE);
          }
          //if the user input is over the number of valid choices or is zero, prompt out the message for asking the user to input again
          if(input==0 || input > sz){
            std::cout<<"That is not a valid choice, please try again"<<std::endl;
          }else{
            //if user select an unavailable choice, prompt out the message for asking the user to input again
            choice_valid = (*location)->checkTheChoiceValidation(input);
            if(!choice_valid){
              std::cout<<"That choice is not available at this time, please try again"<<std::endl;
            }
          }
        }
        //find the page number that will jump to based on the user choice
        size_t jump_page_num = (*location)->findTheChoiceReference(input);
        std::vector<Story *>::iterator it = pages.begin();
        while(it!=pages.end()){
          if((*it)->getPageNum()==jump_page_num){
            location = it;
            break;
          }
          ++it;
        }
      }
      //print the WIN or LOSE page
      (*location)->printOnePage(inventory, 2);
    }
    
    //step 3
    void findPathsToSuccess(){
      std::vector<size_t> res;
      //create an array called visited to prevent visiting the page that has been added to the path
      bool visited[pages.size()] = {false};
      dfs(res,visited,0);
    }
    //This method utilizes the depth-first search algorithm to find possible paths to success 
    void dfs(std::vector<size_t> & res, bool visited[], size_t pos){
      //if the path reaches the success page, print the path and backtrack
      if(pages[pos]->checkOnePage()==1){
        res.push_back(pos);
        printPath(res);
        res.pop_back();
        return;
      }
      if(visited[pos]==true||pages[pos]->checkOnePage()==-1){
        return;
      }
      visited[pos] = true;
      size_t choice_num = 1;
      std::vector<size_t> refs = pages[pos]->getAllChoiceReferences();
      //try all the choice references to seek the possible path
      std::vector<size_t>::iterator rit = refs.begin();
      while(rit!=refs.end()){
        res.push_back(pos);
        res.push_back(choice_num);
        dfs(res,visited,*rit);
        res.pop_back();
        res.pop_back();
        ++choice_num;
        ++rit;
      }
      visited[pos] = false;
      return;
    }
    //This method prints the paths leading to the success
    void printPath(std::vector<size_t> & res){
      std::vector<size_t>::iterator it = res.begin();
      while(it!=res.end()-1){
        std::cout<<*it;
        ++it;
        std::cout<<"("<<*it<<"),";
        ++it;
      }
      std::cout<<*it<<"(win)"<<std::endl;
    }
};