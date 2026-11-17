#include <iostream>
#include <sil/sil.hpp>
#include "random.hpp"
#include <sil/sil.hpp>
#include <string>

// exo vert
void vert_only(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
//      color.g = 0.f;
    }
}





// Échanger les couleurs 
void color_swap(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        std::swap(color.r, color.g);
    }
}





// Exo noir et blanc
void noir_blanc(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float average = (color.r + color.g + color.b) / 3.f;
        color = glm::vec3{average};
    }
}





// Exercice négatif
void negatif(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = 1.f - color;
    }
}





// Exo dégradé
void degrade(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float value = static_cast<float>(x) / (image.width() - 1);
            image.pixel(x, y) = glm::vec3{value};
        }
    }
}






// Exo miroir
void mirroir(sil::Image& image)
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y), image.pixel(image.width() - 1 - x, y));
        }
    }
}




// exo bruit
void bruit(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        if (true_with_probability(0.2f))
        {
            color = glm::vec3{random_float(0.f, 1.f), random_float(0.f, 1.f), random_float(0.f, 1.f)};
        }
    }
}




// rotation 90


void rotation_90(sil::Image& image)
{
    sil::Image nouv_image{image.height(), image.width()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            nouv_image.pixel(image.height() - 1 - y, x) = image.pixel(x, y);
        }
    }

    image = nouv_image;
}








// RGB split
void rgb_split(sil::Image& image)
{
    sil::Image n_image{image.width(), image.height()};
    int offset = 20;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec3 color{};
            
// rouge pixel à droite son propre vert et bleu d'un pixel à gauche
            if (x + offset < image.width())
            {
                color.r = image.pixel(x + offset, y).r;
            }
            
            color.g = image.pixel(x, y).g;
            
            if (x - offset >= 0)
            {
                color.b = image.pixel(x - offset, y).b;
            }

            n_image.pixel(x, y) = color;
        }
    }

    image = n_image;
}




// exo luminosité et assombrissement


void luminosity (sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = glm::vec3{std::pow(color.r, 1.f / 2.f), 
                          std::pow(color.g, 1.f / 2.f), 
                          std::pow(color.b, 1.f / 2.f)};
    }
}


void obscur (sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = glm::vec3{std::pow(color.r,2.f), 
                          std::pow(color.g,2.f), 
                          std::pow(color.b,2.f)};
    }
}



//exo dissqque 

void disque(sil::Image& image)
{
    glm::vec2 center{image.width() / 2.f, image.height() / 2.f};
    float radius = 100.f;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (glm::distance(glm::vec2{x, y}, center) <= radius)
            {
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}

/* pour mettr eimage noire en fond 

int main()
{
    sil::Image image{500, 500};
    disque(image);
    image.save("output/pouet.png");
}*/



//cercle
void cercle(sil::Image& image)
{
    glm::vec2 center{image.width() / 2.f, image.height() / 2.f};
    float radius = 100.f;
    float thickness = 10.f;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float distance = glm::distance(glm::vec2{x, y}, center);
            if (distance <= radius && distance >= radius - thickness)
            {
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}



//animation

void animation(sil::Image& image)
{
    int const frame_count = 10;
    float const radius = 100.f;

    for (int i{0}; i < frame_count; i++)
    {
        image = sil::Image{500, 500};
        glm::vec2 center{static_cast<float>(i) / (frame_count - 1) * image.width(), image.height() / 2.f};

        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                if (glm::distance(glm::vec2{x, y}, center) <= radius)
                {
                    image.pixel(x, y) = glm::vec3{1.f};
                }
            }
        }

        image.save("output/anim/frame_" + std::to_string(i) + ".png");
    }
}

/* output pour animation

int main()
{
    sil::Image image{500, 500};
    animation(image);
}

*/





// Rosace (indice trigo)





int main()
{
    sil::Image image{500, 500};
    disque(image);
    image.save("output/pouet.png");
}

