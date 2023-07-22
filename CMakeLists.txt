cmake_minimum_required(VERSION 3.0)

project(nodec_scene_audio LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE include
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE nodec
)

option(NODEC_SCENE_AUDIO_ENABLE_SERIALIZATION OFF)

if(NODEC_SCENE_AUDIO_ENABLE_SERIALIZATION)
    target_include_directories(
        ${PROJECT_NAME}
        INTERFACE serialization
    )

    target_link_libraries(${PROJECT_NAME}
        INTERFACE
        nodec_scene_serialization
    )
endif()