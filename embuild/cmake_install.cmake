# Install script for directory: /home/russellg/projects/gentlemanly_engine

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/russellg/projects/gentlemanly_engine/embuild/deps/boost/cmake_install.cmake")
  include("/home/russellg/projects/gentlemanly_engine/embuild/deps/ogg/cmake_install.cmake")
  include("/home/russellg/projects/gentlemanly_engine/embuild/deps/vorbis/cmake_install.cmake")
  include("/home/russellg/projects/gentlemanly_engine/embuild/deps/freetype2/cmake_install.cmake")
  include("/home/russellg/projects/gentlemanly_engine/embuild/deps/libRocket/Build/cmake_install.cmake")
  include("/home/russellg/projects/gentlemanly_engine/embuild/ge/cmake_install.cmake")
  include("/home/russellg/projects/gentlemanly_engine/embuild/modules/cmake_install.cmake")
  include("/home/russellg/projects/gentlemanly_engine/embuild/samples/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/russellg/projects/gentlemanly_engine/embuild/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
