idf_component_register(
		SRCS "muti_button.c" "key.c"
		INCLUDE_DIRS "include"
		REQUIRES main driver espressif__button						   
					   )