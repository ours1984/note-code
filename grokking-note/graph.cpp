#include "graph.h"
#include <vector>
#include <queue>

struct EdgeNode
{
    EdgeNode(int iid,int oid,const EdgeData&da):inId(iid),outId(oid),data(da){}

    int inId;
    int outId;

    EdgeNode *in=nullptr;
    EdgeNode *out=nullptr;
    EdgeData data;
};

struct VertexNode
{
    VertexData data;
    bool init = false;
    EdgeNode *firstIn = nullptr;
    EdgeNode *firstOut = nullptr;
};

struct graph::PrivateData
{
    int numEdges=0;
    std::vector<bool> flags;
    std::queue<int> queflag;
    std::vector<VertexNode> nodes;

    bool dfs(int vertex,TravelFn fn)
    {
        if (flags[vertex])
            return true;
        flags[vertex]=true;

        bool ret = fn(vertex,true);
        if (ret)
        {
            auto edge = nodes[vertex].firstOut;
            while (edge)
            {
                if(!dfs(edge->outId,fn))
                    return false;
                edge = edge->out;
            }
            ret = fn(vertex,false);
        }

        return ret;
    }

    void bfs(TravelFn fn)
    {
        int index=-1;
        while (!queflag.empty())
        {
            index = queflag.front();
            queflag.pop();

            if (flags[index])continue;
            flags[index]=true;

            if(!fn(index,true))
                break;

            auto edge =nodes[index].firstOut;
            while (edge)
            {
                queflag.push(edge->outId);
                edge = edge->out;
            }

            if(!fn(index,false))
                break;
        }
    }

    EdgeNode* getEdge(int start,int end)
    {
        auto edge = nodes[start].firstIn;
        while (edge)
        {
            if (edge->inId == end)
            {
                return edge;
            }
            edge = edge -> in;
        }
        return nullptr;
    }

    bool addIn(int orig,int target,EdgeNode* edge)
    {
        if (!nodes[orig].firstIn)
        {
            nodes[orig].firstIn = edge;
            return true;
        }

        auto next = nodes[orig].firstIn;
        while (next)
        {
            if (next->inId == target)
            {
                return false;
            }

            if (!next -> in)
            {
                next -> in = edge;
                return true;
            }
            
            next = next -> in;
        }

        return false;
    }

    EdgeNode* delIn(int orig,int target)
    {  
        if (!nodes[orig].firstIn)
            return nullptr;

        auto prev = nodes[orig].firstIn;
        if (prev->inId==target)
        {
            nodes[orig].firstIn=prev->out;
            return prev;
        }

        auto edge = prev->in;
        while (edge)
        {
            if (edge->inId == target)
            {
                prev->in = edge -> in;
                return edge;
            }

            prev = edge;
            edge = prev -> in;
        }
        return nullptr;
    }
    
    bool addOut(int orig,int target,EdgeNode* edge)
    {
        if (!nodes[orig].firstOut)
        {
            nodes[orig].firstOut = edge;
            return true;
        }

        auto next = nodes[orig].firstOut;
        while (next)
        {
            if (next->outId == target)
            {
                return false;
            }

            if (!next -> out)
            {
                next -> out = edge;
                return true;
            }
            
            next = next -> out;
        }

        return false;
    }

    EdgeNode* delOut(int orig,int target)
    {
        if (!nodes[orig].firstOut)
            return nullptr;

        auto prev = nodes[orig].firstOut;
        if (prev->outId==target)
        {
            nodes[orig].firstOut=prev->out;
            return prev;
        }
        
        auto edge = prev->out;
        while (edge)
        {
            if (edge->outId == target)
            {
                prev->out = edge -> out;
                return edge;
            }

            prev = edge;
            edge = prev -> out;
        }
        return nullptr;
    }
};

graph::graph()
{
    m_private = new PrivateData;
}

graph::~graph()
{
    delete m_private;
}

bool graph::addVertex(int index,const VertexData& vert)
{
    if (m_private->nodes.size()>index 
        && m_private->nodes[index].init
        && index != INDEX_NONE
    )
    {
        return false;
    }
    
    m_private->nodes.resize(index+1);
    m_private->nodes[index].init=true;
    m_private->nodes[index].data=vert;
    return true;
}

bool graph::delVertex(int index)
{
    if (m_private->nodes.size()>index 
        && m_private->nodes[index].init
        && index != INDEX_NONE
    )
    {
        return false;
    }
    
    return false;
}

VertexData* graph::getVertex(int index) const
{
    if (m_private->nodes.size()>index 
        && m_private->nodes[index].init
        && index != INDEX_NONE
    )
    {
        return &m_private->nodes[index].data;
    }
    return nullptr;
}

bool graph::addEdge(int start,int end,const EdgeData& edged)
{
    if (m_private->nodes.size() <= start 
        || m_private->nodes.size() <= end
        || !m_private->nodes[start].init
        || !m_private->nodes[end].init
        || start == INDEX_NONE|| end == INDEX_NONE
    )
    {
        return false;
    }

    auto edge =new EdgeNode(start,end,edged);
    if (!m_private->addIn(end,start,edge))
    {
        delete edge;
        return false;
    }
    else if (!m_private->addOut(start,end,edge))
    {
        delete edge;
        return false;
    }
    
    m_private->numEdges++;
    return true;    
}

bool graph::delEdge(int start,int end)
{
    if (m_private->nodes.size() <= start 
        || m_private->nodes.size() <= end
        || !m_private->nodes[start].init
        || !m_private->nodes[end].init
        || start == INDEX_NONE|| end == INDEX_NONE
    )
    {
        return false;
    }

    auto edge = m_private->delIn(end,start);
    if (!edge)
    {
        return false;
    }

    edge = m_private->delOut(start,end);
    if (!edge)
    {
        return false;
    }

    delete edge;
    m_private->numEdges--;
    return true;
}

EdgeData* graph::getEdge(int start,int end) const
{
    if (m_private->nodes.size() <= start 
        || m_private->nodes.size() <= end
        || !m_private->nodes[start].init
        || !m_private->nodes[end].init
        || start == INDEX_NONE|| end == INDEX_NONE
    )
    {
        return nullptr;
    }    

    auto edge = m_private->getEdge(start,end);
    return edge?&edge->data:nullptr;
}

int graph::firstAdjvex(int vertex,bool out)
{
    if (m_private->nodes.size() <= vertex 
        || !m_private->nodes[vertex].init
        || vertex == INDEX_NONE
    )
    {
        return INDEX_NONE;
    }  

    if (out)
    {
        auto edge = m_private->nodes[vertex].firstOut;
        return edge?edge->outId:INDEX_NONE;
    }
    else
    {
        auto edge = m_private->nodes[vertex].firstIn;
        return edge?edge->inId:INDEX_NONE;
    } 
}

int graph::nextAdjvex(int start,int end,bool inout)
{
    if (m_private->nodes.size() <= start 
        || m_private->nodes.size() <= end
        || !m_private->nodes[start].init
        || !m_private->nodes[end].init
        || start == INDEX_NONE|| end == INDEX_NONE
    )
    {
        return INDEX_NONE;
    }  

    auto edge = m_private->getEdge(start,end);
    if (edge)
    {
        return edge?edge->outId:INDEX_NONE;
    }
    else
    {
        return edge?edge->inId:INDEX_NONE;
    }     
}

void graph::DFSTraverse(int vertex,TravelFn fn) const
{
    if (m_private->nodes.size() <= vertex 
        || !m_private->nodes[vertex].init
        || vertex == INDEX_NONE
    )
    {
        return ;
    }  

    m_private->flags.resize(m_private->nodes.size());
    std::fill(std::begin(m_private->flags),std::end(m_private->flags),false);

    m_private->dfs(vertex,fn);
}

void graph::BFSTraverse(int vertex,TravelFn fn) const
{
    if (m_private->nodes.size() <= vertex 
        || !m_private->nodes[vertex].init
        || vertex == INDEX_NONE
    )
    {
        return ;
    } 

    m_private->flags.resize(m_private->nodes.size());
    std::fill(std::begin(m_private->flags),std::end(m_private->flags),false);

    auto tmp = std::queue<int>();
    std::swap(m_private->queflag,tmp);
    m_private->queflag.push(vertex);

    m_private->bfs(fn);
}
