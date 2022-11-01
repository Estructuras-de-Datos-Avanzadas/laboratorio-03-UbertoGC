#include <iostream>
using namespace std;
class nodo_quadtree{
private:
    nodo_quadtree*hijos;
    int cuadrante;
    float x;
    float y;
public:
    nodo_quadtree();
    nodo_quadtree(float,float,int);
    void anadir(float,float,int,float,float,float,float);
    void division();
    friend ostream& operator << (ostream &,const nodo_quadtree &);
    ~nodo_quadtree();
};
nodo_quadtree::nodo_quadtree(){
    cuadrante=-1;
    hijos=nullptr;
    x=-1;
    y=-1;
}
nodo_quadtree::nodo_quadtree(float x_1,float y_1, int cuadrante_1)
{
    cuadrante=cuadrante_1;
    hijos=nullptr;
    x=x_1;
    y=y_1;
}
void nodo_quadtree::anadir(float x_1, float y_1, int cuad, float x_father, float y_father, float tamano_x, float tamano_y){
    if(this->hijos==nullptr){
        if(this->cuadrante==-1){
            this->cuadrante=cuad;
            this->x=x_1;
            this->y=y_1;
        }
        else{
            this->hijos=new nodo_quadtree[4];
            float bajar_x=this->x;
            float bajar_y=this->y;
            if(cuad%2)
                this->x=x_father + tamano_x/2;
            else
                this->x=x_father - tamano_x/2;
            if(cuad<2)
                this->y=y_father - tamano_y/2;
            else
                this->y=y_father + tamano_y/2;
            if(x_1<this->x){
                if(y_1<this->y)
                    this->hijos[0].anadir(x_1,y_1,0,this->x,this->y,tamano_x/2,tamano_y/2);
                else
                    this->hijos[2].anadir(x_1,y_1,2,this->x,this->y,tamano_x/2,tamano_y/2);
            }
            else{
                if(y_1<this->y)
                    this->hijos[1].anadir(x_1,y_1,1,this->x,this->y,tamano_x/2,tamano_y/2);
                else
                    this->hijos[3].anadir(x_1,y_1,3,this->x,this->y,tamano_x/2,tamano_y/2);
            }
            if(bajar_x<this->x){
                if(bajar_y<this->y)
                    this->hijos[0].anadir(bajar_x,bajar_y,0,this->x,this->y,tamano_x/2,tamano_y/2);
                else
                    this->hijos[2].anadir(bajar_x,bajar_y,2,this->x,this->y,tamano_x/2,tamano_y/2);
            }
            else{
                if(bajar_y<this->y)
                    this->hijos[1].anadir(bajar_x,bajar_y,1,this->x,this->y,tamano_x/2,tamano_y/2);
                else
                    this->hijos[3].anadir(bajar_x,bajar_y,3,this->x,this->y,tamano_x/2,tamano_y/2);
            }
        }
    }
    else{
        if(x_1<this->x){
            if(y_1<this->y)
                this->hijos[0].anadir(x_1,y_1,0,this->x,this->y,tamano_x/2,tamano_y/2);
            else
                this->hijos[2].anadir(x_1,y_1,2,this->x,this->y,tamano_x/2,tamano_y/2);
        }
        else{
            if(y_1<this->y)
                this->hijos[1].anadir(x_1,y_1,1,this->x,this->y,tamano_x/2,tamano_y/2);
            else
                this->hijos[3].anadir(x_1,y_1,3,this->x,this->y,tamano_x/2,tamano_y/2);
        }
    }
}
ostream& operator << (ostream &o,const nodo_quadtree &a){
    o<<"Valor ("<<a.x<<" , "<<a.y<<")"<<endl;
    if(a.hijos!=nullptr){
        o<<"Hijos (x , y): ";
        for (int i = 0; i < 4; i++){
            o<<"("<<a.hijos[i].x<<" , "<<a.hijos[i].y<<")";
            if(i<3){
                o<<" ; ";
            }
            else{
                o<<endl;
            }
        }
        for (int i = 0; i < 4; i++){
            if(a.hijos[i].x!=-1 && a.hijos[i].hijos!=nullptr){
                o<<a.hijos[i];
            }
        }
    }
    return o;
}
nodo_quadtree::~nodo_quadtree()
{
    delete[] this->hijos;
}
class quadtree{
private:
    nodo_quadtree *raiz;
    float largo;
    float ancho;
public:
    quadtree(float, float);
    void anadir(float, float);
    friend ostream& operator<<(ostream&, const quadtree &);
    ~quadtree();
};
quadtree::quadtree(float x, float y)
{
    ancho=x;
    largo=y;
    raiz=new nodo_quadtree();
}
void quadtree::anadir(float x, float y){
    raiz->anadir(x,y,13,0,0,ancho,largo);
}
ostream& operator<< (ostream &o,const quadtree &a){
    o << "Ancho: " << a.ancho << ", Largo: " << a.largo <<endl;
    o << *(a.raiz);
    o << "------------------------------------------------------"<<endl;
    return o;
}
quadtree::~quadtree()
{
    delete[] raiz;
}

int main(){
    quadtree alfa(800,600);
    alfa.anadir(100,200);
    alfa.anadir(330,450);
    alfa.anadir(710,500);
    alfa.anadir(640,100);
    alfa.anadir(80,60);
    alfa.anadir(560,200);
    alfa.anadir(440,230);
    /*añadiendo*/
    alfa.anadir(530,220);
    cout<<alfa;
    return 0;
}