#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <set>

namespace {
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine GENERATOR(seed);
}

// Get a random index [0, max) i.e. can't return max
std::size_t random_index(std::size_t max)
{
    std::uniform_int_distribution<std::size_t> distribution(0, max - 1);
    return distribution(GENERATOR);
}

template <typename T>
void linear_shuffle(std::vector<T>& container)
{
    std::size_t size = container.size();
    for (std::size_t i = 0; i < size; ++i) {
        std::swap(container[i], container[random_index(size)]);
    }
}

template <typename T>
void print(const T& container)
{
    for (const auto& t : container) {
        std::cout << t << " ";
    }
    std::cout <<std::endl;
}

int main()
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    linear_shuffle(v);
    print(v);
    
    return 0;
}