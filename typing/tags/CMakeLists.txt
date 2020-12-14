add_executable(tag_timer_policy timerPolicy.cpp)
target_link_libraries(tag_timer_policy PRIVATE doctest)
add_test(NAME "tag::timer-policy" COMMAND tag_timer_policy)

add_executable(tag_dispatch tag_dispatch.cpp)
target_link_libraries(tag_dispatch PRIVATE doctest)
add_test(NAME "tag::dispatch" COMMAND tag_dispatch)
