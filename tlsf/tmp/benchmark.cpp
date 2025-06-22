#include "utility/TestCommand.h"
#include "tlsf.h"
#include <benchmark/benchmark.h>

void std_test() {
	void* p = malloc(1024);
	*(int*)p = 2134;
	free(p);
}

#define POOL_SIZE 1024 * 1024
// Pool size is in bytes.
static char pool[POOL_SIZE];
void tlsf_test() {
	void* p = tlsf_malloc(1024);
	*(int*)p = 2134;
	tlsf_free(p);
}

static void malloc_std(benchmark::State& state) {
	for (auto _ : state)
		std_test();
}
static void malloc_tlsf(benchmark::State& state) {
	for (auto _ : state)
		tlsf_test();
}
BENCHMARK(malloc_std);
BENCHMARK(malloc_tlsf);

void test_bench() {
	// init tlsf memory pool
	int free_mem = init_memory_pool(POOL_SIZE, pool);
	printf("Total free memory= %d\n", free_mem);

	::benchmark::Initialize(0, nullptr);
	if (::benchmark::ReportUnrecognizedArguments(0, nullptr))
		return;
	::benchmark::RunSpecifiedBenchmarks();
	::benchmark::Shutdown();
}

TEST_FUNC_ENTRY(bench)