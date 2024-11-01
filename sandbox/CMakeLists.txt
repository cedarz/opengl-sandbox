add_library(sandbox
    common/src/sandbox-base.cpp
)
target_include_directories(sandbox PUBLIC
    common/src/
)
target_link_libraries(sandbox PUBLIC
    ogls
    glfw
    imgui
    imgui_glfw_opengl3
)

add_subdirectory(triangle)
add_subdirectory(model-viewer)
add_subdirectory(tangent-space)
add_subdirectory(normal-mapping)
add_subdirectory(bump-mapping)
add_subdirectory(simple-shading)
add_subdirectory(shadow-map)
add_subdirectory(omnidirectional-shadow-map)


set_target_properties(sandbox PROPERTIES FOLDER "sand-box")
set_target_properties(triangle PROPERTIES FOLDER "sand-box")
set_target_properties(model-viewer PROPERTIES FOLDER "sand-box")
set_target_properties(tangent-space PROPERTIES FOLDER "sand-box")
set_target_properties(normal-mapping PROPERTIES FOLDER "sand-box")
set_target_properties(bump-mapping PROPERTIES FOLDER "sand-box")
set_target_properties(simple-shading PROPERTIES FOLDER "sand-box")
set_target_properties(shadow-map PROPERTIES FOLDER "sand-box")
set_target_properties(omnidirectional-shadow-map PROPERTIES FOLDER "sand-box")