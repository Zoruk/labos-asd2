#include "GraphFromImage.h"

namespace ASD2 {

    GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
        /* NOTHING TO DO HERE */
    }

    // Par la suite pour une evolutivite du code, passer cette classe
    // par template a la class GraphFromImage ou juste a la fonction
    // GraphFromImage::adjacent
    class AddIfSameColor {
    private:
        GraphFromImage::Iterable list; // la liste qui sera retournee
        unsigned char _r, _g, _b; // les 3 pixels de la couleur a retenir
        
        const bitmap_image& image; // sur quelle image comparer
        const GraphFromImage* graph; // le graph qui appelle le foncteur
    public:
        /* 
         * Construction du foncteur
         * Parametres : 
         *      graph : le graph appenent
         *      image : l'image sur la quelle comparer
         *      x et y : coordonnée du pixel initial pour la comparaison
         */
        AddIfSameColor(const GraphFromImage* graph, const bitmap_image& image,
                const unsigned int x, const unsigned int y) : image(image), graph(graph) {
            image.get_pixel(x, y, _r, _g, _b);
        }
        
        /*
         * Foncteur qui va ajouter le pixel (x,y) a la liste interne uniquement si
         * il est de la meme couleur que le point passe en parametre au constructeur.
         */
        void operator()(const unsigned int x, const unsigned y) {
            unsigned char r, g, b;
            image.get_pixel(x, y, r, g, b);
            if (_r == r && _g == g && _b == b)
                list.push_back(graph->idx(x, y));
        }
        
        // Operateur de cast pour pouvoir faire "return GraphFromImage;" avec une
        // fonction qui retourne GraphFromImage::Iterable
        operator GraphFromImage::Iterable () {
            return list;
        }
    };

    GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
        
        // Coordonnee du point.
        const unsigned int X = x(v);
        const unsigned int Y = y(v);
        
        // Creation du foncteur décrit au dessus
        AddIfSameColor list(this, image, X, Y);

        // Test les pixels avec le foncteur et verification des bords de l'image
        if (X > 0)
            list(X - 1, Y);
        if (X < image.width() - 1)
            list(X + 1, Y);
        if (Y > 0)
            list(X, Y - 1);
        if (Y < image.height() - 1)
            list(X, Y + 1);
        return list;
    }
    // Getters
    int GraphFromImage::idx(int x, int y) const {
        return y * image.width() + x;
    }

    int GraphFromImage::x(int idx) const {
        return idx % image.width();
    }

    int GraphFromImage::y(int idx) const {
        return idx / image.width();
    }

    int GraphFromImage::V() const {
        return image.width() * image.height();
    }
}
