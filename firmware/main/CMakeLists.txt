idf_component_register(SRCS "banco_de_dados.cpp" "main.cpp" "adc_1.cpp" "display.cpp"  
    INCLUDE_DIRS "." "../components" 
)
set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY LINK_INTERFACE_MULTIPLICITY 5)