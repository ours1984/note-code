#include <benchmark/benchmark.h>
#include <vector>
#include <numeric>
#include <experimental/random>

static std::vector<long> GenerateData(long count)
{
    std::vector<long> ret(count);

    std::iota(ret.begin(),ret.end(),0);

    return std::move(ret);
}

static unsigned long ForceSeach(const std::vector<long>& data,unsigned long value)
{
    for (unsigned long i = 0; i < data.size(); ++i) {
        if (data[i]==value)
        {
            return i;
        }
    }
    return 0;
}

static unsigned long BinarySeach(const std::vector<long>& data,unsigned long value)
{
    unsigned long low=0;
    unsigned long high=data.size()-1;

    while (low<high)
    {
        auto mid=(low+high)/2;
        if (mid==value)
        {
            return mid;
        }
        else if (mid>value)
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }
    return 0;
}

static void benchSearch(benchmark::State& state)
{
    auto data = GenerateData(state.range(0));
    auto method = ForceSeach;

    switch (state.range(1))
    {
    case 0:
        method = ForceSeach;
        break;
    case 1:
        method = BinarySeach;
        break;
    default:
        break;
    }

    for ([[maybe_unused]] auto _ : state) {
        auto random_number = std::experimental::randint(0l, state.range(0));
        benchmark::DoNotOptimize(method(data,random_number));
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(benchSearch)->RangeMultiplier(10)->Ranges({{1000,10000000},{0,0}})->Complexity();
BENCHMARK(benchSearch)->RangeMultiplier(10)->Ranges({{1000,10000000},{1,1}})->Complexity();
