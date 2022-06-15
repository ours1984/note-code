#include <benchmark/benchmark.h>
#include <vector>
#include <numeric>
#include <ctime>
#include <algorithm>

static std::vector<long> GenerateData(long count)
{
    std::vector<long> ret(count);

    std::srand(std::time(nullptr)); // use current time as seed for random generator

    for (auto &value: ret)
    {
        value = std::rand();
    }

    return std::move(ret);
}

static std::vector<long> bubbleSort(const std::vector<long>& data)
{
    std::vector<long> ret=data;
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

static std::vector<long> selectSort(const std::vector<long>& data)
{
    std::vector<long> ret=data;
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
    default:
        break;
    }

    for ([[maybe_unused]] auto _ : state) {
        benchmark::DoNotOptimize(method(data));
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(benchSort)->RangeMultiplier(5)->Ranges({{1000,15000},{0,0}})->Complexity();
BENCHMARK(benchSort)->RangeMultiplier(5)->Ranges({{1000,15000},{1,1}})->Complexity();
