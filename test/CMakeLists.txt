add_executable(test_decorator test_decorator.cpp)
target_link_libraries(test_decorator PRIVATE GTest::GTest GTest::Main DecoratorLib)
add_test(NAME TestDecorator COMMAND test_decorator)
