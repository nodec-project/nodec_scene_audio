#ifndef NODEC_SCENE_AUDIO__COMPONENTS__AUDIO_SOURCE_HPP_
#define NODEC_SCENE_AUDIO__COMPONENTS__AUDIO_SOURCE_HPP_

#include <chrono>
#include <memory>

#include "../resources/audio_clip.hpp"

namespace nodec_scene_audio {
namespace components {

struct AudioSource {
    std::shared_ptr<resources::AudioClip> clip;

    bool loop{false};

    float volume{1.0f};

    std::chrono::milliseconds position{0};

    /**
     * @brief Determines whether the audio source is spatial or not.
     */
    bool is_spatial{false};
};

struct AudioPlay {};
struct AudioStop {};

} // namespace components
} // namespace nodec_scene_audio

#endif
