add_executable(w00_heap_overflow heap_overflow.cpp)
add_executable(w00_signed_overflow signed_overflow.cpp)

add_test(NAME w00_sanity.heap_overflow COMMAND w00_heap_overflow)
set_tests_properties(w00_sanity.heap_overflow PROPERTIES WILL_FAIL TRUE)

add_test(NAME w00_sanity.signed_overflow COMMAND w00_signed_overflow)
set_tests_properties(w00_sanity.signed_overflow PROPERTIES WILL_FAIL TRUE)
