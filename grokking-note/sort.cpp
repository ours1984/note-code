#include <benchmark/benchmark.h>
#include <vector>
#include <numeric>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <experimental/random>

#define FIXTURE_BECHMARK_NAME Sort

class FIXTURE_BECHMARK_NAME : public ::benchmark::Fixture {
 public:
    void SetUp(const ::benchmark::State& state) BENCHMARK_OVERRIDE {
    if (state.thread_index() == 0) {
        generateData(state.range(0));
    }
    }

    void TearDown(const ::benchmark::State& state) BENCHMARK_OVERRIDE {
    if (state.thread_index() == 0) {
        data.clear();
    }
    }

    void bubbleSort()
    {
        for (size_t i = 0; i < ret.size()-1; ++i) {
            for (size_t j = 1; j < ret.size()-i; j++)
            {
                if (ret[j-1]>ret[j])
                {
                    std::swap(ret[j-1],ret[j]);
                }
            }
        }
    }

    void selectSort()
    {
        size_t pos ;
        long tmpmin;

        for (size_t i = 0; i < ret.size()-1; ++i) {
            pos = i;
            tmpmin=ret[i];
            for (size_t j = i+1; j < ret.size(); j++)
            {
                if (ret[j]<tmpmin)
                {
                    tmpmin = ret[j];
                    pos=j;
                }
            }
            if (i!=pos)
            {
                std::swap(ret[pos],ret[i]);
            }
        }
    }

    void insertSort()
    {
        size_t pos ;
        long tmpmin;

        for (int i = 0; i < ret.size()-1; ++i) {
            for (int j = i+1; j > 0; j--)
            {
                if (ret[j]<ret[j-1])
                {
                    std::swap(ret[j],ret[j-1]);
                }
                else{
                    break;
                }
            }
        }
    }

    void countSort()
    {
        //std::fill(tmp.begin(),tmp.end(),0);
        auto sz=ret.size();
        for (size_t i = 0; i < sz; ++i) {
            tmp[ret[i]]++;
        }

        int pos=0;
        for (int i = 0; i < sz; i++)
        {
            while (tmp[i]--)
            {
                ret[pos++]=i;
            }
        }
    }

    void quickSort()
    {
        iterSort(ret,0,ret.size()-1);
    }

protected:

    void printResult()
    {
       for (auto value:data)
       {
           std::cout<<value<<" ";
       }
       std::cout<<std::endl;

       long last=0;
       for (auto value:ret)
       {
           if (last>value)
           {
               std::cout<<last<<">";
           }
           std::cout<<value<<" ";
           last = value;
       }
       std::cout<<std::endl;
    }

    void generateData(int count)
    {
        data.resize(count);
        std::srand(std::time(nullptr)); // use current time as seed for random generator
        for (auto &value: data)
        {
            value = std::experimental::randint(0, count-1);
        }
    }

    void copyData()
    {
        ret = data;
        tmp.resize(ret.size());
        std::fill(tmp.begin(),tmp.end(),0);
    }

    int partition(std::vector<int>& ret,int low,int high)const
    {
        auto pivot = ret[low];
        while (low < high)
        {
            while (low < high && ret[high] > pivot)
            {
                high--;
            }
            ret[low] = ret[high];

            while (low < high && ret[low] <= pivot)
            {
                low++;
            }
            ret[high] = ret[low];
        }
        ret[low] = pivot;
        return low;
    }

    void iterSort(std::vector<int>& ret,int low,int high)const
    {
        if (low < high) {
            auto pivot = partition(ret,low, high);
            iterSort(ret,low, pivot - 1);
            iterSort(ret,pivot + 1, high);
        }
        return;
    }

    decltype(&FIXTURE_BECHMARK_NAME::bubbleSort) method[5]={
        &FIXTURE_BECHMARK_NAME::bubbleSort
        ,&FIXTURE_BECHMARK_NAME::selectSort
        ,&FIXTURE_BECHMARK_NAME::insertSort
        ,&FIXTURE_BECHMARK_NAME::countSort
        ,&FIXTURE_BECHMARK_NAME::quickSort
        };
    std::vector<int> data;
    std::vector<int> ret;
    std::vector<int> tmp;
};

BENCHMARK_DEFINE_F(FIXTURE_BECHMARK_NAME, benchSort)(benchmark::State& state) 
{
    auto m = method[state.range(1)];
    for ([[maybe_unused]] auto _ : state) {
        state.PauseTiming();
        copyData();
        state.ResumeTiming();
        (this->*m)();
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK_DEFINE_F(FIXTURE_BECHMARK_NAME, benchPrint)(benchmark::State& state)
{
    auto m = method[state.range(1)];
    for ([[maybe_unused]] auto _ : state) {
        copyData();
        (this->*m)();
    }
    printResult();
}

//BENCHMARK_REGISTER_F(FIXTURE_BECHMARK_NAME, benchSort)->RangeMultiplier(5)->Ranges({{10,10000},{0,0}})->Complexity(benchmark::oAuto);
//BENCHMARK_REGISTER_F(FIXTURE_BECHMARK_NAME, benchSort)->RangeMultiplier(5)->Ranges({{10,10000},{1,1}})->Complexity(benchmark::oAuto);
//BENCHMARK_REGISTER_F(FIXTURE_BECHMARK_NAME, benchSort)->RangeMultiplier(5)->Ranges({{10,10000},{2,2}})->Complexity(benchmark::oAuto);
//BENCHMARK_REGISTER_F(FIXTURE_BECHMARK_NAME, benchSort)->RangeMultiplier(2)->Ranges({{1000,10000},{3,3}})->Complexity(benchmark::oN);
//BENCHMARK_REGISTER_F(FIXTURE_BECHMARK_NAME, benchSort)->RangeMultiplier(5)->Ranges({{10,10000},{4,4}})->Complexity(benchmark::oAuto);

//BENCHMARK_REGISTER_F(FIXTURE_BECHMARK_NAME, benchPrint)->Args({10,0})->Iterations(1);
//BENCHMARK_REGISTER_F(FIXTURE_BECHMARK_NAME, benchPrint)->Args({10,1})->Iterations(1);
//BENCHMARK_REGISTER_F(FIXTURE_BECHMARK_NAME, benchPrint)->Args({10,2})->Iterations(1);
//BENCHMARK_REGISTER_F(FIXTURE_BECHMARK_NAME, benchPrint)->Args({10,3})->Iterations(1);
//BENCHMARK_REGISTER_F(FIXTURE_BECHMARK_NAME, benchPrint)->Args({10,4})->Iterations(1);
