
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest SFML)

enable_testing()

add_executable(
  Tests
  "addNodes.cpp"
)

target_include_directories(
  Tests
  PRIVATE
  googletest/include
  "../src"
)

target_link_libraries(
  Tests
  GTest::gtest_main
  SFML::Graphics
)

include(GoogleTest)
gtest_discover_tests(Tests)

