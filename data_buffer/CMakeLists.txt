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

add_executable(databuffer_test_runner)

target_compile_features(databuffer_test_runner PUBLIC c_std_11)
set_target_properties(databuffer_test_runner PROPERTIES C_EXTENSIONS OFF)
#target_compile_definitions(rdatabuffer_test_runner r
#  PRIVATE
#    $<$<PLATFORM_ID:CYGWIN,Linux,MSYS>:_POSIX_C_SOURCE=200112L>
#)
target_sources(
  databuffer_test_runner
  PUBLIC
    databuffer_test_runner.c
)

target_include_directories(
  databuffer_test_runner
  PRIVATE
    "${DataBuffer_BINARY_DIR}"
    "${DataBuffer_SOURCE_DIR}"
)

target_link_libraries(
    databuffer_test_runner
    PRIVATE
	databuffer
	unity::framework
)
