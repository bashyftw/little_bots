#ifndef ASDF_H
#define ASDF_H

class Asdf
{
     private :
          int h;
          int m;
          int s;
     public :
          //with default value
          Asdf(int hours, int minutes, int seconds);
          Asdf();
          //	setter function
          void setTime(int h, int m, int s);
          // Print a description of object in " hh:mm:ss"
          void print();
          //compare two time object
          bool equals(Asdf&);
};

Asdf::Asdf (int hours, int minutes , int seconds){
     h = hours;
     m = minutes;
     s = seconds;
}

Asdf::Asdf(){
     h = 4;
     m = 5;
     s = 6; 
}
 
#endif