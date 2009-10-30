.. _configure_and_build:

Configuring the buildspace
==========================

Configuration tools
-------------------

Included in the standard cmake distribution are the Windows `CMake`
gui and the unix `ccmake` curses interface, which allow one to
configure various aspects of the cmake build.  On Microsoft Windows
run the CMake configuration program from the Start menu.  

Having done the initial configuration step as in :ref:`quickstart`,
on unix run::

  make edit_cache

in the binary directory.  On windows just run the cmake gui and choose
the binary dir from the pulldown menu.  You will be presented with a list of editable build options something
like this::

   BOOST_PLATFORM                   linux 
   BUILD_BCP                        ON 
   BUILD_BOOST_WSERIALIZATION       ON 
   BUILD_EXAMPLES                   NONE 
   BUILD_INSPECT                    ON 
   BUILD_TESTS                      NONE 
   BUILD_VERSIONED                  OFF 
   CMAKE_BUILD_TYPE                 Release 
   CMAKE_INSTALL_PREFIX             /usr/local 
   DART_TESTING_TIMEOUT             15 
   DEBUG_COMPILE_FLAGS              -g 
   DOCBOOK_AUTOCONFIG               OFF 
   DOCBOOK_DTD_DIR                  DOCBOOK_DTD_DIR-NOTFOUND 
   DOCBOOK_XSL_DIR                  DOCBOOK_XSL_DIR-NOTFOUND 
   ENABLE_DEBUG                     ON 
   ENABLE_MULTI_THREADED            ON 
   ENABLE_RELEASE                   ON 
   ENABLE_SHARED                    ON 
   ENABLE_SINGLE_THREADED           OFF 
   ENABLE_STATIC                    ON 
   RELEASE_COMPILE_FLAGS            -O3 -DNDEBUG 
   UNZIP                            /usr/bin/unzip 
   XSLTPROC                         /usr/bin/xsltproc 
   XSLTPROC_FLAGS                   --xinclude 

On windows, the configurables will be right in the middle of the gui;
can't miss 'em.  Note the ``[t]`` key to toggle 'advanced mode' which
will show more options (on windows this is a selection box that says
``Simple View`` by default, pull it down to see Advanced and Grouped
views).

Use the arrow keys to select particular options.  Press :kbd:`c` (for
(c)onfigure) to perform the preliminary configuration of the CMake
build system when you are done.  When the options you have selected
have stabilized, CMake will give you the (g)enerate option. If you do
not see this option, press :kbd:`c` again to reconfigure.  Try the
:kbd:`t` key to see more options.  When you're done press :kbd:`g` to
generate makefiles and exit.

See :ref:`VARIANTS` for information about the feature-specific options
(ie ``ENABLE_whatever`` listed above.)

.. _cmakecache.txt:

CMakeCache.txt
==============

The same information is stored in a file `CMakeCache.txt` located in
the build directory.  For this reason, after you've done the initial
configuration of a build directory you can invoke `ccmake` like this::

  ccmake <path-to-build>

or have the makefiles do it for you::

  make edit_cache

The CMakeCache.txt file is hand-editable, though this is usually not
as convenient as the cmake-supplied configuration tools mentioned
above.  An excerpt of this file::

  //
  // Enable/Disable color output during build.
  //
  CMAKE_COLOR_MAKEFILE:BOOL=ON
  
  //
  // Use versioned library names, e.g., boost_filesystem-gcc41-1_34
  //
  BUILD_VERSIONED:BOOL=ON
  

On unix, (?windows too?) the generated makefiles will detect if this
file has been edited and will automatically rerun the makefile
generation phase.  If you should need to trigger this regeneration
manually you may execute ::

  make rebuild_cache

.. rubric:: Deleting the cache

You may find yourself wanting to start from scratch, for instance if
you want to switch from using Visual Studio to using NMake.  To do
this, **delete the cache file**.  On windows, there is a *Delete
Cache* option in the CMake gui's *File* menu.  On unix you can simply
``rm CMakeCache.txt``.

.. index:: CMAKE_BINARY_DIR
.. _CMAKE_BINARY_DIR:

CMAKE_BINARY_DIR
----------------

This variable is set by cmake and corresponds to the toplevel of your
``build/`` directory.


.. _useful_options:

A few useful options
--------------------

CMAKE_OSX_ARCHITECTURES
^^^^^^^^^^^^^^^^^^^^^^^

  *Mac OS X users*: to build universal binaries, set this to
   ``ppc;i386``.

.. index:: BUILD_VERSIONED
.. _build_versioned:

BUILD_VERSIONED
^^^^^^^^^^^^^^^

This option controls whether libraries will be built with mangled-in
compiler name/version and boost version.  For example, with
``BUILD_VERSIONED`` set to ``OFF``, the signals library looks like
this::

  % ls lib/*signals*
  lib/libboost_signals-mt-d.a    lib/libboost_signals-mt.a
  lib/libboost_signals-mt-d.so*  lib/libboost_signals-mt.so*
  
But with it on, (on a gcc 4.3 linux box)::

  % ls lib/*signal*
  lib/libboost_signals-gcc43-mt-1_40.a    
  lib/libboost_signals-gcc43-mt-d-1_40.a
  lib/libboost_signals-gcc43-mt-1_40.so*  
  lib/libboost_signals-gcc43-mt-d-1_40.so*
  
Historically this mangling has been more interesting to windows users
than unix users.

.. note:: The on-disk names of library :ref:`variants <variants>` are
   	  always mangled with the active :ref:`features <features>`.
   	  ``BUILD_VERSIONED`` affects mangling of compiler and boost
   	  version only.

``BUILD_VERSIONED`` does not affect the locations to which files are
installed.  For this see :ref:`INSTALL_VERSIONED`. 

.. index:: BUILD_PROJECTS
.. _BUILD_PROJECTS:

BUILD_PROJECTS
^^^^^^^^^^^^^^

This is a semicolon-separated list of projects to be built, or
``"ALL"`` (the default) for all projects, or ``"NONE"``.  Projects not
appearing in this list (if list not ``"ALL"``) are ignored; no targets in
this project will appear.  Example::

  BUILD_PROJECTS=thread;python

See also the :ref:`boost_library_project_macro` macro.  

.. note::

   If you specify a project with link time dependencies on other
   projects, e.g. ``filesystem``, (which depends on ``system``) and
   omit the dependencies, you will get an error from cmake something
   like this::

      CMake Error at tools/build/CMake/BoostCore.cmake:736 (get_property):
        get_property could not find TARGET boost_system-mt-shared.  Perhaps it has
        not yet been created.
      Call Stack (most recent call first):
        tools/build/CMake/BoostCore.cmake:1170 (boost_library_variant)
        libs/filesystem/src/CMakeLists.txt:7 (boost_add_library)


.. index:: BUILD_EXAMPLES
.. _BUILD_EXAMPLES:

BUILD_EXAMPLES
^^^^^^^^^^^^^^

This is a semicolon-separated list of projects whose examples should
be built, e.g.::

  BUILD_EXAMPLES=iostreams;accumulators

Per-library examples are specified with the :ref:`EXAMPLEDIRS`
argument to the :ref:`boost_library_project_macro` macro.

.. rubric:: Note:

A project's examples will only be built if the project appears in
**both** :ref:`BUILD_PROJECTS` and :ref:`BUILD_EXAMPLES`.  I.e., the
``BUILD_PROJECTS`` filter is applied first, and the ``BUILD_EXAMPLES``
filter has no ability to reverse the result. 

.. index:: BUILD_TOOLS
.. _BUILD_TOOLS:

BUILD_TOOLS
^^^^^^^^^^^

Similar to BUILD_EXAMPLES and BUILD_PROJECTS above, this is a
semicolon-separated list of tools (in subdirectory
``$BOOST_ROOT/tools/``) that should be built, e.g.::

  BUILD_TOOLS=quickbook;wave

``"ALL"`` will build all tools, ``"NONE"`` will build none.  Note that
the values here are lowercase (only subdirectories of ``tools/``
matching one of the strings in the list will be traversed by cmake).

Advanced options
----------------

``ccmake`` provides the keystroke option ``t`` which toggles advanced
mode.  Some of the useful options here are:

.. _verbosity:

.. index:: verbosity; CMAKE_VERBOSE_MAKEFILE

CMAKE_VERBOSE_MAKEFILE
^^^^^^^^^^^^^^^^^^^^^^

  Displays full build commands during build.  Good for debugging.
  This option will generate permanently verbose makefiles; it is
  generally easier to invoke make with the option ``VERBOSE=1``
  instead (this has the same effect, but for one build only).

.. index:: CMAKE_CXX_COMPILER

.. _cmake_cxx_compiler:

CMAKE_CXX_COMPILER
^^^^^^^^^^^^^^^^^^

  Sets the compiler.  If you have a nonstandard compiler and no
  default compiler, you may have to pass the value of this option on
  the commandline, for example::

    cmake ../src -DCMAKE_CXX_COMPILER=gcc-4.4

  On windows you can set this in the gui, but you will probably prefer
  to have cmake generate a set of nmake or project files by choosing
  an appropriate generator.

.. index:: BUILD_SOVERSIONED
.. index:: soversion
.. index:: soname
.. _build_with_soversion:

BUILD_SOVERSIONED
^^^^^^^^^^^^^^^^^

Enables the setting of SOVERSION in built libraries.  If
this is on::

  % ls -l libboost_thread*.so*
  lrwxrwxrwx 1 troy troy     30 Oct 29 18:37 libboost_thread-mt-d.so -> libboost_thread-mt-d.so.1.41.0*
  -rwxr-xr-x 1 troy troy 571361 Oct 29 18:37 libboost_thread-mt-d.so.1.41.0*
  lrwxrwxrwx 1 troy troy     28 Oct 29 18:37 libboost_thread-mt.so -> libboost_thread-mt.so.1.41.0*
  -rwxr-xr-x 1 troy troy 114963 Oct 29 18:37 libboost_thread-mt.so.1.41.0*
  
  % readelf -a libboost_thread-mt.so | grep SONAME
   0x000000000000000e (SONAME)             Library soname: [libboost_thread-mt.so.1.41.0]
      
and if off::

  % ls -l lib/*signals*
  -rwxr-xr-x 1 troy troy  835522 Oct 29 15:10 lib/libboost_signals-mt-d.so*
  -rwxr-xr-x 1 troy troy  121886 Oct 29 15:10 lib/libboost_signals-mt.so*
  
(Unix only, ``ON`` by default)


Options for customizing installation
------------------------------------

.. index:: CMAKE_INSTALL_PREFIX
   single:  installation

.. _cmake_install_prefix:

CMAKE_INSTALL_PREFIX
^^^^^^^^^^^^^^^^^^^^

  This is a standard cmake option that sets the path to which boost
  will be installed.

.. index:: LIB_SUFFIX
.. _lib_suffix:

LIB_SUFFIX
^^^^^^^^^^

  This defines the subdirectory of ``CMAKE_INSTALL_PREFIX`` to which
  libraries will be installed.  It is empty by default. For example,
  if I'm on 64-bit fedora, I want the libs installed to
  ``/usr/lib64``, I'd use::

    cmake ../src -DCMAKE_INSTALL_PREFIX=/usr -DLIB_SUFFIX=64

.. index:: INSTALL_VERSIONED
.. _install_versioned:

INSTALL_VERSIONED
^^^^^^^^^^^^^^^^^

This variable controls whether boost versions will be mangled into the
names of **directories** into which boost is installed.  This is
different than :ref:`BUILD_VERSIONED`.  This option has effect only
when CMake is run the first time: they will be set as explained below
the first time thereafter not modified (so that they are customizable
by users).

Example
"""""""

For boost version 1.41.0, with this option ON, the installation tree
is::

  $CMAKE_INSTALL_PREFIX/
    include/
      boost-1.41.0/
        boost/
          version.hpp 
          ...
    lib/    
      boost-1.41.0/
        libboost_signals-mt-d.so
        ...
    bin/
      boost-1.41.0/
        wave
        quickbook 
        ...

and without it, ::

  $CMAKE_INSTALL_PREFIX/
    include/
      boost/
        version.hpp 
        ...
    lib/
      boost/
        libboost_signals-mt-d.so
        ...
    bin/
      wave
      quickbook 
      ...
   
**Note:** ``lib/`` above will contain :ref:`LIB_SUFFIX` if set.

The relative lib/bin/executable pathnames can be controlled
individually with the following variables:

.. index:: install paths
.. _install_paths:
.. _boost_lib_install_dir:
.. _boost_include_install_dir:
.. _boost_exe_install_dir:

============================  =================== ================================
Variable                      Default Unversioned Default Versioned
============================  =================== ================================
BOOST_INCLUDE_INSTALL_DIR     include/            include/boost-X.YY.ZZ
BOOST_LIB_INSTALL_DIR         lib${LIB_SUFFIX}    lib${LIB_SUFFIX}/boost-X.YY.ZZ
BOOST_EXE_INSTALL_DIR         bin/                bin/boost-X.YY.ZZ
============================  =================== ================================

The versioned bin/ path is kind of ugly, see :ref:`BUILD_TOOLS` to
disable the build of these utilities.

.. index:: BOOST_CMAKE_INFRASTRUCTURE_DIR
.. _boost_cmake_infrastructure_dir:

BOOST_CMAKE_INFRASTRUCTURE_DIR
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is a directory **outside** the boost install tree, by default
``/usr/share/boost/cmake``, to which the targets from this boost
install will be exported: this significanly eases detection of boost
on the systems by developers who use both Boost and CMake.  The name
of the file is Boost-|version|.cmake.  See :ref:`exported_targets` for
more information about how users employ this file.

.. index:: BOOST_INSTALL_FINDBOOST_CMAKE_DRIVERS
.. _boost_install_findboost_cmake_drivers:

BOOST_INSTALL_FINDBOOST_CMAKE_DRIVERS
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There are two optional driver files that can be installed to
``BOOST_CMAKE_INFRASTRUCTURE_DIR``, named ``BoostConfig.cmake`` and
``BoostConfigVersion.cmake``.  These two files coordinate with
Boost-|version|.cmake to enable cmake developers to find boost
installations via the standard cmake incantation::

  find_package(Boost 1.41.0 COMPONENTS thread iostreams)

in their ``CMakeLists.txt``.  These files should be the same from
release to release, so you may wish to disable their installation.

.. index:: BOOST_EXPORTS_FILE
.. _BOOST_EXPORTS_FILE:

BOOST_EXPORTS_FILE
^^^^^^^^^^^^^^^^^^

This is the path to the file that will contain CMake exported targets
in the build tree, by default it is::

  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/Boost.cmake

See :ref:`exported_targets` for information on how to use this handy
file to simply building against an **uninstalled** boost.

.. index:: BOOST_INSTALL_EXPORTS_FILE
.. _BOOST_INSTALL_EXPORTS_FILE:

BOOST_INSTALL_EXPORTS_FILE
^^^^^^^^^^^^^^^^^^^^^^^^^^

This is the path to which the exports file will be installed (only has
effect when making 'install').  By default it is::

  ${BOOST_LIB_INSTALL_DIR}/cmake

See :ref:`exported_targets` for information on how to use this handy
file to simply building against an **installed** boost.

System Dependencies
-------------------

See :ref:`external_dependencies` for information about configuring
detection of system packages like python and bzip2.
