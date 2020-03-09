#include "taskgraph/TaskGraph.h"

namespace taskgraph
{

CU_SINGLETON_DEFINITION(TaskGraph);

extern void regist_rttr();

TaskGraph::TaskGraph()
{
	regist_rttr();
}

}