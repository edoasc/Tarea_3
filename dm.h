#ifndef DM_H_ // DM_H
#define DM_H_ // DM_H

struct Sistema;
typedef struct Sistema sys;


sys * system_alloc(int);
void system_free(sys *);
void crear_red_fcc(sys *);
void guardar_datos(sys *);

#endif // DM_H_