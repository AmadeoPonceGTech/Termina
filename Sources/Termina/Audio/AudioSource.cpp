#include "AudioSource.hpp"
#include "Core/Logger.hpp"

namespace Termina {
    AudioSource::AudioSource(ma_engine& engine, AudioData* data, bool looping)
        : m_Data(data)
        , m_Looping(looping)
    {
        ma_result result = ma_sound_init_from_data_source(&engine, &data->GetDecoder(), 0, nullptr, &m_Sound);
        if (result != MA_SUCCESS) {
            TN_ERROR("Failed to initialize audio source!");
        }

        ma_sound_set_position(&m_Sound, 0.0f, 0.0f, 0.0f);
    }

    AudioSource::~AudioSource()
    {
        if (m_Data != nullptr) {
            ma_sound_uninit(&m_Sound);
        }
    }

    void AudioSource::Play()
    {
        if (m_Data != nullptr) {
            ma_sound_start(&m_Sound);
        }
    }

    void AudioSource::Stop()
    {
        if (m_Data != nullptr) {
            ma_sound_stop(&m_Sound);
        }
    }

    void AudioSource::Update()
    {
        ma_sound_set_looping(&m_Sound, m_Looping);
        ma_sound_set_volume(&m_Sound, m_Volume);
    }
}
