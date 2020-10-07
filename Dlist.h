#ifndef SPISOK_STROK__

#define SPISOK_STROK__
#include<iostream>

struct DlistItem {
    char *str; 
    int lenofstr;
    DlistItem *next, *prev;
};

class Dlist{
    private:
        DlistItem base, *current, *after, *before ;
        void GoToEnd(); //Переход в конец списка
        void GoToBeg(); //Переход в начало списка
        bool GoToNext(); //Переход к следующему
        bool DelAfter(); //Удаление элемента списка после указанной позиции
        bool AtEnd(); //Проверка на нахождение в конце
    public:
        Dlist(); 
        ~Dlist();
        Dlist(char *stroka); //Создание буфера, инициализированного данной строкой
        void InsAfter(const char* x); //Вставка после
        void InsAfter_formass(char* x, int n);
        void InsAfterPos(const char* x, int position); //Вставка после указанной позиции
        void AddToEnd(const char* x); //Добавить заданную строку в конец буфера 
        int ListLength(); //Длина строки, накопленной в буфере
        char* CopyList(char *mass); //Копирует строку буфера в символьный массив
        bool IsEmpty();//Проверка на пустоту
        void PrintList();//Печать буфера
        char* CopyElemList(char *mass, int position); //Копирует подстроку из буфера в символьный массив(в тесте создавать массив нужной длины)
        char TakeSymb(int position); //Получение символа в заданной позиции
        void ChangeSymb(int position, char elem); //Изменение символа в заданной позиции на заданный символ
        void ChangeStr(char *mass, int n, int position);//Заменяет одну подстроку(по указанной позиции) на другую указанной длины
        void SearchSymb(char symbol); //Ищет заданный символ, возвращает номер этого элемента в буфере
        bool SearchStr(const char *stroka, int position); //Ищет заданную подстроку в буфере(в указанной позиции) 
        void CutList(int length); //Обрезает буфер по указанной длине					
};

class Dlist_Exception{
    protected:
        int error_code_;
        std::string s_;
    public:
        Dlist_Exception(int m, const std::string &s);
        void Print_er();
};

#endif
