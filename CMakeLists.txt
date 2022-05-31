cmake_minimum_required(VERSION 3.23)

project(lab_osp LANGUAGES C)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/src/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/src/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/lib)

add_library(lab_objects OBJECT src/lab1aotN3246.c)
add_library(lib_objects OBJECT src/libaotN3246.c)
set_target_properties(lib_objects PROPERTIES POSITION_INDEPENDENT_CODE ON) 
add_custom_target(compile DEPENDS lab_objects lib_objects)


add_executable(lab $<TARGET_OBJECTS:lab_objects>)

add_library(ipv4 SHARED $<TARGET_OBJECTS:lib_objects>)

# Adding make build
add_custom_target(build DEPENDS lab ipv4)


# A dirty hack for make clean
# add_custom_command(
  # TARGET build 
  # POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:lab> ${CMAKE_SOURCE_DIR}/src/bin/ 
  # COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ipv4> ${CMAKE_SOURCE_DIR}/src/lib/ 
  # COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:lab> $<TARGET_FILE:ipv4>)

# Adding scp compatabilty

add_custom_target(scp DEPENDS build)

add_custom_command(
  TARGET scp 
  POST_BUILD COMMAND scp $<TARGET_FILE:lab> drew@localhost:~/study/lab3/scpRecieverDir
  )

# Adding env target 
add_custom_target(env DEPENDS lab ipv4)

add_custom_command(
  TARGET env
  POST_BUILD COMMAND export LAB1DEBUG=1
  )

# Adding clean target
# We use cleann cause clean is reserved in CMake
add_custom_target(super_clean 
  COMMAND ${CMAKE_COMMAND} -E remove  "$<TARGET_OBJECTS:lib_objects>" "$<TARGET_OBJECTS:lab_objects>"
  DEPENDS build
  )

add_executable(test testSrc/test.c $<TARGET_OBJECTS:lib_objects> )
target_compile_options(test PUBLIC -Wl,--wrap=fopen,--wrap=fread,--wrap=fclose -lcmocka)
target_link_libraries(test cmocka)
add_custom_target(music DEPENDS build)
add_custom_command(
  TARGET music
  POST_BUILD COMMAND cvlc --play-and-exit ${CMAKE_SOURCE_DIR}/music.mp3 > /dev/null 2>&1)