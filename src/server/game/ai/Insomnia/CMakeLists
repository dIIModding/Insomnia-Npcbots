# InsomniaBots CMake
add_library(InsomniaBots STATIC
    InsomniaInstincts.cpp
    InsPlayerBot.cpp
    InsPlayerBotAI.cpp
    InsPlayerBotMgr.cpp
    InsPlayerBotSocial.cpp
)

target_include_directories(InsomniaBots
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(InsomniaBots
    PRIVATE
        game
        shared
)

