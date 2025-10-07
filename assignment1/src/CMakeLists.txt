# 建立 sample_lib：若該目錄只有 header（header-only）會建立 INTERFACE，若有 .cpp 則建立實體 library
file(GLOB_RECURSE SRC_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

if(SRC_SOURCES)
  add_library(sample_lib ${SRC_SOURCES})
  target_include_directories(sample_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_compile_features(sample_lib PUBLIC cxx_std_20)
else()
  add_library(sample_lib INTERFACE)
  target_include_directories(sample_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# 若有 main.cpp，建立可執行檔（可選）
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
  add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
  target_link_libraries(main PRIVATE sample_lib)
  target_compile_features(main PRIVATE cxx_std_20)
endif()