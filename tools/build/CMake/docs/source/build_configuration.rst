.. _configure_and_build:

Configuring the buildspace
===========================

Setting the compiler
--------------------

See :ref:`setting_the_compiler` below.

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

.. _useful_options:

A few useful options
--------------------

CMAKE_OSX_ARCHITECTURES
^^^^^^^^^^^^^^^^^^^^^^^

  *Mac OS X users*: to build universal binaries, set this to
   ``ppc;i386``.

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

In addition, with ``BUILD_VERSIONED`` on, the install destination for
header files will contain a subdirectory containing ``boost-VERSION``.
For example, on boost 1.40.0 with ``BUILD_VERSIONED`` ON, and a
default ``CMAKE_INSTALL_PREFIX`` of ``/usr/local``, headers are
installed to::

  /usr/local/include/boost-1_40/boost/...

and with ``BUILD_VERSIONED`` set to ``OFF``, the ``boost-1_40``
segment is omitted::

  /usr/local/include/boost/...

Advanced options
----------------

``ccmake`` provides the keystroke option ``t`` which toggles advanced
mode.  Some of the useful options here are:

.. _verbosity:

.. index:: verbosity

CMAKE_VERBOSE_MAKEFILE
^^^^^^^^^^^^^^^^^^^^^^

  Displays full build commands during build.  Good for debugging.
  This option will generate permanently verbose makefiles; it is
  generally easier to invoke make with the option ``VERBOSE=1``
  instead (this has the same effect, but for one build only).

.. index:: CMAKE_CXX_COMPILER; compiler, setting

.. _setting_the_compiler:

CMAKE_CXX_COMPILER
^^^^^^^^^^^^^^^^^^

  Sets the compiler.  If you have a nonstandard compiler and no
  default compiler, you may have to pass the value of this option on
  the commandline, for example::

    cmake ../src -DCMAKE_CXX_COMPILER=gcc-4.4

  On windows just set it in the gui.

Options for customizing installation
------------------------------------

CMAKE_INSTALL_PREFIX
^^^^^^^^^^^^^^^^^^^^

This is a standard cmake option that sets the path to which boost will
be installed.

BOOST_INSTALL_LIB_SUBDIR_NAME
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This defines the subdirectory of ``CMAKE_INSTALL_PREFIX`` to which
libraries will be installed.  The default is ``lib``. For example, if
I'm on 64-bit fedora, I want the libs installed to ``/usr/lib64``, I'd
use:: 

  cmake ../src -DCMAKE_INSTALL_PREFIX=/usr -DBOOST_INSTALL_LIB_SUBDIR_NAME=lib64





