include(FetchContent)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Android") 

else()
	include(cmake/NotMaintained/glad.cmake)
	include(cmake/NotMaintained/glfw.cmake)
endif()
