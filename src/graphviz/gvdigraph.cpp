/*
 * gvdigraph.cpp
 */

#ifndef CDG_GVDIGRAPH_C
#define CDG_GVDIGRAPH_C

#include "./gvdigraph.h"
#include "./gvproxy.h"
#include "../edge.h"
#include "../node.h"


namespace cdg {


////// Graphviz DiGraph


GvDiGraph::GvDiGraph(std::string name): mName(name) {
}


GvDiGraph::~GvDiGraph() {
  for (auto node : mNodes) {
    delete node;
  }
  mNodes.clear();
  for (auto edge : mEdges) {
    delete edge;
  }
  mEdges.clear();
}


GvNode* GvDiGraph::add(Node* node) {
  if (node) {
    if (get(node)) {
      return get(node);
    }
    else {
      GvNode* gvNode = new GvNode(node);
      mNodes.insert(gvNode);
      mNodeProxyLookupMap[node] = gvNode;
      return gvNode;
    }
  }
  return nullptr;
}


GvEdge* GvDiGraph::add(EdgeBase* edge) {
  if (edge) {
    if (get(edge)) {
      return get(edge);
    }
    else {
      GvEdge* gvEdge = new GvEdge(edge);
      mEdges.insert(gvEdge);
      mEdgeProxyLookupMap[edge] = gvEdge;
      return gvEdge;
    }
  }
  return nullptr;
}


GvNode* GvDiGraph::get(Node* node) {
  return mNodeProxyLookupMap[node];
}


GvEdge* GvDiGraph::get(EdgeBase* edge) {
  return mEdgeProxyLookupMap[edge];
}


GvNodeSet GvDiGraph::getNodes() {
  return mNodes;
}


GvEdgeSet GvDiGraph::getEdges() {
  return mEdges;
}


GvSubGraph& GvDiGraph::addSubgraph(std::string subgraphName) {
  return getSubgraph(subgraphName);
}


GvSubGraph& GvDiGraph::addSubgraph(std::string subgraphName, NodeSet subgraph) {
  mSubgraphs[subgraphName] = GvSubGraph(this, subgraphName, subgraph);
  return getSubgraph(subgraphName);
}


GvSubGraph& GvDiGraph::getSubgraph(std::string subgraphName) {
  if (mSubgraphs.find(subgraphName) == mSubgraphs.end()) {
    mSubgraphs[subgraphName] = GvSubGraph(this, subgraphName);
  }
  return mSubgraphs[subgraphName];
}


void GvDiGraph::addAttributes(std::map<std::string, std::string> attributes) {
  for (auto p : attributes) {
    setAttribute(p.first, p.second);
  }
}


void GvDiGraph::setAttribute(std::string name, std::string value) {
  mAttributes[name] = value;
}


std::string GvDiGraph::getAttribute(std::string key) {
  return mAttributes[key];
}


void GvDiGraph::filter(GvFilter* filter) {
  for (auto gvNode : getNodes()) {
    filter->filter(gvNode);
  }
  for (auto gvEdge : getEdges()) {
    filter->filter(gvEdge);
  }
}


std::string GvDiGraph::to_string() {
  std::stringstream graphStream;
  graphStream << "digraph \"" << graphviz_sanitize(mName) << "\" {" << std::endl;
  for (auto p : mAttributes) {
    graphStream << "  " << graphviz_sanitize(p.first)
                << " = \"" << graphviz_sanitize(p.second) << "\""
                << std::endl;
  }
  for (auto node : mNodes) {
    graphStream << "  " << node->to_string() << std::endl;
  }
  for (auto edge : mEdges) {
    std::string edge_string = edge->to_string();
    if (edge_string != "") {
      graphStream << "  " << edge_string << std::endl;
    }
  }
  for (auto p : mSubgraphs) {
    graphStream << p.second.to_string();
  }
  graphStream << "}" << std::endl;
  return graphStream.str();
}


} // namespace cdg


std::ostream& operator<<(std::ostream& os, cdg::GvDiGraph& gvdg) {
  os << gvdg.to_string();
  return os;
}


std::ostream& operator<<(std::ostream& os, cdg::GvDiGraph gvdg) {
  os << gvdg.to_string();
  return os;
}


#endif
