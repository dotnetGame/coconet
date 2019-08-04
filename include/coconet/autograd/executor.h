#ifndef COCONET_AUTOGRAD_EXECUTOR_H_
#define COCONET_AUTOGRAD_EXECUTOR_H_

#include <memory>
#include <vector>

#include <coconet/autograd/variable.h>
#include <coconet/autograd/function.h>

namespace coconet
{
    namespace autograd
    {
        class Edge
        {
        public:
            std::vector<std::weak_ptr<IVariable>> input_list;
            std::weak_ptr<FunctionBase> fn;
        };

        class Node
        {
        public:
            std::weak_ptr<IVariable> variable;
        };

        class VariableGraph
        {
        public:
            std::vector<Edge> edge_list;
            std::vector<Node> node_list;
        };

        class Executor
        {

        };
    }
}


#endif //! COCONET_AUTOGRAD_EXECUTOR_H_