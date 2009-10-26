foreach(example 

    monitor
    starvephil
    tennis
    condition
    mutex
    once
    recursive_mutex
    thread
    thread_group
    tss
    xtime)

  boost_add_executable(${example} DEPENDS boost_thread MULTI_THREADED)

endforeach()