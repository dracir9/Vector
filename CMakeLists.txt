if(COMMAND idf_component_register)
  idf_component_register(
    SRCS "mat_mult.S" "Mat4.cpp" "Mat3.cpp" "Vector.cpp"
    INCLUDE_DIRS "include"
  )
else()
  message(STATUS "idf_component_register not available; using non-ESP-IDF fallback")
  add_library(Vector STATIC
    mat_mult.S
    Mat4.cpp
    Mat3.cpp
    Vector.cpp
  )
  target_include_directories(Vector PUBLIC include)
endif()