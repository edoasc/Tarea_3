#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dm.h"

int main(int argc, char *argv[]){

    sys *sistema = system_alloc(64);
    crear_red_fcc(sistema);
    guardar_datos(sistema);
    system_free(sistema);
    
    return 0;
}