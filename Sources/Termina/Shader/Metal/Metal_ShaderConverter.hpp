#pragma once

#include <Termina/Core/Common.hpp>

#include <vector>
#include <string>

class IRRootSignature;

namespace Termina {
    class MetalShaderConverter
    {
    public:
        static void Initialize();
        static void Shutdown();

        static std::vector<uint8> Convert(std::vector<uint8>, std::string);
    private:
        static IRRootSignature* s_RootSignature;
    };
}
