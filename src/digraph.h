/*
 * digraph.h
 * 
 * Types:
 *   Node
 */

#ifndef CDG_DIGRAPH_H
#define CDG_DIGRAPH_H

#include <iostream>
#include <list>
#include <set>
#include <string>

namespace cdg {


class Node;
class EdgeBase;


class DiGraph {
public:
  DiGraph(std::string name);
  virtual ~DiGraph();

  void clear();
  void add(Node* node) { mNodes.insert(node); }
  void remove(Node* node) { mNodes.erase(node); }
  void add(EdgeBase* edge) { mEdges.insert(edge); }
  void remove(EdgeBase* edge) { mEdges.erase(edge); }

  std::string to_graphviz();
  std::string to_graphviz(std::string graphname);

  const std::string getName() const;

  std::ostream& operator<<(std::ostream& os);

private:
  const std::string mName;
  std::set<Node*> mNodes;
  std::set<EdgeBase*> mEdges;

};


} // namespace cdg

#endif
