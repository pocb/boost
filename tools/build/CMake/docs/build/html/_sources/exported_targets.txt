.. index:: targets, exported
.. index:: uninstalled tree, building against
.. _exported_targets:

Tricks for Building against Boost with CMake
============================================

Boost.CMake *exports* its targets, making developing independent
projects against an installed boost, or simply against a build tree
sitting on disk.  There are a variety of ways to use these to ease
configuration of boost in your external project.

You only need to do three things:

1.  Add the appropriate include directory.  This is either
    ``${``:ref:`CMAKE_INSTALL_PREFIX`\ ``}/include``, if installed, or the
    toplevel of the boost source directory if not.

2.  ``include`` the generated ``Boost.cmake`` file containing the
    exported targets.  In an installation, this file is in directory
    ``${``:ref:`CMAKE_INSTALL_PREFIX`\ ``}/lib/cmake/Boost.cmake`` [#libsuffix]_, and
    in a not-installed build tree it is located in
    ``${``:ref:`CMAKE_BINARY_DIR`\ ``}/lib/cmake/Boost.cmake``
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


.. index:: Building against uninstalled boost
.. _uninstalled:

With an uninstalled build
^^^^^^^^^^^^^^^^^^^^^^^^^

You only need to do three things:

1.  Add the appropriate include directory.  This is either
    ``${``:ref:`CMAKE_INSTALL_PREFIX`\ ``}/include``, if installed, or the
    toplevel of the boost source directory if not.

2.  ``include`` the generated ``Boost.cmake`` from the build tree
    containing the exported targets.  I is located in
    ``${``:ref:`CMAKE_BINARY_DIR`\ ``}/lib/cmake/Boost.cmake``

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

Since these are exported targets, CMake will add appropriate *rpaths*
as necessary; fiddling with ``LD_LIBRARY_PATH`` should not be
necessary.

Example
-------

There is an unpacked boost in ``/home/troy/boost-1.41.0/src`` and
built boost in directory ``/home/troy/boost/1.41.0/build``. I have a
program that builds from one file, ``main.cpp`` and uses boost
threads.  My ``CMakeLists.txt`` looks like this::

   include_directories("/home/troy/boost-1.41.0/src")
   include("/home/troy/boost-1.41.0/build/lib/cmake/Boost.cmake")

   add_executable(my_program main.cpp)
   target_link_libraries(my_program boost_thread-mt-shared-debug)

When I build, I see
(wrapped, and some output replaced with ... for brevity)::

  % make VERBOSE=1
  ...
  [100%] Building CXX object CMakeFiles/main.dir/main.cpp.o
  /usr/bin/c++ -I/home/troy/boost-1.41.0/src -o CMakeFiles/main.dir/main.cpp.o -c /home/troy/myproject/main.cpp
  ...
  linking CXX executable main
  /usr/bin/c++ -fPIC CMakeFiles/main.dir/main.cpp.o -o main -rdynamic /home/troy/boost-1.41.0/build/lib/libboost_thread-mt-d.so.1.41.0 -lpthread -lrt -Wl,-rpath,/home/troy/boost-1.41.0/build/lib 
  ...
  [100%] Built target main

With an installed boost
^^^^^^^^^^^^^^^^^^^^^^^

There is an easy way, and a hard way, depending on your your boost was
installed.  

The Easy Way
------------

If your boost was installed with
:ref:`BOOST_INSTALL_FINDBOOST_CMAKE_DRIVERS` on and an appropriate
:ref:`BOOST_CMAKE_INFRASTRUCTURE_DIR`, cmake's ``find_package`` will
find without setting any particular path::

  set(Boost_USE_MULTITHREADED ON)
  find_package(Boost 1.41.0 COMPONENTS thread NO_MODULE)

  include(${Boost_INCLUDE_DIR})
  add_executable(main main.cpp)
  target_link_libraries(main ${Boost_LIBRARIES})

.. rubric:: Note 

the ``NO_MODULE`` is required if your cmake is older than (FIXME,
currently required with all versions, modification to the
FindBoost.cmake distributed with cmake itself is required).

Here, having installed to ``/usr/local/boost-1.41.0``, I see::

  % make VERBOSE=1
  ...
  [100%] Building CXX object CMakeFiles/main.dir/main.cpp.o
  /usr/bin/c++    -I/usr/local/boost-1.41.0/include   -o CMakeFiles/main.dir/main.cpp.o -c /home/troy/Projects/boost/cmake/proj/main.cpp
  ...
  Linking CXX executable main
  /usr/bin/c++     -fPIC CMakeFiles/main.dir/main.cpp.o  -o main -rdynamic /usr/local/boost-1.41.0/lib/libboost_thread-mt-d.so.1.41.0 -lpthread -lrt -Wl,-rpath,/usr/local/boost-1.41.0/lib 
  ...
  [100%] Built target main

See also the documentation for ``FindBoost.cmake``.

The Somewhat harder way
-----------------------

If your boost installation does *not* come with the file installed
when :ref:`BOOST_INSTALL_FINDBOOST_CMAKE_DRIVERS`, you will need to
specify the path to the Boost.cmake file installed in
:ref:`BOOST_LIB_INSTALL_DIR <install_paths>` (try
``$CMAKE_INSTALL_PREFIX/lib/boost/cmake/Boost.cmake``


.. rubric:: Footnotes

.. [#libsuffix] If your distribution specifies a :ref:`LIB_SUFFIX`
   		(e.g. if it installs libraries to
   		``${``:ref:`CMAKE_INSTALL_PREFIX`\ ``/lib64``, you
   		will find `Boost.cmake` there.  If the installation is
   		'versioned', the ``Boost.cmake`` file may be in a
   		versioned subdirectory of lib, e.g. ``lib/boost-1.41.0``.
