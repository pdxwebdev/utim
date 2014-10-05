project(tagger C CXX)
cmake_minimum_required(VERSION 2.8.9)

#do not remove this line, its required for the correct functionality of the Ubuntu-SDK
set(UBUNTU_MANIFEST_PATH "manifest.json.in" CACHE INTERNAL "Tells QtCreator location and name of the manifest file")
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Qt5Core)
find_package(Qt5Qml)
find_package(Qt5Quick)
#find_package(ubuntu-sdk-libs)

#automatically create moc files
set(CMAKE_AUTOMOC ON)

# components PATH
execute_process(
    COMMAND dpkg-architecture -qDEB_HOST_MULTIARCH
    OUTPUT_VARIABLE ARCH_TRIPLET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(QT_IMPORTS_DIR "lib/${ARCH_TRIPLET}")

set(APP_NAME          tagger)

#set install paths
set(CMAKE_INSTALL_PREFIX /usr/share/tagger-app/)
set(DATA_DIR /usr/share/tagger-app/)
set(DESKTOP_DIR ${DATA_DIR})

#This command figures out the target architecture and puts it into the manifest file
execute_process(
  COMMAND dpkg-architecture -qDEB_HOST_ARCH
  OUTPUT_VARIABLE CLICK_ARCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(CMAKE_BINARY_DIR /home/phablet/tagger/build)
execute_process(
  COMMAND cp
  /usr/lib/libzbar.so.0
  /usr/lib/arm-linux-gnueabihf/libqrencode.so
  /usr/lib/arm-linux-gnueabihf/libqrencode.so.3
  /usr/lib/arm-linux-gnueabihf/libqrencode.so.3.4.3
  ${CMAKE_BINARY_DIR}
)

configure_file(manifest.json.in ${CMAKE_CURRENT_BINARY_DIR}/manifest.json)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/manifest.json
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(DIRECTORY "app/graphics" DESTINATION ${DATA_DIR})
install(FILES "tagger.apparmor" DESTINATION ${DATA_DIR})
install(PROGRAMS "app/tagger-wrapper" DESTINATION ${DATA_DIR})
install(FILES
  "${CMAKE_BINARY_DIR}/libzbar.so.0"
  "${CMAKE_BINARY_DIR}/libqrencode.so"
  "${CMAKE_BINARY_DIR}/libqrencode.so.3"
  "${CMAKE_BINARY_DIR}/libqrencode.so.3.4.3"
DESTINATION lib)

add_subdirectory(app)

#no op custom target for all not compiled files, so they show up in the QtCreator project tree
add_custom_target("tagger_ClickFiles" ALL SOURCES "tagger.apparmor" "manifest.json.in")

