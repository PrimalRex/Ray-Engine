#ifndef CPU_RENDERER_H
#define CPU_RENDERER_H
#include <cstdint>

//PARAMS

// Render resolution (3840x2160p = 2160 Res)
inline unsigned int resolution = 512;
// Aspect ratio, e.g. 16.0/9.0, 4.0/3.0, 1.0/1.0 ...
inline float ratio = 16.0/9.0;

struct RGB {
    uint8_t r, g, b;
};

class cpu_renderer {
public:
    cpu_renderer();
    ~cpu_renderer();
    void Render();

    static RGB CalculatePixel(const double &x, const double &y);
    RGB* GetimgBuffer() const;

    static int GetOutputWidth();

    static int GetOutputHeight();
private:
    RGB* m_imgBuffer;
};



#endif //CPU_RENDERER_H
