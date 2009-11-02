.. _install_customization:

Customizing the install
=======================

.. index:: CMAKE_INSTALL_PREFIX
   single:  installation

.. _cmake_install_prefix:

CMAKE_INSTALL_PREFIX
--------------------

  This is a standard cmake option that sets the path to which boost
  will be installed.

.. index:: LIB_SUFFIX
.. _lib_suffix:

LIB_SUFFIX
----------

  This defines the subdirectory of ``CMAKE_INSTALL_PREFIX`` to which
  libraries will be installed.  It is empty by default. For example,
  if I'm on 64-bit fedora, I want the libs installed to
  ``/usr/lib64``, I'd use::

    cmake ../src -DCMAKE_INSTALL_PREFIX=/usr -DLIB_SUFFIX=64

.. index:: INSTALL_VERSIONED
.. _install_versioned:

INSTALL_VERSIONED
-----------------

This variable controls whether boost versions will be mangled into the
paths into which boost is installed.  This option has effect only when
CMake is run the first time: they will be set as explained below the
first time thereafter not modified, so that the paths are customizable
by users.  (ie If you have configured a build and change this option,
it will have no effect, you must start "from scratch")

.. rubric:: Example

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
   
**Note:** ``lib/`` above will contain :ref:`LIB_SUFFIX` if set.

The relative lib and include pathnames can be controlled individually
with the following two variables:


.. index:: BOOST_LIB_INSTALL_DIR
.. _boost_lib_install_dir:

BOOST_LIB_INSTALL_DIR
---------------------

The directory to which libs will be installed under
:ref:`CMAKE_INSTALL_PREFIX`.  This variable will be forcibly modified
when :ref:`INSTALL_VERSIONED` is true.  The default is ``lib/``.



.. index:: BOOST_INCLUDE_INSTALL_DIR
.. _boost_include_install_dir:

BOOST_INCLUDE_INSTALL_DIR
-------------------------

The directory to which boost header files will be installed under
:ref:`CMAKE_INSTALL_PREFIX`.  This variable will be forcibly modified
when :ref:`INSTALL_VERSIONED` is true.  The default is ``include/``.


.. index:: BOOST_CMAKE_INFRASTRUCTURE_DIR
.. _boost_cmake_infrastructure_dir:

BOOST_CMAKE_INFRASTRUCTURE_DIR
------------------------------

This is a directory to which the targets from this boost install will
be exported, by default ``${CMAKE_INSTALL_PREFIX}/share/boost/cmake``:
this significanly eases detection of boost installations by CMake.
The name of the file is Boost-|version|.cmake.  See
:ref:`exported_targets` for more information about how users employ
this file.

.. index:: BOOST_INSTALL_FINDBOOST_CMAKE_DRIVERS
.. _boost_install_findboost_cmake_drivers:

BOOST_INSTALL_FINDBOOST_CMAKE_DRIVERS
-------------------------------------

There are two optional driver files that can be installed to
``BOOST_CMAKE_INFRASTRUCTURE_DIR``, named ``BoostConfig.cmake`` and
``BoostConfigVersion.cmake``.  These two files coordinate with
Boost-|version|.cmake to enable cmake developers who use both boost
and cmake to find local boost installations via the standard cmake
incantation::

  find_package(Boost 1.41.0 COMPONENTS thread iostreams)

These driver files should be the same from release to release.  

.. index:: BOOST_EXPORTS_FILE
.. _BOOST_EXPORTS_FILE:

BOOST_EXPORTS_FILE
------------------

This is the path to the file that will contain CMake exported targets
in the build tree, by default it is::

  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/Boost.cmake

See :ref:`exported_targets` for information on how to use this handy
file when building against an **uninstalled** boost.  *This variable
has no effect on installation.*

.. index:: BOOST_INSTALL_EXPORTS_FILE
.. _BOOST_INSTALL_EXPORTS_FILE:

BOOST_INSTALL_EXPORTS_FILE
--------------------------

This is the path to which the exports file (See
:ref:`BOOST_EXPORTS_FILE` will be installed.  By default it is::

  ${BOOST_LIB_INSTALL_DIR}/cmake

See :ref:`exported_targets` for information on how to use this handy
file to simply building against an **installed** boost.

