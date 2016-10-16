TITLE Compiling gentlemanly_engine dependencies for visual studio...

:: Get the location of the script
PUSHD "%~dp0" >NUL && SET scripts_dir=%CD% && POPD >NUL

:: Set some variables
SET ge_dir=%scripts_dir%/..
SET deps_dir=%ge_dir%/deps
SET build_dir=%deps_dir%/build
SET install_dir=%deps_dir%/install

cd %build_dir%
cmake .. -G"Unix Makefiles"
cmake --build . --target install
