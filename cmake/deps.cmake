# for finding external thirdparty dependecies
set(CMAKE_PREFIX_PATH ${CMAKE_INSTALL_PREFIX})

find_package(Git REQUIRED)
#----------------------------
# tinyxml2
#----------------------------
if(BUILD_TINYXML2)
  message(STATUS "> tinyxml2:")
  # updating/initializing the git submodule
  execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init -- thirdparty/tinyxml2
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  # copying the External project CMakeLists.txt
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinyxml2.ext.in
    ${CMAKE_BINARY_DIR}/thirdparty/tinyxml2/CMakeLists.txt)
  # calling the cmake command to generate thirdparty library project
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/thirdparty/tinyxml2)
  if(result)
    message(FATAL_ERROR "CMake step for tinyxml2 failed: ${result}")
  endif()
  # calling the cmake command to build thirdparty library and install it
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/thirdparty/tinyxml2)
  if(result)
    message(FATAL_ERROR "Build step for tinyxml2 failed: ${result}")
  endif()
endif()
