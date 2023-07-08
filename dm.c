#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dm.h"

typedef struct{
  double lbox;
  double densidad;
  double volumen;
  double nc;
  double radio;
} auxiliar;

struct Sistema{
  int n;
  double **r;
  auxiliar *aux;
};

sys * system_alloc(int n){
    sys * obj = malloc(sizeof(sys));

    obj->n = n;

    obj->r = malloc(sizeof(double *) * n);

    for (int i = 0; i < n; i++){
        obj->r[i] = calloc(3, sizeof(double));
    }

    obj->aux = malloc(sizeof(auxiliar));
    obj->aux->lbox = 1.0;
    obj->aux->volumen = 1.0;
    obj->aux->nc = 3;
    obj->aux->radio = 0.25 / 2;
    obj->aux->densidad = obj->n / obj->aux->volumen;

    return obj;
}

void system_free(sys *obj){
  for (int i = 0; i < (obj->n); i++) {
    free(obj->r[i]);
  }
  free(obj->aux);
  free(obj);
}

void crear_red_fcc(sys *obj){
    // funcion que crea una red cristalina cubica del tipo fcc

    int l = 0, m = 0, n = 0, contador = 0;
    double a = pow((4.0/obj->aux->densidad), 1.0/3.0);

    for (l = 0; l < obj->aux->nc; l++){
      for (m = 0; m < obj->aux->nc; m++){
        for (n = 0; n < obj->aux->nc; n++){

          obj->r[contador][0] = a*l;
          obj->r[contador][1] = a*m;
          obj->r[contador][2] = a*n;
          ++contador;
          if(contador==obj->n){
          break;
          }

          obj->r[contador][0] = a * (l + 0.5);
          obj->r[contador][1] = a * (m + 0.5);
          obj->r[contador][2] = a * n;
          ++contador;
          if(contador==obj->n){
          break;
          }

          obj->r[contador][0] = a * (l + 0.5);
          obj->r[contador][1] = a * m;
          obj->r[contador][2] = a * (n + 0.5);
          ++contador;
          if(contador==obj->n){
          break;
          }
         
          obj->r[contador][0] = a * l;
          obj->r[contador][1] = a * (m + 0.5);
          obj->r[contador][2] = a * (n + 0.5);
          ++contador;
          if(contador==obj->n){
          break;
          }
        }
        if(contador==obj->n){
          break;
        }
      }
      if(contador==obj->n){
          break;
      }
    }
}

void guardar_datos(sys *obj){
    
    FILE *archivo = fopen("archivo.xyz", "w");
    fprintf(archivo, "%i\n", obj->n); 
    fprintf(archivo, "Lattice=\"%f 0 0 0 %f 0 0 0 %f\"", obj->aux->lbox, obj->aux->lbox, obj->aux->lbox);
    fprintf(archivo, " Properties=id:I:1:pos:R:3:radius:R:1\n");

    for (int i = 0; i < obj->n; i++){
        fprintf(archivo, 
               "%i %f %f %f %f\n", i,
               obj->r[i][0],
               obj->r[i][1],
               obj->r[i][2],
               obj->aux->radio);
    }
    fclose(archivo);
}