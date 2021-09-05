#pragma once
#include "linklist.h"

template<As_parameter Ty>
int getDecimalValue(List_node<Ty>* head)
{
  static unsigned int d = 1;
  if(!head->next)
      return d * head->val;
  auto ret = getDecimalValue(head->next);
  d <<= 1;
  ret += d * head->val;
  return ret;
}
