#include <Arduino.h>
#include <Servo.h>

int stDel = 20;
Servo arm[6] = {};

//Servo vars
int pos[6] = {};
int goal[6] = {}; 

void updArm(int spd){
    int stepRes = 20;
    int del;
    int maxSpd = 5 + spd;
    int minSpd = maxSpd*3;

    for(int j = 0; j < stepRes; j++){
        //HANDLE ACCELERATION
        if(j < stepRes/2){
            del = map(j, 0, stepRes, minSpd, maxSpd);
        }
        else{
            del = map(j, stepRes/2, stepRes, maxSpd, minSpd);
        }
        for(int k = 0; k <= 5; k++){
            if(goal[k] != -1){
                int newPos = map(j, 0, stepRes, pos[k], goal[k]);
                arm[k].write(newPos);
               /* 
                Serial.print("MOVE:     ");
                Serial.print(k);
                Serial.print("  ");
                Serial.println(newPos);
                */
                delay(del);
            }
        }
        //Serial.println("");
    }
    for(int i = 0; i <= 5; i++){
        if(goal[i] != -1){
            pos[i] = goal[i];
        }
    }
}
void goToPos(int p0, int p1, int p2, int p3, int p4, int p5, int spd){
    // Update goals
    goal[0] = p0;
    goal[1] = p1;
    goal[2] = p2;
    goal[3] = p3;
    goal[4] = p4;
    goal[5] = p5;

    //move to new goals
    updArm(spd);

    delay(10);
}
void prog1(){
    // sets goal positions for servos 0-5, -1 = no change. Last arg is for speed
    goToPos(20, -1, -1, 180, -1, 140, 0);
    goToPos(-1, 150, 20, -1, 60, -1, 0); // go to pickup
    goToPos(-1, -1, -1, -1, -1, 80, 0); // close gripper
    goToPos(-1, 130, 75, -1, 115, -1, 0); // lift
    goToPos(90, -1, -1, 90, -1, -1, 6);
    goToPos(-1, -1, -1, -1, -1, 140, 0);
    goToPos(-1, 130, 75, -1, 115, -1, 5);



    // DONT ERASE PAST THIS YA DOPE
    goToPos(50, -1, -1, -1, -1, -1, 4);
    goToPos(-1, -1, -1, 180, -1, -1, 0);

    goToPos(90, -1, -1, 90, -1, -1, 8);
    goToPos(-1, -1, -1, -1, -1, 80, 0);
    goToPos(20, -1, -1, 180, -1, -1, 8);
    goToPos(-1, 150, 20, -1, 60, -1, 0);
    goToPos(-1, -1, -1, -1, -1, 140, 6);
    goToPos(-1, 130, 75, -1, 115, -1, 0); // lift
    goToPos(50, -1, -1, -1, -1, -1, 8);

    delay(500);
}
void goToHome(){
    goToPos(80, 100, 125, 180, 120, 80, 0);

    Serial.println("");
    Serial.println("HOMED");
    Serial.println("");

    delay(100);
}
void setup() {
    arm[0].attach(11);
    arm[1].attach(10);
    arm[2].attach(9);
    arm[3].attach(6);
    arm[4].attach(5);
    arm[5].attach(3);
    
    Serial.begin(9600);

    goToHome();
}
void loop() {
    prog1();
    //arm[4].write(40);
    //Serial.println("moved base");
    //delay(100);
    //goToHome();
}