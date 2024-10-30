#include <iostream>

using namespace std;
void printMessage(strring message , ball printTop = true , bool printBottom = true )
{
    if(printTop)
    {
        cout <<"+---------------------------------+" << endl ;
        cout << "|";
        }
        else{
            cout <<"|"<< endl;
        }
    bool front - true;
    for (int  i = message.lenght(); i < 33; i++)
    {
       if (front){
        message = " "+ message
       }
       else 
       {
        message = message = message +"";

       }
       front = ! front ;

    }
    cout << mesage.c_str();
    if (printBottom)
    {
       cout <<"|";
       cout << "+---------------------------------+" << endl;
    }
    else{
        cout <<"|" << endl;
    }
    void DrawHangman(int guessCount =0 )
    {
        if (guessCount >= 1)
           printMessage("|",false , false)
        else
         printMessage(" ",false , false)
        if (guessCount >= 2)
           printMessage("|",false , false)
        else
         printMessage(" ",false , false)
        if (guessCount >= 3)
           printMessage("o",false , false)
        else
         printMessage(" ",false , false)
         if (guessCount == 4)
           printMessage("/",false , false)
        
         if (guessCount == 5)
           printMessage("/|",false , false)
        else
         printMessage(" ",false , false)
         if (guessCount >= 6)
           printMessage("/|\\",false , false)
        else
         printMessage(" ",false , false)
         if (guessCount >= 7)
           printMessage("|",false , false)
        else
         printMessage(" ",false , false)
         if (guessCount == 8)
           printMessage("/",false , false)
        else
         printMessage(" ",false , false)
         if (guessCount >= 9)
           printMessage("|\\",false , false)
        else
         printMessage(" ",false , false)
        

    }
    
        
            
    
}

int main()
{
    printMessage("HANG MAN IS COOL")
    DrawHangman(1);
    getchar();
    return  0;
}