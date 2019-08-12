#include <coconet/autograd/executor.h>

namespace coconet
{
	namespace autograd
	{
		std::vector<Node> Executor::topology_sort(const VariableGraph & graph)
		{
			return std::vector<Node>();
		}

		VariableGraph Executor::collect_backward_subgraph(const VariableGraph & graph, const Node & root)
		{
			return VariableGraph();
		}
	}
}

