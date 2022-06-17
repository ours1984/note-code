#pragma once
#include <string>
#include <functional>

#define INDEX_NONE -1

struct VertexData
{
    std::string name;
};

struct EdgeData
{
    float weight;
};

class graph
{
public:
    graph();
    ~graph();

    bool addVertex(int index,const VertexData& vert);
    bool delVertex(int index);
    VertexData* getVertex(int index)const;

    bool addEdge(int start,int end,const EdgeData& edge);
    bool delEdge(int start,int end);
    EdgeData* getEdge(int start,int end)const;

    int firstAdjvex(int vertex,bool out);
    int nextAdjvex(int start,int end,bool out);

    using TravelFn=std::function<bool(int,bool)>;
    void DFSTraverse(int vertex,TravelFn)const;
    void BFSTraverse(int vertex,TravelFn)const;

private:
    struct PrivateData;
    PrivateData *m_private = nullptr;
};
