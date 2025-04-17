#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <memory>
#include <stdexcept> // invalid_argument exception
#include <type_traits> // template usage

class Random
{
    Random(unsigned int seed);
    static Random *getObject();
public:

    static void setSeed(unsigned int givenSeed);
    static void setRandomSeed();

    // generates random int from range [min, max]
    template <typename T>
    static T getInt(T min, T max);

    // generates random float from range [min, max)
    template <typename T>
    static T getFloat(T min, T max);

    // generates random boolean with given propability
    static bool getBool(double probability = 0.5);

    // random element from container (std::vector)
    template <typename Container>
    static auto& getElement(const Container& container);

private:
    std::mt19937 randomEngine;
    static std::unique_ptr<unsigned int> seed;
};

#endif // RANDOM_H
