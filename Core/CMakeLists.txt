# Set the project name
project (CDS)

add_library(${PROJECT_NAME} INTERFACE)
add_library(Chen::CDS ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)