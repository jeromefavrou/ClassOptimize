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

#ifndef __GTKMMUTILITYS_HPP__
#define __GTKMMUTILITYS_HPP__

#include <string>
#include <thread>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <gtkmm-3.0/gtkmm/hvbox.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/switch.h>
#include <gtkmm-3.0/gtkmm/dialog.h>
#include <glibmm-2.4/glibmm/dispatcher.h>
#include <gtkmm-3.0/gtkmm/messagedialog.h>
#include <gtkmm-3.0/gtkmm/scale.h>
#include <gtkmm-3.0/gtkmm.h>


/// @brief supprime les enfant d'un conteneur Gtkmm
/// @param _wref //Conteneur parent Gtkmm
static void gtkmmRemoveChilds(Gtk::Container & _wref)
{
    for (auto& child : _wref.get_children()) 
        _wref.remove(*child);
}


class DisplayValueUser : public Gtk::Table
{
    public:

        DisplayValueUser(void):Gtk::Table(1,2),m_unit("")
        {
            this->m_title.set_label("unknow") ;
            this->attach(this->m_title, 0, 1, 0, 1 , Gtk::SHRINK, Gtk::SHRINK);
            this->attach(this->m_value, 1, 2, 0, 1 , Gtk::SHRINK, Gtk::SHRINK);
        }

        void set_title(std::string const & _ttl)
        {
            this->m_title.set_label(_ttl + " : ");
        }

        template<typename T> void set_value(T const & value)
        {
            this->m_value.set_label( std::to_string( value ) + this->m_unit );
        }

        void set_value(const double& value) 
        {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << value;
            this->m_value.set_label(stream.str() + this->m_unit);
        }

        void set_value(const std::string& value) 
        {

            this->m_value.set_label( value + this->m_unit);
        }

        void set_value(const float& value) 
        {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << value;
            this->m_value.set_label(stream.str() + this->m_unit);
        }

        void set_unit(std::string const & _unit)
        {
            this->m_unit  =_unit;
        }

    protected:

        std::string m_unit;
        Gtk::Label m_title , m_value;
        

};


/// @brief cree un bouton de type switch avec sont label
class SwitchUser : public Gtk::HBox
{
   public :
      SwitchUser( bool _default = false , std::string const & _label ="");


      void set_label(std::string const & _label);
      bool get_active(void);
      void set_active(bool _stat);

     
       Glib::SignalProxyProperty  signal_changed(void);

   private:
      Gtk::Switch m_switchButton;
      Gtk::Label m_label;

} ;

/// @brief initialisse le bouton
/// @param _default etat par defaut
/// @param _label nom du bouton
SwitchUser::SwitchUser(bool _default  , std::string const & _label )
{
    this->pack_start( this->m_label , Gtk::PACK_SHRINK);
    this->pack_start( this->m_switchButton , Gtk::PACK_SHRINK );

    this->set_label(_label);
    this->set_active(_default);
}


/// @brief met a jour le nom du bouton
/// @param _label 
void SwitchUser::set_label(std::string const & _label)
{
    this->m_label.set_label(_label + " ");
}

/// @brief renvoie l'etat du bouton
bool SwitchUser::get_active(void)
{
    return this->m_switchButton.get_active();
}

/// @brief impose un etat au bouton
/// @param _stat etat a imposer
void SwitchUser::set_active(bool _stat)
{
    this->m_switchButton.set_active(_stat); 
    this->m_switchButton.property_active().signal_changed();
}

/// @brief renvoie le signal associer au changement d'etat
/// @return 
Glib::SignalProxyProperty  SwitchUser::signal_changed(void)
{
    return  this->m_switchButton.property_active().signal_changed();
}

class ScaleUser : public Gtk::HBox
{
    public:
        ScaleUser(float val , float min , float max , float pas);
        ScaleUser(void);
        void init( float val , float min , float max , float pas )
        {
            auto adjustment =  Gtk::Adjustment::create(val, min, max, pas, 100, 0);
            this->m_scale =  Gtk::Scale( adjustment , Gtk::ORIENTATION_HORIZONTAL);
            m_scale.set_value_pos(Gtk::POS_RIGHT); // Position des valeurs à droite
            m_scale.set_draw_value(); // Affichage des valeurs

            this->pack_start(this->m_scale , Gtk::PACK_EXPAND_WIDGET);
        }

        float get_value(void)
        {
            return this->m_scale.get_value();
        }
    private:

        Gtk::Scale m_scale;
};
ScaleUser::ScaleUser(void):Gtk::HBox()
{
    
}



ScaleUser::ScaleUser(float val,float min , float max , float pas):Gtk::HBox()
{
    this->init(val , min , max , pas);
}

/// @brief cree un dialog dans un thread séparé
class DialogThread : public Gtk::Dialog
{
   public :
      DialogThread(void);
      ~DialogThread(void);

      void run(void);
      void stop(void);

   private :

      bool thread_func(void);

       std::unique_ptr<std::jthread> m_th;
       std::atomic<bool> m_continue , m_end ;
       Glib::Dispatcher m_signalDone;

       std::chrono::_V2::steady_clock::time_point m_start;
      
};

/// @brief initialisation de la fenetre 
/// @param  
DialogThread::DialogThread(void):Gtk::Dialog()
{
    this->m_signalDone.connect(sigc::mem_fun(this, &DialogThread::show_all));
    this->m_continue = false;
    this->m_end = false;
    this->m_th = nullptr;
}

/// @brief arret de la fenetre et de son thread
/// @param  
DialogThread::~DialogThread(void)
{
    this->stop();
}

/// @brief demare le thread
/// @param  
void DialogThread::run(void)
{
    std::chrono::duration<double> elapsed_seconds{std::chrono::steady_clock::now() - this->m_start};

    if(this->m_continue || elapsed_seconds.count() < 500 )
        return ;

    this->m_end = false;
    this->m_continue = true;
    this->m_th.reset(new std::jthread(&DialogThread::thread_func, this)) ;
}

/// @brief arret du thread
/// @param  
void DialogThread::stop(void)
{
    if(!this->m_continue || !this->m_th )
        return;
    
    this->m_continue = false;
    if(this->m_th->joinable())
        this->m_th->join();

    
    this->m_th.reset();

    this->m_start = std::chrono::steady_clock::now();
}

/// @brief routine du thread
/// @param  
/// @return 
bool DialogThread::thread_func(void)
{
    while( this->m_continue || !this->m_th)
    {
        this->m_signalDone.emit();

        //emet un delai avant la mise a jour de la fenetre
        const std::chrono::duration<double, std::milli> duration(500);

        //s'assure que apres le delais on est tjr ouvert
        if(!this->m_continue)
            break;

        std::this_thread::sleep_for(duration);
    }

    this->m_end = true;
    return true;
}


/// @brief permet d'aficher dans une fenetre d'erreur une exception logic
class LogicExceptionDialog : public std::logic_error
{
    public : 
        LogicExceptionDialog(std::string const & _msg);

        void show( std::string const & _titre) const;
};


LogicExceptionDialog::LogicExceptionDialog(std::string const & _msg) : std::logic_error(_msg)
{
    
}

void LogicExceptionDialog::show( std::string const & _titre = "Erreur" )const
{

    std::cerr << this->what() << std::endl;

    Gtk::MessageDialog dialog( _titre );

    dialog.set_secondary_text(this->what());

    dialog.run();
}


/// @brief classe pour la gestion de l'import et de l'export des données au format csv

class CSVDialog : public Gtk::FileChooserDialog
{
    public:
        CSVDialog(Gtk::Window& parent , Gtk::FileChooserAction action = Gtk::FILE_CHOOSER_ACTION_OPEN);
        
    private:
};

CSVDialog::CSVDialog(Gtk::Window& parent , Gtk::FileChooserAction action) : Gtk::FileChooserDialog(parent , "Choisir un fichier" , action)
{
    auto filter = Gtk::FileFilter::create();
    filter->set_name("Fichiers CSV");
    filter->add_pattern("*.csv");
    this->add_filter(filter);

    // Boutons
    this->add_button("_Annuler", Gtk::RESPONSE_CANCEL);
    if( action == Gtk::FILE_CHOOSER_ACTION_OPEN )
        this->add_button("_Ouvrir", Gtk::RESPONSE_OK);
    else
        this->add_button("_Enregistrer", Gtk::RESPONSE_OK);

}


#endif