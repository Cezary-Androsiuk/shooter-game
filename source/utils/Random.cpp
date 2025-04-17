#include "Random.h"

std::unique_ptr<unsigned int> Random::seed = nullptr;

Random::Random(unsigned int seed) : randomEngine(seed) {}

Random *Random::getObject()
{
    static Random random(std::random_device{}());
    return &random;
}

void Random::setSeed(unsigned int givenSeed)
{
    Random::getObject()->randomEngine.seed(givenSeed);
}

void Random::setRandomSeed()
{
    Random::getObject()->randomEngine.seed(std::random_device{}());
}

template<typename T>
T Random::getInt(T min, T max)
{
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    std::uniform_int_distribution<T> dist(min, max);
    return dist(Random::getObject()->randomEngine);
}

template<typename T>
T Random::getFloat(T min, T max)
{
    static_assert(std::is_floating_point_v<T>, "T must be a floating-point type");
    std::uniform_real_distribution<T> dist(min, max);
    return dist(Random::getObject()->randomEngine);
}

bool Random::getBool(double probability)
{
    std::bernoulli_distribution dist(probability);
    return dist(Random::getObject()->randomEngine);
}

template<typename Container>
auto &Random::getElement(const Container &container)
{
    if (container.empty()) {
        throw std::invalid_argument("Container cannot be empty");
    }
    std::uniform_int_distribution<size_t> dist(0, container.size() - 1);
    return *std::next(container.begin(), dist(Random::getObject()->randomEngine));
}

template int Random::getInt<int>(int, int);
template float Random::getFloat<float>(float, float);
template double Random::getFloat<double>(double, double);
