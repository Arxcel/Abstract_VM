add_executable(
    avm_tests
    main.cpp
    example_add.cpp
    )

target_link_libraries(
    avm_tests
    gtest_main
)
get_target_property(incDirs avm INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(avm_tests PRIVATE ${incDirs})

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )