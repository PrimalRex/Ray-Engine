
#include "cpu_renderer.h"

#include <float.h>

#include "vec3.h"

cpu_renderer::cpu_renderer() {
    // Allocate the image size worth of memory
    m_imgBuffer = new RGB[GetOutputHeight() * GetOutputWidth()];
}

cpu_renderer::~cpu_renderer() {
    // Stop any leaks
    delete[] m_imgBuffer;
}

int cpu_renderer::GetOutputWidth() {
    return resolution * ratio;
}

int cpu_renderer::GetOutputHeight() {
    return resolution;
}

// Starts the rendering
void cpu_renderer::Render(const Scene &scene) {
    for (unsigned int y = 0; y < GetOutputHeight(); y++) {
        for (unsigned int x = 0; x < GetOutputWidth(); x++) {
            // Calculate normalized coordinates in the range [-1, 1]
            double normalized_x = (2.0 * x / GetOutputWidth()) - 1.0;
            // Factor aspect ratio
            normalized_x *= ratio;
            double normalized_y = (2.0 * y / GetOutputHeight()) - 1.0;

            m_imgBuffer[x + y * GetOutputWidth()] = CalculatePixel(normalized_x, normalized_y, scene);
        }
    }
}


//Should be placed inside the render or at a callback but not a problem if not multithread.
RGB* cpu_renderer::GetimgBuffer() const {
    return m_imgBuffer;
}

// Calculate at each pixel the color that should be displayed.
RGB cpu_renderer::CalculatePixel(const double &x, const double &y, const Scene &scene) {
    RGB out{0,0,0};

    // Pixel Calibration Test

    /*out.r = static_cast<uint8_t>(255.999 * x);
    out.g = static_cast<uint8_t>(255.999 * y);
    out.b = static_cast<uint8_t>(255.999 * 0.25);*/

    vec3 rayLoc(0, 0, -2);
    vec3 rayDir(x, y, -1.0f);
    vec3 sunDir(-.8,-.4,1);
    sunDir.Normalize();

    float hitDistance = FLT_MAX;
    const world_object* closestObj = nullptr;

    for (const auto& obj : scene.Objects) {
        const sphere* spherePtr = dynamic_cast<sphere*>(obj);
        if (spherePtr) {

            float sphereRadius = spherePtr->m_scale.x;
            vec3 sphereCenter = spherePtr->m_position;

            // Quadratic coefficients for the sphere intersection equation
            float a = vec3::Dot(rayDir, rayDir);
            float b = 2.0f * vec3::Dot(rayLoc - sphereCenter, rayDir);
            float c = vec3::Dot(rayLoc - sphereCenter, rayLoc - sphereCenter) - sphereRadius * sphereRadius;

            // Discriminant of the quadratic equation
            float disc = b * b - 4.0f * a * c;
            if (disc < 0) {
                continue;
            }

            float sqrt_disc = sqrt(disc);
            float inv_a = 1.0f / (2.0f * a);

            // Using the + value instead of - as the negation does backfacing
            float intersec1 = (-b + sqrt_disc) * inv_a;

            if (intersec1 < hitDistance) {
                hitDistance = intersec1;
                closestObj = obj;
            }

        }
    }

    if (closestObj == nullptr) {
        return out;
    }

    vec3 sphereCenter = closestObj->m_position;
    vec3 sphereColor = closestObj->m_albedoColor;

    vec3 hitPos = rayLoc + rayDir * hitDistance;
    vec3 normal = hitPos - sphereCenter;
    normal.Normalize();

    // Debug Surface Normal
    /*out.r = static_cast<uint8_t>(normal.x * 0.5f * 255.999f + 0.5f);
    out.g = static_cast<uint8_t>(normal.y * 0.5f * 255.999f + 0.5f);
    out.b = static_cast<uint8_t>(normal.z * 0.5f * 255.999f + 0.5f);*/

    //Highlight only the parts that are visible to the light source
    float surfaceIntensity = vec3::Dot(normal, sunDir * -1);
    if (surfaceIntensity < 0.0f) {
        surfaceIntensity = 0.0f;
    }

    //Apply the sun intensity to the albedo
    out.r = sphereColor.x * surfaceIntensity;
    out.g = sphereColor.y * surfaceIntensity;
    out.b = sphereColor.z * surfaceIntensity;

    return out;
}
