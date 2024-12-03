#pragma once
#ifndef RENDER_ENVIROMENT_H
#define RENDER_ENVIROMENT_H


void setDoorLastTime(int time);
bool getIsDoorOpening();
float getDoorAngle();
void setDoorOpening(bool opening);

void loadEnvironmentAssets();
void RenderEnvironment();

#endif
