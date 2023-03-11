#include <string>
#include <iostream>

class Choice{
  private:
    size_t page_num;
    size_t choice_num;
    size_t jump_page_num;
    std::string choice_content;
    bool valid;
    std::pair<std::string,long int> condition;
    
  public:
    //constructor
    Choice(): page_num(0), choice_num(1), jump_page_num(0), choice_content(""), valid(false){}
    Choice(size_t pn, size_t cn, size_t jpn, std::string cc): page_num(pn), choice_num(cn), jump_page_num(jpn), choice_content(cc), valid(false){}
    //destructor
    ~Choice(){}
    //copy constructor
    Choice(const Choice & rhs): page_num(rhs.page_num), choice_num(rhs.choice_num), jump_page_num(rhs.jump_page_num), choice_content(rhs.choice_content), valid(rhs.valid){
      condition = rhs.condition;
    }
    //assignment operator
    Choice & operator=(const Choice & rhs){
      if(this != &rhs){
        page_num = rhs.page_num;
        choice_num = rhs.choice_num;
        jump_page_num = rhs.jump_page_num;
        choice_content = rhs.choice_content;
        valid = rhs.valid;
        condition = rhs.condition;
      }
      return *this;
    }
    //This method checks the user's inventory and condition of the choice and prints the choice
    void printChoice(std::vector<std::pair<std::string,long int> > & inventory){
      //if there is no condition
      if(condition.second == -1){
        valid = true;
        std::cout<<" "<<choice_num<<". "<<choice_content<<std::endl;
        return;
      }
      std::vector<std::pair<std::string,long int> >::iterator it = inventory.begin();
      while(it!=inventory.end()){
        if((*it).first.compare(condition.first)==0){
          if((*it).second==condition.second){
            valid = true;
            std::cout<<" "<<choice_num<<". "<<choice_content<<std::endl;
          }else{
            valid = false;
            std::cout<<" "<<choice_num<<". <UNAVAILABLE>"<<std::endl;
          }
          return;
        }
        ++it;
      }
      //treat any variable which has not been set as having a value of 0.
      if(condition.second == 0){
        valid = true;
        std::cout<<" "<<choice_num<<". "<<choice_content<<std::endl;
      }else{
        valid = false;
        std::cout<<" "<<choice_num<<". <UNAVAILABLE>"<<std::endl;
      }
    }
    //This method adds a precondition to a choice
    void addCondition(std::string name,long int value){
      condition.first = name;
      condition.second = value;
    }
    //The following methods return the value of private variables in Choice class
    size_t getJumpPageNum(){
      return jump_page_num;
    }
    bool getValidationOfChoice(){
      return valid;
    }
};