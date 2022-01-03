#include "PerlinNoise.h"

#include "../World/WorldConstants.h"

#include <random>
#include <functional>

template<typename T = double>
inline T dot(const Vec2<T>& v1, const Vec2<T>& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

inline double smoothstep(const double& t)
{
    return t * t * (3 - 2 * t);
    // return ((6 * t - 15) * t + 10) * t * t * t;
}

PerlinNoise::PerlinNoise(unsigned seed)
{
    m_frequency     = 0.005;
    m_lacunarity    = 2.0;
    m_gain          = 0.5;
    m_layers        = 8;

    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_real_distribution<> dist;
    auto randF = std::bind(dist, e);

    for(unsigned i = 0; i < m_scMaxSize; i++)
    {
#if 1
        // Create random vector(gradient) in the range [0,1] and map to [-1,1]
        m_rvals[i] = Vec2f(2 * randF() - 1, 2 * randF() - 1);
        auto length2 = m_rvals[i].length2();
        // Normalize vector
        m_rvals[i] /= sqrtf(length2);
#else
        float theta = acos(2 * randF() - 1); 
        float phi = 2 * randF() * M_PI; 

        float x = cos(phi) * sin(theta); 
        float y = sin(phi) * sin(theta); 
        float z = cos(theta); 
        m_rvals[i] = Vec2f(x, y); 
#endif
        m_permutations[i] = i;
    }
    
    std::uniform_int_distribution<> idist;
    auto randI = std::bind(idist, e);
    // Shuffle and extend the permuatation table
    for(unsigned i = 0; i < m_scMaxSize; i++)
    {
        std::swap(m_permutations[i], m_permutations[randI() & m_scMaxSizeMask]);
        // range [256:512]
        m_permutations[i + m_scMaxSize] = m_permutations[i];
    }
}

double PerlinNoise::lerp(double p1, double p2, double t) const
{
    return p1 * (1 - t) + p2 * t;
}

double PerlinNoise::get(double x, double z) const
{
    // We use floot, because it returns right integers
        // for negative values. 
        // For -1.2 it will return -2, when (int) will return -1
        // We use mask instead of modulo operator
        int xi0 = ((int)std::floor(x)) & m_scMaxSizeMask;
        int zi0 = ((int)std::floor(z)) & m_scMaxSizeMask;

        int xi1 = (xi0 + 1) & m_scMaxSizeMask;
        int zi1 = (zi0 + 1) & m_scMaxSizeMask;

        float tx = x - ((int)std::floor(x)); 
        float tz = z - ((int)std::floor(z));  

        float sx = smoothstep(tx);
        float sz = smoothstep(tz);

        auto& c00 = m_rvals[m_permutations[m_permutations[xi0] + zi0]];
        auto& c10 = m_rvals[m_permutations[m_permutations[xi1] + zi0]];
        auto& c01 = m_rvals[m_permutations[m_permutations[xi0] + zi1]];
        auto& c11 = m_rvals[m_permutations[m_permutations[xi1] + zi1]];

        // Get vectors that cast from grid points to our p point
        auto v00 = Vec2f(tx,tz);
        auto v10 = Vec2f(tx-1,tz);
        auto v01 = Vec2f(tx, tz-1);
        auto v11 = Vec2f(tx-1, tz-1);

        // Interpolating between dot products of these vectors and random grid vectors
        float a = lerp(dot(c00, v00), dot(c10, v10), sx);
        float b = lerp(dot(c01, v01), dot(c11, v11), sx);

        return lerp(a, b, sz);
}

double PerlinNoise::getHeight(int x, int z, int chunkX, int chunkZ)
{
    int worldX = x + chunkX * CHUNK_SIZE;
    int worldZ = z + chunkZ * CHUNK_SIZE;

    double noiseSum  = 0.0;
    double amplitude = 1.0;
    double amplitudeSum = 0.0;

    // double pX = worldX * m_frequency;
    // double pZ = worldZ * m_frequency;

    for(unsigned l = 0; l < m_layers; l++)
    {
        noiseSum    += get(worldX * m_frequency,worldZ * m_frequency) * amplitude;
        amplitudeSum += amplitude;
        amplitude   *= m_gain;
        worldX      *= m_lacunarity;
        worldZ      *= m_lacunarity;

    //     if(noiseSum > m_maxNoise) m_maxNoise = noiseSum;
    }

    return std::pow((noiseSum / amplitudeSum + 1.0) * 0.5, 4);
}
