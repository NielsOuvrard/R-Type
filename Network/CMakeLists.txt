cmake_minimum_required(VERSION 3.16)
project(Network)

set(SOURCES
        net_common.h
        net_client.h
        net_connection.h
        net_tsqueue.h
        net_server.h
        net_message.h
        net_data_channel.h
        net_datagram.h
)

add_library(${PROJECT_NAME} INTERFACE ${SOURCES})

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} INTERFACE asio)
