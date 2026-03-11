#pragma once

#include "Common.hpp"

#include <unordered_set>
#include <random>

namespace Termina {
    class IDGenerator
    {
    public:
        static IDGenerator& Get()
        {
            static IDGenerator instance;
            return instance;
        }

        uint64 Generate();
        void Reserve(uint64 id);
        void Release(uint64 id);
        bool IsUsed(uint64 id) const;
        void Clear();

    private:
        IDGenerator();

        std::unordered_set<uint64> m_UsedIDs;
        std::mt19937_64 m_Generator;
        std::uniform_int_distribution<uint64> m_Distribution;
    };

    inline uint64 NewID()
    {
        return IDGenerator::Get().Generate();
    }
}
