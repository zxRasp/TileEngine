#ifndef _FRAME_H_
#define _FRAME_H_

#include <vector>
#include "Module.h"
#include "Graphics.h"

enum Anchor
{
    LEFT    = 1,
    HCENTER = 2,
    RIGHT   = 4,
    TOP     = 8,
    VCENTER = 16,
    BOTTOM  = 32
};

struct ModuleEntry
{
    Module* m;
    int     x;
    int     y;

    //ctor
    ModuleEntry(Module* _m, int _x, int _y) : m(_m), x(_x), y(_y) {}
};

class Frame
{
public:
    Frame(int width, int height);

    void addModule(Module* m, int x, int y);
    void draw(Graphics& g, int x, int y, int anchor = 0, bool isDebug = false);

private:
    std::vector<ModuleEntry> m_ModulesEnties;
    int m_Width;
    int m_Height;
};

#endif // _FRAME_H_
