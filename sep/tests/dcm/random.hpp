#ifndef __RANDOM_H__
#define __RANDOM_H__
#include <cstdint>
#include <random>

/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class Random
{

    /**
     * The Singleton's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */
public:

    /**
     * Singletons should not be cloneable.
     */
    Random(Random &other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const Random &) = delete;
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static Random &GetInstance();
    static float Float();
    static double Double();
    static uint16_t InRange(uint16_t first, uint16_t last);

private:
    float FloatImpl();
    double DoubleImpl();
    uint16_t InRangeImpl(uint16_t first, uint16_t last);
    uint32_t InRangeImpl(uint32_t first, uint32_t last);

private:
    Random();
    std::random_device rd_;
    std::mt19937_64 eng_;
};

#endif // __RANDOM_H__