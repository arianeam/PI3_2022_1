idf_component_register(SRCS "tarefas.cpp" "display.cpp" "tarefas.cpp" "main.cpp"  
    INCLUDE_DIRS "." "../components" 
)
set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY LINK_INTERFACE_MULTIPLICITY 5)