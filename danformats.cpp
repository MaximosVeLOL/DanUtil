#include "danformats.h"
#include <QDebug>
#include <string.h>


namespace Cutscene {

namespace FrameEvent {

#pragma region Type Definitions

#define ERROR_NONE 0x00
#define ERROR_ARGS 0x01

char FEvent::Use(byte argc, char* argv[]) {
    char ret = OnUse(argc, argv);
    switch(ret) {
    case ERROR_NONE:
        break;

    case ERROR_ARGS:
        World::Get()->Log(Error, "%s returned with invalid argument count");
        break;
    }

    return ret;
}

struct TPlaySound : FEvent {
    TPlaySound() {
        name = "play_sound";
    }

    char OnUse(byte argc, char* argv[]) override {
        if(argc != 1) {
            return ERROR_ARGS;
        }
        World::Get()->uPlaySound(argv[0]);
        return ERROR_NONE;
    }

};

struct TStopSound : FEvent {
    TStopSound() {
        name = "stop_sound";
    }

    char OnUse(byte argc, char* argv[]) override {
        if(argc != 1) {
            return ERROR_ARGS;
        }
        World::Get()->uStopSound(argv[0]);
        return ERROR_NONE;
    }

};

struct TPlayMusic : FEvent {
    TPlayMusic() {
        name = "play_music";
    }
    char OnUse(byte argc, char* argv[]) override {
        if(argc != 1) return ERROR_ARGS;
        World::Get()->uPlayMusic(argv[1]);
        return ERROR_NONE;
    }
};

#pragma endregion

FEvent EVENTS[] = {
    TPlaySound(),
};
const byte EVENTS_LENGTH = (byte)(sizeof(EVENTS) / sizeof(FEvent));

char Call(const char* pName, byte argumentCount, char* arguments[]) {
    if(pName[0] == '\0') return -1; //No name provided
    for(byte i = 0 ; i < EVENTS_LENGTH;i++) {
        if(strcmp(pName, EVENTS[i].name) == 0) {
            return EVENTS[i].Use(argumentCount, arguments);
        }
    }
    return -1;
}

} //EventType namespace


void World::Log(LogType pType, const char* pFormat, ...) {
    qDebug(pFormat);
}

void World::uPlaySound(const char* pName) {

}

void World::uStopSound(const char* pName) {

}

void World::uPlayMusic(const char* pName) {

}

} //Cutscene namespace