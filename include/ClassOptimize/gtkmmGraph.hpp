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

#ifndef __GTKMMGRAPH_HPP__
#define __GTKMMGRAPH_HPP__

#include "../include/ClassOptimize/gtkmmutilitys.hpp"

#include "../include/ClassOptimize/genetique.hpp"

#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/viewport.h>
#include <gtkmm-3.0/gtkmm/drawingarea.h>
//#include <cairomm-1.0/cairomm/context.h>

#include <cmath>

class Point
{
    public :
        Point(void):x(.0f),y(.0f){}
        Point(double _x , double _y):x(_x),y(_y){}

        virtual Point operator=(Point const & cpy)
        {
            this->x = cpy.x;
            this->y = cpy.y;
            return *this;
        }

        virtual Point operator-(Point const & cpy)
        {
            return Point( this->x - cpy.x , this->y - cpy.y);
        }

        virtual Point operator-=(Point const & cpy)
        {
            this->x -= cpy.x;
            this->y -= cpy.y;

            return *this;
        }

        virtual Point operator-(double value)
        {
            return Point( this->x - value , this->y - value);
        }

        virtual Point operator-=(double value)
        {
            this->x -= value;
            this->y -= value;

            return *this;
        }


        virtual Point operator+(Point const & cpy)
        {
            return Point( this->x + cpy.x , this->y + cpy.y);
        }

        virtual Point operator+=(Point const & cpy)
        {
            this->x += cpy.x;
            this->y += cpy.y;

            return *this;
        }

        virtual Point operator+(double value)
        {
            return Point( this->x + value , this->y + value);
        }

        virtual Point operator+=(double value)
        {
            this->x += value;
            this->y += value;

            return *this;
        }

        virtual Point operator/(Point const & cpy)
        {
            return Point( this->x / cpy.x , this->y / cpy.y);
        }

        virtual Point operator/(double value)
        {
            return Point( this->x / value , this->y / value);
        }


        virtual Point operator*(Point const & cpy)
        {
            return Point( this->x * cpy.x , this->y * cpy.y);
        }

        virtual Point operator*(double value)
        {
            return Point( this->x * value , this->y * value);
        }


        virtual Point operator*=(Point const & cpy)
        {
            this->x *= cpy.x;
            this->y *= cpy.y;

            return *this;
        }

        virtual Point operator*=(double value)
        {
            this->x *= value;
            this->y *= value;

            return *this;
        }

        virtual Point operator/=(Point const & cpy)
        {
            this->x /= cpy.x;
            this->y /= cpy.y;
            
            return *this;
        }

        virtual Point operator/=(double value)
        {
            this->x /= value;
            this->y /= value;

            return *this;
        }

        virtual void floor(void)
        {
            this->x = std::floor(this->x);
            this->y = std::floor(this->y);
        }

        static Point floor(Point const & p)
        {
            return Point( std::floor(p.x) , std::floor(p.y));
        }

        virtual void ceil(void)
        {
            this->x = std::ceil(this->x);
            this->y = std::ceil(this->y);
        }

        static Point ceil(Point const & p)
        {
            return Point( std::ceil(p.x) , std::ceil(p.y));
        }

        virtual float lenght(void)
        {
            return std::sqrt( std::pow( this->x , 2)  + std::pow(this->y , 2) );
        }

        virtual float ratio(void)
        {
            return this->x / this->y ;
        }

        virtual void normalize(void)
        {
            float l = this->lenght();

            this->x /= l ;
            this->y /= l ;
        }

        virtual bool valid(void)
        {
            return !std::isnan( this->x ) && !std::isnan( this->y ) ;
        }

        double x , y ;

        static bool cmpY(Point const & yA , Point const & yB)
        {
            return yB.y > yA.y; 
        }

        static bool cmpX(Point const & xA , Point const & xB)
        {
            return xB.x > xA.x; 
        }

        static bool ncmpY(Point const & yA , Point const & yB)
        {
            return yB.y < yA.y; 
        }

        static bool ncmpX(Point const & xA , Point const & xB)
        {
            return xB.x < xA.x; 
        }
};

/// @brief objet patron de partage par poiteur de donné essentiel
class TemplateGui 
{
   public:
      TemplateGui(void);

      virtual void addCssProvider(Glib::RefPtr<Gtk::CssProvider> _cssProvider);
      virtual void addParent(Gtk::Window* _parent);

      Glib::RefPtr<Gtk::CssProvider> const getCssProvider(void);
      Gtk::Window* const getParent(void);


      Glib::RefPtr<Gtk::CssProvider> const atCssProvider(void);
      Gtk::Window* const atParent(void);


      virtual ~TemplateGui(void);
      
      private :
protected :
      Gtk::Window* m_parent;

      Glib::RefPtr<Gtk::CssProvider> m_cssProvider;

};

TemplateGui::TemplateGui(void)
{
    this->m_parent = nullptr;
}

TemplateGui::~TemplateGui(void)
{
    this->m_parent = nullptr;


}

//setter
void TemplateGui::addCssProvider(Glib::RefPtr<Gtk::CssProvider> _cssProvider)
{
    this->m_cssProvider = _cssProvider;
}

//setter
void TemplateGui::addParent(Gtk::Window* _parent)
{
    this->m_parent  = _parent;
}


//getter
Glib::RefPtr<Gtk::CssProvider> const TemplateGui::getCssProvider(void)
{
    return this->m_cssProvider;
}

//getter
Gtk::Window* const TemplateGui::getParent(void)
{
    return this->m_parent;
}


//acces securisé 
Glib::RefPtr<Gtk::CssProvider> const TemplateGui::atCssProvider(void)
{
    if(!this->m_cssProvider)
        throw LogicExceptionDialog("bad provider acces");

    return this->m_cssProvider;
}

//acces securisé 
Gtk::Window* const TemplateGui::atParent(void)
{
    if(this->m_parent == nullptr)
       throw LogicExceptionDialog("bad raw window acces");

    return this->m_parent;
}


class GraphGui : public Gtk::DrawingArea , public TemplateGui
{
    public:

        enum class GirdType : int{ NORMAL , POLAR };

        GraphGui( void);

        virtual ~GraphGui(void){}

        //virtual void addCssProvider(Glib::RefPtr<Gtk::CssProvider>  _provider);


        void force_redraw()
        {
            auto win = this->get_window();
            if (win)
            {
                Gdk::Rectangle r(0, 0, this->get_allocation().get_width(), this->get_allocation().get_height());
                win->invalidate_rect(r, false);
            }
        }


    protected:

        void calculateResolutionScreen(void)
        {
            const int width = this->get_allocation().get_width();
            const int height = this->get_allocation().get_height();

            this->m_resolutionScreen = (float)height / (float)width  ;

        }

        void drawRect(const Cairo::RefPtr<Cairo::Context>& cr , Point const & _point, Point const & _size )
        {
            cr->set_line_width(1);

            cr->rectangle( _point.x , _point.y  , _size.x , _size.y);
            cr->fill();

            cr->close_path();
        }

        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override
        {
            this->calculateResolutionScreen();

            cr->stroke();

            return true;
        }

        virtual bool catchGraph( GdkEventButton * bp_event )
        {

            return true;
        }

        bool unCatchGraph( GdkEventButton * bp_event )
        {
            if(bp_event->button == GDK_BUTTON_PRIMARY)
                this->m_catchGraph = false;

            this->m_actionBp = false;

            return true;
        }


        bool scrollDelta(GdkEventScroll* scroll_event)
        {
        
            if(scroll_event->delta_y > 0)
            {
                this->m_scale.x*=1.1;
            }
            else if(scroll_event->delta_y < 0)
            {
                this->m_scale.x*=0.9;
            }

            this->force_redraw();

            return true;
        }
        virtual bool showPos(GdkEventMotion* motion_event)
        {
            return true;
        }
        

        bool m_catchGraph , m_actionBp;

        //unsigned int m_sizePoint;

        float m_resolutionScreen;

        Point m_catchPoint;
        Point m_minCatch , m_maxCatch;



        Point m_scale;
        Point m_mousePos;
        Point m_index;


};

GraphGui::GraphGui(void):Gtk::DrawingArea(),TemplateGui()
{
  this->m_index= Point(0 , 0);
  this->m_scale = Point(1 , 1);

  this->m_actionBp = false;
  this->m_catchGraph=false;

  this->add_events(Gdk::POINTER_MOTION_MASK);
  this->add_events(Gdk::SMOOTH_SCROLL_MASK);
  this->add_events(Gdk::BUTTON_PRESS_MASK);
  this->add_events(Gdk::BUTTON_RELEASE_MASK);
  

  this->signal_scroll_event().connect( sigc::mem_fun(*this,&GraphGui::scrollDelta ));
  this->signal_button_press_event().connect(sigc::mem_fun(*this ,&GraphGui::catchGraph) );
  this->signal_button_release_event().connect(sigc::mem_fun(*this ,&GraphGui::unCatchGraph) );
  this->signal_motion_notify_event().connect( sigc::mem_fun(*this,&GraphGui::showPos ));
}


class CrossGraph : public GraphGui , public Genetique::genitiqueSharedClass
{
    public:

        CrossGraph(Genetique::genitiqueSharedClass const & ref):GraphGui(),Genetique::genitiqueSharedClass(ref)
        {
        };


        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override
        {
            this->calculateResolutionScreen();

            this->drawAxe(cr);
            this->drawWish(cr);

            cr->stroke();

            return true;
        }

        protected : 

        Point m_indexCross;

        void drawWish(const Cairo::RefPtr<Cairo::Context>& cr )
        {
            //commance par replir en noir toute les case non utilisable
            cr->set_source_rgb(0.0, 0.0, 0.0);
            for(auto i = 0u ; i < this->get_keyGene()->size() ;i++)
            {
                int idx =(i+1-(size_t)this->m_index.x); 
                int idy =(i+1-(size_t)this->m_index.y);

                if(idx <= 0 || idy <= 0)
                    continue;

                this->drawRect(cr,Point(idx*this->m_indexCross.x,idy*this->m_indexCross.y),this->m_indexCross);
            }
            cr->stroke();
            //ensuite on dessine les case souhait
            for(auto i = 0u ; i < this->get_keyGene()->size() ;i++)
            {
                int idx =(i+1-(size_t)this->m_index.y); 

                for(auto y = 0u ; y < this->get_keyGene()->size() ;y++)
                {
                    if(i == y)
                        continue;

                    int idy =(y+1-(size_t)this->m_index.x);

                    if(idx <= 0 || idy <= 0)
                        continue;
                        
                     //determine les clé  fonction du clic
                    auto itx = this->keyByIdx((unsigned int) i);
                    auto ity = this->keyByIdx((unsigned int) y);

                    //on determine les donné en fonction de l'id des clé
                    auto genex = this->vectPtrGeneByID( itx->second );
                    auto geney = this->vectPtrGeneByID( ity->second );
                    //on colorie les case si nescesaire
                    
                    if( !genex->freeWish( geney->get_caract().id) )
                    {
                        cr->set_source_rgb(0.0, 1.0,0.0);
                        this->drawRect(cr,Point(idy*this->m_indexCross.x+1,idx*this->m_indexCross.y+1),this->m_indexCross-1);
                        cr->stroke();
                    }
                    else if(!genex->freeBan(geney->get_caract().id) )
                    {
                        cr->set_source_rgb(1.0, 0.0,0.0);
                        this->drawRect(cr,Point(idy*this->m_indexCross.x+1,idx*this->m_indexCross.y+1),this->m_indexCross-1);
                        cr->stroke();
                    }
                    

                }
            }

            cr->stroke();
        }

        void drawAxe(const Cairo::RefPtr<Cairo::Context>& cr )
        {
            const int sizeMaj = 3;
            const int sizeMin = 1;
            Pango::FontDescription font;

            font.set_family("Monospace");
            font.set_weight(Pango::Weight::WEIGHT_LIGHT);
            font.set_size(14 * PANGO_SCALE*  this->m_scale.x);

            auto layoutX = create_pango_layout("Nom");
            layoutX->set_font_description(font);

            int text_width , text_height , text_width_max=0;
            layoutX->get_pixel_size(text_width, text_height);

            this->m_indexCross.y = text_height +10;

            if(text_width_max < text_width)
                text_width_max = text_width;


            cr->set_line_width(sizeMaj);
            cr->set_source_rgb(0.0, 0.0, 0.0);
            
            //dessine la aprtie vertical

            for(auto const & keys : *this->get_keyGene())
            {
                auto layout = create_pango_layout(keys.first);
                layout->set_font_description(font);

                int tmpx=0,tmpY=0;

                layout->get_pixel_size(tmpx, tmpY);

                if(text_width_max < tmpx)
                    text_width_max = tmpx;
            }

            this->m_indexCross.x = text_width_max +10;
            text_height+=10;

            auto maxwidth = (text_width_max+10) * (this->get_keyGene()->size()+1-(size_t)this->m_index.x);

            int iy = 0;
            for(auto const & keys : *this->get_keyGene())
            {
                if( iy < (int)this->m_index.y)
                {
                    iy++;
                    continue;
                }

                auto layout = create_pango_layout(keys.first);
                layout->set_font_description(font);

                int tmpx=0,tmpY=0;

                layout->get_pixel_size(tmpx, tmpY);

                cr->move_to(0,text_height);
                layout->show_in_cairo_context(cr);
                
                text_height+=tmpY+10;

                cr->close_path();
                cr->stroke();
                cr->set_line_width(sizeMin);

                cr->move_to(0, text_height);
                cr->line_to(maxwidth,  text_height );
                cr->close_path();
                cr->stroke();

                cr->set_line_width(sizeMaj);
            }
            cr->close_path();
            cr->stroke();

            cr->move_to(text_width_max+10, 0);
            cr->line_to(text_width_max+10,  text_height );


            cr->close_path();
            cr->stroke();

            //dessinne la partie horizontal
            text_width = text_width_max+10;
            int ix =0;
            for(auto const & keys : *this->get_keyGene())
            {
                if( ix < (int)this->m_index.x)
                {
                    ix++;
                    continue;
                }

                auto layout = create_pango_layout(keys.first);
                layout->set_font_description(font);

                cr->move_to(text_width,0);
                layout->show_in_cairo_context(cr);
                
                text_width+=text_width_max+10;

                cr->close_path();
                cr->stroke();
                cr->set_line_width(sizeMin);

                cr->move_to(text_width, 0);
                cr->line_to(text_width,  text_height );
                cr->close_path();
                cr->stroke();

                cr->set_line_width(sizeMaj);

            }
            cr->close_path();
            cr->stroke();


            layoutX->get_pixel_size(text_width, text_height);
            //coin haut gauche
            cr->move_to(0,0);
            layoutX->show_in_cairo_context(cr);
            
            cr->move_to(0, text_height+10);
            cr->line_to(maxwidth,  text_height+10 );

            cr->close_path();

            cr->stroke();
        }


        bool showPos(GdkEventMotion* motion_event) override
        {

            this->m_mousePos.x = motion_event->x;
            this->m_mousePos.y = motion_event->y;

            if(this->m_catchGraph)
            {

            auto deltaPoint = this->m_mousePos - this->m_catchPoint ;


            if(this->get_keyGene()->size() !=0)
            {
                this->m_index.x -= 1.0/this->m_scale.x*this->m_resolutionScreen*0.5*deltaPoint.x / this->get_allocation().get_width() ;
                this->m_index.y -= 1.0/this->m_scale.x*0.5*deltaPoint.y / this->get_allocation().get_height() ;

                if(this->m_index.x < 0)
                    this->m_index.x=0;

                if(this->m_index.y < 0)
                    this->m_index.y=0; 

                if(this->m_index.y > this->get_keyGene()->size() - 1)
                    this->m_index.y=this->get_keyGene()->size() - 1;
                
                if(this->m_index.x > this->get_keyGene()->size() - 1)
                    this->m_index.x=this->get_keyGene()->size() - 1; 
            }

            }

            
            if(this->m_catchGraph)
                this->force_redraw();

            return true;
        }

        bool catchGraph( GdkEventButton * bp_event ) override
        {
            if(bp_event->button == GDK_BUTTON_SECONDARY && !this->m_actionBp)
            {
                this->m_actionBp = true;
                if(this->m_mousePos.x > this->m_indexCross.x && this->m_mousePos.y > this->m_indexCross.y )
                {
                    auto res = this->m_mousePos/(this->m_indexCross);
                    res.floor();
                    res-=1;
                    res.x+=(size_t)this->m_index.x;
                    res.y+=(size_t)this->m_index.y;

                    if(res.x != -1 && res.y != -1 && res.x < this->get_keyGene()->size() && res.y < this->get_keyGene()->size() && res.x!=res.y)
                    {
                        //determine les clé  fonction du clic
                        auto itx = this->keyByIdx((unsigned int) res.x);
                        auto ity = this->keyByIdx((unsigned int) res.y);

                        //on determine les donné en fonction de l'id des clé
                        auto genex = this->vectPtrGeneByID( itx->second );
                        auto geney = this->vectPtrGeneByID( ity->second );

                       
                        auto statWish = geney->freeWish(genex->get_caract().id );
                        auto statBan = geney->freeBan(genex->get_caract().id);

                        if( statWish && statBan)
                            geney->addWish( genex->get_caract().id );
                            
                        
                        else if( !statWish && statBan)
                        {
                            geney->removeWish( genex->get_caract().id );
                            geney->addBan( genex->get_caract().id );
                        }
                        
                        else if( statWish && !statBan)
                        {
                            geney->removeBan( genex->get_caract().id );
                            geney->removeWish( genex->get_caract().id );
                        }
                        
                        this->force_redraw();
                    }
                    
                }
                
            }

            if(this->m_catchGraph || bp_event->button != GDK_BUTTON_PRIMARY)
                return true;

            this->m_catchGraph = true;

            this->m_catchPoint = this->m_mousePos;

            return true;
        }
};


class CapacityGraph : public GraphGui, public Genetique::genitiqueSharedClass
{
    public:

        CapacityGraph(Genetique::genitiqueSharedClass const & ref):GraphGui(),Genetique::genitiqueSharedClass(ref)
        {

        };


        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override
        {

            this->calculateResolutionScreen();

            this->drawAxe(cr);
            this->drawAttrib(cr);

            cr->stroke();

            return true;
        }

        protected : 

        Point m_indexCross;

        void drawAttrib(const Cairo::RefPtr<Cairo::Context>& cr )
        {
           //determine les clé  fonction du clic
                    
             for(auto i = 0u ; i < this->get_keyGene()->size() ;i++)
            {

                auto it = this->keyByIdx( i );

                //on determine les donné en fonction de l'id des clé

                auto gene = this->vectPtrGeneByID( it->second );
                
                int idx =(i+1-(size_t)this->m_index.y); 

                for(auto y = 0u ; y < 3u ;y++)
                {

                    int idy =(y+1);

                    if(idx <= 0 || idy <= 0)
                        continue;

                    
                    if(y == 0)
                    {
                        if( !gene->get_caract().sexe )
                        {
                            cr->set_source_rgb(0.0, 0.0,1.0);
                            this->drawRect(cr,Point(idy*this->m_indexCross.x+1,idx*this->m_indexCross.y+1),this->m_indexCross-1);
                            cr->stroke();
                        }
                        else
                        {
                            cr->set_source_rgb(1.0, 0.1,0.3);
                            this->drawRect(cr,Point(idy*this->m_indexCross.x+1,idx*this->m_indexCross.y+1),this->m_indexCross-1);
                            cr->stroke();
                        }
                    }
                    
                    else if(y == 1)
                    {
                        

                        cr->set_source_rgb(1.0, float(gene->get_caract().niveau + 2) /4.0 , 0.3);
                        this->drawRect(cr,Point(idy*this->m_indexCross.x+1,idx*this->m_indexCross.y+1),this->m_indexCross-1);
                        cr->stroke();

                    }
                    
                    
                    else if(y == 2)
                    {
                        

                        cr->set_source_rgb(1.0, float(gene->get_caract().attention + 2) /4.0 , 0.3);
                        this->drawRect(cr,Point(idy*this->m_indexCross.x+1,idx*this->m_indexCross.y+1),this->m_indexCross-1);
                        cr->stroke();

                    }
                    
                }
            }
        }

        void drawAxe(const Cairo::RefPtr<Cairo::Context>& cr )
        {
            const int sizeMaj = 3;
            const int sizeMin = 1;
            Pango::FontDescription font;

            font.set_family("Monospace");
            font.set_weight(Pango::Weight::WEIGHT_LIGHT);
            font.set_size(14 * PANGO_SCALE*  this->m_scale.x);

            auto layoutX = create_pango_layout("Nom");
            layoutX->set_font_description(font);

            auto layout1 = create_pango_layout("Sexe");
            layout1->set_font_description(font);


            auto layout2 = create_pango_layout("Niveau");
            layout2->set_font_description(font);

            auto layout3 = create_pango_layout("Attention");
            layout3->set_font_description(font);

            int text_width , text_height , text_width_max=0;
            layout3->get_pixel_size(text_width, text_height);

            this->m_indexCross.y = text_height +10;

            if(text_width_max < text_width)
                text_width_max = text_width;

            cr->move_to(0,0);
            layoutX->show_in_cairo_context(cr);


            cr->set_line_width(sizeMaj);
            cr->set_source_rgb(0.0, 0.0, 0.0);
            
            //dessine la aprtie vertical

            for(auto const & keys : *this->get_keyGene())
            {
                auto layout = create_pango_layout(keys.first);
                layout->set_font_description(font);

                int tmpx=0,tmpY=0;

                layout->get_pixel_size(tmpx, tmpY);

                if(text_width_max < tmpx)
                    text_width_max = tmpx;
            }

            this->m_indexCross.x = text_width_max +10;
            text_height+=10;

             cr->move_to(this->m_indexCross.x,0);
            layout1->show_in_cairo_context(cr);


             cr->move_to(this->m_indexCross.x*2,0);
            layout2->show_in_cairo_context(cr);

             cr->move_to(this->m_indexCross.x*3,0);
            layout3->show_in_cairo_context(cr);


            cr->move_to(0, this->m_indexCross.y );
            cr->line_to(this->m_indexCross.x*4,  this->m_indexCross.y );

            cr->move_to(this->m_indexCross.x, 0 );
            cr->line_to(this->m_indexCross.x,  this->m_indexCross.y *  (this->get_keyGene()->size()+1 -(size_t)this->m_index.y) );

            cr->move_to(this->m_indexCross.x*2, 0 );
            cr->line_to(this->m_indexCross.x*2,  this->m_indexCross.y *  (this->get_keyGene()->size()+1 -(size_t)this->m_index.y) );

            cr->move_to(this->m_indexCross.x*3, 0 );
            cr->line_to(this->m_indexCross.x*3,  this->m_indexCross.y *  (this->get_keyGene()->size()+1 -(size_t)this->m_index.y) );

            cr->move_to(this->m_indexCross.x*4, 0 );
            cr->line_to(this->m_indexCross.x*4,  this->m_indexCross.y *  (this->get_keyGene()->size()+1 -(size_t)this->m_index.y) );
            
            //dessine la aprtie vertical

             int iy =0;
            for(auto const & keys : *this->get_keyGene())
            {
                if( iy < (int)this->m_index.y)
                {
                    iy++;
                    continue;
                }
                auto layout = create_pango_layout(keys.first);
                layout->set_font_description(font);

                int tmpx=0,tmpY=0;

                layout->get_pixel_size(tmpx, tmpY);

                cr->move_to(0,text_height);
                layout->show_in_cairo_context(cr);
                
                text_height+=tmpY+10;

                cr->close_path();
                cr->stroke();
                cr->set_line_width(sizeMin);

                cr->move_to(0, text_height);
                cr->line_to(this->m_indexCross.x*4,  text_height );
                cr->close_path();
                cr->stroke();

                cr->set_line_width(sizeMaj);
                
                
            }
            cr->close_path();
            cr->stroke();
        }

        bool showPos(GdkEventMotion* motion_event) override
        {

            this->m_mousePos.x = motion_event->x;
            this->m_mousePos.y = motion_event->y;

            if(this->m_catchGraph)
            {

            auto deltaPoint = this->m_mousePos - this->m_catchPoint ;


            if(this->get_keyGene()->size() !=0)
            {
                this->m_index.x -= 1.0/this->m_scale.x*this->m_resolutionScreen*0.5*deltaPoint.x / this->get_allocation().get_width() ;
                this->m_index.y -= 1.0/this->m_scale.x*0.5*deltaPoint.y / this->get_allocation().get_height() ;

                if(this->m_index.x < 0)
                    this->m_index.x=0;

                if(this->m_index.y < 0)
                    this->m_index.y=0; 

                if(this->m_index.y > get_keyGene()->size() - 1)
                    this->m_index.y=get_keyGene()->size() - 1;
                
                if(this->m_index.x > get_keyGene()->size() - 1)
                    this->m_index.x=get_keyGene()->size() - 1; 
            }

            }

            
            if(this->m_catchGraph)
                this->force_redraw();

            return true;
        }

        bool catchGraph( GdkEventButton * bp_event ) override
        {
            if(bp_event->button == GDK_BUTTON_SECONDARY && !this->m_actionBp)
            {
                this->m_actionBp = true;
                if(this->m_mousePos.x > this->m_indexCross.x && this->m_mousePos.y > this->m_indexCross.y )
                {
                    auto res = this->m_mousePos/(this->m_indexCross);
                    res.floor();
                    res-=1;
                    res.x+=(size_t)this->m_index.x;
                    res.y+=(size_t)this->m_index.y;

                    //determine les clé  fonction du clic
                    auto it = this->keyByIdx((unsigned int) res.y);

                    //on determine les donné en fonction de l'id des clé
                    auto gene = this->vectPtrGeneByID( it->second );
                   

                    if(res.x == 0 && res.y != -1  && res.y < this->get_keyGene()->size() )
                    {
                       gene->get_caract().sexe = !gene->get_caract().sexe;

                        this->force_redraw();
                    }
                    
                    

                    if(res.x == 1 && res.y != -1  && res.y < this->get_keyGene()->size() )
                    {
                        gene->get_caract().niveau = gene->get_caract().niveau +1;
                        if(gene->get_caract().niveau > 2)
                            gene->get_caract().niveau = -2;
                    

                        this->force_redraw();
                    } 

                    if(res.x == 2 && res.y != -1  && res.y < this->get_keyGene()->size() )
                    {

                        gene->get_caract().attention = gene->get_caract().attention +1;
                        if(gene->get_caract().attention > 2)
                            gene->get_caract().attention = -2;

                        this->force_redraw();
                    }
                 
                    
                }
                
            }

            if(this->m_catchGraph || bp_event->button != GDK_BUTTON_PRIMARY)
                return true;

            this->m_catchGraph = true;

            this->m_catchPoint = this->m_mousePos;

            return true;
        }
};


#endif