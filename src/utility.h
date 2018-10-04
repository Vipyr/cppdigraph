/*
 * utility.h
 */

#ifndef CDG_UTILITY_H
#define CDG_UTILITY_H


namespace cdg {


class Node;
class EdgeBase;


template<typename T>
struct NameCompare {
  bool operator()(T* lhs, T* rhs) {
    if (lhs and rhs) {
      return lhs->getCdgId() < rhs->getCdgId();
    }
    else if (rhs) {
      return true;
    }
    return false;
  }
};


typedef std::set<Node*, NameCompare<Node>> NodeSet;
typedef std::set<EdgeBase*, NameCompare<EdgeBase>> EdgeSet;


} // namespace cdg


#endif