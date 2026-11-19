#include <iostream>
#include <sil/sil.hpp>
#include "random.hpp"
#include <sil/sil.hpp>
#include <string>
#include <cmath>
#include <algorithm>


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

void rosace(sil::Image& image)
{
    glm::vec2 center{image.width() / 2.f, image.height() / 2.f};
    float radius = 100.f;
    float thickness = 5.f;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec2 pos{x, y};
            
/* faire cercle autour du centre*/
            for (int i{0}; i < 6; i++)
            {
                float angle = i * 2.f * M_PI / 6.f;
                glm::vec2 circle_center = center + radius * glm::vec2{std::cos(angle), std::sin(angle)};
                
                float distance = glm::distance(pos, circle_center);
                if (distance <= radius && distance >= radius - thickness)
                {
                    image.pixel(x, y) = glm::vec3{1.f};
                }
            }
        }
    }
}


/*mosaique*/
void mosaique(sil::Image& image)
{
    sil::Image original = image; 
    int width = image.width();
    int height = image.height();

    for (int x{0}; x < width; x++)
    {
        for (int y{0}; y < height; y++)
        {
            int original_x = (x * 6) % width;
            int original_y = (y * 6) % height;

            image.pixel(x, y) = original.pixel(original_x, original_y);
        }
    }
}


/* bien changer l'image noire pour logo
int main()
{
    sil::Image image{"images/logo.png"};
    mosaique(image);
    image.save("output/pouet.png"); 
}
    */




/* meme chose mais inverser une image sur 2*/
void mosaique_inverse(sil::Image& image)
{
    sil::Image original = image;
    int width = image.width();
    int height = image.height();

    for (int x{0}; x < width; x++)
    {
        for (int y{0}; y < height; y++)
        {
            int tile_x = (x * 3) / width;
            int tile_y = (y * 3) / height;
            int original_x = (x * 3) % width;
            int original_y = (y * 3) % height;

        /*si impair sur abscisses alors => inverse pareil pour oordonnées
            */
            if (tile_x % 2 == 1)
            {
                original_x = width - 1 - original_x;
            }
            if (tile_y % 2 == 1)
            {
                original_y = height - 1 - original_y;
            }
            image.pixel(x, y) = original.pixel(original_x, original_y);
        }
    }
}





/*glitch*/
#include <sil/sil.hpp>
#include "random.hpp"

void glitch(sil::Image& image)
{
    int const nb_glitches = 50; // Nombre de rectangles à échanger

    for (int i{0}; i < nb_glitches; i++)
    {
        
        int rect_width = random_int(10, 50);
        int rect_height = random_int(2, 8);

        int x1 = random_int(0, image.width() - rect_width);
        int y1 = random_int(0, image.height() - rect_height);
        int x2 = random_int(0, image.width() - rect_width);
        int y2 = random_int(0, image.height() - rect_height);
        for (int x{0}; x < rect_width; x++)
        {
            for (int y{0}; y < rect_height; y++)
            {
                std::swap(image.pixel(x1 + x, y1 + y), image.pixel(x2 + x, y2 + y));
            }
        }
    }
}




/* tri de pixels*/
/*trier tous les pixels*/


float brightness(glm::vec3 const& color)
{
    return (color.r + color.g + color.b) / 3.f;
}

void tri_all_pixel(sil::Image& image)
{
    std::sort(image.pixels().begin(), image.pixels().end(), [](glm::vec3 const& color1, glm::vec3 const& color2) {
        return brightness(color1) < brightness(color2);
    });
}


/*trier lignes*/

void tri_ligne_pixel(sil::Image& image)
{
    for (int y{0}; y < image.height(); y++)
    {
        auto rang_start = image.pixels().begin() + y * image.width();
        auto rang_end = rang_start + image.width();

        std::sort(rang_start, rang_end, [](glm::vec3 const& color1, glm::vec3 const& color2) {
            return brightness(color1) < brightness(color2);
        });
    }
}



/*trier parties aléatoires*/

void tri_random_pixel(sil::Image& image)
{
    int const nb_parties = 400;

    for (int i{0}; i < nb_parties; i++)
    {
        int y = random_int(0, image.height() - 1);
        int x1 = random_int(0, image.width() - 1);
        int x2 = random_int(0, image.width() - 1);

        if (x1 > x2)
        {
            std::swap(x1, x2);
        }

        auto rang_start = image.pixels().begin() + y * image.width();
        std::sort(rang_start + x1, rang_start + x2, [](glm::vec3 const& color1, glm::vec3 const& color2) {
            return brightness(color1) < brightness(color2);
        });
    }
}



int main()
{
    sil::Image image{"images/logo.png"};
    tri_random_pixel(image);
    image.save("output/pouet.png"); 
}



/* rappel pour push sur mon github
git add .
git commit -m "MAJ"
git push
*/