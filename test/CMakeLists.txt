rock_testsuite(test_suite suite.cpp
                          ImageSonar_test.cpp
   DEPS vizkit3d_image_sonar
   LIBS ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY}
   DEPS_PKGCONFIG opencv vizkit3d_normal_depth_map)
