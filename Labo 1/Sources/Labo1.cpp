/*============================================================================
 * Name        : Labo1.cpp
 * Date        : 12 juil. 2013
 * Author      : Fabien Dutoit
 * Version     : 1.0
 *
 * Description : Permet d'utiliser et de vérifier le code produit dans ce labo
 *============================================================================*/

#include <time.h>

#include "Labo1_tools.h"

int main(int argc, char** argv)
{
    clock_t tick;
    
    std::string filenameIn  = "img.bmp";
    std::string filenameComp = "img.huf";
    std::string filenameOut  = "output_img.bmp";

    if (argc >= 3) {
        filenameIn = argv[1];
        filenameComp = argv[2];
        filenameOut = argv[3];
    }

    std::cout << "Compression en cours..." << std::endl;
    tick = clock();
    compresser(filenameIn, filenameComp);
    std::cout << "Temps de compression: " << ((double)clock() - tick) / CLOCKS_PER_SEC << " sec." << std::endl;
    
    std::cout << "Decompression en cours..." << std::endl;
    tick = clock();
    decompresser(filenameComp, filenameOut);
    std::cout << "Temps de decompression: " << ((double)clock() - tick) / CLOCKS_PER_SEC << " sec." << std::endl;
    
    return EXIT_SUCCESS;
    
}
