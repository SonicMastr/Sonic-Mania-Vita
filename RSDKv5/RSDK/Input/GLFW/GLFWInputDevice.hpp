
namespace SKU
{

struct InputDeviceGLFW : InputDevice {
    void UpdateInput(void);
    void ProcessInput(int32 controllerID);
    void CloseDevice();

    int32 inputFlags;
    int32 prevInputFlags;
    uint8 stateUp;
    uint8 stateDown;
    uint8 stateLeft;
    uint8 stateRight;
    uint8 stateA;
    uint8 stateB;
    uint8 stateC;
    uint8 stateX;
    uint8 stateY;
    uint8 stateZ;
    uint8 stateStart;
    uint8 stateSelect;
    uint8 stateBumper_L;
    uint8 stateBumper_R;
    uint8 stateStick_L;
    uint8 stateStick_R;
    float triggerDeltaL;
    float triggerDeltaR;
    float hDelta_L;
    float vDelta_L;
    float vDelta_R;
    float hDelta_R;

    SDL_GameController *controllerPtr;
};

InputDeviceSDL *InitSDL2InputDevice(uint32 id, uint8 controllerID);

void InitSDL2InputAPI();

} // namespace SKU