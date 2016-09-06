rock_library(vizkit3d_image_sonar
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(vizkit3d_image_sonar_bin Main.cpp
    DEPS vizkit3d_image_sonar)

