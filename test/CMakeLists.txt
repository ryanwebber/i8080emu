include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

set(TEST_SOURCES
  run_tests.c
)

add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests bloom)

