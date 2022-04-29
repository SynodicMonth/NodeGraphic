#include "graphsolver.h"
#include <QDebug>

GraphSolver::GraphSolver(NOutput *node){
    _outputNode = node;
}

void GraphSolver::solve(){
    solveNode(_outputNode);
}

void GraphSolver::solveNode(NodeItem *node){
    if(node->_nodetype == inputNode){
        node->execute();
        return;
    }
    for(int i = 0; i < node->_in.size(); i++){
        if(!node->_in[i]->_connections.isEmpty())
            solveNode(node->_in[i]->_connections[0]->_in->_parent);
    }
    node->execute();
}
