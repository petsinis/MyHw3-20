#include <iostream>

using namespace std;

class C4{
    private:
        int x;
        int y;
    public:
        C4(): x {4}, y {44} {};
        virtual int get_x();
        virtual int get_y();
        virtual void set_x(int x);
        virtual void set_y(int y);

};

int C4::get_x(){
    return(x);
}
int C4::get_y(){
    return(y);
}

void C4::set_x(int x){
    this->x=x;
}
void C4::set_y(int y){
    this->y=y;
}

class C5{
    private:
        int z;
        int w;
    public:
        C5(): z {5}, w {55} {};
        virtual int get_z();
        virtual int get_w();
        virtual void set_z(int z);
        virtual void set_w(int w);

};

int C5::get_z(){
    return(z);
}
int C5::get_w(){
    return(w);
}

void C5::set_z(int z){
    this->z=z;
}
void C5::set_w(int w){
    this->w=w;
}



class C2:  virtual public C4
{
    private:
        int x2;
    public:
        C2(): x2 {2}{};
};
class C3:  virtual public C5, virtual public C4
{
    private:
        int x3;
    public:
        C3(): x3 {3}{};
};
class C1:  virtual public C3,  virtual public C2
{
    private:int x1;
    public:C1(): x1 {1}{};
};


int main()
{
    cout<<"Object *c4 layout"<<endl;
    cout<<"--------------------------------"<<endl;
    C4 *c4 = new C4();
    cout<<"-> Size of *c4: "<<sizeof(*c4)<<endl;
    for(int i=0;i<sizeof(*c4)/4;i++){
        cout<<"Address Memory "<<((int*)c4+i)<<" has value "<<*((int*)c4+i)<<endl;
    }
    cout<<"--------------------------------"<<endl;
    cout<<"Pointer to C4-v-table: "<<*(void**)c4<<" (with c4 pointer = "<<c4<<")"<<endl;
    cout<<"--------------------------------"<<endl;
    cout<<endl;

    cout<<"Object *c5 layout"<<endl;
    cout<<"--------------------------------"<<endl;
    C5 *c5 = new C5();
    cout<<"-> Size of *c5: "<<sizeof(*c5)<<endl;
    for(int i=0;i<sizeof(*c5)/4;i++){
        cout<<"Address Memory "<<((int*)c5+i)<<" has value "<<*((int*)c5+i)<<endl;
    }
    cout<<"--------------------------------"<<endl;
    cout<<"Pointer to C5-v-table: "<<*(void**)c5<<" (with c5 pointer = "<<c5<<")"<<endl;
    cout<<"--------------------------------"<<endl;
    cout<<endl;

    cout<<"Object *c2 layout"<<endl;
    cout<<"--------------------------------"<<endl;
    C2 *c2 = new C2();
    cout<<"-> Size of *c5: "<<sizeof(*c2)<<endl;
    for(int i=0;i<sizeof(*c2)/4;i++){
        cout<<"Address Memory "<<((int*)c2+i)<<" has value "<<*((int*)c2+i)<<endl;
    }
    cout<<"--------------------------------"<<endl;
    cout<<"Pointer to C2-v-table: "<<*(void**)c2<<" (with c2 pointer = "<<c2<<")"<<endl;
    C4 *c4_2 = c2;
    cout<<"Pointer to C4_2-v-table: "<<*(void**)c4_2<<" (with c4_2 pointer = "<<c4_2<<")"<<endl;
    cout<<"--------------------------------"<<endl;
    cout<<endl;

    cout<<"Object *c3 layout"<<endl;
    cout<<"--------------------------------"<<endl;
    C3 *c3 = new C3();
    cout<<"-> Size of *c3: "<<sizeof(*c3)<<endl;
    for(int i=0;i<sizeof(*c3)/4;i++){
        cout<<"Address Memory "<<((int*)c3+i)<<" has value "<<*((int*)c3+i)<<endl;
    }
    cout<<"--------------------------------"<<endl;
    cout<<"Pointer to C3-v-table: "<<*(void**)c3<<" (with c3 pointer = "<<c3<<")"<<endl;
    C4 *c4_3 = c3;
    cout<<"Pointer to C4_3-v-table: "<<*(void**)c4_3<<" (with c4_3 pointer = "<<c4_3<<")"<<endl;
    C5 *c5_3 = c3;
    cout<<"Pointer to C5_3-v-table: "<<*(void**)c5_3<<" (with c5_3 pointer = "<<c5_3<<")"<<endl;
    cout<<"--------------------------------"<<endl;
    cout<<endl;

    cout<<"Object *c1 layout"<<endl;
    cout<<"--------------------------------"<<endl;
    C1 *c1 = new C1();
    cout<<"-> Size of *c1: "<<sizeof(*c1)<<endl;
    for(int i=0;i<sizeof(*c1)/4;i++){
        cout<<"Address Memory "<<((int*)c1+i)<<" has value "<<*((int*)c1+i)<<endl;
    }
    cout<<"--------------------------------"<<endl;
    cout<<"Pointer to C1-v-table: "<<*(void**)c1<<" (with c1 pointer = "<<c1<<")"<<endl;
    C2 *c2_1 = c1;
    C3 *c3_1 = c1;

    C4 *c4_2_1 = c2_1;
    C4 *c4_3_1 = c3_1;
    C5 *c5_3_1 = c3_1;

    cout<<"Pointer to C2_1-v-table: "<<*(void**)c2_1<<" (with c2_1 pointer = "<<c2_1<<")"<<endl;
    cout<<"Pointer to C3_1-v-table: "<<*(void**)c3_1<<" (with c3_1 pointer = "<<c3_1<<")"<<endl;
    cout<<"Pointer to C4_2_1-v-table: "<<*(void**)c4_2_1<<" (with c4_2_1 pointer = "<<c4_2_1<<")"<<endl;
    cout<<"Pointer to C4_3_1-v-table: "<<*(void**)c4_3_1<<" (with c4_3_1 pointer = "<<c4_3_1<<")"<<endl;
    cout<<"Pointer to C5_3_1-v-table: "<<*(void**)c5_3_1<<" (with c5_3_1 pointer = "<<c5_3_1<<")"<<endl;

    cout<<"--------------------------------"<<endl;
    cout<<endl;


    //typedef int(*mymeth)(void *);
    //mymeth *ptr = (mymeth *)c4;
    //cout<<ptr<<endl;
    //cout<<ptr+1<<endl;
    //cout<<(*(*(ptr)))(c4)<<endl;



    void * vtblAddress = *(void **)c4;

    typedef int(*getters)(C4*);
    getters *g = (getters *) vtblAddress;
    getters get_x = *(g+0);
    getters get_y = *(g+1);

    typedef void(*setters)(C4*, int);
    setters *s = (setters *) vtblAddress;
    setters set_x = *(s+2);
    setters set_y = *(s+3);


    cout<<"Call virtual methods of *c4 using v-table."<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<"The field x has value:"<<endl;
    cout<<get_x(c4)<<endl;
    cout<<"The field y has value:"<<endl;
    cout<<get_y(c4)<<endl<<endl;

    cout<<"Changing x field from 4 to 40 and y field from 44 to 440."<<endl;
    cout<<"Changing x..."<<endl;
    set_x(c4, 40);
    cout<<"Changing y..."<<endl;
    set_y(c4, 440);


    cout<<"Now the field x has value:"<<endl;
    cout<<get_x(c4)<<endl;
    cout<<"Now the field y has value:"<<endl;
    cout<<get_y(c4)<<endl<<endl;


    cout<<endl;

    void * vtblAddress2 = *(void **)c5;

    typedef int(*getters2)(C5*);
    getters2 *g2 = (getters2 *) vtblAddress2;
    getters2 get_z = *(g2+0);
    getters2 get_w = *(g2+1);

    typedef void(*setters2)(C5*, int);
    setters2 *s2 = (setters2 *) vtblAddress2;
    setters2 set_z = *(s2+2);
    setters2 set_w = *(s2+3);


    cout<<"Call virtual methods of *c5 using v-table."<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<"The field z has value:"<<endl;
    cout<<get_z(c5)<<endl;
    cout<<"The field w has value:"<<endl;
    cout<<get_w(c5)<<endl<<endl;

    cout<<"Changing w field from 5 to 50 and z field from 55 to 550."<<endl;
    cout<<"Changing w..."<<endl;
    set_z(c5, 50);
    cout<<"Changing z..."<<endl;
    set_w(c5, 550);


    cout<<"Now the field w has value:"<<endl;
    cout<<get_z(c5)<<endl;
    cout<<"Now the field z has value:"<<endl;
    cout<<get_w(c5)<<endl<<endl;


    return 0;
}
