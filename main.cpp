#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <thread>

int main() {
	size_t num_elements = (2ull * 1024 * 1024 * 1024) / sizeof(int); // 2GB
	std::cout << "Allocating " << num_elements << " ints (" << num_elements * sizeof(int) / (1024 * 1024) << " MB)..." << std::endl;

	std::vector<int> data(num_elements);

	auto start_seq = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < num_elements; ++i) {
		data[i] = i;
	}
	auto end_seq = std::chrono::high_resolution_clock::now();

	std::vector<size_t> indices(num_elements);
	for (size_t i = 0; i < num_elements; ++i) indices[i] = i;
	std::mt19937 rng(42);
	std::shuffle(indices.begin(), indices.end(), rng);

	auto start_rand = std::chrono::high_resolution_clock::now();
	long long sum = 0;
	for (size_t i = 0; i < num_elements; ++i) {
		sum += data[indices[i]];
	}
	auto end_rand = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_seq = end_seq - start_seq;
	std::chrono::duration<double> time_rand = end_rand - start_rand;

	std::cout << "Sequential write time: " << time_seq.count() << " seconds" << std::endl;
	std::cout << "Random read time: " << time_rand.count() << " seconds" << std::endl;
	std::cout << "Sum (ignore): " << sum << std::endl;

	std::cout << "Sleeping for 30 seconds for system analysis..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(30));

	return 0;
}
