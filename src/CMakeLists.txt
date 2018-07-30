set(CMAKE_BUILD_TYPE Debug)

set(LIB_SOURCES
  bloom.c
  cpu.c
  instruction/noop.c
)

set(MAIN_SOURCES
  cpu.c
  main.c
)

set(HEADERS 
  ${CONFIG_HEADER}
  bloom.h
  cpu.h
  instruction/noop.h
)

add_library(bloom STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(main bloom)

install(TARGETS bloom
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/bloom.h DESTINATION include)

