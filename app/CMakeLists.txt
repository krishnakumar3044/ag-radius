message("Building agrcbin")

#add_subdirectory(src/agrclib)

message("CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

# Add "access-gateway-radius-client-lib" library
add_library(access-gateway-radius-client-lib SHARED "")

message("Building access-gateway-radius-client-lib")

# Add target sources
target_sources(
    access-gateway-radius-client-lib
    PRIVATE
    	${CMAKE_CURRENT_LIST_DIR}/src/agrclib/AccessGatewayRadiusClient.cpp
	#${CMAKE_CURRENT_LIST_DIR}/AccessGatewayRadiusClient.cpp
    PUBLIC
    	${CMAKE_CURRENT_LIST_DIR}/include/AccessGatewayRadiusClient.h
	)

# Add include directories
target_include_directories(
	access-gateway-radius-client-lib
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	)

message("Before: CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")
set(CMAKE_LIBRARY_PATH "/usr/local/lib" ${CMAKE_LIBRARY_PATH})
message("After: CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")
#set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/user/home2")

unset(RADCLI_SEARCH_RESULT)
find_library(RADCLI_SEARCH_RESULT radcli REQUIRED)
message("RADCLI_SEARCH_RESULT: ${RADCLI_SEARCH_RESULT}")

# Create access-gateway-radius-client-lib by linking to radcli
target_link_libraries(access-gateway-radius-client-lib PUBLIC radcli)

# Add executable (for testing) using the access-gateway-radius-client-lib
add_executable (agrcbin src/main.cpp)
target_link_libraries(agrcbin access-gateway-radius-client-lib)

install (FILES ${CMAKE_CURRENT_LIST_DIR}/include/AccessGatewayRadiusClient.h
	 DESTINATION include  
	 PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE WORLD_EXECUTE WORLD_READ  
	 )

install (TARGETS access-gateway-radius-client-lib  
	 DESTINATION lib
	 PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE WORLD_EXECUTE WORLD_READ  
	 )
