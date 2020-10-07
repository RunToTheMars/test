#include"Dlist.h"
#include<string.h>
#include<iostream>
using namespace std;
Dlist:: Dlist(){  
    base.str=nullptr;
    base.lenofstr=0;
    base.next=base.prev=&base;
    current=after=before=&base;
}

bool Dlist:: AtEnd(){   
    return after==&base;
}

void Dlist:: GoToEnd(){  
    after=&base;
    current=after->prev;
    before=current->prev;	
}

bool Dlist:: GoToNext(){  
    if(AtEnd()) return false;
    current=current->next;
    after=after->next;
    before=current->prev;
    return true;
}

bool Dlist:: DelAfter(){ 
    if(AtEnd()) return false;
    delete[] (after->str);
    current->next=after->next;
    after->next->prev=current;
    DlistItem* tmp=after;
    after=after->next;
    delete tmp;
    return true;
}

Dlist:: ~Dlist(){ 
    if(!IsEmpty()){
        for(GoToBeg();!AtEnd();DelAfter());  
        delete []  current->str;
        delete current;
    }    
}


Dlist:: Dlist(char *stroka){  
    DlistItem *New=new DlistItem;
    New->lenofstr=strlen(stroka);
    New->str=new char [strlen(stroka) + 1];
    New->next=New->prev=&base;
    current=New;
    base.str=nullptr;
    base.lenofstr=0;
    base.next=base.prev=New;
    after=&base;
    before=&base;
    memcpy(current->str, stroka, New->lenofstr + 1);
}

void Dlist:: InsAfter_formass(char* x, int n){

    DlistItem *newelem;
    newelem=new DlistItem;
    newelem->lenofstr=n;
    newelem->str=new char[n+1];
    int min_len = n > strlen(x) ? strlen(x) : n;
    memcpy(newelem->str, x, min_len + 1);
    current->next=newelem;
    after->prev=newelem;
    newelem->next=after;
    newelem->prev=current;
    before=current;
    current=newelem;
    after=current->next;

}

void Dlist:: InsAfter(const char* x){  

    int n=strlen(x);
    DlistItem *newelem=new DlistItem;
    newelem->lenofstr=n;
    newelem->str=nullptr;
    newelem->str=new char[n+1];
    memcpy(newelem->str, x, n + 1);

    //    current->next->prev = newelem;
    newelem->next=current->next;
    current->next=newelem;
    after->prev=newelem;//
    newelem->prev=current;
    before = current; 
    current=newelem;
    after=current->next;

}

void Dlist:: InsAfterPos(const char* x, int position){//
    if(position>ListLength()){
        throw Dlist_Exception(1, "Буфер имеет меньшую длину.");
        return;
    }
    if(position<0){
        throw Dlist_Exception(2, "Укажите корректное значение позици");
        return;
    }

    GoToBeg();
    if(position==0){
        current=&base;
        InsAfter(x);
    }
    int h=(current->lenofstr);
    int g=0;
    int u=0;
    for(GoToBeg();!AtEnd();GoToNext()){
        for(int i=g, j=0;(i<h)&&(j<(current->lenofstr));i++, j++)
            if(i==(position-1)){
                if((current->lenofstr)>j+1){
                    char * array = new char[(current->lenofstr)-(j+1)];
                    for(int ds=0; ds<((current->lenofstr)-(j+1)); ds++){
                        array[ds]=current->str[j+1+ds];
                    }
                    u=((current->lenofstr)-(j+1));
                    current->str[j+1]=0;
                    current->lenofstr=j+1;
                    InsAfter(x); 
                    InsAfter_formass(array, u);	
                    delete [] array;
                    return;
                }
                else{
                    InsAfter(x);
                    return;
                }
            }
        g=h;
        h+=after->lenofstr;
    }
    GoToEnd();
    for(int l=current->lenofstr; l>0; l--){
        if(position==ListLength()-l+1){
            if(position!=ListLength()){
                char* array = new char[(current->lenofstr)-l];
                for(int rn=0; rn<(current->lenofstr)-l; rn++){
                    array[rn]=current->str[l+rn];
                }
                u=(current->lenofstr)-l;
                current->str[l]=0;
                current->lenofstr=l;

                InsAfter(x);
                InsAfter_formass(array, u);
                delete [] array;
                return;        
            }
            else{
                InsAfter(x);
            }
        }
    }
}

void Dlist::AddToEnd(const char* x){  
    GoToEnd();
    InsAfter(x);	
}

void Dlist:: GoToBeg(){  
    before=&base;
    current=before->next;
    after=current->next;
}

int Dlist:: ListLength(){  
    if(!IsEmpty())
        return 0;
    int res = 0;
    for(GoToBeg();;GoToNext()){
        res += current->lenofstr;
        if (AtEnd())
            break;
    }
    return res;
}
void Dlist:: PrintList(){  
    if(IsEmpty()){
        cout<<"The buffer is empty"<<endl;
        return;
    }
    cout<<"String in the buffer: ";
    GoToBeg();
    int h=(current->lenofstr);
    int g=0;
    for(GoToBeg();!AtEnd();GoToNext()){
        for(int i=g, j=0;(i<h) && (j<(current->lenofstr)); i++,j++)
            cout<<current->str[j];
        g=h;
        h+=after->lenofstr;

    }
    GoToEnd();

    for(int l=current->lenofstr; l>0; l--){
        cout<<current->str[(current->lenofstr)-l]; 
    }
    cout<<endl;
}

char*  Dlist:: CopyList(char *mass){ //
    if(IsEmpty()==true){
        throw Dlist_Exception(3, "The buffer is empty");
        return nullptr;
    }
    GoToBeg();
    int h=strlen(mass);
    int g=0;
    for(GoToBeg();!AtEnd();GoToNext()){
        for(int i=g, j=0;(i<h) && (j<(current->lenofstr)); i++,j++)
            mass[i]=current->str[j];
        g=h;
        h+=after->lenofstr;
    }
    GoToEnd();

    for(int l=current->lenofstr; l>0; l--){
        mass[ListLength()-l]=current->str[(current->lenofstr)-l]; 
    }

    return mass; 
}

bool Dlist:: IsEmpty(){  
    GoToBeg();
    return current==&base;
} 

char* Dlist:: CopyElemList(char *mass, int position){  
    if(IsEmpty()==true){
        throw Dlist_Exception(3, "The buffer is empty");
        return 0;
    }

    if(position>ListLength()){
        throw Dlist_Exception(1,"Строка, накопленная в буфере, меньшей длины.");
        return 0;
    }

    if(position<=0){
        throw Dlist_Exception(2,"Укажите корректное значение позиции");
        return 0;
    }

    GoToBeg();
    int h=(current->lenofstr);
    int g=0;
    for(GoToBeg();!AtEnd();GoToNext()){
        for(int i=g, j=0;(i<h)&&(j<(current->lenofstr)); i++,j++)
            if(i==position-1){
                for(int val=0; val<current->lenofstr; val++){
                    mass[val]=current->str[val];
                } 
                return mass;             
            }
        g=h;
        h+=after->lenofstr;
    }
    GoToEnd();
    for(int t=(current->lenofstr); t>0; t--){
        if(ListLength()-t==position-1){
            for(int val2=0; val2<current->lenofstr; val2++){
                mass[val2]=current->str[val2];
                return mass;
            }
        } 
    }

}

char Dlist:: TakeSymb(int position){   
    if(IsEmpty()==true){
        throw Dlist_Exception(3,"The buffer is empty");
        return 0;
    }
    if(position>ListLength()){
        throw Dlist_Exception(1, "Строка, накопленная в буфере, меньшей длины.Укажите другое значение.");
        return 0;
    }
    if(position<=0){
        throw Dlist_Exception(2,"Укажите корректное значение позиции.");
        return 0;
    }
    GoToBeg();
    int h=(current->lenofstr);
    int g=0;
    for(GoToBeg();!AtEnd();GoToNext()){
        for(int i=g, j=0;(i<h)&&(j<(current->lenofstr)); i++,j++)
            if(i==position-1){
                return current->str[j];
            }
        g=h;
        h+=after->lenofstr;	
    }
    GoToEnd();
    for(int t=(current->lenofstr); t>0; t--){
        if(ListLength()-t==position-1) return current->str[(current->lenofstr)-t];
    }

}

void Dlist:: ChangeSymb(int position, char elem){  
    if(IsEmpty()==true){
        throw Dlist_Exception(3, "The buffer is empty");
        return;
    }

    if(position>ListLength()){
        throw Dlist_Exception(1, "Строка, накопленная в буфере, меньшей длины, чем указанная позиция.");
        return;
    }

    if(position<=0){
        throw Dlist_Exception(2, "Укажите корректное значение изменяемой позиции");
        return;
    }

    GoToBeg();
    int h=(current->lenofstr);
    int g=0;
    for(GoToBeg();!AtEnd();GoToNext()){
        for(int i=g, j=0;(i<h)&&(j<(current->lenofstr));i++, j++)
            if(i==(position-1)){
                (current->str[j])=elem;
            }
        g=h;
        h+=after->lenofstr;	
    }
    GoToEnd();
    for(int l=current->lenofstr; l>0; l--){
        if(position==ListLength()-l+1) (current->str[(current->lenofstr)-l])=elem;
    }
}

void Dlist::ChangeStr(char *mass, int n, int position){ 
    if(position<=0) {
        throw Dlist_Exception(2, "Некоректное значение позиции");
        return;
    }
    if(IsEmpty()==true){
        throw Dlist_Exception(3,"The buffer is empty");
        return;
    }
    if(position>ListLength()){
        throw Dlist_Exception(1, "Строка, накопленная в буфере, имеет меньшую длину, чем указанная позиция.");
        return;
    }

    GoToBeg();
    int h=(current->lenofstr);
    int g=0;
    for(GoToBeg();!AtEnd();GoToNext()){
        for(int i=g, j=0;(i<h)&&(j<(current->lenofstr));i++, j++)
            if(i==(position-1)){
                current->lenofstr=n;
                delete [] current->str;
                current->str = new char[n];
                for(int ql=0; ql<n; ql++){
                    current->str[ql]=mass[ql];
                }
                return;
            }
        g=h;
        h+=after->lenofstr;
    }
    GoToEnd();
    for(int l=current->lenofstr; l>0; l--){
        if(position==ListLength()-l+1){
            current->lenofstr=n;
            delete [] current->str;
            current->str = new char [n];
            for(int un=0; un<n; un++){
                current->str[un]=mass[un];
            }

            return;
        }
    }
}

void Dlist:: SearchSymb(char symbol){ 
    int f=0;
    if(IsEmpty()==true){
        throw Dlist_Exception(3, "The buffer is empty");
        return;
    }
    char * mass=new char[ListLength()];
    GoToBeg();
    int h=(current->lenofstr);
    int g=0;
    for(GoToBeg();!AtEnd();GoToNext()){
        for(int i=g, j=0;(i<h)&&(j<(current->lenofstr)); i++,j++)
            mass[i]=current->str[j];

        g=h;
        h+=after->lenofstr;	
    }
    GoToEnd();

    for(int r1=(current->lenofstr);r1>0;r1--){
        mass[ListLength()-r1]=current->str[(current->lenofstr)-r1]; 
    }

    for(int l=0;l<ListLength();l++)
    {

        if(mass[l]==symbol) f++; 
    }
    if(f==0){
        cout<<"This symbol is not found in the buffer"<<endl;
        delete [] mass;
        return;
    }
    // else{
    int * positions=new int[f];
    int m=0;
    for(int r=0;r<ListLength();r++){
        if(mass[r]==symbol){
            positions[m]=r+1;
            m++; 
        }
    }
    cout<<"The symbol is found in the position(s): ";
    for(int t=0;t<f-1;t++){
        cout<<positions[t]<<", ";
    }
    cout<<positions[f-1]<<";"<<endl;
    delete[] positions;
    //}
    delete [] mass;
}

bool Dlist:: SearchStr(const char *stroka, int position){ 
    cout<<"Пытаемся найти подстроку "<<stroka<<" c позиции "<<position<<" в буфере"<<endl; 

    if(position>ListLength()){
        throw Dlist_Exception(1,"Строка, накопленная в буфере, меньшей длины, чем указанная позиция.");
        return false;
    }
    if(position<=0){
        throw  Dlist_Exception(2, "Некорректное значение указанной позиции");
        return false;
    }

    for(int i=0; i<strlen(stroka);i++){
        if(position==ListLength()) return false;
        if(TakeSymb(position)!=stroka[i]) return false;
        position++; 
    }
    return true;

}

void Dlist:: CutList(int length){  
    GoToBeg();
    int h=(current->lenofstr);
    int g=0;
    if(length<0){
        throw Dlist_Exception(2, "Некорректное значение");
        return;
    }

    if(length==0){
        for(GoToBeg();!AtEnd();DelAfter());
        base.next = base.prev = &base;
        delete[] current->str;
        // current->lenofstr=0;
        // current->next=current->prev=&base;
        delete current;
    }	
    for(GoToBeg();!AtEnd();GoToNext()){
        for(int i=g, j=0;(i<h) && (j<(current->lenofstr)); i++,j++){
            if(i+1==length){
                if((j)!=current->lenofstr-1) {
                    current->str[j+1]=0;
                    current->lenofstr=j+1;
                }
                for(;!AtEnd();DelAfter());          
                return;
            }
        }
        g=h;
        h+=after->lenofstr;	
    }
    GoToEnd();
    for(int e=(current->lenofstr); e>0; e--){
        if(ListLength()-e+1==length){
            current->str[(current->lenofstr)-e+1]=0;
            current->lenofstr=((current->lenofstr)-e+1);
        }
    }
}

Dlist_Exception:: Dlist_Exception(int m, const std::string &s){
    s_=s;
    error_code_=m;
} 
void Dlist_Exception:: Print_er(){
    cout<<"Код ошибки "<<error_code_<<endl;
    cout<<s_<<endl;
}
