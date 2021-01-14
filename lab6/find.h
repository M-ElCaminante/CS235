#ifndef FIND_H_
#define FIND_H_

#include <list>

namespace KW {
/*   template<typename Item_Type> */
/*     typename std::list<Item_Type>::iterator find(std::list<Item_Type>& a_list, */
/*                                                  const Item_Type& target) */
/*     { */
/*       typedef typename std::list<Item_Type>::iterator iterator; */
/*       for (iterator itr = a_list.begin(); */
/*            itr != a_list.end(); ++itr) { */
/*         if (*itr == target) */
/*           return itr; */
/*       } */
/*       return a_list.end(); */
/*     } */

template <typename Container>
  typename Container::iterator find(Container cont, 
                                    typename Container::const_reference target)
  {
    typename Container::iterator iter = cont.begin();
    while (iter != cont.end()) {
      if (*iter == target)
        return iter;
      ++iter;
    }
    return iter;
  }
  
  template <typename iterator, typename Target>
    iterator find(iterator first, iterator last, const Target& target)
    {
      while (first != last) {
        if (*first == target)
          return first;
        ++first;
      }
      return first;
    }


  template <typename iterator, typename Pred>
    iterator find_if(iterator first, iterator last, Pred pred)
    {
      while (first != last) {
        if (pred(*first))
          return first;
        else
          ++first;
      }
      return first;
    }




} // end namespace KW

#endif
