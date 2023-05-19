cmake_minimum_required(VERSION 3.20)
project(my_native_library)

# Set C++ 17 as teh standard
set(CMAKE_CXX_STANDARD 17)

# Print our JAVA_HOME in the console when we run CMake to help identifying problems with our java home.
message(STATUS "JAVA_HOME= $ENV{JAVA_HOME}")
message(STATUS "")

# Next we set some variables that the JNI package needs to load in
# Here is how its done on MacOS and Linux

# If Linux
if(UNIX AND NOT APPLE)
    set(JAVA_AWT_LIBRARY "$ENV{JAVA_HOME}/lib/libjawt.so")
    set(JAVA_JVM_LIBRARY "$ENV{JAVA_HOME}/lib/server/libjvm.so")
    set(JAVA_INCLUDE_PATH2 "$ENV{JAVA_HOME}/include/linux")
endif()

# if MacOS
if(UNIX AND APPLE)
    set(JAVA_AWT_LIBRARY "$ENV{JAVA_HOME}/lib/libjawt.dylib")
    set(JAVA_JVM_LIBRARY "$ENV{JAVA_HOME}/lib/server/libjvm.dylib")
    set(JAVA_INCLUDE_PATH2 "$ENV{JAVA_HOME}/include/darwin")
endif()

set(JAVA_INCLUDE_PATH "$ENV{JAVA_HOME}/include")
set(JAVA_AWT_INCLUDE_PATH "$ENV{JAVA_HOME}/include")

# While running CMake, this will create a folder called "sharedlibs" in the root of our project.
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/../../../sharedlibs")

# This will load in external packages that we need to get JNI to work
find_package(Java COMPONENTS Development)
find_package(JNI REQUIRED)

if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
endif()

include_directories(.)

# This will load all C++ code files onto variables so that we can link it to a target
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/*.h")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/*.cpp")

# link the code files onto our target. "shared" is important here, this is the magic that will make it so our compiled code comes out as a shared library.
add_library(my_native_library SHARED ${HEADER_LIST} ${SOURCE_LIST})

# Next we need to link JNI to our target
target_link_libraries(my_native_library PRIVATE JNI::JNI)

# After our build, copy the compiled shared library to our shared libs folder.
add_custom_command(TARGET my_native_library
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:my_native_library> "${CMAKE_SOURCE_DIR}/../../../sharedlibs/")