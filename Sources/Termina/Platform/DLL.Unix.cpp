#include "DLL.hpp"
#include "Core/Logger.hpp"

#if !defined(TRMN_WINDOWS)

#include <dlfcn.h>
#include <climits>
#include <cstdio>
#include <atomic>

#if defined(TRMN_MACOS)
#include <mach-o/dyld.h>
#elif defined(TRMN_LINUX)
#include <unistd.h>
#endif

namespace Termina {

    static std::string GetExecutableDir()
    {
#if defined(TRMN_MACOS)
        char buf[PATH_MAX];
        uint32_t size = sizeof(buf);
        if (_NSGetExecutablePath(buf, &size) == 0) {
            std::string p(buf);
            size_t slash = p.find_last_of('/');
            if (slash != std::string::npos)
                return p.substr(0, slash);
        }
#elif defined(TRMN_LINUX)
        char buf[PATH_MAX];
        ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
        if (len > 0) {
            buf[len] = '\0';
            std::string p(buf);
            size_t slash = p.find_last_of('/');
            if (slash != std::string::npos)
                return p.substr(0, slash);
        }
#endif
        return ".";
    }

    DLL::DLL(const char* path)
    {
        Load(path);
    }

    DLL::~DLL()
    {
        if (m_Handle) {
            dlclose(m_Handle);
            m_Handle = nullptr;
        }
        if (!m_TempPath.empty()) {
            std::remove(m_TempPath.c_str());
            m_TempPath.clear();
        }
    }

    void DLL::Load(const char* path)
    {
        if (m_Handle) {
            dlclose(m_Handle);
            m_Handle = nullptr;
        }
        if (!m_TempPath.empty()) {
            std::remove(m_TempPath.c_str());
            m_TempPath.clear();
        }

        // Shadow-copy the library to a unique path so that dyld doesn't serve
        // the cached image when we dlopen the same path after a hot-reload.
        // Resolve the full path relative to the executable (matching rpath layout).
        static std::atomic<int> s_Generation{0};
        int gen = s_Generation.fetch_add(1);

        std::string src = GetExecutableDir() + "/" + path;
        std::string tempPath = src;
        size_t dotPos = tempPath.rfind('.');
        if (dotPos != std::string::npos)
            tempPath.insert(dotPos, "_hot" + std::to_string(gen));
        else
            tempPath += "_hot" + std::to_string(gen);

        if (FILE* in = std::fopen(src.c_str(), "rb")) {
            if (FILE* out = std::fopen(tempPath.c_str(), "wb")) {
                char buf[65536];
                size_t n;
                while ((n = std::fread(buf, 1, sizeof(buf), in)) > 0)
                    std::fwrite(buf, 1, n, out);
                std::fclose(out);
                std::fclose(in);
                m_TempPath = tempPath;
            } else {
                std::fclose(in);
                TN_ERROR("Failed to create shadow copy '%s'", tempPath.c_str());
                m_TempPath.clear();
            }
        } else {
            TN_ERROR("Failed to open '%s' for shadow copy", src.c_str());
            m_TempPath.clear();
        }

        const char* loadPath = m_TempPath.empty() ? path : m_TempPath.c_str();
        m_Handle = dlopen(loadPath, RTLD_NOW | RTLD_LOCAL);
        if (!m_Handle) {
            TN_FATAL("Failed to load DLL %s: %s", loadPath, dlerror());
        }
    }

    void* DLL::GetSymbol(const char* name)
    {
        if (m_Handle) {
            return dlsym(m_Handle, name);
        }
        return nullptr;
    }
}

#endif
