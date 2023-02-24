#include <assert.h>
#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester
{
public:
  // testing for default constructor is done for you
  void testDefCtor()
  {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront()
  {
    IntList il;
    il.addFront(5);
    assert(il.head->data == 5);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail == il.head);
    il.addFront(3);
    assert(il.head->next->data == 5);
    assert(il.head->next->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail == il.head->next);
    assert(il.head->next->prev == il.head);
    assert(il.getSize() == 2);
  }
  void testAddBack()
  {
    IntList il;
    il.addBack(4);
    assert(il.head->data == 4);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail == il.head);
    il.addBack(5);
    assert(il.head->next->data == 5);
    assert(il.head->next->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail == il.head->next);
    assert(il.head->next->prev == il.head);
    assert(il.getSize() == 2);
  }
  void testCopyConstructor()
  {
    IntList il;
    il.addFront(77);
    il.addFront(3);
    assert(il.head->next->data == 77);
    assert(il.head->next->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail == il.head->next);
    assert(il.head->next->prev == il.head);
    assert(il.getSize() == 2);
    try
    {
      /* code */
      IntList il2(il);
      assert(il2.head->data == 3);
      assert(il2.head->prev == NULL);
      assert(il2.head->next->data == 77);
      assert(il2.head->next->next == NULL);
      assert(il2.head->prev == NULL);
      assert(il2.tail == il2.head->next);
      assert(il2.head->next->prev == il2.head);
      assert(il2.getSize() == 2);
      il2 = il;
      assert(il2.head != il.head);
      il.addFront(4);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }
  void testRemoval()
  {
    IntList il;
    il.addFront(5);
    il.remove(5);
    assert(il.remove(3) == false);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
    il.addFront(3);
    il.addBack(4);
    assert(il.getSize() == 2);
    assert(il.head->next->data == 4);
    assert(il.head->next->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail == il.head->next);
    assert(il.head->next->prev == il.head);
    assert(il.getSize() == 2);
    il.remove(3);
    assert(il.remove(3) == false);
    assert(il.head->data == 4);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail == il.head);
    assert(il.getSize() == 1);
    il.addFront(5);
    IntList il2 = il;
    il2.addBack(0);
    assert(il2.remove(0) == true);
    il2.remove(5);
    assert(il2.head != il.head);
    assert(il2.tail->prev == NULL);
    assert(il2.getSize() == 1);
    assert(il2.head->next == NULL);
    assert(il2.head->data == 4);
    il2.addBack(1);
    il2.addFront(10);
    assert(il2.remove(4) == true);
    assert(il2.tail->prev->prev == NULL);
  }
};

int main(void)
{
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopyConstructor();
  t.testRemoval();
  return EXIT_SUCCESS;
}