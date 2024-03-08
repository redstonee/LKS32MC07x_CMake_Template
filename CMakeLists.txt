cmake_minimum_required(VERSION 3.20)

# Set the toolchain location if using Windows
set(TOOLCHAIN_PREFIX "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/13.2 Rel1")

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/toolchain-arm-none-eabi.cmake)

project(fuckLKS32)

enable_language(ASM)
enable_language(C)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OUTPUT_EXE_NAME ${CMAKE_PROJECT_NAME}.elf)


# Set the directories
set(SYS_DIR ${CMAKE_CURRENT_LIST_DIR}/System)

include_directories(${SYS_DIR}/Drivers/Include)
include_directories(${SYS_DIR}/Device/Include)
include_directories(${SYS_DIR}/CMSIS/Include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Add source files
file(GLOB_RECURSE DRV_SRC ${SYS_DIR}/Drivers/Source/*.c)

file(GLOB_RECURSE USER_SRCS ${CMAKE_CURRENT_LIST_DIR}/src/*.c ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

set(STARTUP_SRC ${CMAKE_CURRENT_LIST_DIR}/startup_lks32mc07x.s)


add_executable(${OUTPUT_EXE_NAME}
        ${DRV_SRC}
        ${USER_SRCS}
        ${STARTUP_SRC}
)

add_compile_definitions(
        USE_STDPERIPH_DRIVER
)

set(LD_SCRIPT_PATH ${CMAKE_CURRENT_LIST_DIR}/ldscript.ld)
get_filename_component(LD_SCRIPT_PATH_ABS ${LD_SCRIPT_PATH} ABSOLUTE)

set_target_properties(${OUTPUT_EXE_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        LINK_DEPENDS ${LD_SCRIPT_PATH_ABS}
        LINK_FLAGS "-T \"${LD_SCRIPT_PATH_ABS}\""
)


add_custom_target(
        showSize ALL
        ${TOOLCHAIN_PREFIX}/bin/${TOOLCHAIN}-size "${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_EXE_NAME}"
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_EXE_NAME})

        
add_custom_target(convertToBin ALL
        ${TOOLCHAIN_PREFIX}/bin/${TOOLCHAIN}-objcopy -O binary ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_EXE_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
        DEPENDS showSize)

find_program(PYOCD_FOUND pyocd)

if(PYOCD_FOUND)
        add_custom_target(BuildAndFlash COMMAND DEPENDS flash-cmd)
        add_custom_command(
                USES_TERMINAL 
                OUTPUT flash-cmd
                COMMAND pyocd load ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_EXE_NAME} -t lks32mc074dof8q8 # Modify this to match your target
                DEPENDS showSize
        )
else()
        message(WARNING "pyocd not found, flashing will not be available")
endif()