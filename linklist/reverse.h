#pragma once
#include "linklist.h"

template<As_parameter Ty>
static List_node<Ty>* rev(List_node<Ty>* &head, List_node<Ty>* ln)
    {
        if (!ln->next) 
        {
            head = ln;
            return ln;
        }
        rev(head, ln->next)->next = ln;
        return ln;
    }

template<As_parameter Ty>
List_node<Ty>* reverse(List_node<Ty>* ln)
{
    if (!ln || !ln->next)
        return ln;
    auto head = ln;
    rev(head, ln);
    ln->next = nullptr;
    return head;
}
