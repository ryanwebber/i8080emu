include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

set(CMAKE_BUILD_TYPE Debug)

set(MAIN_SOURCES
  bloomdbg.c
  tested/8080emu.c
  
  #The loader is not bundled in the library
  ../src/loader.c
)

set(MAIN_HEADERS
  ${CONFIG_HEADER}
  tested/8080emu.h
)

add_executable(bloomdbg ${MAIN_HEADERS} ${MAIN_SOURCES})
target_link_libraries(bloomdbg bloom)

