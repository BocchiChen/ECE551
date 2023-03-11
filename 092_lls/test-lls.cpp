#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"

class Tester {
 public:
  // example of another method you might want to write
  void testAllCases() {
    LinkedList<int> il = LinkedList<int>();
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
    
    //12
    il.addFront(12);
    assert(il.head->data == 12);
    assert(il.tail->data == 12);
    assert(il[0] == 12);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);
    
    //5 12
    il.addFront(5);
    assert(il.getSize() == 2);
    assert(il.head->data == 5);
    assert(il.tail->data == 12);
    assert(il[1] == 12);
    assert(il[0] == 5);
    assert(il.head->next->data == 12);
    assert(il.head->prev == NULL);
    assert(il.tail->prev->data == 5);
    assert(il.tail->next == NULL);
    assert(il.head->next->next==NULL);
    assert(il.tail->prev->prev == NULL);
    
    //5 12 4
    il.addBack(4);
    assert(il.getSize() == 3);
    assert(il.head->data == 5);
    assert(il.tail->data == 4);
    assert(il[0] == 5);
    assert(il[1] == 12);
    assert(il[2] == 4);
    assert(il.head->next->data == 12);
    assert(il.head->prev == NULL);
    assert(il.tail->prev->data == 12);
    assert(il.tail->next == NULL);
    assert(il.head->next->next->data==4);
    assert(il.tail->prev->prev->data == 5);
    assert(il.head->next->next->next==NULL);
    assert(il.tail->prev->prev->prev == NULL);
    assert(il.head->next->prev->data==5);
    assert(il.tail->prev->next->data == 4);
    assert(il.head->next->next->prev->prev->data==5);
    assert(il.tail->prev->prev->next->next->data == 4);
    
    il.addFront(9);
    il.addBack(5);
    //9 5 12 4 5
    assert(il.find(5)==1);
    assert(il.remove(10)==false);
    //remove
    il.remove(5);
    //9 12 4 5
    assert(il.getSize() == 4);
    assert(il.head->data == 9);
    assert(il.tail->data == 5);
    assert(il[0] == 9);
    assert(il[1] == 12);
    assert(il[2] == 4);
    assert(il[3] == 5);
    assert(il.head->next->data == 12);
    assert(il.head->prev == NULL);
    assert(il.tail->prev->data == 4);
    assert(il.tail->next == NULL);
    assert(il.head->next->next->data==4);
    assert(il.tail->prev->prev->data == 12);
    assert(il.head->next->next->next->data==5);
    assert(il.tail->prev->prev->prev->data == 9);
    assert(il.head->next->next->next==il.tail);
    assert(il.tail->prev->prev->prev== il.head);
    assert(il.head->next->next->next->next==NULL);
    assert(il.tail->prev->prev->prev->prev == NULL);
    assert(il.head->next->prev->data==9);
    assert(il.tail->prev->next->data == 5);
    assert(il.head->next->prev==il.head);
    assert(il.tail->prev->next== il.tail);
    assert(il.head->next->next->prev->data==12);
    assert(il.tail->prev->prev->next->data == 4);
    assert(il.head->next->next->prev->prev==il.head);
    assert(il.tail->prev->prev->next->next==il.tail);
    assert(il.head->next->next->next->prev->prev->prev->data==9);
    assert(il.tail->prev->prev->prev->next->next->next->data==5);
    assert(il.head->next->next->next->prev->prev->prev==il.head);
    assert(il.tail->prev->prev->prev->next->next->next==il.tail);
    assert(il.head->next->next->prev->prev->data==9);
    assert(il.tail->prev->prev->next->next->data == 5);
    assert(il.head->next->next->prev->prev==il.head);
    assert(il.tail->prev->prev->next->next== il.tail);
    
    assert(il.find(9)==0);
    assert(il.find(5)==3);
    
    il.remove(5);
    assert(il.remove(5)==false);
    //9 12 4
    assert(il.getSize() == 3);
    assert(il.head->data == 9);
    assert(il.tail->data == 4);
    assert(il[0] == 9);
    assert(il[1] == 12);
    assert(il[2] == 4);
    assert(il.head->next->data == 12);
    assert(il.head->prev == NULL);
    assert(il.tail->prev->data == 12);
    assert(il.tail->next == NULL);
    assert(il.head->next->next->data==4);
    assert(il.tail->prev->prev->data == 9);
    assert(il.head->next->next==il.tail);
    assert(il.tail->prev->prev== il.head);
    assert(il.head->next->next->next==NULL);
    assert(il.tail->prev->prev->prev == NULL);
    assert(il.head->next->prev->data==9);
    assert(il.tail->prev->next->data == 4);
    assert(il.head->next->prev==il.head);
    assert(il.tail->prev->next== il.tail);
    assert(il.head->next->next->prev->data==12);
    assert(il.tail->prev->prev->next->data == 12);
    assert(il.head->next->next->prev->prev->data==9);
    assert(il.tail->prev->prev->next->next->data == 4);
    assert(il.head->next->next->prev->prev==il.head);
    assert(il.tail->prev->prev->next->next== il.tail);
    assert(il.find(9)==0);
    assert(il.find(12)==1);
    assert(il.find(4)==2);
    
    il.remove(9);
    //12 4
    assert(il.getSize() == 2);
    assert(il.head->data == 12);
    assert(il.tail->data == 4);
    assert(il[0] == 12);
    assert(il[1] == 4);
    assert(il.head->next->data == 4);
    assert(il.head->prev == NULL);
    assert(il.tail->prev->data == 12);
    assert(il.tail->next == NULL);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.head->next->next==NULL);
    assert(il.tail->prev->prev == NULL);
    assert(il.head->next->prev->data==12);
    assert(il.tail->prev->next->data == 4);
    assert(il.head->next->prev==il.head);
    assert(il.tail->prev->next == il.tail);
    assert(il.find(12)==0);
    assert(il.find(4)==1);
    
    il.remove(12);
    il.remove(4);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
    
    il.addFront(4);
    il.addFront(12);
    il.addFront(9);
    
    il.remove(12);
    //9 4
    assert(il.getSize() == 2);
    assert(il.head->data == 9);
    assert(il.tail->data == 4);
    assert(il[0] == 9);
    assert(il[1] == 4);
    assert(il.head->next->data == 4);
    assert(il.head->prev == NULL);
    assert(il.tail->prev->data == 9);
    assert(il.tail->next == NULL);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.head->next->next==NULL);
    assert(il.tail->prev->prev == NULL);
    assert(il.head->next->prev->data==9);
    assert(il.tail->prev->next->data == 4);
    assert(il.head->next->prev==il.head);
    assert(il.tail->prev->next == il.tail);
    assert(il.find(9)==0);
    assert(il.find(4)==1);
    
    il.remove(9);
    il.addFront(12);
    il.addFront(9);
    
    //assign
    //9 12 4
    LinkedList<int> il2 = LinkedList<int>();
    il2.addFront(6);
    il2.addBack(0);
    //6 0
    il2 = il;
    assert(il2.getSize() == 3);
    assert(il2.head->data == 9);
    assert(il2.tail->data == 4);
    assert(il2[0] == 9);
    assert(il2[1] == 12);
    assert(il2[2] == 4);
    assert(il2.head->next->data == 12);
    assert(il2.head->prev == NULL);
    assert(il2.tail->prev->data == 12);
    assert(il2.tail->next == NULL);
    assert(il2.head->next->next == il2.tail);
    assert(il2.tail->prev->prev == il2.head);
    assert(il2.head->next->next->next==NULL);
    assert(il2.tail->prev->prev->prev == NULL);
    assert(il2.head->next->prev->data==9);
    assert(il2.tail->prev->next->data == 4);
    assert(il2.head->next->prev == il2.head);
    assert(il2.tail->prev->next == il2.tail);
    assert(il2.head->next->next->prev->data==12);
    assert(il2.tail->prev->prev->next->data == 12);
    assert(il2.head->next->next->prev->prev->data==9);
    assert(il2.tail->prev->prev->next->next->data == 4);
    assert(il2.head->next->next->prev->prev == il2.head);
    assert(il2.tail->prev->prev->next->next == il2.tail);
    assert(il2.find(12)==1);
    assert(il2.find(4)==2);
    assert(il2.find(9)==0);
    
    //12 4 7
    il2.remove(9);
    il2.addBack(7);
    assert(il.getSize() == 3);
    assert(il[0] == 9);
    assert(il[1] == 12);
    assert(il[2] == 4);
    assert(il2.getSize() == 3);
    assert(il2[0] == 12);
    assert(il2[1] == 4);
    assert(il2[2] == 7);
    assert(il2.remove(9) == false);
    assert(il2.remove(10) == false);
    
    //copy
    //9 12 4
    LinkedList<int> il3(il);
    assert(il3.getSize() == 3);
    assert(il3.head->data == 9);
    assert(il3.tail->data == 4);
    assert(il3[0] == 9);
    assert(il3[1] == 12);
    assert(il3[2] == 4);
    assert(il3.head->next->data == 12);
    assert(il3.head->prev == NULL);
    assert(il3.tail->prev->data == 12);
    assert(il3.tail->next == NULL);
    assert(il3.head->next->next->data==4);
    assert(il3.tail->prev->prev->data == 9);
    assert(il3.head->next->next->next==NULL);
    assert(il3.tail->prev->prev->prev == NULL);
    assert(il3.head->next->prev->data==9);
    assert(il3.tail->prev->next->data == 4);
    assert(il3.head->next->next->prev->data==12);
    assert(il3.tail->prev->prev->next->data == 12);
    assert(il3.head->next->next->prev->prev->data==9);
    assert(il3.tail->prev->prev->next->next->data == 4);
    assert(il3.find(12)==1);
    assert(il3.find(4)==2);
    assert(il3.find(9)==0);
    
    //21 9 4 7
    il3.remove(12);
    il3.addFront(21);
    il3.addBack(7);
    assert(il.getSize() == 3);
    assert(il[0] == 9);
    assert(il[1] == 12);
    assert(il[2] == 4);
    assert(il3.getSize() == 4);
    assert(il3[0] == 21);
    assert(il3[1] == 9);
    assert(il3[2] == 4);
    assert(il3[3] == 7);
    assert(il3.head->next->next->next == il3.tail);
    assert(il3.tail->prev->prev->prev == il3.head);
    assert(il3.tail->prev->next == il3.tail);
    
    //9 12 4
    il.remove(9);
    assert(il2.getSize() == 3);
    assert(il2[0] == 12);
    assert(il2[1] == 4);
    assert(il2[2] == 7);
    assert(il3.getSize() == 4);
    assert(il3[0] == 21);
    assert(il3[1] == 9);
    assert(il3[2] == 4);
    assert(il3[3] == 7);
    assert(il3.head->next->next->next == il3.tail);
    assert(il3.tail->prev->prev->prev == il3.head);
    assert(il3.tail->prev->next == il3.tail);
  }
};

int main(void) {
  Tester t;
  t.testAllCases();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
