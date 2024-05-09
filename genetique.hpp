#ifndef __GENETIQUE_HPP
#define __GENETIQUE_HPP

#include <vector>
#include <memory>
#include <thread>
#include <algorithm>
#include <random>
#include <chrono>


using std::vector;
using std::shared_ptr;
using std::thread;


namespace Genetique
{

	/* class definisant les parametre qui influron le modele genetique  */
	class Parametre
	{
		public:
			typedef shared_ptr<Parametre> ptr;

			double coef_souhait , coef_non_souhait , coef_pariter , coef_competence , coef_attention , coef_souhait_multiple , coef_homogeneiter ;

			Parametre(void)
			{
				this->reset();
			}

			virtual ~Parametre(void)
			{
			}

			Parametre operator=(Parametre const & _cpy)
			{
				this->coef_souhait = _cpy.coef_souhait ; 
				this->coef_non_souhait = _cpy.coef_non_souhait;
				this->coef_pariter = _cpy.coef_pariter;
				this->coef_competence = _cpy.coef_competence;
				this->coef_attention = _cpy.coef_attention;
				this->coef_souhait_multiple = _cpy.coef_souhait_multiple;
				this->coef_homogeneiter = _cpy.coef_homogeneiter;

				return *this;
			}

			virtual void reset(void)
			{
				this->coef_souhait = 1.0 ; 
				this->coef_non_souhait = 1.0;
				this->coef_pariter = 1.0;
				this->coef_competence = 1.0;
				this->coef_attention = 1.0;
				this->coef_souhait_multiple = 1.0;
				this->coef_homogeneiter = 1.0;
			}

		protected:

		private:
	};

	
	//class qui gere les caracteristique d'un gene
	class Gene 
	{
		public:
			
			typedef shared_ptr<Gene> ptr;
			typedef vector<Gene> vect;
			typedef vector< ptr > vectPtr;

			struct Caracteristique
			{
				short int niveau , attention ;
				bool sexe ;
				unsigned short int id;
				vector< unsigned short int > attracteur;
				vector< unsigned short int > repulseur;
			};

			Gene(void)
			{
				this->m_caract.niveau = 0 ;
				this->m_caract.attention  = 0;
				this->m_caract.sexe  = false;
				this->m_caract.id  = 0;

				this->score = 0;
			}

			Gene operator=(Gene const & cpy)
			{
				this->score = cpy.score;
				this->m_caract = cpy.m_caract;
				
				return *this;
			}

			bool operator!=(Gene const & cpy)
			{
				
				return cpy.m_caract.id != this->m_caract.id;
			}

			struct Caracteristique & get_caract(void)
			{
				return this->m_caract;
			}

			float evaluate_attract(  vectPtr::iterator beg , vectPtr::iterator end , float combo_factor = 1)
			{
				this->score = 0;
				float combo = 1;

				if(combo_factor > 0.001 || combo_factor <= -0.001)
				{
					for( auto it = beg ; it != end ; it++)
					{
						if( std::find( this->m_caract.attracteur.begin()  , this->m_caract.attracteur.end()  , (*it)->get_caract().id ) != this->m_caract.attracteur.end() )
						{
								score+= combo_factor / combo + 1 - combo_factor;
								combo+=1;
						}
					}
				}
				else
					for( auto it = beg ; it != end ; it++)
						if( std::find( this->m_caract.attracteur.begin()  , this->m_caract.attracteur.end()  , (*it)->get_caract().id ) != this->m_caract.attracteur.end() )
							score+=1.0;
						


				return this->score;
			}

			float evaluate_repuls(  vectPtr::iterator beg , vectPtr::iterator end )
			{
				this->score = 0;
				for( auto it = beg ; it != end ; it++)
					if( std::find( this->m_caract.repulseur.begin()  , this->m_caract.repulseur.end()  , (*it)->get_caract().id ) != this->m_caract.repulseur.end() )
						score-=1;
					
				
				return this->score;
			}

			float score;


		protected:

			struct Caracteristique m_caract;

		private:
	};



	class Chromosone
	{

		public:

		typedef shared_ptr <Chromosone > ptr;
		typedef vector< Chromosone> vect;
		typedef vector< ptr > vectPtr;

		struct Caracteristique
		{
			short int distance , size;
			unsigned short int id;

		};

		
		Chromosone(void)
		{
			this->m_caract.id  = 0;
			this->m_caract.distance  = 0;
			this->m_caract.size  = 0;
			this->score = 0;
		}

		struct Caracteristique & get_caract(void)
		{
			return this->m_caract;
		}
		
		float score;

		protected:

			struct Caracteristique m_caract;
			

	};



		/*classe patron pour definir les utilisare commun au differente classe de lalgo genetique*/
	class Patron
	{
		public:
			Patron(void)
			{
				this->reset();
			}

			Patron(Patron const & _p )
			{
				this->set_prop( _p.get_prop() );
				this->m_base_gene =  _p.get_base_gene() ; 
				this->m_base_chromosone =  _p.get_base_chromosone() ; 
			}

			virtual void reset(void)
			{
				this->m_prop.reset();
			}

			void set_prop(Parametre::ptr const & _cpy)
			{
				this->m_prop = _cpy;
			}


			Parametre::ptr const get_prop(void) const
			{
				return this->m_prop;
			}



			void set_base_chromosone(shared_ptr<Chromosone::vect> const & _cpy)
			{
				this->m_base_chromosone = _cpy;
			}


			shared_ptr<Chromosone::vect> const get_base_chromosone(void) const
			{
				return this->m_base_chromosone;
			}

			

			void set_base_gene(Gene::vectPtr const & _cpy)
			{
				this->m_base_gene = _cpy;
			}

			Gene::vectPtr & rget_base_gene(void)
			{
				return this->m_base_gene;
			}

			Gene::vectPtr const get_base_gene(void)const
			{
				return this->m_base_gene;
			}

			virtual ~Patron(void){}

		protected:
			Parametre::ptr m_prop;

			Gene::vectPtr m_base_gene;

			shared_ptr<Chromosone::vect> m_base_chromosone;

		private:
	};



	/*Individu : ici represente un ensemble de plusieur groupe/ilot/table d'éleve*/
	class Individu : public Patron
	{
 		public:
			
			typedef shared_ptr<Individu> ptr;
			typedef vector<Individu> vect;
			typedef vector< ptr > vectPtr;


			explicit Individu( Patron const & _p  ):Patron(_p )
			{
				this->m_evaluable = true;
				this->m_score = -1000;
				this->initialisation();
			}

			explicit Individu( void  ):Patron( )
			{
				this->m_score = -1000;
			}

			bool operator==(Individu  & _ref)
			{
				for( auto i = 0 , y = 0 ; i < this->m_base_gene.size()  ;i++ , y++)
				{

					if( *(this->m_base_gene[i])!= *(_ref.rget_base_gene()[y]) )
						return false;
				}

				return true;
			}


			void reset(void) override
			{
				this->m_prop.reset();
				this->m_evaluable = true;
			}

			void initialisation(void)
			{
				this->m_evaluable = true;

				std::random_device rd;
    			std::mt19937 g(rd());

				//trie aleatoire uniforme
				std::shuffle( this->m_base_gene.begin(), this->m_base_gene.end() , g);
			}

			////validé
			vect croisement( Individu const & _idv)
			{
				this->m_evaluable = true;
				
				auto sep = this->m_base_gene.size()/2;


				vect enfants;
				enfants.emplace_back( *this );
				enfants.emplace_back( _idv );

				//creation des enfant en créant des croisement

				enfants.front().rget_base_gene().erase(enfants.front().rget_base_gene().begin() + sep, enfants.front().rget_base_gene().end());
				enfants.front().rget_base_gene().insert(enfants.front().rget_base_gene().end() , enfants.back().rget_base_gene().begin() + sep , enfants.back().rget_base_gene().end() );

				enfants.back().rget_base_gene().erase(enfants.back().rget_base_gene().begin() + sep, enfants.back().rget_base_gene().end());
				enfants.back().rget_base_gene().insert(enfants.back().rget_base_gene().end() , this->m_base_gene.begin() + sep , this->m_base_gene.end() );

				// verification et swap des genes identique
				auto it_dbl1 = enfants.front().check_double();
				auto it_dbl2 = enfants.back().rget_base_gene().end();
		

				while( it_dbl1 != enfants.front().rget_base_gene().end() )
				{
					it_dbl2 = enfants.back().check_double();
					
					std::iter_swap( it_dbl1 , it_dbl2 );

					it_dbl1 = enfants.front().check_double();
				}

				return enfants;
			}


			////validé
			void mutation( std::uniform_int_distribution<int> & dis ,  std::default_random_engine  & re  )
			{
				if( this->m_base_gene.size() <=1 )
					return ;

				this->m_evaluable = true;

				//selection de 2 gene différents
				
				auto it1 = this->m_base_gene.begin() + dis(re);
				auto it2 = this->m_base_gene.begin() + dis(re);

				while( it1 == it2 )
					it2 = this->m_base_gene.begin() + dis(re);
				
				//echange des individu sans touché modifier les adresses des iterator
				std::iter_swap( it1 , it2 );

			}

			void evaluation( float niveau_moyen_general = 3.0)
			{
				//si rien n'a changé pas de raison de réevaluer l'individue son scrore doit etre identique
				
				if( !this->m_evaluable ) 
					return ;

				this->m_score = 0;
				float moyenne_score = 0;

				int index_base_gene = 0;
				for( int i = 0 ; i < this->m_base_chromosone->size() ; i++)
				{
					//on calcule tout les score a calculer sur ce chromosone
					this->m_base_chromosone->at(i).score = 0;


					auto beg_crom = this->m_base_gene.begin() + index_base_gene;
					auto end_crom = this->m_base_gene.begin() +index_base_gene +  this->m_base_chromosone->at(i).get_caract().size;


					//on regarde chaque gene d'un chrommozone
					//et on evalu les souhait
					float tmp_score = 0;
					
					for( auto itg = beg_crom ; itg != end_crom ; itg++  )
					{
						tmp_score += (*itg)->evaluate_attract( beg_crom , end_crom , this->m_prop->coef_souhait_multiple);
					}

					this->m_base_chromosone->at(i).score += this->m_prop->coef_souhait * tmp_score;
					tmp_score = 0;

					//on regarde chaque gene d'un chrommozone
					//et on evalu les non souhait
					for( auto itg = beg_crom ; itg != end_crom ; itg++  )
					{
						
						tmp_score += (*itg)->evaluate_repuls( beg_crom , end_crom );
					}

					this->m_base_chromosone->at(i).score += this->m_prop->coef_non_souhait * tmp_score;

					tmp_score = -this->m_base_chromosone->at(i).get_caract().size / 2.0 ;

					//on regarde chaque gene d'un chrommozone
					//et on evalu la parité
					for( auto itg = beg_crom ; itg != end_crom ; itg++  )
					{
						if( (*itg)->get_caract().sexe )
							tmp_score+=1;

					}

					if(tmp_score > 0)
						tmp_score =-tmp_score;

					this->m_base_chromosone->at(i).score += this->m_prop->coef_pariter * tmp_score;
					tmp_score=0;

					//on regarde chaque gene d'un chrommozone
					//et on evalu le niveau moyen
					for( auto itg = beg_crom ; itg != end_crom ; itg++  )
					{
						tmp_score += (*itg)->get_caract().niveau;
					}

					tmp_score/= this->m_base_chromosone->at(i).get_caract().size ;

					tmp_score -= niveau_moyen_general;

					if(tmp_score > 0)
						tmp_score =-tmp_score;

					this->m_base_chromosone->at(i).score += this->m_prop->coef_competence * tmp_score;
					tmp_score = 0;

					//on regarde chaque gene d'un chrommozone
					//et on evalu l'attention 

					for( auto itg = beg_crom ; itg != end_crom ; itg++  )
					{
						tmp_score += this->m_base_chromosone->at(i).get_caract().distance * (*itg)->get_caract().attention  ;
					}

					this->m_base_chromosone->at(i).score += tmp_score * this->m_prop->coef_attention ;

					index_base_gene += this->m_base_chromosone->at(i).get_caract().size ;

					this->m_score += this->m_base_chromosone->at(i).score ;
					moyenne_score += this->m_base_chromosone->at(i).score;
				}


				//on calcule l'ecart type des crhomosone pour les equilibré
				if( this->m_prop->coef_homogeneiter!= 0)
				{
					moyenne_score /= this->m_base_chromosone->size();

					float sigma = 0;

					for( int i = 0 ; i < this->m_base_chromosone->size() ; i++)
					{
						sigma += ( this->m_base_chromosone->at(i).score - moyenne_score ) * ( this->m_base_chromosone->at(i).score - moyenne_score);
					}

					sigma /= this->m_base_chromosone->size();

					this->m_score -= abs(sigma) * this->m_prop->coef_homogeneiter;
				}

				this->m_evaluable = false;
			}

			double const get_score(void) const
			{
				 return this->m_score;
			}

			Gene::vectPtr::iterator check_double(void)
			{
				for( auto it1 = this->m_base_gene.begin() ; it1 != this->m_base_gene.end() ; it1++ )
				{
					for( auto it2 = it1+1 ; it2 != this->m_base_gene.end() ; it2++ )
					{
						if( *it1 == *it2 ) 
							return it1;
					}
				}

				return this->m_base_gene.end();
			}

		protected:


			bool m_evaluable;
			float m_score;

		private:

		
	};


	class Process : public Patron
	{
		public:

			long int temps_arret;
			unsigned int cycle_arret ;
			double score_arret , taux_mutation , taux_selection , n_individu , taux_stabiliter , temps_limite;

			explicit Process(void):Patron( )
			{
				
				this->set_prop( Parametre::ptr(new Parametre()) ) ;
				this->set_base_chromosone( shared_ptr<Chromosone::vect>(new Chromosone::vect()) ) ;
				
				this->reset();
			}

			~Process(void)
			{
			}

			void reset(void) override
			{

				if( this->m_prop	)
				{
					this->m_prop->coef_souhait = 1.0 ; 
					this->m_prop->coef_non_souhait = 1.0;
					this->m_prop->coef_pariter = 1.0;
					this->m_prop->coef_competence = 1.0;
					this->m_prop->coef_attention = 1.0;
					this->m_prop->coef_souhait_multiple = 1.0;
					this->m_prop->coef_homogeneiter = 1.0;
					
				}
				

				this->temps_arret = -1;
				this->score_arret = 1000000.0;
				this->taux_mutation = 0.5;
				this->taux_selection = 0.5;
				this->cycle_arret = 1000 ;
				this->n_individu = 1000 ;
				this->taux_stabiliter =1;
				this->temps_limite = 300;
			}

			Individu::vect process(void)
			{
				auto start = std::chrono::high_resolution_clock::now();

				//verifi les valeur des variables de la fonction
				if(  this->n_individu < 2)
					return Individu::vect(0 , Individu( *this )) ;

				// genese : créé les population des simulation 
				// on partage les parametre a chaque Individu de population
				Individu::vect population ;

				population.reserve(this->n_individu);

				for( auto i = 0 ; i < this->n_individu ; i++)
					population.emplace_back(  *this  );

				//simulation non asynchrone

				//on initialise le generateur aleatoire 
				std::default_random_engine  re( std::chrono::system_clock::now().time_since_epoch().count() );

				std::uniform_int_distribution<int> dis(0, this->m_base_gene.size() -1 );
				std::uniform_real_distribution<> dis_mut(0, this->taux_mutation );

				unsigned int idx_selection = this->taux_selection * (population.size()-1);

					
				std::uniform_int_distribution<int> dis_pop_sel( 0 , idx_selection);
				int count_stab_great =0;
				unsigned int stop_stap = this->taux_stabiliter * this->cycle_arret;


				float niveau_moyen_general = 0;

				for( auto i =0 ;  i < this->m_base_gene.size() ; i++)
					niveau_moyen_general += this->m_base_gene[i]->get_caract().niveau;

				niveau_moyen_general /= this->m_base_gene.size();

				for( unsigned int k = 0 ; k < this->cycle_arret ; k++)
				{

					//si timout dépassé arret de l'algo
					 auto end = std::chrono::high_resolution_clock::now();
					 std::chrono::duration<double> elapsed = end - start;
					 if(elapsed.count() >= this->temps_limite)
					 {
						break;
					 }
					 	

					// on commence par evaluer la population en cour de simulation

					for( auto & idv : population )
						idv.evaluation( niveau_moyen_general );

					//trie par ordre de score
					std::sort( population.begin() , population.end() , [](Individu const & a, Individu const & b){ return a.get_score() > b.get_score();});

					if( this->m_meilleur.get_score() < population.front().get_score())
					{
						
						this->m_meilleur = population.front();
						
						count_stab_great=0;
					}
					else
						count_stab_great++;



					//on regarde les condition d'arret
					if( count_stab_great >= stop_stap )
					{
						break;
					}

					

					Individu::vect enfants ;

					enfants.reserve(idx_selection * 2);

					//on effectue un croisement entre les selectionné et les non selectionne choisie aleatoirement
					for( auto mere = population.begin() ; mere != population.begin()+idx_selection ; mere++ )
					{
						//on croise les individu 
						//et on créé une liste d'enfant
						auto pere = population[dis_pop_sel( re )] ;

						//reselectionne un diféréent si identique 
						while( (int*)(&pere) == (int*)(&mere))
						{
							pere = population[dis_pop_sel( re )] ;
						}
						
						auto tmp = mere->croisement( pere ) ;
						
						enfants.insert(enfants.end() , tmp.begin() , tmp.end()) ;

					}

					//on evalut les enfant pour trier en fonction des meilleur
					for( auto & idv : enfants )
						idv.evaluation();

					//trie par ordre de score
					std::sort( enfants.begin() , enfants.end() , [](Individu const & a, Individu const & b){ return a.get_score() > b.get_score();});

					//fusion des deux groupe
					for(auto idv = population.end()-1 , enfant= enfants.begin(); idv != population.begin() && enfant != enfants.end(); idv-- , enfant++ )
					{
						if( idv->get_score() > enfant->get_score() ) 
						{
							//on fusionne au croisement des score_arret

							if(idv+1 == population.end())
								break;

							population.erase( idv+1 , population.end() );
							population.insert( population.end() , enfants.begin() , enfant);

							break;
						}
					}


					//on effectue une mutation sur la population
					for( auto & idv : population )
						if( dis_mut( re ) <= this->taux_mutation )
							idv.mutation( dis , re);

					continue;
					
				}

				population.insert(population.begin() , this->m_meilleur);


				population.erase(std::unique(population.begin(), population.end()), population.end());

				std::sort( population.begin() , population.end() , [](Individu const & a, Individu const & b){ return a.get_score() > b.get_score();});

				return population ;
			}

		protected:
			
			Individu m_meilleur;

		private:

	};
}

#endif
