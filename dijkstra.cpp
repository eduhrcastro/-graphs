#ifndef DIJKSTRA_CPP
#define DIJKSTRA_CPP

#include <iostream>
#include "priorityqueue.cpp"
#include "graph.cpp"

template<class T>
class Dijkstra{
	
	private:
		
		PriorityQueue< Vertex<T> > *queue;
		List< Vertex<T> > *shortPath;
		Graph<T> *graph;
		static int const INFINITY = 9999;
		
		void resetFlag(){
			bool reset = false;
			for(Node< Vertex<T> > *temp = getQueue()->getHead();temp!=NULL;temp=temp->getNext())
				temp->setVisited(reset);
		}
		
		Node< Vertex<T> > *getNodeLassDistance(){
			
			Node< Vertex<T> > *aux = getQueue()->getHead();
			
			for(Node< Vertex<T> > *temp = getQueue()->getHead()->getNext();temp!=NULL;temp=temp->getNext()){
				if(temp->getVisited() == false){
					if(aux->getData()->compareTo(temp->getData()) > 0)
						aux = temp;
				}
			}
			
			return aux;
		}
		
		void checkPriority(Node< Vertex<T> > *head,int priority){
			if(head!=NULL){
				Node< Vertex<T> > *lassDistance = getNodeLassDistance();
				lassDistance->setVisited(true);
				lassDistance->setPriority(priority);
				checkPriority(head->getNext(),priority-1);
			}
		}
		
	public:
		
		Dijkstra(Graph<T> *graph){
			setGraph(graph);
			setShortPath(new List< Vertex<T> >());
			setQueue(new PriorityQueue< Vertex<T> >());
		}
		
		void setGraph(Graph<T> *graph){
			this->graph = graph;
		}
		void setQueue(PriorityQueue< Vertex<T> > *queue){
			this->queue = queue;
		}
		void setShortPath(List< Vertex<T> > *shortPath){
			this->shortPath = shortPath;
		}
		
		Graph<T> *getGraph(){
			return (graph);
		}
		List< Vertex<T> > *getShortPath(){
			return (shortPath);
		}
		PriorityQueue< Vertex<T> > *getQueue(){
			return (queue);
		}
		
		void findShortPath(Vertex<T> *dataSource){
			
			//DEFININDO TODOS OS V�RTICE COMO TENDO DISTANCIA INFINITA;
			for(Node< Vertex<T> > *t = getGraph()->getHead();t!=NULL;t=t->getNext())
				t->getData()->setAuxDistance(INFINITY);
				
			//DEFININDO O V�RTICE INICIAL COMO SENDO 0;
			dataSource->setAuxDistance(0);
			
			//DEFININDO UMA ESTRATURA Q PARA RECEBER TODOS OS V�RTICES;
			for(Node< Vertex<T> > *t = getGraph()->getHead();t!=NULL;t=t->getNext())
				getQueue()->enqueue(t->getData());
			
			//DEFININDO A PRIORIDADE DE SA�DA DA ESTRUTURA Q;	
			resetFlag();	
			checkPriority(getQueue()->getHead(),getQueue()->getCount());
			
			//VARI�VEL AUXILIAR DE ALTURA;
			int alt=0;
			
			//LOOP PRINCIPAL;
			while(!getQueue()->isEmpty()){
					
					//REMOVENDO ELEMENTO DE MENOR DISTANCIA TEMPORARIA;
					Vertex<T> *u = getQueue()->dequeue();
					u->setVisited(true);
											
					//PARA TODOS AS ARESTAS LIGADAS AO V�RTICE REMOVIDO;
					for(Node< Edge<T> > *v = u->getListAdj()->getHead();v!=NULL;v=v->getNext()){ 
					
						//PEGUE O V�RTICE REFERENTE A ESSA ARESTA;
						Vertex<T> *aux = getGraph()->getVertex(v->getData()->getData());
						
						//VERIFIQUE SE ESSA ARESTA J� N�O � UM V�RTICE J� VISITADO, SE N�O FOR;
						if(aux->getVisited()==false){
						
							//GUARDA NA VARI�VEL ALT = ESTIMATIVA + PESO DO ARCO u AT� v;	
							alt = u->getAuxDistance() + v->getData()->getDistance();
							
							//VERIFICA SE A ESTIMATIVA � MENOR DO QUE A DISTANCIA TEMPORARIA ATUAL, SE FOR;
							if(alt < aux->getAuxDistance()){
								aux->setAuxDistance(alt);
								aux->setPrevious(u);
								resetFlag();
								checkPriority(getQueue()->getHead(),getQueue()->getCount());
							}
							
						}
					}
			}
		
		}
		
};

#endif
