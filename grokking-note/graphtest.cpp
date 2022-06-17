#include <benchmark/benchmark.h>
#include <vector>
#include <numeric>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <set>
#include <experimental/random>
#include "graph.h"

using namespace std;
#define FIXTURE_BECHMARK_NAME GraphTest

class FIXTURE_BECHMARK_NAME : public ::benchmark::Fixture {
 public:
    void SetUp(const ::benchmark::State& state) BENCHMARK_OVERRIDE {
    if (state.thread_index() == 0) {

    }
    }

    void TearDown(const ::benchmark::State& state) BENCHMARK_OVERRIDE {
    if (state.thread_index() == 0) {

    }
    }

    bool printResult(int indexn,bool in)
    {
        if(!in)return true;

        auto data = m_graph.getVertex(indexn);
        std::cout<<data->name<<" ";
        return true;
    }

protected:

    void generate()
    {
        static std::vector<std::string> s_names={"you","BoB","claire","alice","anuj","peggy","jonny","thom"};
        for (size_t i = 0; i < s_names.size(); i++)
        {
            m_graph.addVertex(i,{s_names[i]});
        }

        m_graph.addEdge(0,1,{0});
        m_graph.addEdge(0,3,{0});
        m_graph.addEdge(0,2,{0});
        m_graph.addEdge(1,4,{0});
        m_graph.addEdge(1,5,{0});
        m_graph.addEdge(3,5,{0});
        m_graph.addEdge(2,6,{0});
        m_graph.addEdge(2,7,{0});
        
    }

    graph m_graph;
};


BENCHMARK_DEFINE_F(FIXTURE_BECHMARK_NAME, benchPrint)(benchmark::State& state)
{
    generate();

    std::cout<<std::endl<<"dfs"<<std::endl;
    m_graph.DFSTraverse(0,std::bind(&FIXTURE_BECHMARK_NAME::printResult,this,std::placeholders::_1, std::placeholders::_2));

    std::cout<<std::endl<<"bfs"<<std::endl;
    m_graph.BFSTraverse(0,std::bind(&FIXTURE_BECHMARK_NAME::printResult,this,std::placeholders::_1, std::placeholders::_2));

    std::cout<<std::endl<<"search m"<<std::endl;
    int mindex = INDEX_NONE;
    auto searchM =[&mindex,this](int index,bool in)->bool
    {
        if(!in)return true;
        auto name = this->m_graph.getVertex(index)->name;
        if (name.back() == 'm')
        {
            mindex = index;
            return false;
        }
        return true;
    };
    m_graph.BFSTraverse(0,searchM);

    list<string> path;
    auto prinM =[&path,this,mindex](int index,bool in)->bool
    {
        if(in)
        {
            path.push_back(this->m_graph.getVertex(index)->name);
            if (mindex == index)
            {
                return false;
            }
        }
        else
        {
            path.pop_back();
        }
        return true;
    };
    m_graph.DFSTraverse(0,prinM);
    for (auto name:path)
    {
        std::cout<<name<<" ";
    }
}

BENCHMARK_REGISTER_F(FIXTURE_BECHMARK_NAME, benchPrint)->Iterations(1);



