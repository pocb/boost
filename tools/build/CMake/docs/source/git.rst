.. _testing:

Hacking Alt.Boost.CMake with Git
================================

Boost-cmake, in addition to using an alternative build system, uses
alternate version control.  This makes boost.cmake feasable: without
distributed version control it would be very difficult to maintain a
build system against upstream boost.

This document will review some common version-control procedures for
those who are unfamiliar with git.  More documentation is available at
`Hacking Boost via Git
<http://gitorious.org/boost/git-docs/blobs/raw/master/build/html/index.html>`_.


The first step is to get `Git <http://git-scm.com>`_.  Any recent
version will do.  On windows, git downloads come with a bash shell, so
the commandline interface is essentially identical.  There is also
`TortoiseGit <http://code.google.com/p/tortoisegit/>`_, which is
evolving quickly and quite usable.

Scenarios and associated howtos
-------------------------------

I just want to try the HEAD of the <whatever> branch
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Pick some directory to work in.  Here I'll use ``/tmp``.  Clone the
repository to a subdirectory called ``src``::

  git clone git://gitorious.org/boost/cmake.git src
  Initialized empty Git repository in /tmp/src/.git/
  remote: Counting objects: 425396, done.
  remote: Compressing objects: 100% (129689/129689), done.
  remote: Total 425396 (delta 298454), reused 419119 (delta 292368)
  Receiving objects: 100% (425396/425396), 135.56 MiB | 1260 KiB/s, done.
  Resolving deltas: 100% (298454/298454), done.
  Checking out files: 100% (23865/23865), done.
  
inside this directory you'll see the branch that is checked out::

  % cd src       
  % git branch -l
  * 1.41.0
  
This means I'm on the ``1.41.0`` branch, and the files are checked
out::

  % ls
  CMakeLists.txt     boost/           bootstrap.sh*  libs/    tools/
  CTestConfig.cmake  boost-build.jam  build/         more/    wiki/
  INSTALL            boost.css        doc/           people/
  Jamroot            boost.png        index.htm      rst.css
  LICENSE_1_0.txt    bootstrap.bat    index.html     status/

Now you can go ahead and do your out-of-source build.  Now, say you
find a problem
