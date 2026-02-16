#ifndef __DATANOTEBOOK_HPP__
#define __DATANOTEBOOK_HPP__

#include "../include/ClassOptimize/gtkmmcomponent.hpp"

/// @brief classe qui gère la partie de l'interface ou on affiche les souhaits , les attributs et les groupes

class DataNoteBook : public Gtk::HPaned , public Genetique::genitiqueSharedClass , public TemplateGui
{
    public :

        /// @brief constructeur de la classe cree l'interface graphique dans la fenetre principale
        /// @param ref une référence de la classe genitiqueSharedClass pour pouvoir accéder aux données de la génétique
        /// @param parent une référence de la fenêtre principale pour pouvoir y ajouter des éléments graphiques
        DataNoteBook(Genetique::genitiqueSharedClass const & ref , Gtk::Window& parent):Gtk::HPaned(),Genetique::genitiqueSharedClass(ref),m_graphWish(ref),m_graphCapacity(ref),m_pb(ref),m_rb(ref),m_processing(false),TemplateGui()
        {   
            this->m_parent = &parent;
            auto adduser = Gtk::manage( new Gtk::VBox() );

            #ifdef __CO_VERSION_DEBUG 
                auto bp_dev = Gtk::manage( new Gtk::Button("Bouton developpeur"));
                bp_dev->signal_clicked().connect(sigc::mem_fun(*this,&DataNoteBook::load_exemple));
                adduser->pack_start( *bp_dev , Gtk::PACK_SHRINK);
            #endif


            adduser->pack_start( this->m_addUser , Gtk::PACK_SHRINK);

            this->m_addUser.set_can_focus(true);
            this->m_addUser.set_focus_on_click(true);
            this->m_addUser.grab_focus();
            this->m_addUser.set_alignment(Gtk::ALIGN_START);
            this->m_addUser.set_placeholder_text("Entrer un nom d'individu");

            this->m_addUser.signal_activate().connect(sigc::mem_fun(*this , &DataNoteBook::on_entry_user_activate));

            this->m_addGrp.set_can_focus(true);
            this->m_addGrp.set_focus_on_click(true);
            this->m_addGrp.grab_focus();
            this->m_addGrp.set_alignment(Gtk::ALIGN_START);
            this->m_addGrp.set_placeholder_text("Entrer un nom de groupe / ilot / ensemble");

            this->m_addGrp.signal_activate().connect(sigc::mem_fun(*this , &DataNoteBook::on_entry_grp_activate));

            auto lsswu = Gtk::manage( new  Gtk::ScrolledWindow());
            auto lsswg = Gtk::manage( new  Gtk::ScrolledWindow());

            this->m_lsUser = std::shared_ptr<VContenantUser>( new VContenantUser(*this));
            
            this->m_lsUser->signalChange().connect(sigc::mem_fun(this->m_graphWish , &GraphGui::force_redraw));
            this->m_lsUser->signalChange().connect(sigc::mem_fun(this->m_graphCapacity , &GraphGui::force_redraw));
            this->m_lsUser->signalChange().connect(sigc::mem_fun(*this , &DataNoteBook::update_n_permutat));
            

            this->m_lsGrp  = std::shared_ptr<VContenantGrp>( new VContenantGrp(*this));
            this->m_lsGrp->signalChange().connect(sigc::mem_fun(*this , &DataNoteBook::update_n_permutat));

            lsswu->add( *this->m_lsUser );
            adduser->pack_start( *lsswu , Gtk::PACK_EXPAND_WIDGET);


            this->m_size.set_range(1, 100); // Limite entre 0 et 100000
            this->m_size.set_increments(1, 10); // Pas de 1 par défaut, pas de 10 si Shift enfoncé
            this->m_size.set_value(2); // Valeur initiale
            this->m_size.set_numeric(true); // Affichage numérique

            this->m_dist.set_range(0, 100); // Limite entre 0 et 100000
            this->m_dist.set_increments(1, 10); // Pas de 1 par défaut, pas de 10 si Shift enfoncé
            this->m_dist.set_value(0); // Valeur initiale
            this->m_dist.set_numeric(true); // Affichage numérique


            auto grpEdit = Gtk::manage( new Gtk::HBox() );
            grpEdit->pack_start( this->m_addGrp ,Gtk::PACK_EXPAND_WIDGET);
            grpEdit->pack_start( *Gtk::manage( new Gtk::Label(" taille: ")) ,Gtk::PACK_SHRINK);
            grpEdit->pack_start( this->m_size ,Gtk::PACK_SHRINK);
            grpEdit->pack_start( *Gtk::manage( new Gtk::Label(" distance: "))  ,Gtk::PACK_SHRINK);
            grpEdit->pack_start( this->m_dist ,Gtk::PACK_SHRINK);


            adduser->pack_start( *grpEdit , Gtk::PACK_SHRINK );

            lsswg->add( *this->m_lsGrp );
            adduser->pack_start( *lsswg , Gtk::PACK_EXPAND_WIDGET);


            auto addTable = Gtk::manage( new Gtk::Notebook() );

            addTable->append_page( this->m_graphWish , "Souhaits" );
            addTable->append_page( this->m_graphCapacity , "Attributs" );

            auto f1 = Gtk::manage( new Gtk::Frame());
            auto f2 = Gtk::manage( new Gtk::Frame());

            f1->add(*adduser);
            f2->add(*addTable);

            this->pack1(*f1);
            this->pack2(*f2);

            this->m_res_dialog.get_content_area()->add(this->m_rb);

            this->m_res_dialog.signal_hide().connect(sigc::mem_fun( this->m_res_dialog, &DialogThread::stop));
            this->m_res_dialog.signal_show().connect(sigc::mem_fun( this->m_res_dialog, &DialogThread::run));
            this->m_res_dialog.set_title(" resultat ");
            this->m_res_dialog.set_resizable( true  );

            this->m_res_dialog.set_position(Gtk::WIN_POS_CENTER);

            this->m_pb.set_vexpand(true);
            this->m_pb.set_hexpand(true);

            this->m_param_dialog.get_content_area()->add(this->m_pb);

            this->m_param_dialog.signal_hide().connect(sigc::mem_fun( this->m_param_dialog, &DialogThread::stop));
            this->m_param_dialog.signal_show().connect(sigc::mem_fun( this->m_param_dialog, &DialogThread::run));
            this->m_param_dialog.set_title(" parametre algo genetique");
            this->m_param_dialog.set_resizable( true  );

            this->m_param_dialog.set_position(Gtk::WIN_POS_CENTER);

            auto hbtmp = Gtk::manage( new Gtk::HBox());
            auto processBp = Gtk::manage( new Gtk::Button("Calculer") );
            auto paramBp = Gtk::manage( new Gtk::Button("Parametre") );

            processBp->signal_clicked().connect(sigc::mem_fun(*this,&DataNoteBook::process));
            paramBp->signal_clicked().connect(sigc::mem_fun(this->m_param_dialog ,&DialogThread::show_all));

            
            hbtmp->pack_start(*processBp, Gtk::PACK_EXPAND_WIDGET);
            hbtmp->pack_start(*paramBp, Gtk::PACK_SHRINK);
            
            this->m_np.set_label("Np : nan");
            hbtmp->pack_start(this->m_np, Gtk::PACK_SHRINK);
            adduser->pack_start(*hbtmp, Gtk::PACK_SHRINK);
        }


        /// @brief Met à jour le nombre de permutations possibles
 
        void update_n_permutat(void)
        {
            size_t tts =0;
            for( size_t i = 0 ; i < this->get_genAlgo()->get_base_chromosone()->size() ; i++)
            {
                tts+=this->get_genAlgo()->get_base_chromosone()->at(i).get_caract().size;
            }

            if( tts != this->get_genAlgo()->get_base_gene().size() )
            {
                return ;
            }
            
            unsigned long long np = 1;
            unsigned long long sr = 0;
            for( size_t i = 0 ; i < this->get_genAlgo()->get_base_chromosone()->size() ; i++)
            {

                if(i == this->get_genAlgo()->get_base_chromosone()->size()-1)
                {
                    np+=1;
                    break;
                }

                auto n = this->get_genAlgo()->get_base_gene().size() - sr;
                auto fact_g = utilitys::factorial( n );


                np *= (fact_g / ( utilitys::factorial( this->get_genAlgo()->get_base_chromosone()->at(i).get_caract().size ) * utilitys::factorial( n - this->get_genAlgo()->get_base_chromosone()->at(i).get_caract().size ) ));
                
                sr+=this->get_genAlgo()->get_base_chromosone()->at(i).get_caract().size;

            }

            np/= utilitys::factorial( this->get_genAlgo()->get_base_chromosone()->size() );

            std::string res = std::to_string(np);

            if( res == "0")
            {
                res = "+Inf";
            }

            this->m_np.set_label("Np : " + res);

        }

        std::shared_ptr< VContenantUser > get_lsUser(void)
        {
            return this->m_lsUser;
        }
        std::shared_ptr< VContenantGrp > get_lsGrp(void)
        {
            return this->m_lsGrp;
        }

        #pragma region import export

        void import_project2csv(void)
        {

            CSVDialog dialog(*this->m_parent , Gtk::FILE_CHOOSER_ACTION_OPEN );

            int result = dialog.run();

            if (result == Gtk::RESPONSE_OK)
            {
                std::string filename = dialog.get_filename();

                std::ifstream file(filename);
                if(!file.is_open())
                {
                    LogicExceptionDialog popup("Impossible d'ouvrir le fichier en lecture");
                    popup.show();
                    return;
                }


                std::string line;
                std::getline(file, line); // Lire la première ligne (en-tête) et l'ignorer

                while (std::getline(file, line)) 
                {
                    if(line == "END_NAME_LIST")
                    {
                        break; // Fin de la section des utilisateurs
                    }

                    std::istringstream ss(line);
                    std::string name, id_str, sexe_str, niveau_str, attention_str, attracteur_str , repulseur_str;

                    std::getline(ss, name, ';');
                    std::getline(ss, id_str, ';');
                    std::getline(ss, sexe_str, ';');
                    std::getline(ss, niveau_str, ';');
                    std::getline(ss, attention_str, ';');
                    std::getline(ss, attracteur_str, ';');
                    std::getline(ss, repulseur_str, ';');

                    // Ajouter l'utilisateur à la liste
                    this->m_addUser.set_text(name);
                    this->on_entry_user_activate();

                    try
                    {
                        int id = std::stoi(id_str);
                        bool sexe = (sexe_str == "1" || sexe_str == "true");
                        int niveau = std::stoi(niveau_str);
                        int attention = std::stoi(attention_str);



                        // Récupérer le dernier utilisateur ajouté pour lui assigner les autres caractéristiques
                        auto& gene = this->get_genAlgo()->rget_base_gene().back();
                        gene.get()->get_caract().id = id;
                        gene.get()->get_caract().sexe = sexe;
                        gene.get()->get_caract().niveau = niveau;
                        gene.get()->get_caract().attention = attention;
                    

                        // Traiter les attracteurs
                        std::istringstream attracteur_ss(attracteur_str);
                        std::string attracteur_id;
                        while (std::getline(attracteur_ss, attracteur_id, ',')) 
                        {
                            if (!attracteur_id.empty()) 
                            {
                                try
                                {
                                    gene.get()->get_caract().attracteur.push_back(std::stoi(attracteur_id));
                                }
                                catch(const std::exception& e)
                                {
                                    std::cerr << "Erreur lors de la lecture d'un attracteur : " << e.what() << '\n';
                                    LogicExceptionDialog popup("Erreur lors de la lecture d'un attracteur : " + std::string(e.what()));
                                    popup.show();
                                    continue; // Passer à l'attracteur suivant
                                }
                                
                            }
                        }

                        // Traiter les répulseurs
                        std::istringstream repulseur_ss(repulseur_str);
                        std::string repulseur_id;
                        while (std::getline(repulseur_ss, repulseur_id, ',')) 
                        {
                            if (!repulseur_id.empty()) 
                            {
                                try
                                {
                                    gene.get()->get_caract().repulseur.push_back(std::stoi(repulseur_id));
                                }
                                catch(const std::exception& e)
                                {
                                    std::cerr << "Erreur lors de la lecture d'un répulseur : " << e.what() << '\n';
                                    LogicExceptionDialog popup("Erreur lors de la lecture d'un répulseur : " + std::string(e.what()));
                                    popup.show();
                                    continue; // Passer au répulseur suivant
                                }
                            }
                        }

                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << "Erreur lors de la lecture de l'utilisateur : " << e.what() << '\n';
                        LogicExceptionDialog popup("Erreur lors de la lecture de l'utilisateur : "+ name + " - " + std::string(e.what()));
                        popup.show();
                        continue; // Passer à l'utilisateur suivant
                    }
                }


                //puis les groupe
                std::getline(file, line); // Lire la première ligne (en-tête) et l'ignorer
                while(std::getline(file, line)) 
                {
                    std::istringstream ss(line);
                    std::string name, id_str, size_str, distance_str;

                    std::getline(ss, name, ';');
                    std::getline(ss, id_str, ';');
                    std::getline(ss, size_str, ';');
                    std::getline(ss, distance_str, ';');

                    try
                    {
                        int id = std::stoi(id_str);
                        int size = std::stoi(size_str);
                        int distance = std::stoi(distance_str);

                        // Ajouter le groupe à la liste
                        this->m_addGrp.set_text(name);
                        this->m_size.set_value(size);
                        this->m_dist.set_value(distance);
                        this->on_entry_grp_activate(); 
                        
                        // Récupérer le dernier groupe ajouté pour lui assigner les autres caractéristiques
                        auto& chromo = this->get_genAlgo()->get_base_chromosone()->back();
                        chromo.get_caract().id = id;
                        chromo.get_caract().size = size;
                        chromo.get_caract().distance = distance;
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << "Erreur lors de la lecture du groupe : " << e.what() << '\n';
                        LogicExceptionDialog popup("Erreur lors de la lecture du groupe : "+ name + " - " + std::string(e.what()));
                        popup.show();
                        continue; // Passer au groupe suivant
                    }
                }


            }
        }

        void export_project2csv(void)
        {
            CSVDialog dialog(*this->m_parent , Gtk::FILE_CHOOSER_ACTION_SAVE );

            int result = dialog.run();

            if (result == Gtk::RESPONSE_OK)
            {
                std::string filename = dialog.get_filename();

                std::ofstream file(filename);
                
                if(!file.is_open())
                {
                    LogicExceptionDialog popup("Impossible d'ouvrir le fichier en écriture");
                    popup.show();
                    return;
                }

                file << "Nom;Id;Sexe;Niveau;Attention;Attracteur;Repulseur\n";

                for( auto i =0; i < this->get_genAlgo()->get_base_gene().size(); i++ )
                {
                    auto gene = this->get_genAlgo()->get_base_gene()[i];
                    file << this->m_lsUser->get_contenant().at(i).get_name() << ";" << gene.get()->get_caract().id << ";" << gene.get()-> get_caract().sexe << ";" << gene.get()-> get_caract().niveau << ";" << gene.get()-> get_caract().attention << ";";

                    for( auto & att : gene.get()->get_caract().attracteur )
                    {
                        file << att << ",";
                    }
                    file << ";";

                    for( auto & att : gene.get()->get_caract().repulseur )
                    {
                        file << att << ",";
                    }

                    file << "\n";
                }

                //puis les groupe

                file << "END_NAME_LIST\n";

                file << "Nom;Id;Taille;Distance\n";

                for( auto i =0; i < this->get_genAlgo()->get_base_chromosone()->size(); i++ )
                {
                    auto chromo = this->get_genAlgo()->get_base_chromosone()->at(i);
                    file << this->m_lsGrp->get_contenant().at(i).get_name() << ";" << chromo.get_caract().id << ";" << chromo.get_caract().size << ";" << chromo.get_caract().distance << "\n";
                }
                
            }
        }

        #pragma endregion

        protected:

        void process(void)
        {
            if(this->m_processing)
                return;

            if( this->get_genAlgo()->get_base_gene().size() == 0  || this->get_genAlgo()->get_base_chromosone()->size() == 0  )
            {
                LogicExceptionDialog popup("Pas asser de données pour réaliser le calcule");
                popup.show();
                return ;
            }


            
                
            this->m_processing = true;

            this->get_genAlgo()->get_prop()->coef_souhait_multiple = this->m_pb.m_wishFactor.get_value();
            this->get_genAlgo()->get_prop()->coef_souhait = this->m_pb.m_wishGeneral.get_value();
            this->get_genAlgo()->get_prop()->coef_non_souhait = this->m_pb.m_ban.get_value();
            this->get_genAlgo()->get_prop()->coef_pariter = this->m_pb.m_parity.get_value();
            this->get_genAlgo()->get_prop()->coef_competence = this->m_pb.m_capacity.get_value();
            this->get_genAlgo()->get_prop()->coef_attention = this->m_pb.m_warn.get_value();
            this->get_genAlgo()->get_prop()->coef_homogeneiter = this->m_pb.m_sigma.get_value();


            try
            {
                auto start = std::chrono::high_resolution_clock::now();

                *this->get_resPopulation() =  this->get_genAlgo()->process();

                auto end = std::chrono::high_resolution_clock::now();

                // Calcul de la durée écoulée
                std::chrono::duration<double> elapsed = end - start;

                // Affichage du temps écoulé en secondes
                LogicExceptionDialog popup(std::to_string(this->get_resPopulation()->size()) + " solution.s différente.s trouvée.s en : " + std::to_string(elapsed.count()) + " seconde \n Seul les 20 meilleurs seront disponible");
                popup.show("Calcule fini");
                
                this->m_rb.update();

                this->m_res_dialog.show_all();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';

                LogicExceptionDialog popup(e.what());
                popup.show();
            }

            this->m_processing = false;

        }



        private : 

        #ifdef __CO_VERSION_DEBUG
        void load_exemple(void)
        {
            std::array< std::string , 12 > const ls_name{"Eleanor" ,"Manon"  ,"Eugenie"  , "Loris"  , "Timeo"  ,"Neo" , "Alexane" , "Lola"  ,"Lena" ,"Antoine" , "Anais" , "leevan" };
            std::array< bool , 12 > const ls_sexe{  true, true ,  true , false ,  false ,false , true , true , true , false , true , false};
            std::array< std::vector< unsigned short int > , 12 > ls_attract { std::vector< unsigned short int >{9},std::vector< unsigned short int >{},std::vector< unsigned short int >{7},std::vector< unsigned short int >{12,10,5},std::vector< unsigned short int >{},std::vector< unsigned short int >{5,9,12,3},std::vector< unsigned short int >{3,5,11},std::vector< unsigned short int >{11,10},std::vector< unsigned short int >{1},std::vector< unsigned short int >{12},std::vector< unsigned short int >{8,10},std::vector< unsigned short int >{10}};

            for(auto st : ls_name)
            {
                this->m_addUser.set_text(st);
                this->on_entry_user_activate();
            }

            int i =0;

            for(auto &l : this->m_lsUser->get_genAlgo()->rget_base_gene() )
            {
                l.get()->get_caract().sexe = ls_sexe[i];
                l.get()->get_caract().attracteur = ls_attract[i];
                i++;
            }

            this->m_size.set_value(4);
            this->m_dist.set_value(1);
            
            this->m_addGrp.set_text("Table 1 ");
            this->on_entry_grp_activate();
            this->m_dist.set_value(2);
            this->m_addGrp.set_text("Table 2 ");
            this->on_entry_grp_activate();
            this->m_dist.set_value(3);
            this->m_addGrp.set_text("Table 3 ");
            this->on_entry_grp_activate();
        }

        #endif
        

        void on_entry_user_activate(void)
        {
            if(this->m_addUser.get_text() == "")
            {
                return;
            }
            //verifie que l'netré n'a pas déja été ajouté
            for(auto & cont : this->m_lsUser->get_contenant())
            {
                if(this->m_addUser.get_text() == cont.get_name())
                {
                    LogicExceptionDialog er("nom deja existant");

                    er.show();

                    return;
                }
            }

            //ajoute l'entré
            this->m_lsUser->add( this->m_addUser.get_text());

            this->m_addUser.set_text("");

            return;
        }

        void update(void)
        {
        }

        void on_entry_grp_activate(void)
        {
            if(this->m_addGrp.get_text() == "")
            {
                return;
            }
            //verifie que l'netré n'a pas déja été ajouté
            for(auto & cont : this->m_lsGrp->get_contenant())
            {
                if(this->m_addGrp.get_text() == cont.get_name())
                {
                    LogicExceptionDialog er("nom deja existant");

                    er.show();

                    return;
                }
            }

            //ajoute l'entré
            this->m_lsGrp->add( this->m_addGrp.get_text() , this->m_size.get_value() , this->m_dist.get_value() );

            this->m_addGrp.set_text("");
        }

        Gtk::Entry m_addUser , m_addGrp;
        std::shared_ptr<VContenantGrp>  m_lsGrp;
        std::shared_ptr< VContenantUser > m_lsUser;
        Gtk::SpinButton m_dist , m_size;

        Gtk::Label m_np;
        
        CrossGraph m_graphWish;
        CapacityGraph  m_graphCapacity;

        DialogThread m_res_dialog,m_param_dialog;

        ParamNoteBook m_pb;
        ResultatNoteBook m_rb;

         bool m_processing;
        
};

#endif