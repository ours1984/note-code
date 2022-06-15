#include <benchmark/benchmark.h>
#include <vector>
#include <numeric>
#include <ctime>
#include <algorithm>
#include <iostream>

static std::vector<int> GenerateData(int count)
{
    std::vector<int> ret(count);

    std::srand(std::time(nullptr)); // use current time as seed for random generator

    for (auto &value: ret)
    {
        value = std::rand();
    }

    return std::move(ret);
}

static std::vector<int> bubbleSort(const std::vector<int>& data)
{
    std::vector<int> ret = data;
    for (size_t i = 0; i < ret.size()-1; ++i) {
        for (size_t j = 1; j < ret.size()-i; j++)
        {
            if (ret[j-1]>ret[j])
            {
                std::swap(ret[j-1],ret[j]);
            }
        }
    }
    return std::move(ret);
}

static std::vector<int> selectSort(const std::vector<int>& data)
{
    std::vector<int> ret=data;
    size_t pos ;
    long tmpmin;

    for (size_t i = 0; i < ret.size()-1; ++i) {
        pos = i;
        tmpmin=ret[i];
        for (size_t j = i+1; j < ret.size()-1; j++)
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
    return std::move(ret);
}

static std::vector<int> insertSort(const std::vector<int>& data)
{
    std::vector<int> ret=data;
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
    return std::move(ret);
}

static std::vector<int> countSort(const std::vector<int>& data)
{
    std::vector<char> tmp(INT32_MAX);
    std::fill(tmp.begin(), tmp.end(), 0);

    for (size_t i = 0; i < data.size(); ++i) {
        tmp[data[i]]++;
    }

    std::vector<int> ret(data.size());

    int pos=0;
    for (int i = 0; i < INT32_MAX; i++)
    {
        auto num = tmp[i];
        if (num!=0)
        {
            std::fill(ret.begin()+pos,ret.begin()+pos+num,i);
            pos += num;
        }
    }
    
    return std::move(ret);
}

static int partition(std::vector<int>& ret,int low,int high){
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

static void iterSort(std::vector<int>& ret,int low,int high){
    if (low < high) {
        auto pivot = partition(ret,low, high);
        iterSort(ret,low, pivot - 1);
        iterSort(ret,pivot + 1, high);
    }
    return;
}

static std::vector<int> quickSort(const std::vector<int>& data)
{
    std::vector<int> ret=data;
    iterSort(ret,0,ret.size()-1);
    return std::move(ret);
}

static void benchSort(benchmark::State& state)
{
    auto data = GenerateData(state.range(0));
    auto method = bubbleSort;

    switch (state.range(1))
    {
    case 0:
        method = bubbleSort;
        break;
    case 1:
        method = selectSort;
        break;
    case 2:
        method = insertSort;
        break;
    case 3:
        method = countSort;
        break;
    case 4:
        method = quickSort;
        break;
    default:
        break;
    }
    
    for ([[maybe_unused]] auto _ : state) {
        benchmark::DoNotOptimize(method(data));
    }
    state.SetComplexityN(state.range(0));
}

static void benchPrint(benchmark::State& state)
{
    auto data = GenerateData(state.range(0));
    auto method = bubbleSort;

    switch (state.range(1))
    {
    case 0:
        method = bubbleSort;
        break;
    case 1:
        method = selectSort;
        break;
    case 2:
        method = insertSort;
        break;
    case 3:
        method = countSort;
        break;
    case 4:
        method = quickSort;
        break;
    default:
        break;
    }

    auto ret = method(data);
    long last=0;
    for (auto value:ret)
    {
        if (last>value)
        {
            std::cout<<std::endl<<last<<">"<<value<<std::endl;
        }
        else
        {
            std::cout<<value<<" ";
        }
    }

    std::cout<<std::endl;
}


BENCHMARK(benchSort)->RangeMultiplier(8)->Ranges({{1000,10000},{0,0}})->Complexity();
BENCHMARK(benchSort)->RangeMultiplier(8)->Ranges({{1000,10000},{1,1}})->Complexity();
BENCHMARK(benchSort)->RangeMultiplier(8)->Ranges({{1000,10000},{2,2}})->Complexity();
BENCHMARK(benchSort)->RangeMultiplier(8)->Ranges({{1000,10000},{3,3}})->Complexity();
BENCHMARK(benchSort)->RangeMultiplier(8)->Ranges({{1000,10000},{4,4}})->Complexity();

//BENCHMARK(benchPrint)->Args({100,0})->Iterations(1);
//BENCHMARK(benchPrint)->Args({100,1})->Iterations(1);
//BENCHMARK(benchPrint)->Args({100,2})->Iterations(1);
//BENCHMARK(benchPrint)->Args({100,3})->Iterations(1);
//BENCHMARK(benchPrint)->Args({100,4})->Iterations(1);
