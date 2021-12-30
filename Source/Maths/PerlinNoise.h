#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <glm/glm.hpp>

template<typename T>
struct Vec2
{
    Vec2() : x(T(0)), y(T(0)) {}
    Vec2(T xx, T yy) : x(xx), y(yy) {}
    T length2() const { return x * x + y * y; }
    Vec2 operator*(const T& v) const { return {x*v, y*v}; }
    Vec2& operator/=(const T& r) { x /= r; y /= r; return *this; }
    Vec2 operator-(const Vec2& r) const { return {x - r.x, y - r.y}; }
    T x;
    T y;
};

typedef Vec2<double> Vec2f;

class PerlinNoise
{
    public:
        PerlinNoise();

        double getHeight(int x, int z, int chunkX, int chunkZ);

    private:
        double lerp(double p1, double p2, double t) const;
        double get(double x, double z) const;
        
        static const unsigned m_scMaxSize = 256;
        static const unsigned m_scMaxSizeMask = m_scMaxSize - 1;
        
        Vec2f m_rvals[m_scMaxSize];
        unsigned m_permutations[m_scMaxSize * 2];

        int m_layers;
        double m_frequency;
        double m_amplitude;
        double m_gain;       // Rate of change in the amplitude
        double m_lacunarity; // Rate of change in the frequency
        double m_maxNoise;
};

#endif // PERLINNOISE_H
