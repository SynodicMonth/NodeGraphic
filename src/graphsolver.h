#ifndef GRAPHSOLVER_H
#define GRAPHSOLVER_H

#include "noutput.h"

class GraphSolver
{
private:
    NOutput *_outputNode;
    //let hutao burry me if i cannot implement this.
public:
    GraphSolver(NOutput *node);
    void solve();
    void solveNode(NodeItem *node);
};

#endif // GRAPHSOLVER_H
