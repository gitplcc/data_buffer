add_library(databuffer)

target_compile_features(databuffer PUBLIC c_std_11)
set_target_properties(databuffer PROPERTIES C_EXTENSIONS OFF)
#target_compile_definitions(databuffer
#  PRIVATE
#    $<$<PLATFORM_ID:CYGWIN,Linux,MSYS>:_POSIX_C_SOURCE=200112L>
#)
target_sources(
  databuffer
  PUBLIC
    data_buffer.c
)

target_include_directories(
  databuffer
  PRIVATE
    "${DataBuffer_BINARY_DIR}"
    "${DataBuffer_SOURCE_DIR}"
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(
  databuffer
  PRIVATE
  $<$<PLATFORM_ID:Windows>:Ws2_32 Wlanapi>
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_executable(test_runner)
  target_compile_features(test_runner PUBLIC c_std_11)
  set_target_properties(test_runner PROPERTIES C_EXTENSIONS OFF)
  #target_compile_definitions(rdatabuffer_test_runner r
  #  PRIVATE
  #    $<$<PLATFORM_ID:CYGWIN,Linux,MSYS>:_POSIX_C_SOURCE=200112L>
  #)
  target_sources(
    test_runner
    PUBLIC
      test_runner.c
      dbuf_empty_testcase.c
      dbuf_full_testcase.c
  )
  target_include_directories(
    test_runner
    PRIVATE
      "${DataBuffer_BINARY_DIR}"
      "${DataBuffer_SOURCE_DIR}"
  )
  target_link_libraries(
      test_runner
      PRIVATE
        databuffer
        unity::framework
  )
  add_test(NAME data_buffer_test COMMAND test_runner)
endif()
