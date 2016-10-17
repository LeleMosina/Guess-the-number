#include <iostream>
#include <cstdlib>
#include <math.h>
#include <malloc.h>
using namespace std;
/*
###################
##Emanuele Riccio##
###################
*/
void decToBin(int number,int arrayOut[]); //Dichiaro la funzione
int howMuchBit(int number); //Dichiaro la funzione
int howMuchNumberTable(int MAX,int table); //Serve per sapere quanti numeri da 0 a MAX, usano un bit alto a posizione table
void numberTable(int MAX,int table, int arrayOut[]); //Serve a mettere in una tabella i numeri
int binToDec(bool arrayIn[],int len); //Per convertire da binario a decimale
int main(){
    int MAX=0; //Numero massimo che compare nelle tabelle, contatori per scorrere nelle tabelle
    char risposta; //Risposta
    bool *listaRisposte;
    cout << "Inserisci il numero MAX: ";
    cin >> MAX;
    cout << "Pensa ad un numero compreso tra 1-"<<MAX<<endl<<endl;
    cin.ignore();
    int listaTabelle[howMuchBit(MAX)][60]; //Lista delle tabelle, array bidimensionale
    listaRisposte = (bool*)malloc(howMuchBit(MAX));
    for(int i=0;i<howMuchBit(MAX);i++){ //Itera per il numero di tabelle
        numberTable(MAX,i,listaTabelle[i]); //Mette nell'array tutti i numeri della tabella
        int sizeArray = howMuchNumberTable(MAX,i); //Prende il numero di elementi in quella tabella
        for(int i2=1;i2<=sizeArray;i2++){//Itera per tutti gli elementi di una tabella
            cout << "[";
            if(listaTabelle[i][i2]<10){
               cout << "0";
            }
            cout <<listaTabelle[i][i2] << "] ";
            if(i2%4==0){ //Va a capo, ogni 4 elementi
            cout << "\n";
            }
        }
        cout << "\n\nIl numero e' presente in questa tabella?(y\\n)"<<endl;
        cin>>risposta;
        if(tolower(risposta)=='y'){listaRisposte[howMuchBit(MAX)-i-1]=true;}
        else if(tolower(risposta)=='n'){listaRisposte[howMuchBit(MAX)-i-1]=false;}
        cout << "________________________________________________" << endl;
    }
    cout << "Il numero e': " << binToDec(listaRisposte,howMuchBit(MAX)) << endl;
    return 0;
}
int binToDec(bool arrayIn[],int len){ //Riceve in input una lista di bit, e la lunghezza
             int dec=0,exp=0; //Risultato, ed esponente
             for(int i=len-1;i>=0;i--){ //Decrementa i, perche' deve partire dal bit meno significativo, l'ultimo elemento dell'array
                 dec+=arrayIn[i]*pow(2,exp); //a dec aggiunge il bit a posizione i * 2^exp
                 exp++; //Incrementa exp
             }
             return dec; //Restituisce il valore
}
void decToBin(int number,int arrayOut[],int len){
             int val=number,ris=0,counter=0; //Dichiara le variabili per la funzione, val=numero, ris= resto delle divisioni per 2, counter= contatore
             while(val!=0){ //Finche val e' disiguale da 0, ovvero finche ci sono bit da codificare
                   ris=val%2; //Calcolare il resto di val/2 (il bit)
                   val=(int)(val/2); //Divide val per due, e lo casta ad int
                   arrayOut[counter]=ris; //Nell'array di supporto inserisce il bit
                   counter++; //Incrementa counter
             }
             //i bit sono scritti partento da arrayOut[0], da quello meno significativo a quello piu' significativo
}
int howMuchBit(int number){ //Restituisce quanti bit occupa un numero
              int counter=0; //Indice di potenza
              while(number>pow(2,counter)){ //Finche il numero sara' maggiore di 2^counter, significa che counter non soddisfa, il numero di bit necessari per tradurre number
                    counter++; //Aumenta counter di 1
              }
              return counter; //Restituisce counter
}
void numberTable(int MAX,int table, int arrayOut[]){ //Serve a determinare  quali numeri dovra' contenere ogni tabella
                    int number=0; //numero degli elementi che dovra' contenere la tabella
                    for(int i=pow(2,table);i<=MAX;i++){ //Parte da 2^table, quindi l'unita' minima per quella tabella
                        int arrayBit[howMuchBit(i)]; //Setta arrayBit
                        decToBin(i,arrayBit,howMuchBit(i)); //Converte in bit
                        if(arrayBit[table]==1){number++;arrayOut[number]=i;} //Se il bit a posizione table e' usato significa che la tabella conterra' questo numero, quindi number ++
                    }
}
int howMuchNumberTable(int MAX,int table){
                     int number=0; //numero degli elementi che dovra' contenere la tabella
                    for(int i=pow(2,table);i<=MAX;i++){ //Parte da 2^table, quindi l'unita' minima per quella tabella
                        int arrayBit[howMuchBit(i)]; //Setta arrayBit
                        decToBin(i,arrayBit,howMuchBit(i)); //Converte in bit
                        if(arrayBit[table]==1){number++;} //Se il bit a posizione table e' usato significa che la tabella conterra' questo numero, quindi number ++
                    }
                    return number; //Restituisce il numero
}
