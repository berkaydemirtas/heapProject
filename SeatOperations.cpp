/*
Student Name:
Student Number:
Project Number: 3
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "SeatOperations.h"

using namespace std;

SeatOperations::SeatOperations(int N, int M){



    Person person;
    person.type3LastOperation=-1;
    lines[0].resize(N);
    lines[1].resize(M);
    for(int i=0;i<N;i++)
        lines[0][i]=person;
    for(int i=0;i<M;i++){
        lines[1][i]=person;
    }
    this->N=N;
    this->M=M;
}

void SeatOperations::addNewPerson(int personType, const string& ticketInfo){




    Person person;
    person.initial=ticketInfo;
    person.type3LastOperation=-1;
    person.type=personType;
    if(ticketInfo.substr(0,1)=="A"){
        person.line=1;
    }
    else{
        person.line=2;
    }
    int ticketNumber=stoi(ticketInfo.substr(1));
    if(ticketNumber==0 && person.line==1){
        ticketNumber=N;
    }
    if(ticketNumber==0 && person.line==2){
        ticketNumber=M;
    }
    person.seatNumber=ticketNumber;

    if(person.line==1){

        if(lines[0][(person.seatNumber-1)%N].type==0){
            lines[0][(person.seatNumber-1)%N]=person;
            return;
        }
        else{
           Person person2=lines[0][(person.seatNumber-1)%N];
            lines[0][(person.seatNumber-1)%N]=person;

            if(person2.type==1){
                type1(person2);
                return; }
            if(person2.type==2) {
                type2(person2);
                return;
            }
            if(person2.type==3) {
                type3(person2);
                return;
            }
        }

    }
    else{
        if(lines[1][(person.seatNumber-1)%M].type==0){
            lines[1][(person.seatNumber-1)%M]=person;
            return;
        }
        else{
            Person person2=lines[1][(person.seatNumber-1)%M];
            lines[1][(person.seatNumber-1)%M]=person;

            if(person2.type==1){
                type1(person2);
                return; }
            if(person2.type==2) {
                type2(person2);
                return;
            }
            if(person2.type==3) {
                type3(person2);
                return;
            }
        }

    }




}

void SeatOperations::printAllSeats(ofstream& outFile){
    // IMPLEMENT ME!
    for(int i=0;i<N ;i++){
      if(lines[0][i].type==0)
       outFile<<0<<endl;
      else
          outFile<<lines[0][i].type<<" "<<lines[0][i].initial<<endl ;
    }

    for(int i=0;i<M ;i++){
        if(lines[1][i].type==0)
            outFile<<0 << endl;
        else
            outFile<<lines[1][i].type<<" "<<lines[1][i].initial<<endl ;
    }

}

void SeatOperations::type1(Person person){
        if(person.line==1){

        if(lines[1][(person.seatNumber-1)%M].type==0){
            person.line=2;
            lines[1][(person.seatNumber-1)%M]=person;
           return;
        }
        else{
            Person person2=lines[1][(person.seatNumber-1)%M];
            person.line=2;
            lines[1][(person.seatNumber-1)%M]=person;
             typer(person2);
             return;
        }
    }
        if(person.line==2){

            if(lines[0][(person.seatNumber-1)%N].type==0){
                person.line=1;
                lines[0][(person.seatNumber-1)%N]=person;
                return;
            }
            else{
                Person person2=lines[0][(person.seatNumber-1)%N];
                person.line=1;
                lines[0][(person.seatNumber-1)%N]=person;
                typer(person2);
                return;
            }


        }



}

void SeatOperations::type2(Person person){
    if(person.line==1){

        if(person.seatNumber%N==0){
            Person person2;
            person2=lines[1][0];
            person.seatNumber=1;
            person.line=2;
            lines[1][0]=person;

            typer(person2);
            return;
        }

        else{
            Person person2;
            person2=lines[0][(person.seatNumber-1)%N+1];

            lines[0][(person.seatNumber-1)%N+1]=person;
            lines[0][(person.seatNumber-1)%N+1].seatNumber++;
            typer(person2);
            return;
        }


    }
    if(person.line==2){

        if(person.seatNumber%M==0){
            Person person2;
            person2=lines[0][0];
            person.seatNumber=1;
            person.line=1;
            lines[0][0]=person;

            typer(person2);
            return;
        }

        else{
            Person person2;
            person2=lines[1][(person.seatNumber-1)%M+1];

            lines[1][(person.seatNumber-1)%M+1]=person;
            lines[1][(person.seatNumber-1)%M+1].seatNumber++;
            typer(person2);
            return;
        }


    }
}

void SeatOperations::type3(Person person) {

    int move = person.type3LastOperation + 2;

    if (person.line == 1) {

        int curr = (person.seatNumber - 1) % N;

        int move2 = (move + curr) % (M + N);

        if (move2 < N) {
            Person person2;
            person2 = lines[0][move2];
            lines[0][move2] = person;
            lines[0][move2].seatNumber = move2 + 1;
            lines[0][move2].type3LastOperation=lines[0][move2].type3LastOperation+2;
            typer(person2);
            return;
        } else {

            Person person2;
            int move3 = move2 - N;
            person2 = lines[1][move3];
            lines[1][move3] = person;
            lines[1][move3].seatNumber = move3 + 1;
            lines[1][move3].line = 2;
            lines[1][move3].type3LastOperation=lines[1][move3].type3LastOperation+2;
            typer(person2);
            return;
        }


    }

    if (person.line == 2) {

        int curr = (person.seatNumber - 1) % M;

        int move2 = (move + curr) % (M + N);

        if (move2 < M) {
            Person person2;
            person2 = lines[1][move2];
            lines[1][move2] = person;
            lines[1][move2].seatNumber = move2 + 1;
            lines[1][move2].type3LastOperation= lines[1][move2].type3LastOperation+2;
            typer(person2);
            return;
        } else {

            Person person2;
            int move3 = move2 - M;
            person2 = lines[0][move3];
            lines[0][move3] = person;
            lines[0][move3].seatNumber = move3 + 1;
            lines[0][move3].line = 1;
            lines[0][move3].type3LastOperation= lines[0][move3].type3LastOperation+2;
            typer(person2);
            return;
        }


    }
}






void SeatOperations:: typer(Person person){

    if(person.type==1){
        type1(person);
        return;
    }
    if(person.type==2){
        type2(person);
        return;
    }
    if(person.type==3){
        type3(person);
        return;
    }

}

// YOU CAN ADD YOUR HELPER FUNCTIONS