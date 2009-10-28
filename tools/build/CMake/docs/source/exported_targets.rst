.. index:: variants
.. index:: features

.. _VARIANTS:
.. _features:

Developing with Boost.CMake
===========================

Boost.CMake *exports* its targets, making developing independent
projects against an installed boost, or simply against a build tree
sitting on disk.

You only need to do three things:

1.  Add the appropriate include directory.  This is either
    ``${``:ref:`CMAKE_INSTALL_PREFIX`\ ``}/include``, if installed, or the
    toplevel of the boost source directory if not.
2.  ``include`` the generated ``Boost.cmake`` file containing the
    exported targets.  In an installation, this file is in directory
    ``${``:ref:`CMAKE_INSTALL_PREFIX`\ ``}/lib/Boost.cmake`` [#libsuffix]_, and
    in a not-installed build tree it is located in
    ``${``:ref:`CMAKE_BINARY_DIR`\ ``}/lib/Boost.cmake``
3.  Tell cmake about your link dependencies with
    ``target_link_libraries``.  Note that you use the **names of the
    cmake targets**, not the shorter names that the libraries have on
    disk.   ``make help`` shows a list::

       % make help | grep signals
       ... boost_signals
       ... boost_signals-mt-shared
       ... boost_signals-mt-shared-debug
       ... boost_signals-mt-static
       ... boost_signals-mt-static-debug
              
    See also :ref:`fixme` for details on the naming conventions.

Examples
--------

With an uninstalled build
^^^^^^^^^^^^^^^^^^^^^^^^^

There is an unpacked boost in ``/home/troy/boost-1.41.0/src`` and
built boost in directory ``/home/troy/boost/1.41.0/build`` ::, you
need do only two things to build your code against the build tree.  I
have a program that builds from one file, ``main.cpp``.  My ``CMakeLists.txt``::

   include_directories("/home/troy/boost-1.41.0/src")
   include("/home/troy/boost-1.41.0/build/Boost.cmake")

   add_executable(my_program main.cpp)
   target_link_libraries(my_program boost_thread-mt-shared-debug)

When you build, you'll see
(wrapped, and some output replaced with ... for brevity)::

  % make VERBOSE=1
  ...
  [100%] Building CXX object CMakeFiles/main.dir/main.cpp.o
  /usr/bin/c++ -I/home/troy/boost-1.41.0/src -o CMakeFiles/main.dir/main.cpp.o -c /home/troy/myproject/main.cpp
  ...
  Linking CXX executable main
  /usr/bin/c++ -fPIC CMakeFiles/main.dir/main.cpp.o -o main -rdynamic /home/troy/boost-1.41.0/build/lib/libboost_thread-mt-d.so.1.41.0 -Wl,-rpath,/home/troy/boost-1.41.0/build/lib 
  ...
  [100%] Built target main

  
With an installed boost
^^^^^^^^^^^^^^^^^^^^^^^

Here, I've installed boost to ``/usr/local/boost-1.41.0`` ::

  include(/usr/local/boost-1.41.0/lib/Boost.cmake)
  include_directories(/usr/local/boost-1.41.0/include)
  
  add_executable(main main.cpp)
  
  target_link_libraries(main boost_thread-mt-shared-debug)

And I see ::

  % make VERBOSE=1
  ...
  [100%] Building CXX object CMakeFiles/main.dir/main.cpp.o
  /usr/bin/c++    -I/usr/local/boost-1.41.0/include   -o CMakeFiles/main.dir/main.cpp.o -c /home/troy/Projects/boost/cmake/proj/main.cpp
  ...
  Linking CXX executable main
  /usr/bin/c++     -fPIC CMakeFiles/main.dir/main.cpp.o  -o main -rdynamic /usr/local/boost-1.41.0/lib/libboost_thread-mt-d.so.1.41.0 -lpthread -lrt -Wl,-rpath,/usr/local/boost-1.41.0/lib 
  ...
  [100%] Built target main


.. rubric:: Footnotes

.. [#libsuffix] If your distribution specifies a :ref:`LIB_SUFFIX` (e.g. if 
   		it installs libraries to
   		``${``:ref:`CMAKE_INSTALL_PREFIX`\ ``/lib64``, you will find
   		`Boost.cmake` there.
