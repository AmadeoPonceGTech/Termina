#include "AudioData.hpp"

#include <Termina/Core/Logger.hpp>

namespace Termina {
    AudioData::AudioData(ma_engine& engine, const std::string& path)
    {
        ma_result result = ma_decoder_init_file(path.c_str(), nullptr, &m_Decoder);
        m_IsValid = (result == MA_SUCCESS);

        if (!m_IsValid) {
            TN_ERROR("Failed to load audio file: %s", path.c_str());
        }
    }

    AudioData::~AudioData()
    {
        ma_decoder_uninit(&m_Decoder);
        m_IsValid = false;
    }
}
