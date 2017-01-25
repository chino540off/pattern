#! /bin/bash

function build()
{
  if [ -d build ]; then
          rm -rf build
  fi

  mkdir build
  cd build
  cmake .. -DCMAKE_BUILD_TYPE=Debug
  make
}

function test()
{
  cd build

  lcov --zerocounters --directory .
  lcov --capture --initial --directory . --output-file app

  ctest

  lcov --no-checksum --directory . --capture --output-file app.info
  genhtml app.info -o genhtml
}

$1
