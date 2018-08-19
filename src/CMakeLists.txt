set(CMAKE_BUILD_TYPE Debug)

set(LIB_SOURCES
  cpu.c
  machine.c
)

set(MAIN_SOURCES
  cpu.c
  loader.c
  main.c
)

set(LIB_HEADERS
  ${CONFIG_HEADER}
  bloom.h
)

set(MAIN_HEADERS
  ${CONFIG_HEADER}
  loader.h
)

add_library(bloom STATIC ${LIB_SOURCES} ${LIB_HEADERS})
  target_compile_definitions(bloom PRIVATE BLOOM_DEBUG=1)

add_executable(main ${MAIN_HEADERS} ${MAIN_SOURCES})
  target_link_libraries(main bloom)

install(TARGETS bloom
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/bloom.h DESTINATION include)

