/* 
 * File:   ex2.cpp
 * Author: Olivier Cuisenaire
 *
 * Created on 2 oct. 2014, 11:19:03
 */

#include <stdlib.h>
#include <iostream>

#include "GraphFromImage.h"
#include "ParcoursEnProfondeur.h"

int main(int argc, char** argv) {
    
    std::string filename("input.bmp");
    bitmap_image image(filename);
    
   if (!image) {
      std::cout << "test1 : Failed to open " << filename << ") \n";
      return (EXIT_FAILURE);
   }
    
    std::cout << "image size: " << image.width() << " x " << image.height() << "\n";
    
    ASD2::GraphFromImage G(image);
    ASD2::DFS<ASD2::GraphFromImage> dfs(G);

    //Question BONUS: Pourquoi n'utilisons-nous pas la methode visite pour parcourir l'image ?
    // Car visit suivent comment on l'appelle fais la modification sur le pixel avent la recursion
    // Donc lors de l'analyse des voisins la couleur ne sera pas identique.
    // On peut par contre sans autre appeler la fonction comme ceci et cela fonctionnerais:
    //            Noeud de depart, Pre fonction, Post fonction
    //  dfs.visit(G.idx(x, y),     [](int){},    [](int){
    //      image.set_pixel( G.x(v), G.y(v), 224, 128, 64);
    //  });

    //on colore la carotte
    int x = 250, y = 400;
    dfs.visit( G.idx(x,y), [](int){}, [&G, &image] (int v) {
        image.set_pixel( G.x(v), G.y(v), 224, 128, 64);
    });
    
    //on ajoute une couleur de fond
    dfs.iterativeVisit( G.idx(0,0), [&G, &image] (int v) {
        image.set_pixel( G.x(v), G.y(v), 0, 255, 64);
    });
    
    //on sauve l'image modifiee
    image.save_image("output.bmp");
    
    
    //on charge l'image temoin pour verifier notre code
    bitmap_image image_gold("goal.bmp");
    
    if(image.psnr(image_gold) < 1000000)
        std::cout  << "test failed - psnr = " << image.psnr(image_gold)  << ") \n";
    else
        std::cout << "test succeeded - image is identical to goal.bmp\n";
    
    return (EXIT_SUCCESS);
    
}

