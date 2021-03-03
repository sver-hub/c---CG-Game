#include "config.h"

struct FadeController
{
    bool out;
    bool in;
    bool showLabel;
    int state;
    const int fadeDelay = 40;

    FadeController() : out(false), in(true), showLabel(true) {
        state = fadeDelay;
    }

    float outCurve() { return 1.0f * state/ fadeDelay; }

    float inCurve() { return (1.0f * fadeDelay - state) / fadeDelay; }

    bool inProgress() { return out || in; }

    bool finished() { return state == 0; }

    void setFadedOut() {
        out = false;
        in = true;
        state = fadeDelay;
    }

    void setFadedIn() {
        if (showLabel) {
            showLabel = false;
            out = true;
            state = fadeDelay;
            } 
        in = false;
    }

    void start() {
        out = true;
        showLabel = true;
        state = fadeDelay;
    }


};
