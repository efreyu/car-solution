include(AddGoogleTest)

function(INIT_TEST ARG_TARGET)
    add_executable(${ARG_TARGET} ${ARGN})
    set_property(TARGET ${ARG_TARGET} PROPERTY CXX_STANDARD 17)
    target_compile_options(${ARG_TARGET} PRIVATE -Wall)
    target_link_libraries(${ARG_TARGET} PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
    add_gtest(${ARG_TARGET})
endfunction()

init_test(TestStructTransform TestStructTransform.cpp)
init_test(TestStructCar TestStructCar.cpp)
init_test(TestManagerClass TestManagerClass.cpp ../src/Classes/Game.cpp)
