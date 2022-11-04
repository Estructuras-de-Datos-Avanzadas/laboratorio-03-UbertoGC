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
    nodo_quadtree(float,float);
    void anadir(float,float,int,float,float,float,float);
    void buscar(float,float,float,float);
    friend ostream& operator << (ostream &,const nodo_quadtree &);
    ~nodo_quadtree();
};
nodo_quadtree::nodo_quadtree(){
    cuadrante=-1;
    hijos=nullptr;
    x=-1;
    y=-1;
}
nodo_quadtree::nodo_quadtree(float x_1,float y_1)
{
    cuadrante=-3;
    hijos=new nodo_quadtree[4];
    x=x_1/2;
    y=y_1/2;
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
void nodo_quadtree::buscar(float x_min, float y_min, float x_max, float y_max){
    if(this->hijos==nullptr){
        if(this->x>x_min && this->x<=x_max && this->y>y_min && this->y<=y_max)
            cout<<"("<<this->x<<" , "<<this->y<<")"<<endl;
    }
    else{
        if(x_min<this->x){
            if(y_min<this->y){
                this->hijos[0].buscar(x_min,y_min,x_max,y_max);
            }
            if(y_max>=this->y){
                this->hijos[2].buscar(x_min,y_min,x_max,y_max);
            }
        }
        if(x_max>=this->x){
            if(y_min<this->y){
                this->hijos[1].buscar(x_min,y_min,x_max,y_max);
            }
            if(y_max>=this->y){
                this->hijos[3].buscar(x_min,y_min,x_max,y_max);
            }
        }
    }
}
ostream& operator << (ostream &o,const nodo_quadtree &a){
    if(a.hijos!=nullptr){
        for (int i = 0; i < 4; i++){
            o<<char(34)<<a.x<<" - "<<a.y<<char(34)<<" -> ";
            if(a.hijos[i].x==-1)
                o<<"void"<<i<<"_"<<a.x<<a.y<<"; ";
            else
                o<<char(34)<<a.hijos[i].x<<" - "<<a.hijos[i].y<<char(34)<<"; ";
        }
        o<<endl;
        for (int i = 0; i < 4; i++)
            if(a.hijos[i].x!=-1 && a.hijos[i].hijos!=nullptr)
                o<<a.hijos[i];
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
    void buscar(float,float,float,float);
    friend ostream& operator<<(ostream&, const quadtree &);
    ~quadtree();
};
quadtree::quadtree(float x, float y)
{
    ancho=x;
    largo=y;
    raiz=new nodo_quadtree(x,y);
}
void quadtree::anadir(float x, float y){
    raiz->anadir(x,y,13,0,0,ancho,largo);
}
void quadtree::buscar(float x_min, float y_min, float x_max, float y_max){
    raiz->buscar(x_min,y_min,x_max,y_max);
    cout << "------------------------------------------------------"<<endl;
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
    quadtree alfa(6400,4800);
    for (int i = 0; i < 50; i++){
        float x=rand()%6400+1;
        float y=rand()%4800+1;
        alfa.anadir(x,y);
    }
    cout<<alfa;
    alfa.buscar(1600,1200,4800,3600);
    return 0;
}