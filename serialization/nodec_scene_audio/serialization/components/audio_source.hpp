#ifndef NODEC_SCENE_AUDIO__SERIALIZATION__COMPONENTS__AUDIO_SOURCE_HPP_
#define NODEC_SCENE_AUDIO__SERIALIZATION__COMPONENTS__AUDIO_SOURCE_HPP_

#include <nodec_scene_audio/components/audio_source.hpp>
#include <nodec_scene_audio/resources/audio_clip.hpp>
#include <nodec_scene_serialization/archive_context.hpp>
#include <nodec_scene_serialization/serializable_component.hpp>

namespace nodec_scene_audio {
namespace components {

struct SerializableAudioSource : nodec_scene_serialization::BaseSerializableComponent {
    SerializableAudioSource()
        : BaseSerializableComponent{this} {}

    SerializableAudioSource(const AudioSource &other)
        : BaseSerializableComponent(this),
          clip(other.clip),
          is_spatial(other.is_spatial),
          loop(other.loop),
          volume(other.volume),
          position(other.position) {}

    operator AudioSource() const noexcept {
        AudioSource value;

        value.clip = clip;
        value.is_spatial = is_spatial;
        value.loop = loop;
        value.volume = volume;
        value.position = position;
        return value;
    }

    std::shared_ptr<resources::AudioClip> clip;

    bool loop{false};
    float volume{1.0f};
    std::chrono::milliseconds position{0};
    bool is_spatial{false};

    template<class Archive>
    void save(Archive &archive) const {
        using namespace nodec_scene_serialization;
        auto &context = cereal::get_user_data<ArchiveContext>(archive);

        archive(cereal::make_nvp("clip", context.resource_registry().lookup_name<resources::AudioClip>(clip).first));
        archive(cereal::make_nvp("loop", loop));
        archive(cereal::make_nvp("volume", volume));
        archive(cereal::make_nvp("is_spatial", is_spatial));
    }

    template<class Archive>
    void load(Archive &archive) {
        using namespace nodec_scene_serialization;
        using namespace nodec::resource_management;
        auto &context = cereal::get_user_data<ArchiveContext>(archive);

        {
            std::string name;
            archive(cereal::make_nvp("clip", name));
            clip = context.resource_registry().get_resource_direct<resources::AudioClip>(name);
        }
        archive(cereal::make_nvp("loop", loop));
        archive(cereal::make_nvp("volume", volume));
        archive(cereal::make_nvp("is_spatial", is_spatial));
    }
};

struct SerializableAudioPlay : nodec_scene_serialization::BaseSerializableComponent {
    SerializableAudioPlay()
        : BaseSerializableComponent(this) {
    }
    SerializableAudioPlay(const AudioPlay &)
        : BaseSerializableComponent(this) {
    }
    operator AudioPlay() const noexcept {
        return AudioPlay();
    }

    template<class Archive>
    void serialize(Archive &) {
    }
};

struct SerializableAudioStop : nodec_scene_serialization::BaseSerializableComponent {
    SerializableAudioStop()
        : BaseSerializableComponent(this) {
    }
    SerializableAudioStop(const AudioStop &)
        : BaseSerializableComponent(this) {
    }
    operator AudioStop() const noexcept {
        return AudioStop();
    }

    template<class Archive>
    void serialize(Archive &) {
    }
};

} // namespace components
} // namespace nodec_scene_audio

NODEC_SCENE_REGISTER_SERIALIZABLE_COMPONENT(nodec_scene_audio::components::SerializableAudioSource)
NODEC_SCENE_REGISTER_SERIALIZABLE_COMPONENT(nodec_scene_audio::components::SerializableAudioPlay)
NODEC_SCENE_REGISTER_SERIALIZABLE_COMPONENT(nodec_scene_audio::components::SerializableAudioStop)

#endif