### Application binary

include_directories(
  /usr/include/zbar
)

set(tagger_SRCS
  main.cpp
  qrcodereader.cpp
  qrcodegenerator.cpp
  qrcodeimageprovider.cpp
  client.cpp
)

add_executable(tagger ${tagger_SRCS})
qt5_use_modules(tagger Gui Quick Qml)
target_link_libraries(tagger -lzbar -lqrencode)
install(TARGETS tagger RUNTIME DESTINATION ".")

set(DESKTOP_FILE "tagger.desktop")
configure_file(${DESKTOP_FILE}.in ${CMAKE_CURRENT_BINARY_DIR}/${DESKTOP_FILE})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${DESKTOP_FILE} DESTINATION ${DESKTOP_DIR})


add_subdirectory(qml)
if(NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
add_custom_target(tagger-qmlfiles ALL
    COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/qml ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${QMLFILES}
)
endif(NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")


