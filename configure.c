#include <stdlib.h>
#include "configure.h"
configuration default_config(){
    configuration config={NULL,NULL};
    return config;
}
configuration set_config(char*src_dir,char*dst_dir){
    configuration config=default_config();
    config.src_path=src_dir;
    config.dst_path=dst_dir;
    return config;
}