#pragma once

#include "AudioData.hpp"

namespace Termina {
    class AudioSource
    {
    public:
        AudioSource(ma_engine& engine, AudioData* data, bool looping = false);
        ~AudioSource();

        void Play();
        void Stop();
        void Update();

        bool IsValid() const { return m_Data != nullptr; }
        ma_sound& GetSound() { return m_Sound; }
        const ma_sound& GetSound() const { return m_Sound; }

        float GetVolume() const { return m_Volume; }
        void SetVolume(float volume) { m_Volume = volume; }
    private:
        AudioData* m_Data;
        ma_sound m_Sound;
        bool m_Looping = false;
        float m_Volume = 1.0f;
    };
}
