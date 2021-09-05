#pragma once
#include "linklist.h"

template<As_parameter Ty>
void common_node(List_node<Ty>* p1, List_node<Ty>* p2, List_node<Ty>* tail3, size_t len1, size_t len2, List_node<Ty>* &ret)
{
    // find common node

  auto t1 = len1 < len2 ? p1 : p2;
  auto t2 = len1 < len2 ? p2 : p1;

  while (t1 != t2)
  {
    if (!t1->next) t1->next = p2;
    t1 = t1->next;
    if (t2->next == p2) t2->next = p1;
    t2 = t2->next;
  }
  tail3->next = nullptr; // back to origin

  ret = t1;
}