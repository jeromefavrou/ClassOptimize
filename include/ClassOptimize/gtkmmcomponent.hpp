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

#ifndef __GTKMMCOMPONENT_HPP__
#define __GTKMMCOMPONENT_HPP__

#include "../include/ClassOptimize/gtkmmutilitys.hpp"
#include "../include/ClassOptimize/gtkmmGraph.hpp"
#include "../include/ClassOptimize/utilitys.hpp"

#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/viewport.h>
#include <gtkmm-3.0/gtkmm/drawingarea.h>
//#include <cairomm-1.0/cairomm/context.h>


class ResultatNoteBook : public Gtk::VBox , public Genetique::genitiqueSharedClass, public TemplateGui
{
    public:

     ResultatNoteBook(Genetique::genitiqueSharedClass const & ref , Gtk::Window& parent):Gtk::VBox(false , 5) , Genetique::genitiqueSharedClass(ref),TemplateGui()
     {
        this->m_parent = &parent;
     
        auto slt = Gtk::manage( new Gtk::HBox());

        this->m_solution.signal_changed().connect(sigc::mem_fun(*this,&ResultatNoteBook::solution_change));

        slt->pack_start( *Gtk::manage(new Gtk::Label("Solution : ")) , Gtk::PACK_SHRINK );
        slt->pack_start( this->m_solution ,Gtk::PACK_EXPAND_WIDGET );
        
        this->pack_start(*slt , Gtk::PACK_SHRINK);
        

        this->pack_start( this->m_taux2_parity_gen , Gtk::PACK_SHRINK);
        this->pack_start( this->m_taux_parity_gen , Gtk::PACK_SHRINK);
        this->pack_start( this->m_taux_wish_gen , Gtk::PACK_SHRINK);
        this->pack_start( this->m_taux_wish_honor_gen , Gtk::PACK_SHRINK);
        this->pack_start( this->m_taux_unwish_gen , Gtk::PACK_SHRINK);
        this->pack_start(this->m_taux_capacity_gen , Gtk::PACK_SHRINK);
        this->pack_start( this->m_attention_gen , Gtk::PACK_SHRINK);

        this->m_taux_parity_gen.set_title("Ratio de parité");
        this-> m_taux2_parity_gen.set_title("Parité respecté");
        this->m_taux_wish_gen.set_title("Souhait respecté");
        this->m_taux_wish_honor_gen.set_title("Au moins 1 souhait respecté");
        this->m_taux_unwish_gen.set_title("Désintérêt respecté");
        this->m_taux_capacity_gen.set_title("Niveau moyen");
        this->m_attention_gen.set_title("Score d'attention");

        this->m_taux_parity_gen.set_unit("");
        this->m_taux2_parity_gen.set_unit("%");
        this->m_taux_wish_gen.set_unit("%");
        this->m_taux_wish_honor_gen.set_unit("%");
        this->m_taux_unwish_gen.set_unit("%");
        this->m_taux_capacity_gen.set_unit(" / 4 ");
        this->m_attention_gen.set_unit("");
        
        auto grp = Gtk::manage( new Gtk::HBox());

        this->m_grp_solution.signal_changed().connect(sigc::mem_fun(*this,&ResultatNoteBook::solution_grp_change));


        grp->pack_start( *Gtk::manage(new Gtk::Label("Groupe : ")) , Gtk::PACK_SHRINK );
        grp->pack_start( this->m_grp_solution ,Gtk::PACK_EXPAND_WIDGET );
        
        this->pack_start(*grp , Gtk::PACK_SHRINK);

        this->pack_start( this->m_taux_parity_grp , Gtk::PACK_SHRINK);
        this->pack_start( this->m_taux2_parity_grp , Gtk::PACK_SHRINK);
        this->pack_start( this->m_taux_wish_grp , Gtk::PACK_SHRINK);
        this->pack_start( this->m_taux_wish_honor_grp , Gtk::PACK_SHRINK);
        this->pack_start( this->m_taux_unwish_grp , Gtk::PACK_SHRINK);
        this->pack_start(this->m_taux_capacity_grp , Gtk::PACK_SHRINK);
        this->pack_start( this->m_attention_grp , Gtk::PACK_SHRINK);

        this->m_taux_parity_grp.set_title("Ratio de parité");
        this-> m_taux2_parity_grp.set_title("Parité respecté");
        this->m_taux_wish_grp.set_title("Souhait respecté");
        this->m_taux_wish_honor_grp.set_title("Au moins 1 souhait respecté");
        this->m_taux_unwish_grp.set_title("Désintérêt respecté");
        this->m_taux_capacity_grp.set_title("Niveau moyen");
        this->m_attention_grp.set_title("Score d'attention");

        this->m_taux_parity_grp.set_unit("");
        this-> m_taux2_parity_grp.set_unit("%");
        this->m_taux_wish_grp.set_unit("%");
        this->m_taux_wish_honor_grp.set_unit("%");
        this->m_taux_unwish_grp.set_unit("%");
        this->m_taux_capacity_grp.set_unit(" / 4");
        this->m_attention_grp.set_unit("");

        auto ls = Gtk::manage( new Gtk::Frame());
        auto lsc = Gtk::manage( new  Gtk::ScrolledWindow());


            ls->set_vexpand(true);
            ls->set_hexpand(true);

            lsc->set_vexpand(true);
            lsc->set_hexpand(true);

            show_grp.set_vexpand(true);
            show_grp.set_hexpand(true);

        lsc->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        ls->add(*lsc);
    
        lsc->add(show_grp);

        this->pack_start( *ls , Gtk::PACK_EXPAND_WIDGET);

        //ajout d'un bouton export
        auto exportBp = Gtk::manage( new Gtk::Button("Exporter") );
        exportBp->signal_clicked().connect(sigc::mem_fun(*this,&ResultatNoteBook::exporter));
        this->pack_start(*exportBp , Gtk::PACK_SHRINK);
     }

     void update()
     {
        if(this->get_resPopulation()->size()==0)
            return;

        this->m_solution.remove_all();

        int ilimite = 20 ;

        for( auto const & r : *this->get_resPopulation())
        {
            if(ilimite == 0)
                break;
            
            this->m_solution.append("Score : " + std::to_string( r.get_score() ) );
            ilimite--;
        }

         this->m_solution.set_active(0);
         
     }

     void exporter()
     {
        CSVDialog dialog(*this->m_parent , Gtk::FILE_CHOOSER_ACTION_SAVE );

            int result = dialog.run();

            if (result == Gtk::RESPONSE_OK)
            {
                std::string filename = dialog.get_filename();

                if( filename.substr(filename.size() - 4) != ".csv" )
                {
                    filename += ".csv";
                }

                std::ofstream file(filename);
                
                if(!file.is_open())
                {
                    LogicExceptionDialog popup("Impossible d'ouvrir le fichier en écriture");
                    popup.show();
                    return;
                }

                //exporte tout les groupe de la solution selectionné
                int idx = this->m_solution.get_active_row_number();

                if(idx < 0)
                    return ;

                auto const & idv = this->get_resPopulation()->at(idx);

                //list tout les groupe etablie
                for( auto  & t : *this->get_genAlgo()->get_base_chromosone())
                {
                    file << utilitys::findKeyByValue( *this->get_keyChromozone() , (unsigned int)t.get_caract().id ) ;


                    ///pour une solution donné liste tout les gene de ce groupe
                    auto ids = Genetique::Mesure::lsId(this->get_resPopulation()->at(idx) , *this->get_genAlgo()->get_base_chromosone() , (unsigned int)t.get_caract().id-1 );
                    
                    for(auto const & id : ids )
                    {
                        file << ";" << utilitys::findKeyByValue( *this->get_keyGene()  , id ) ;
                    }

                    file << std::endl;
                }

                file << std::endl;


                file.close();

            }
     }

     void solution_change(void)
     {
        
         if(!this->get_resPopulation())
            return;
        if(this->get_resPopulation()->size()==0)
            return;

        int idx = this->m_solution.get_active_row_number();

        if(idx < 0)
            return ;

        double mixRatio = Genetique::Mesure::parite( this->get_resPopulation()->at(idx) ) ;
        this->m_taux_parity_gen.set_value("F = "+std::to_string((int)(mixRatio*100)) + "% / H = " + std::to_string((int)((1.0-mixRatio)*100))+"%");
        this->m_taux2_parity_gen.set_value(100- Genetique::Mesure::pariteHonnor( this->get_resPopulation()->at(idx) , *this->get_genAlgo()->get_base_chromosone() ) *100 );
        this->m_taux_capacity_gen.set_value(  Genetique::Mesure::niveauMoyen(this->get_resPopulation()->at(idx ) ) );
        this->m_taux_wish_gen.set_value( Genetique::Mesure::tauxAttract(this->get_resPopulation()->at(idx ) ,*this->get_genAlgo()->get_base_chromosone() ) *100) ;
        this->m_taux_wish_honor_gen.set_value(  Genetique::Mesure::tauxAttractHonnor( this->get_resPopulation()->at(idx ) ,*this->get_genAlgo()->get_base_chromosone() ) *100) ;
        this->m_attention_gen.set_value( Genetique::Mesure::attention(this->get_resPopulation()->at(idx ) ,*this->get_genAlgo()->get_base_chromosone()));
        this->m_taux_unwish_gen.set_value(Genetique::Mesure::tauxRepuls(this->get_resPopulation()->at(idx ) ,*this->get_genAlgo()->get_base_chromosone()) *100);
        this->m_grp_solution.remove_all();


        for( auto  & t : *this->get_genAlgo()->get_base_chromosone())
        {
            
            this->m_grp_solution.append( utilitys::findKeyByValue( *this->get_keyChromozone() , (unsigned int)t.get_caract().id ) );
        }
        
        this->m_grp_solution.set_active(0);
        
     }

     void solution_grp_change(void)
     {

        if(this->get_resPopulation()->size()==0)
            return;


         int idx = this->m_solution.get_active_row_number();

         int idxGrp = this->m_grp_solution.get_active_row_number();

         if(idx < 0 || idxGrp < 0)
            return;


        gtkmmRemoveChilds(show_grp);

        float mixRatio = Genetique::Mesure::parite( this->get_resPopulation()->at(idx) , *this->get_genAlgo()->get_base_chromosone() ,idxGrp );
        float tauxMix =  Genetique::Mesure::pariteHonnor( this->get_resPopulation()->at(idx) , *this->get_genAlgo()->get_base_chromosone() ,idxGrp ) ;

        this->m_taux_parity_grp.set_value("Ratio de parité : F = " + std::to_string((int)(mixRatio*100)) + "% / H = " + std::to_string((int)((1.0-mixRatio)*100))  + "%");
        this->m_taux2_parity_grp.set_value(100-(tauxMix*100));
        this->m_taux_capacity_grp.set_value( Genetique::Mesure::niveauMoyen( this->get_resPopulation()->at(idx) , *this->get_genAlgo()->get_base_chromosone() ,idxGrp ) );
        this->m_taux_wish_grp.set_value(Genetique::Mesure::tauxAttract(this->get_resPopulation()->at(idx) , *this->get_genAlgo()->get_base_chromosone() ,idxGrp)*100);
        this->m_taux_wish_honor_grp.set_value(Genetique::Mesure::tauxAttractHonnor(this->get_resPopulation()->at(idx) , *this->get_genAlgo()->get_base_chromosone() ,idxGrp)*100);
        this->m_attention_grp.set_value(Genetique::Mesure::attention(this->get_resPopulation()->at(idx ) ,*this->get_genAlgo()->get_base_chromosone() , idxGrp));
        this->m_taux_unwish_grp.set_value(Genetique::Mesure::tauxRepuls(this->get_resPopulation()->at(idx ) ,*this->get_genAlgo()->get_base_chromosone() ,idxGrp ) *100) ;

        auto ids = Genetique::Mesure::lsId(this->get_resPopulation()->at(idx) , *this->get_genAlgo()->get_base_chromosone() ,idxGrp);

        

        for(auto const & id : ids )
        {
                show_grp.pack_start( *Gtk::manage( new Gtk::Label( utilitys::findKeyByValue( *this->get_keyGene()  , id ) )) ,Gtk::PACK_EXPAND_WIDGET);
        }
        
        show_grp.show_all();

     }

    protected:

    Gtk::ComboBoxText m_solution , m_grp_solution;

    Gtk::VBox show_grp;


    DisplayValueUser m_taux_parity_gen ,m_taux_wish_gen ,m_taux_wish_honor_gen , m_taux_parity_grp , m_taux_wish_grp , m_taux_wish_honor_grp , m_taux_unwish_gen , m_taux_unwish_grp;
    DisplayValueUser m_taux_capacity_gen , m_taux_capacity_grp , m_taux2_parity_gen , m_taux2_parity_grp , m_attention_gen , m_attention_grp;
};


class ParamNoteBook : public TemplateGui , public Gtk::VBox , public Genetique::genitiqueSharedClass
{

    public:

        ParamNoteBook(Genetique::genitiqueSharedClass const & ref):TemplateGui(), Gtk::VBox(false , 5) , Genetique::genitiqueSharedClass(ref) , m_table(19,4)
        {   

            this->m_table.attach(*Gtk::manage( new Gtk::Label("Nombre cycle limite:")), 1, 3, 0, 1 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach( this->m_nMutation, 1, 3, 1, 2 , Gtk::SHRINK, Gtk::SHRINK);

            this->m_table.attach(*Gtk::manage( new Gtk::Label(" Nombre de Population:")), 1, 3, 2, 3 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach( this->m_nGeneration, 1, 3, 3, 4 , Gtk::SHRINK, Gtk::SHRINK);

            this->m_table.attach(*Gtk::manage( new Gtk::Label(" % stabilité  :")), 1, 3, 4, 5 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach( this->m_tauxStab, 1, 3, 5, 6 , Gtk::SHRINK, Gtk::SHRINK);

            this->m_table.attach(*Gtk::manage( new Gtk::Label(" temps limite :")), 1, 3, 6, 7 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach( this->m_timeOut, 1, 3, 7, 8 , Gtk::SHRINK, Gtk::SHRINK);

            this->m_table.attach(*Gtk::manage( new Gtk::Label(" % ( probabilité ) selection pour croisement par cycle:")), 1, 3, 8, 9 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach( this->m_tauxSel, 1, 3, 9, 10 , Gtk::SHRINK, Gtk::SHRINK);

            this->m_table.attach(*Gtk::manage( new Gtk::Label(" % ( probabilité ) mutation par cycle:")), 1, 3, 10, 11 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach( this->m_tauxMut, 1, 3, 11, 12 , Gtk::SHRINK, Gtk::SHRINK);

            this->m_table.attach(*Gtk::manage( new Gtk::Label("héterogène")), 1, 2, 12, 13 , Gtk::SHRINK, Gtk::SHRINK);

            this->m_table.attach(*Gtk::manage( new Gtk::Label("homogène")), 3, 4, 12, 13 , Gtk::SHRINK, Gtk::SHRINK);

            this->m_table.attach(*Gtk::manage( new Gtk::Label("Coefficient de pondération des souhaits multiples: ")), 0, 1, 13, 14 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach(this->m_wishFactor, 1, 4, 13, 14 , Gtk::FILL | Gtk::EXPAND,Gtk::FILL | Gtk::EXPAND);
            
            this->m_table.attach(*Gtk::manage( new Gtk::Label("Coefficient des souhait: ")), 0, 1, 14, 15 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach(this->m_wishGeneral, 1, 4, 14, 15 , Gtk::FILL | Gtk::EXPAND,Gtk::FILL | Gtk::EXPAND);

            this->m_table.attach(*Gtk::manage( new Gtk::Label("Coefficient de la paritée: ")), 0, 1, 15, 16 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach(this->m_parity, 1, 4, 15, 16 , Gtk::FILL | Gtk::EXPAND,Gtk::FILL | Gtk::EXPAND);

            this->m_table.attach(*Gtk::manage( new Gtk::Label("Coefficient du niveau: ")), 0, 1, 16, 17 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach(this->m_capacity, 1, 4, 16, 17 , Gtk::FILL | Gtk::EXPAND,Gtk::FILL | Gtk::EXPAND);

            this->m_table.attach(*Gtk::manage( new Gtk::Label("Coefficient du désintérêt: ")), 0, 1, 17, 18 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach(this->m_ban, 1, 4, 17, 18 , Gtk::FILL | Gtk::EXPAND,Gtk::FILL | Gtk::EXPAND);

            this->m_table.attach(*Gtk::manage( new Gtk::Label("Coefficient de l'attention: ")), 0, 1, 18, 19 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach(this->m_warn, 1, 4, 18, 19 , Gtk::FILL | Gtk::EXPAND,Gtk::FILL | Gtk::EXPAND);

            this->m_table.attach(*Gtk::manage( new Gtk::Label("Coefficient d'homogénéité global: ")), 0, 1, 19, 20 , Gtk::SHRINK, Gtk::SHRINK);
            this->m_table.attach(this->m_sigma, 1, 4, 19, 20 , Gtk::FILL | Gtk::EXPAND,Gtk::FILL | Gtk::EXPAND);
           
            this->m_nMutation.set_numeric(true); // Affichage numérique
            this->m_nMutation.set_range(100, 10000); // Limite entre 0 et 100000
            this->m_nMutation.set_increments(100, 10); // Pas de 1 par défaut, pas de 10 si Shift enfoncé
            this->m_nMutation.set_value( this->get_genAlgo()->cycle_arret ); // Valeur initiale
            this->m_nMutation.signal_value_changed().connect(sigc::mem_fun(*this,&ParamNoteBook::spinChangeNmut));
            
            
            this->m_nGeneration.set_numeric(true); // Affichage numérique
            this->m_nGeneration.set_range(100, 10000); // Limite entre 0 et 100000
            this->m_nGeneration.set_increments(10, 10); // Pas de 1 par défaut, pas de 10 si Shift enfoncé
            this->m_nGeneration.set_value(this->get_genAlgo()->n_individu ); // Valeur initiale
            this->m_nGeneration.signal_value_changed().connect(sigc::mem_fun(*this,&ParamNoteBook::spinChangeNgen));
            
            
            this->m_tauxStab.set_numeric(true);
            this->m_tauxStab.set_range(0, 100);
            this->m_tauxStab.set_increments(5, 1);
            this->m_tauxStab.set_value( this->get_genAlgo()->taux_stabiliter * 100);
            this->m_tauxStab.signal_value_changed().connect(sigc::mem_fun(*this,&ParamNoteBook::spinChangetstab));
            
            
            this->m_timeOut.set_numeric(true);
            this->m_timeOut.set_range(1, 300);
            this->m_timeOut.set_increments(1, 1);
            this->m_timeOut.set_value( this->get_genAlgo()->temps_limite );
            this->m_timeOut.signal_value_changed().connect(sigc::mem_fun(*this,&ParamNoteBook::spinChangetimeout));
            
            
            this->m_tauxSel.set_numeric(true);
            this->m_tauxSel.set_range(0, 100);
            this->m_tauxSel.set_increments(10, 1);
            this->m_tauxSel.set_value( this->get_genAlgo()->taux_selection * 100);
            this->m_tauxSel.signal_value_changed().connect(sigc::mem_fun(*this,&ParamNoteBook::spinChangetsel));
            
            
            this->m_tauxMut.set_numeric(true);
            this->m_tauxMut.set_range(0, 100);
            this->m_tauxMut.set_increments(10, 1);
            this->m_tauxMut.set_value( this->get_genAlgo()->taux_mutation * 100 );
            this->m_tauxMut.signal_value_changed().connect(sigc::mem_fun(*this,&ParamNoteBook::spinChangetmut));
            

            this->m_wishFactor.init( this->get_genAlgo()->get_prop()->coef_souhait_multiple ,-2 , 2 , 0.1);
            this->m_wishGeneral.init( this->get_genAlgo()->get_prop()->coef_souhait ,-2 , 2 , 0.1);
            this->m_parity.init( this->get_genAlgo()->get_prop()->coef_pariter ,-2 , 2 , 0.1);
            this->m_capacity.init( this->get_genAlgo()->get_prop()->coef_competence ,-2 , 2 , 0.1);
            this->m_ban.init( this->get_genAlgo()->get_prop()->coef_non_souhait ,-2 , 2 , 0.1);
            this->m_warn.init(  this->get_genAlgo()->get_prop()->coef_attention ,-2 , 2 , 0.1);
            this->m_sigma.init( this->get_genAlgo()->get_prop()->coef_homogeneiter ,0 , 1 , 0.1);


            auto bp_auto = Gtk::manage(new Gtk::Button("Auto"));

            bp_auto->signal_clicked().connect(sigc::mem_fun( *this ,&ParamNoteBook::EstimateParam));
            this->pack_start( *bp_auto );
            this->pack_start( this->m_table , Gtk::PACK_EXPAND_WIDGET);
        }

        void EstimateParam(void)
        {
            this->m_nMutation.set_value( 2.2 * std::pow( this->get_genAlgo()->get_base_gene().size() , 2.5 ) );
            this->m_timeOut.set_value( 0.001 * std::pow( this->get_genAlgo()->get_base_gene().size() , 3.2 ) );

            double tmp = 5000.0/static_cast<double>(this->m_nMutation.get_value());
            this->m_tauxStab.set_value( tmp > 1 ? tmp : 1);
            this->m_nGeneration.set_value( 0.93 * std::pow( this->get_genAlgo()->get_base_gene().size() , 2.13 ) );

            this->m_tauxSel.set_value( 15 );
            this->m_tauxMut.set_value( 10 );
        }

        void spinChangeNmut( void )
        {
           this->get_genAlgo()->cycle_arret =  this->m_nMutation.get_value();
        }

        void spinChangeNgen( void )
        {
           this->get_genAlgo()->n_individu =  this->m_nGeneration.get_value();
        }

        void spinChangetstab( void )
        {
           this->get_genAlgo()->taux_stabiliter =  (float)this->m_tauxStab.get_value() / 100;
        }

        void spinChangetimeout( void )
        {
           this->get_genAlgo()->temps_limite =  this->m_timeOut.get_value();
        }

        void spinChangetsel( void )
        {
           this->get_genAlgo()->taux_selection =  (float)this->m_tauxSel.get_value() / 100;
        }

        void spinChangetmut( void )
        {
           this->get_genAlgo()->taux_mutation =  (float) this->m_tauxMut.get_value() / 100;
        }
        
        ScaleUser m_wishFactor , m_wishGeneral , m_parity , m_capacity, m_ban , m_warn , m_sigma;

    protected :
        


    private:

        Gtk::VBox m_heuristicParam;

        Gtk::Table m_table;

        Gtk::SpinButton m_nMutation , m_nGeneration , m_tauxStab , m_timeOut , m_tauxSel , m_tauxMut ;

        
};
 
class Contenant : public  Gtk::HBox
{
    public:

    Contenant(std::string const & name="" , int _attrib = 0 , int _attrib2 = 0):Gtk::HBox(),m_attribut(_attrib),m_attribut2(_attrib2)
    {
        this->pack_start( this->m_remove , Gtk::PACK_SHRINK); 

        this->m_remove.set_label("X");

        this->pack_start( this->m_name, Gtk::PACK_EXPAND_WIDGET);

        if( _attrib2 != 0 || _attrib!=0)
        {
            this->pack_start(  this->m_attrib, Gtk::PACK_EXPAND_WIDGET);
            this->pack_start( this->m_attrib2, Gtk::PACK_EXPAND_WIDGET);
            
            this->m_attrib.set_label(std::to_string(_attrib));
            this->m_attrib2.set_label(std::to_string(_attrib2));
        }

        this->m_name.set_label(name);
        
    }

    std::string const get_name(void) const
    {
        return this->m_name.get_label();
    }

    Gtk::Button & get_remove(void)
    {
        return this->m_remove;
    }




    private: 

    Gtk::Button m_remove;
    Gtk::Label m_name , m_attrib , m_attrib2;
    int m_attribut,m_attribut2;
};

class VContenant : public Gtk::VBox
{
    public:

        VContenant(void):Gtk::VBox()
        {   
        }

        virtual void add(std::string const & name , int _attrib=0 ,int _attrib2=0)
        {
            this->m_container.emplace_back(name , _attrib , _attrib2);
            this->m_container.back().get_remove().signal_clicked().connect(sigc::bind<std::string>(sigc::mem_fun(*this,&VContenant::remove_action), name));
            this->pack_start( this->m_container.back() , Gtk::PACK_SHRINK);

            this->show_all();

            this->m_signalChange.emit();
        }

        std::vector<Contenant> & get_contenant(void) 
        {
            return this->m_container;
        }

        sigc::signal<void> signalChange(void)
        {
            return this->m_signalChange;
        }

        virtual ~VContenant(void){}
    protected:

        virtual void remove_action(std::string _name)
        {
            //suprime la ligne demmandé
            gtkmmRemoveChilds(*this);


            for(size_t i = 0 ; i < this->m_container.size() ; i++)
            {
                if(this->m_container[i].get_name() == _name)
                {
                    this->m_container.erase(this->m_container.begin() + i);
                    break;
                }

            }


            for(auto & c : this->m_container )
            {
                this->pack_start( c , Gtk::PACK_SHRINK);
            }

            this->show_all();

            this->m_signalChange.emit();
        }

        std::vector<Contenant> m_container;
        sigc::signal<void> m_signalChange;
};

class VContenantUser : public VContenant , public Genetique::genitiqueSharedClass
{
    public:

    VContenantUser(Genetique::genitiqueSharedClass const & ref):VContenant(),Genetique::genitiqueSharedClass(ref)
    {   
    }

    void add(std::string const & name , int _attrib=0 ,int _attrib2=0) override
    {
        //on cree la partie graphique de la liste
        this->m_container.emplace_back(name , _attrib , _attrib2);
        this->m_container.back().get_remove().signal_clicked().connect(sigc::bind<std::string>(sigc::mem_fun(*this,&VContenantUser::remove_action), name));
        this->pack_start( this->m_container.back() , Gtk::PACK_SHRINK);
        this->show_all();

        //on met a jour la base de donné utile

        auto newGene = Genetique::Gene::ptr( new Genetique::Gene() );

        newGene->get_caract().id = this->get_keyGene()->size()+1;

        //attribut un id unique
        while( true )
        {
            bool attrib = false;

            for (const auto& pair : *this->get_keyGene()) 
            {
                if (pair.second == newGene->get_caract().id ) 
                {
                    newGene->get_caract().id++;

                    attrib = true;
                    break;
                }
            }

            if( !attrib )
                break;
        }
        this->get_keyGene()->insert({name , newGene->get_caract().id})  ;

        this->get_genAlgo()->rget_base_gene().push_back( newGene );

        this->m_signalChange.emit();
    }

    protected:

    void remove_action(std::string _name) override
    {   
        for(size_t i = 0 ; i < this->m_container.size() ; i++)
        {
            if(this->m_container[i].get_name() == _name)
            {
                this->m_container.erase(this->m_container.begin() + i);
                break;
            }

        }
        auto it = this->get_keyGene()->find(_name);

        // Vérifiez si l'élément existe 
        if (it == this->get_keyGene()->end()) 
            return; 

        //supprime toute les enfant graphique
        gtkmmRemoveChilds(*this);
        

        //Supprime la donné
        for( auto it2 = this->get_genAlgo()->rget_base_gene().begin() ; it2 != this->get_genAlgo()->rget_base_gene().end(); it2++)
        {
            //si les id sont les meme que la clé a suprrimer on suprrime
            if( it->second == (*it2)->get_caract().id )
            {
                this->get_genAlgo()->rget_base_gene().erase(it2) ;
                break;
            }
        }
        
        //suprime la clé demandé
        this->get_keyGene()->erase(it);


        //on recrée les element graphique restant
        for(auto & c : this->m_container )
            this->pack_start( c , Gtk::PACK_SHRINK);

        this->show_all();

        this->m_signalChange.emit();
    }

};


class VContenantGrp : public VContenant , public Genetique::genitiqueSharedClass
{
    public:

    VContenantGrp(Genetique::genitiqueSharedClass const & ref):VContenant() , Genetique::genitiqueSharedClass(ref)
    {   
    }

    void add(std::string const & name , int _attrib=0 ,int _attrib2=0) override
    {
        //on cree la partie graphique de la liste
        this->m_container.emplace_back(name , _attrib , _attrib2);
        this->m_container.back().get_remove().signal_clicked().connect(sigc::bind<std::string>(sigc::mem_fun(*this,&VContenantGrp::remove_action), name));
        this->pack_start( this->m_container.back() , Gtk::PACK_SHRINK);
        this->show_all();
        
        
        //on met a jour la base de donné utile

        Genetique::Chromosone newCrom ;

        newCrom.get_caract().id = this->get_keyChromozone()->size()+1;
        newCrom.get_caract().distance = _attrib2;
        newCrom.get_caract().size = _attrib;

        //attribut un id unique
        while( true )
        {
            bool attrib = false;

            for (const auto& pair : *this->get_keyChromozone()) 
            {
                if (pair.second == newCrom.get_caract().id ) 
                {
                    newCrom.get_caract().id++;

                    attrib = true;
                    break;
                }
            }

            if( !attrib )
                break;
        }
        this->get_keyChromozone()->insert({name , newCrom.get_caract().id})  ;

        this->get_genAlgo()->get_base_chromosone()->push_back( newCrom );

        this->m_signalChange.emit();
    }

    protected:

    void remove_action(std::string _name) override
    {

        for(size_t i = 0 ; i < this->m_container.size() ; i++)
        {
            if(this->m_container[i].get_name() == _name)
            {
                this->m_container.erase(this->m_container.begin() + i);
                break;
            }

        }

         auto it = this->get_keyChromozone()->find(_name);

        // Vérifiez si l'élément existe 
        if (it == this->get_keyChromozone()->end()) 
            return; 

        //supprime toute les enfant graphique
        gtkmmRemoveChilds(*this);
        

        //Supprime la donné
        for( auto it2 = this->get_genAlgo()->get_base_chromosone()->begin() ; it2 != this->get_genAlgo()->get_base_chromosone()->end(); it2++)
        {
            //si les id sont les meme que la clé a suprrimer on suprrime
            if( it->second == it2->get_caract().id )
            {
                this->get_genAlgo()->get_base_chromosone()->erase(it2) ;
                break;
            }
        }
        
        //suprime la clé demandé
        this->get_keyChromozone()->erase(it);


        //on recrée les element graphique restant
        for(auto & c : this->m_container )
            this->pack_start( c , Gtk::PACK_SHRINK);

        this->show_all();

        this->m_signalChange.emit();
    }
};






#endif
