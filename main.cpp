#include "SYSJF_includes/main.hpp"
#include "genetique.hpp"

using namespace std;




int SYSJF::Main::body(void)
{
	Genetique::Process genAlg;

	genAlg.cycle_arret = 1000;
	genAlg.score_arret = 10000;
	genAlg.taux_mutation = 0.3;
	genAlg.taux_selection = 0.4;
	genAlg.n_individu = 300 ;
	genAlg.taux_stabiliter = 0.02 ;
	genAlg.temps_limite = 1 ;

	genAlg.get_prop()->coef_souhait = 1 ; 
	genAlg.get_prop()->coef_non_souhait = 10;
	genAlg.get_prop()->coef_pariter = 1;
	genAlg.get_prop()->coef_competence = 1;
	genAlg.get_prop()->coef_attention = 1;
	genAlg.get_prop()->coef_souhait_multiple = 1;
	genAlg.get_prop()->coef_homogeneiter = 0;

	genAlg.get_base_chromosone()->emplace_back( );
	genAlg.get_base_chromosone()->back().get_caract().id = 1;
	genAlg.get_base_chromosone()->back().get_caract().size = 4;

	genAlg.get_base_chromosone()->emplace_back();
	genAlg.get_base_chromosone()->back().get_caract().id = 2;
	genAlg.get_base_chromosone()->back().get_caract().size = 4;

	genAlg.get_base_chromosone()->emplace_back();
	genAlg.get_base_chromosone()->back().get_caract().id = 3;
	genAlg.get_base_chromosone()->back().get_caract().size = 4;



	genAlg.rget_base_gene().push_back( Genetique::Gene::ptr( new Genetique::Gene() ) );
	genAlg.rget_base_gene().back()->get_caract().id = 1;
	genAlg.rget_base_gene().back()->get_caract().sexe = true;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {9};

	genAlg.rget_base_gene().push_back(Genetique::Gene::ptr( new Genetique::Gene()) );
	genAlg.rget_base_gene().back()->get_caract().id = 2;
	genAlg.rget_base_gene().back()->get_caract().sexe = true;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {};


	genAlg.rget_base_gene().push_back(Genetique::Gene::ptr( new Genetique::Gene()) );
	genAlg.rget_base_gene().back()->get_caract().id = 3;
	genAlg.rget_base_gene().back()->get_caract().sexe = true;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {7};

	genAlg.rget_base_gene().push_back(Genetique::Gene::ptr( new Genetique::Gene()) );
	genAlg.rget_base_gene().back()->get_caract().id = 4;
	genAlg.rget_base_gene().back()->get_caract().sexe = false;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {12,10,5};

	genAlg.rget_base_gene().push_back(Genetique::Gene::ptr( new Genetique::Gene()) );
	genAlg.rget_base_gene().back()->get_caract().id = 5;
	genAlg.rget_base_gene().back()->get_caract().sexe = false;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {};

	genAlg.rget_base_gene().push_back(Genetique::Gene::ptr( new Genetique::Gene()) );
	genAlg.rget_base_gene().back()->get_caract().id = 6;
	genAlg.rget_base_gene().back()->get_caract().sexe = false;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {5,8,12,3};

	genAlg.rget_base_gene().push_back(Genetique::Gene::ptr( new Genetique::Gene()) );
	genAlg.rget_base_gene().back()->get_caract().id = 7;
	genAlg.rget_base_gene().back()->get_caract().sexe = true;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {11,5,3};

	genAlg.rget_base_gene().push_back(Genetique::Gene::ptr( new Genetique::Gene()) );
	genAlg.rget_base_gene().back()->get_caract().id = 8;
	genAlg.rget_base_gene().back()->get_caract().sexe = true;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {11,10};

	genAlg.rget_base_gene().push_back(Genetique::Gene::ptr( new Genetique::Gene()) );
	genAlg.rget_base_gene().back()->get_caract().id = 9;
	genAlg.rget_base_gene().back()->get_caract().sexe = true;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {1};

	genAlg.rget_base_gene().push_back(Genetique::Gene::ptr( new Genetique::Gene()) );
	genAlg.rget_base_gene().back()->get_caract().id = 10;
	genAlg.rget_base_gene().back()->get_caract().sexe = false;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {12};

	genAlg.rget_base_gene().push_back(Genetique::Gene::ptr( new Genetique::Gene()) );
	genAlg.rget_base_gene().back()->get_caract().id = 11;
	genAlg.rget_base_gene().back()->get_caract().sexe = true;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {10,8};

	genAlg.rget_base_gene().push_back(Genetique::Gene::ptr( new Genetique::Gene()) );
	genAlg.rget_base_gene().back()->get_caract().id = 12;
	genAlg.rget_base_gene().back()->get_caract().sexe = false;
	genAlg.rget_base_gene().back()->get_caract().attracteur = {10};



	auto start = std::chrono::high_resolution_clock::now();
    
    // Appel de la fonction à chronométrer
  
    auto res =  genAlg.process();

    // Fin du chronomètre
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calcul de la durée écoulée
    std::chrono::duration<double> elapsed = end - start;
    
    // Affichage du temps écoulé en secondes
    std::cout << "Temps d'execution : " << elapsed.count() << " secondes\n";
	std::cout << "meilleur score: " << res[0].get_score() << std::endl<< std::endl;
	
	for( auto elev : res[0].get_base_gene())
	{
		std::cout <<  elev->get_caract().id  << std::endl;
	}

	return 0;
}

int main(int argc , char * argv[])
{
	SYSJF::Main main(argc , argv);

	main.progInfo.version = "0.01\tno test version";
	main.progInfo.type = "debug" ;
	main.progInfo.date = "--" ;
	main.progInfo.develloper = "Jerome Favrou ( SYSJF compagny )";
	main.progInfo.maintener = main.progInfo.develloper;
	main.progInfo.contacte = "jerome_favrou@protonmail.com" ;
	main.progInfo.advertisment = "any use is the sole responsibility of the user";

	main.showVersion(false , false , false);

	return main.run();
}

