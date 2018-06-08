
add_custom_command(
    OUTPUT "ice_interface.cpp"
    COMMAND slice2cpp --underscore ice_interface.ice
    DEPENDS ice_interface.ice
)

include_directories(
    ./
    ${CMAKE_SOURCE_DIR}/
    ${CMAKE_SOURCE_DIR}/common/
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/third-party
    ${CMAKE_SOURCE_DIR}/third-party/rapidjson
    ${CMAKE_SOURCE_DIR}/third-party/evhtp/include
    ${CMAKE_SOURCE_DIR}/third-party/libcuckoo/include
    /home/apps/cpplibs/Ice-3.6.4/include
    /home/apps/cpplibs/libgo/include
    /home/apps/cpplibs/boost-1.61.0/include
)

link_directories(
    ${CMAKE_SOURCE_DIR}/
    ${CMAKE_SOURCE_DIR}/common/
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/third-party/evhtp/lib
    ${CMAKE_SOURCE_DIR}/third-party/libcuckoo/lib
    /home/apps/cpplibs/Ice-3.6.4/lib64/c++11
    /home/apps/cpplibs/libgo/lib
    /home/apps/cpplibs/boost-1.61.0/lib
)

set(SERVER_SRC
    main.cpp
    conf.cpp
    api.cpp
    ice_interface.cpp
)

ADD_EXECUTABLE(midware-ice-service ${SERVER_SRC})
target_link_libraries(midware-ice-service
    libgo dl
    pthread
    Ice IceUtil
    boost_thread boost_system
)

set(CLIENT_SRC
    client.cpp
    ice_interface.cpp
)

ADD_EXECUTABLE(midware-ice-service-client ${CLIENT_SRC})
target_link_libraries(midware-ice-service-client
    pthread
    Ice IceUtil
)

