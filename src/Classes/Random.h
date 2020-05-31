#ifndef CAR_EXAMPLE_RANDOM_H
#define CAR_EXAMPLE_RANDOM_H

#include <random>

class Random {

public:
    static int GenerateBetween(int a, int b) {
        std::random_device rnd_device;
        std::mt19937 mt_rand {rnd_device()};
        std::uniform_int_distribution<int> dist {a, b};
        return dist(mt_rand);
    }

    template <typename T1, typename T2>
    static T1 GetRandomVector(std::vector<T2> array) {
        int key = Random::GenerateBetween(0, array.size() - 1);

        try {
            auto& element = array.at(key);
            return element;
        }
        catch (const std::out_of_range& oor) {
            return GetRandomVector<T1>(array);
        }
    }
};


#endif //CAR_EXAMPLE_RANDOM_H
