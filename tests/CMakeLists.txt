include(AddGoogleTest)

function(INIT_TEST ARG_TARGET)
    add_executable(${ARG_TARGET} ${ARGN})
    set_property(TARGET ${ARG_TARGET} PROPERTY CXX_STANDARD 17)
    target_compile_options(${ARG_TARGET} PRIVATE -Wall)
    add_gtest(${ARG_TARGET})
endfunction()

init_test(TestStructTransform TestStructTransform.cpp ../src/game.hpp)
init_test(TestStructCar TestStructCar.cpp ../src/game.hpp)
init_test(TestGameClass TestGameClass.cpp ../src/game.hpp)
