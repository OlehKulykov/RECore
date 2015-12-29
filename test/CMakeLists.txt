#
#   Copyright (c) 2012 - 2015 Kulykov Oleh <info@resident.name>
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in
#   all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#   THE SOFTWARE.
#

include(CheckLibraryExists)

include_directories(${PROJECT_BINARY_DIR})

include_directories(${PROJECT_BINARY_DIR})

link_directories(${PROJECT_BINARY_DIR})

remove_definitions(-DCMAKE_BUILD)

add_executable(test_recore_swap test_recore_swap.cpp)
target_link_libraries(test_recore_swap RECore)
add_test(test_recore_swap test_recore_swap)


add_executable(test_recore_allocator test_recore_allocator.cpp)
target_link_libraries(test_recore_allocator RECore)
add_test(test_recore_allocator test_recore_allocator)


add_executable(test_recore_stringsplit test_recore_stringsplit.cpp)
target_link_libraries(test_recore_stringsplit RECore)
add_test(test_recore_stringsplit test_recore_stringsplit)


add_executable(test_recore_rerandomizer test_recore_rerandomizer.cpp)
target_link_libraries(test_recore_rerandomizer RECore)
add_test(test_recore_rerandomizer test_recore_rerandomizer)


add_executable(test_recore_strings test_recore_strings.cpp)
target_link_libraries(test_recore_strings RECore)
add_test(test_recore_strings test_recore_strings)


add_executable(test_recore_int24 test_recore_int24.cpp)
target_link_libraries(test_recore_int24 RECore)
add_test(test_recore_int24 test_recore_int24)


add_executable(test_recore_json test_recore_json.cpp)
target_link_libraries(test_recore_json RECore)
add_test(test_recore_json test_recore_json)


add_executable(test_recore_uuidv4 test_recore_uuidv4.cpp)
target_link_libraries(test_recore_uuidv4 RECore)
add_test(test_recore_uuidv4 test_recore_uuidv4)


add_executable(test_recore_filepaths test_recore_filepaths.cpp)
target_link_libraries(test_recore_filepaths RECore)
add_test(test_recore_filepaths test_recore_filepaths)


add_executable(test_recore_lzma2 test_recore_lzma2.cpp)
target_link_libraries(test_recore_lzma2 RECore)
add_test(test_recore_lzma2 test_recore_lzma2)


#install(TARGETS test_recore_rerandomizer DESTINATION bin)
#install(TARGETS test_recore_uuidv4 DESTINATION bin)

