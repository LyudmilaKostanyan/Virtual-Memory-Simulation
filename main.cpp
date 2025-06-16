#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <thread>
#include <iomanip>

int main() {
	size_t num_elements = (2ull * 1024 * 1024 * 1024) / sizeof(int); // 2GB
	std::cout << "\nAllocating " << num_elements << " ints (" << num_elements * sizeof(int) / (1024 * 1024) << " MB)...\n";

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

	std::cout << std::left << std::setw(25) << "Sequential write time:" 
		<< std::right << std::setw(10) << time_seq.count() << " seconds\n";
	std::cout << std::left << std::setw(25) << "Random read time:"     
		<< std::right << std::setw(10) << time_rand.count() << " seconds\n\n";

	std::cout << "Sleeping for 30 seconds for system analysis...\n";
	std::this_thread::sleep_for(std::chrono::seconds(30));

	return 0;
}
