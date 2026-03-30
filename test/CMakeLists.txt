include(GoogleTest)

set(TEST_PROJECT_NAME liblifegame_test)
set(LIBRARY_TESTS_SOURCE liblifegame_test.cpp)

add_executable(${TEST_PROJECT_NAME} ${LIBRARY_TESTS_SOURCE})

target_link_libraries(${TEST_PROJECT_NAME} 
    gtest 
    gtest_main 
    ${LIBRARY_NAME}
)

enable_testing()

add_test(NAME ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME})