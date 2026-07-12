#ifndef DANFORMATS_H
#define DANFORMATS_H

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;

constexpr ushort _DEFAULT = 65535;

namespace Tex {

    struct RGBA {
        byte r = 0;
        byte g = 0;
        byte b = 0;
        byte a = 0;
    };
    struct RGB {
        byte r = 0;
        byte g = 0;
        byte b = 0;
        operator RGBA() {
            return {r, g, b, 0xFF};
        }
    };
    enum ImageType : uint {
        RGBOnly = 0x00000000,
        //RGBA = 0x00000003,
        Unknown = 6,
        TexRGBA = 50331648,
    };

    struct Format {
        char header[4] = {
            'T',
            'E',
            'X',
            '\x1',
        };
        ImageType type = ImageType::TexRGBA;
        byte reserved1[8] = {
            //0x00,
            //0x00,
            //0x00,
            //0x03,
            0x08,
            0x01,
            0x08,
            0x04,
            0x08,
            0x03,
            0x08,
            0x02
        };
        int reserved2 = 0;
        ushort shortWidth = _DEFAULT;
        ushort shortHeight = _DEFAULT;
        uint reserved3 = 0x01000100;
        uint width = _DEFAULT;
        uint height = _DEFAULT;
        byte reserved4[12] = {0x00};
        uint unknown1 = _DEFAULT;
        RGBA* pixelData = nullptr;

        void SetHeaderForType() {
            if(type == ImageType::TexRGBA) return;
            else {
                constexpr byte d[8] = {
                    0x08,
                    0x02,
                    0x08,
                    0x03,
                    0x08,
                    0x04,
                    0x00,
                    0x00,
                };

                for(byte i = 0 ; i < 8;i++) {
                    reserved1[i] = d[i];
                }
            }
        }
    };
};
namespace Cutscene {

using time_t = ushort;

//An element in the XML world, not the DTM world.
struct Element {
    const char* name = "";
    const char** parameters = nullptr;
};

struct EAnimatedScene : Element {
    EAnimatedScene() {
        name = "AnimatedScene";
    }
};

struct Layer : Element {};

struct ECamera : Layer {
    uint x = 0;
    uint y = 0;

    ECamera() {
        name = "Camera";
    }
};

struct Vector {
    short x = 0;
    short y = 0;

};

enum MotionType : byte {
    MT_HOLD = 0,
    MT_LINEAR = 1,
    MT_EASEOUT = 2
};

enum FlipType : byte {
    FLIP_NONE = 0,
    FLIP_DEFAULT = 1,
    FLIP_FLIPPED = 2,
};

struct Keyframe {
    time_t time = 0;
    MotionType motionType = MT_HOLD;
    const char* animation = nullptr;
    bool animationLoop = false;
    Vector target = {0};
    char zoom = 0; //Using char for safety
    FlipType flip = FLIP_NONE;
    //The event that occurs (play_sound, info_,
    const char* frameEvent = nullptr;
};

namespace FrameEvent {
struct FEvent {
    const char* name = nullptr;
    virtual char OnUse(byte argc, char* argv[]){return 0;} //Included definition because of compiler issues
    char Use(byte argc, char* argv[]);
};

extern char Call(const char* pName);
} //FrameEvent

 enum LogType : byte {
    Debug = 0,
    Info = 1,
    Error = 2,
    FatalError = 3,

};



class World {
private:
    time_t timeFrame = 0;
    byte timeScale = 1;
public:
    static World* Get() {
        static World* ret = nullptr;
        if(!ret) ret = new World();
        return ret;
    }
    void uPlaySound(const char* pName);
    void uStopSound(const char* pName);

    void uPlayMusic(const char* pName);

    void Log(LogType pType, const char* pFormat, ...);

};

};

#endif // DANFORMATS_H
