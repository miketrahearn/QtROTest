cmake_minimum_required(VERSION 3.24)

# --- START DEFENSIVE OVERLAY SETUP ---
set(LOCAL_QTRO_PATH "$ENV{HOME}/qt-sources/qtremoteobjects/install")

if(EXISTS "${LOCAL_QTRO_PATH}")
    message(STATUS "Defensive Setup: Enforcing local QtRemoteObjects overlay!")

    # 1. Force the directory path for the library configuration
    # (Adjust 'lib' to 'lib64' if your linux distro uses that, but usually 'lib' for local builds)
    set(Qt6RemoteObjects_DIR "${LOCAL_QTRO_PATH}/lib/cmake/Qt6RemoteObjects" CACHE PATH "Force Local QtRO" FORCE)

    # 2. Force the directory path for the tools (repc)
    set(Qt6RemoteObjectsTools_DIR "${LOCAL_QTRO_PATH}/lib/cmake/Qt6RemoteObjectsTools" CACHE PATH "Force Local QtRO Tools" FORCE)

    # 3. Prepend to prefix path just in case
    list(PREPEND CMAKE_PREFIX_PATH "${LOCAL_QTRO_PATH}")

else()
    message(STATUS "Using Standard System QtRemoteObjects")
endif()
# --- END DEFENSIVE OVERLAY SETUP ---
