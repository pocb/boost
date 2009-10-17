.. boost-cmake documentation master file, created by
   sphinx-quickstart on Mon May 11 08:53:19 2009.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. _quickstart:

Quickstart
==========

This page describes how to configure and build Boost with CMake. By
following these instructions, you should be able to get CMake,
configure a Boost build tree to your liking with CMake, and then
build, install, and package Boost libraries.

Download CMake
--------------

You can get it here:  http://www.cmake.org/HTML/Download.html

There are precompiled binaries for CMake on several different
platforms. The installation of these pre-compiled binaries is mostly
self-explanatory. If you need to build your own copy of CMake, please
see the `CMake installation instructions
<http://www.cmake.org/HTML/Install.html>`_.  

Check out the code
------------------

The code associated with these docs is available at
http://gitorious.org/boost/cmake with tag |version|.  You can clone
the repository locally and then check out the tag.  Tarballs and
zipfiles corresponding to these tags are avaiable at
http://sodium.resophonic.com/boost-cmake.

In these instructions, we will do things such that the Boost source
tree (with CMake build files) is available in the directory
``$BOOST/src`` and that the build will happen in ``$BOOST/build``::

  $BOOST/
    src/     # (source checked out to here)
    build/   # (build output here) 

Note that it is *not* actually necessary to set any environment
variable ``BOOST``, this is a convention used in this document.
 
On Unix
-------

Create and change to the directory that will hold the binaries that
CMake build::

  mkdir $BOOST/build 
  cd $BOOST/build

Configure
^^^^^^^^^

Run the CMake configuration program, providing it with the Boost
source directory::

  cmake -DCMAKE_INSTALL_PREFIX=/somewhere $BOOST/src 

(``CMAKE_INSTALL_PREFIX`` defaults to ``/usr/local``).  You'll see output
from ``cmake``.  It looks somewhat like this::

  -- Check for working C compiler: /usr/bin/gcc
  -- Check for working C compiler: /usr/bin/gcc -- works
  -- Check size of void*
  -- Check size of void* - done
  -- Check for working CXX compiler: /usr/bin/c++
  -- Check for working CXX compiler: /usr/bin/c++ -- works
  -- Scanning subdirectories:
  --  + io
  --  + any
  --  + crc
  --  + mpl
  
    (etc, etc)
  
  --  + program_options
  --  + ptr_container
  --  + type_traits
  -- Configuring done
  -- Generating done
  -- Build files have been written to: $BOOST/build

The directory ``$BOOST/build`` should now contain a bunch of generated
files, including a top level ``Makefile``, something like this::

  % ls
  CMakeCache.txt           CPackConfig.cmake    Makefile  
  cmake_install.cmake      libs/                CMakeFiles/     
  CPackSourceConfig.cmake  bin/                 lib/

Build and Install
^^^^^^^^^^^^^^^^^

Now build and install boost::

  make install

You'll see::

  Scanning dependencies of target boost_date_time-mt-shared
  [  0%] Building CXX object libs/date_time/src/CMakeFiles/boost_date_time-mt-shared.dir/gregorian/greg_month.cpp.o
  [  0%] Building CXX object libs/date_time/src/CMakeFiles/boost_date_time-mt-shared.dir/gregorian/greg_weekday.cpp.o
  [  1%] Building CXX object libs/date_time/src/CMakeFiles/boost_date_time-mt-shared.dir/gregorian/date_generators.cpp.o
  Linking CXX shared library ../../../lib/libboost_date_time-mt.so
  [  1%] Built target boost_date_time-mt-shared

  (etc etc)

  [100%] Built bcp

  (etc etc)

  -- Installing: /tmp/flanboost/lib/libboost_wave-mt-d.a
  -- Installing: /tmp/flanboost/lib/libboost_wave-mt-d.so
  -- Removed runtime path from "/tmp/flanboost/lib/libboost_wave-mt-d.so"
  -- Installing: /tmp/flanboost/bin/bcp
  -- Installing: /tmp/flanboost/bin/inspect

And you're done. Once the build completes (which make take a while, if
you are building all of the Boost libraries), the Boost libraries will
be in a predictable layout under the directory passed to
``CMAKE_INSTALL_PREFIX`` (default ``/usr/local``)

On Windows
----------

Configure
^^^^^^^^^

Run CMake by selecting it from the Start menu. 

* Use the *Browse...* button to point CMake at the Boost source code
  in ``$BOOST\src``.
* Use the second *Browse...* button to select the directory where
  Boost will build binaries, ``$BOOST\build``.
* Click *Configure* a first time to configure Boost, which will
  search for various libraries on your system and prepare the build.
* CMake will ask you what kind of project files or make files to
  build. If you're using Microsoft Visual Studio, select the
  appropriate version to generate project files. Otherwise, you can
  use Borland's make files, generate NMake files, etc.
* You will then be given the opportunity to tune build options in
  the CMake GUI (see also :ref:`configure_and_build`. These options
  will affect what libraries are built and how.  They will initially
  appear red.  Click *Configure* again when you are done editing
  them.  You may wish to configure ``CMAKE_INSTALL_PREFIX`` at this
  time. 
* Finally, click *OK* to generate project files.

Build
^^^^^

If you have generated project files for Microsoft Visual Studio, you
will need to start up Visual Studio to build Boost. Once Visual Studio
has loaded, load the solution or project ``Boost`` from the Boost build
directory you set in the CMake configuration earlier. Then, just click
*Build* to build all of Boost.

Install
^^^^^^^

The installation of Boost's headers and compiled libraries uses the
same tools as building the library. With Microsoft Visual Studio, just
load the Boost solution or project and build the 'INSTALL' target to
perform the installation. 

