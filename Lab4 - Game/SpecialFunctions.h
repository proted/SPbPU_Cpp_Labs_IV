#pragma once

#include "glut.h"
#include "MenuView.h"

//Special drawing functions
void sdf_button11(MenuItem* item);
void sdf_stats(MenuItem* item);

//Special clicking functions
void scf_button11(MenuItem* item, prtd_ct::Point &point);
void scf_button21(MenuItem* item, prtd_ct::Point &point);

//Special keyboard functions
void skf_scene2(MenuScene* scene, unsigned char key);

//Special idle functions
void sif_scene2(MenuScene* scene);

//Special special functions :)
void ssf_scene2(MenuScene* scene, int key);
