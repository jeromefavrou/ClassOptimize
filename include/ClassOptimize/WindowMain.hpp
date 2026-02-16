#ifndef __WINDOWMAIN_HPP__
#define __WINDOWMAIN_HPP__

#include "../include/ClassOptimize/DataNoteBook.hpp"

/// @brief barre d'outil de la fenetre principale

class ToolbarMain : public Gtk::Toolbar , public TemplateGui
{
    public:

        ToolbarMain(DataNoteBook& db):Gtk::Toolbar( )
        {
            auto bp_import = Gtk::manage( new Gtk::ToolButton(Gtk::Stock::OPEN) );
            auto bp_export = Gtk::manage( new Gtk::ToolButton(Gtk::Stock::SAVE) );

            bp_import->set_label("Importer un projet");
            bp_export->set_label("Exporter le projet");

            //signal avec le parent

            bp_import->signal_clicked().connect(sigc::mem_fun( &db ,&DataNoteBook::import_project2csv));
            bp_export->signal_clicked().connect(sigc::mem_fun( &db ,&DataNoteBook::export_project2csv));

            this->append(*bp_import);
            this->append(*bp_export);
        }


    protected:

    private:
};

/// @brief gestion de la fenetre principale
class WindowMain : public Gtk::Window , public TemplateGui , protected Genetique::genitiqueSharedClass
{
    public:

        WindowMain( Genetique::genitiqueSharedClass & ref );

        void init(void);
        
    protected :

         DataNoteBook m_db;
        ToolbarMain m_toolbar;
    private:

};


WindowMain::WindowMain(Genetique::genitiqueSharedClass & ref) : Gtk::Window() , TemplateGui() ,  Genetique::genitiqueSharedClass(ref) ,m_db(ref , *this) , m_toolbar(m_db)
{
    this->m_parent = this;
}


void WindowMain::init(void)
{
    try
    {
        std::string icon_path;

        #ifdef __CO_VERSION_DEBUG
            icon_path = __CO_PROJECT_DIR +"ClassOptimize.png";
        #else
            #ifdef __linux__
                icon_path = "/usr/share/pixmaps/ClassOptimize.png";
            #else
                icon_path = "..\\resources\\icons\\ClassOptimize.png";
            #endif
        #endif


        //verifie que l'icon est bien acceeible avant de le set 
        std::ifstream icon_file(icon_path);
        if(!icon_file)
        {
            std::runtime_error e("icon not found at path : " + icon_path);
            throw e;
        }

        this->set_icon_from_file(  icon_path );
       
    }
    catch(const std::exception& e)
    {
        std::cerr << "icons  error : " << e.what() << '\n';
    }
    catch(Gdk::PixbufError & e)
    {
        std::cerr << "icons error : " <<e.what() << '\n';
    }
    

    this->unfullscreen();
	this->set_position(Gtk::WIN_POS_CENTER);
	this->resize(1200, 480);
    //this->maximize();

    Gtk::VBox * mainBox = Gtk::manage( new Gtk::VBox() );
    mainBox->pack_start( this->m_toolbar , Gtk::PACK_SHRINK);
    mainBox->pack_start( this->m_db , Gtk::PACK_EXPAND_WIDGET);

    this->add(*mainBox);

    
}

#endif // __WINDOWMAIN_HPP__