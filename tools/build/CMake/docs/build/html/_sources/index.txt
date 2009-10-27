.. boost-cmake documentation master file, created by
   sphinx-quickstart on Mon May 11 08:53:19 2009.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.


Boost-CMake |version|
=====================

Boost.\ `CMake <http://www.cmake.org>`_ is an alternate
build system for boost, under development since boost version 1.35.
As of Boost version 1.38, boost.cmake can reliably build and
package boost.  

.. index:: Mailing List, IRC

**boost-cmake mailing list**    
  http://lists.boost.org/mailman/listinfo.cgi/boost-cmake      
**IRC**             
  ``#boost-cmake`` on the `freenode network <http://freenode.net>`_
**CMake/CTest regression testing of boost**
  http://www.cdash.org/CDashPublic/index.php?project=Boost
**CMake home page** 
  http://www.cmake.org

Users's guide
=============

.. toctree::
   :maxdepth: 3

   quickstart
   build_configuration
   build_variants
   testing
   individual_libraries
   add_boost_library
   add_compiled_library
   adding_regression_tests
   build_installer
   external_dependencies
   notes_by_version

.. modularize_library

Reference
=========

.. toctree::
   :maxdepth: 1

   reference/boost_library_project
   reference/boost_module
   reference/boost_add_library
   reference/boost_add_executable
   reference/boost_additional_test_dependencies
   reference/boost_test_compile
   reference/boost_test_compile_fail
   reference/boost_test_run
   reference/boost_test_run_fail

About this documentation
========================

This documentation was created with `Sphinx
<http://sphinx.pocoo.org>`_.  

The source is in the restructuredtext files in subdirectory
``tools/build/CMake/docs/source/``.  Hack on them (see the
`documentation for Sphinx <http://sphinx.pocoo.org/contents.html>`_).
When you're ready to see the html::

  make html

Once you've written a ton of docs, push them someplace where I can see
them (or use ``git diff`` to send a patch).

Release checklist
=================

* Update ``BOOST_CMAKE_VERSION`` in toplevel ``CMakeLists.txt``
* Update notes by version in ``tools/build/CMake/docs/notes_by_version.rst``
* Reconfig cmake with ``BOOST_MAINTAINER`` set to ON
* Rebuild docs and commit
* Tag commit with ``BOOST_CMAKE_VERSION``
* ``make do-release``

Index
=====

:ref:`genindex`


