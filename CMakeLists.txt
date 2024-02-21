# Declare the minimum required CMake version
cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)

# Name the project
project(CanadianExperience)
set(APPLICATION_LIBRARY CanadianExperienceLib)
set(MACHINE_LIBRARY MachineLib)

# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})


# Fetch miniaudio from Github
include(FetchContent)
FetchContent_Declare(
        miniaudio
        GIT_REPOSITORY https://github.com/mackron/miniaudio.git
        GIT_TAG 1778a5e839514f35f41d31449f3573e3adffc51a # Version 0.11.10
)

FetchContent_MakeAvailable(miniaudio)

include_directories(${miniaudio_SOURCE_DIR})

# This sets the Mac icon for the program
set(MACOSX_BUNDLE_ICON_FILE CanadianExperienceIcon.icns)
set_source_files_properties(${MACOSX_BUNDLE_ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")


# Define a variable containing a list of source files for the project
set(SOURCE_FILES main.cpp CanadianExperienceApp.cpp CanadianExperienceApp.h pch.h resources/CanadianExperience.rc ${MACOSX_BUNDLE_ICON_FILE})



# Define the build target for the executable
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)


add_subdirectory(${MACHINE_LIBRARY})
add_subdirectory(Tests)
add_subdirectory(MachineTests)
add_subdirectory(MachineDemo)

# Copy resources into output directory
file(COPY resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${MACHINE_LIBRARY}/resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

if(APPLE)
    # When building for MacOS, also copy resources into the bundle resources
    set(RESOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Resources)
    file(COPY resources/ DESTINATION ${RESOURCE_DIR}/)
    file(COPY ${MACHINE_LIBRARY}/resources/ DESTINATION ${RESOURCE_DIR}/)
endif()

