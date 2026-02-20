/*
BSD 3-Clause License

Copyright (c) 2024, SYSJF
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <string>

#define __CO_VERSION_MAJOR 1
#define __CO_VERSION_MINOR 2
#define __CO_VERSION_PART 0

//#define __CO_VERSION_DEBUG

#ifndef __CO_VERSION_DEBUG
    #define __CO_VERSION_RELEASE
#else
    #define  __CO_PROJECT_DIR std::string("C:\\Users\\Rigel85\\Desktop\\GenGrp\\")
#endif

#include "../include/ClassOptimize/WindowMain.hpp"


int main(int argc, char *argv[]) 
{
    std::stringstream ss ;
    // affichage de la version en console
    ss << "version : " << __CO_VERSION_MAJOR <<"." <<__CO_VERSION_MINOR << "." << __CO_VERSION_PART ;

    #ifdef __CO_VERSION_RELEASE
        ss << " RELEASE"<< std::endl;
    #else
        ss << " DEBUG"<< std::endl;
    #endif

    std::string vers("");

    std::getline(ss , vers);

    std:: cout << vers << std::endl;

    Gtk::Main app(argc, argv);

    try
    {
        Genetique::genitiqueSharedClass genetiqueInst;

        //definition des parametre par défaut de l'algorithme
        genetiqueInst.get_genAlgo()->cycle_arret = 2000;
        genetiqueInst.get_genAlgo()->taux_mutation = 0.1;
        genetiqueInst.get_genAlgo()->taux_selection = 0.15;
        genetiqueInst.get_genAlgo()->n_individu = 300 ;
        genetiqueInst.get_genAlgo()->taux_stabiliter = 0.03 ;
        genetiqueInst.get_genAlgo()->temps_limite = 20 ;

        genetiqueInst.get_genAlgo()->get_prop()->coef_souhait = 1 ; 
        genetiqueInst.get_genAlgo()->get_prop()->coef_non_souhait = 2;
        genetiqueInst.get_genAlgo()->get_prop()->coef_pariter = 1;
        genetiqueInst.get_genAlgo()->get_prop()->coef_competence = 1;
        genetiqueInst.get_genAlgo()->get_prop()->coef_attention = 1;
        genetiqueInst.get_genAlgo()->get_prop()->coef_souhait_multiple = 1;
        genetiqueInst.get_genAlgo()->get_prop()->coef_homogeneiter = 0.1;


        WindowMain fenetre( genetiqueInst );

	    fenetre.set_title("ClassOptimize   " + vers);

        fenetre.init();
        
        fenetre.show_all();
        
        Gtk::Main::run(fenetre);
    }
    catch(LogicExceptionDialog const & _e)
    {
        _e.show();
        std::cin.get();
    }
    catch(std::exception const & _e)
    {
        std::cerr << _e.what() << std::endl;

        std::cin.get();
    }
    
    

    return 0;
}

