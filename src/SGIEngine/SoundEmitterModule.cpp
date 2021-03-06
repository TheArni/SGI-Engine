/* 
 * File:   SoundEmitterModule.cpp
 * Author: arnau
 * 
 * Created on 9 / de setembre / 2015, 22:36
 */

#include "SoundEmitterModule.h"
#include "AudioEngine.h"
#include "WorldObject.h"

#include <iostream>

int ticks = 0;

void SoundEmitterModule::loadModule(WorldObject* prop, World* world, rapidjson::Value& json){
    BaseObjectModule::loadModule(prop, world, json);
    audio = json["audio"].GetString();
}

void SoundEmitterModule::onInteract(){
    AudioEngine::playAudio(audio, worldobj->position);
}