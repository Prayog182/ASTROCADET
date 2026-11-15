#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <fstream>

using namespace std;

// 1. RESOURCES STRUCTURE

struct Resources {
    int oxygen = 100;
    int water = 100;
    int food = 100;
    int power = 100;
    int radiation = 0;
};

//2. INPUT VALIDATION

int getChoice(int minimum, int maximum) {

    int choice;

    while(true){

        cout << "Enter your choice: ";
        
        if(cin >> choice && choice >= minimum && choice <= maximum){
            return choice;
        }
        cout << "Invalid input! Try again.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// 3. RESOURCE LIMITS

void limitResources(Resources &r){

    r.oxygen = max(0, min(100,r.oxygen));
    r.water = max(0, min(100, r.water));
    r.food = max(0,min(100,r.food));
    r.power = max(0, min(100, r.power));
    r.radiation = max(0, min(100, r.radiation));
}

// 4. RESOURCE BAR

void drawBar(string name, int value){
    cout << name << "[";

    int filled = value / 5;

    for(int i = 0; i < 20; i++){
        if( i < filled)
            cout << "#";
            else
            cout << "-";
    }
    cout << "] " << value << "%\n";
}

//  STATUS DISPLAY

void showStatus(Resources r, int day, int sciencePoints, int score) {
    cout << "\n================================================\n";
    cout << "                ASTROCADET MISSION CONTROL         \n";
    cout << "===================================================\n";

    cout << "MISSION DAY: " << day << "/7\n";
    cout << "SCIENCE POINTS: " << sciencePoints << "\n";
    cout << "MISSION SCORE: " << score << "\n";
    
    cout << "\n ---- RESOURCES DASHBOARD-----------------------\n";
    
    drawBar("Oxygen   ", r.oxygen);
    drawBar("Water  ", r.water);
    drawBar("Food   ", r.food);
    drawBar("Power   ", r.power);
    drawBar("Radiation   ", r.radiation);

    cout << "\n=================================================\n";
}

// MISSION FAILURE

bool missionFailed(Resources r) {
    return r.oxygen <= 0 ||
           r.water <= 0 ||
           r.food <= 0 ||
           r.power <= 0 ||
           r.radiation >= 100;
}

// LEARN MODE

void showLearnMode() {
    cout << "\n===================================================\n";
    cout << "                    ASTRONAUT SCHOOL\n";
    cout << "=====================================================\n";

    cout << "\n1. OXYGEN\n";
    cout << "Astronaut need oxygen to breathe.\n";
    
    cout << "\n2. WATER RECYCLING\n";
    cout << "Space station recycle water to reduce waste.\n";

    cout << "\n3. SOLAR ENERGY\n";
    cout << "Solar panels convert sunlight into electricity.\n";

    cout << "\n4. RADIATION PROTECTION\n";
    cout << "Shelters help protect astronauts from radiation.\n";

    cout << "\n5. GREENHOUSE\n";
    cout << "Plants can help produce food and support life.\n";

    cout << "\nPlease Enter to continue....\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// DAILY ACTION MENU

int chooseDailyAction() {
    cout << "\n---------------- CHOOSE YOUR DAILY ACTION ---------------\n";
    cout << "1. Conduct scientific resarch.\n";
    cout << "2. Conserve resources.\n";
    cout << "3. Maintain solar panels.\n";
    cout << "4. Operate the green house.\n";
    cout << "5. Recycle the water.\n";
    
    return getChoice(1 , 5);
}

//  PERFORM ACTION

bool performAction(Resources &r, int action, int &sciencePoints, int &score) {
    bool conserving = false;

    switch(action){

        case 1:
           cout << "\nResearch Completed!\n";
           sciencePoints += 10;
           score +=  15;
           r.power -= 5;
           break;
          
         case 2:
           cout << "\nResources Conserved!\n";
           conserving = true;
           score += 10;
           break;
         
         case 3:
          cout << "\nSolar panels maintained!\n";
          r.power += 12;
          r.power -= 3;
          score += 10;
          break;
          
          case 4:
          cout << "\nGreen house operated!\n";
          r.food += 8;
          r.water -= 5;
          r.power -=  10;
          score += 15;
          break;

          case 5:
          cout << "\nWater recycling completed!\n";
          r.water += 10;
          r.power -= 8;
          score += 10;
          break;
    }
    limitResources(r);

    return conserving;
}

// RESOURCES CONSUMPTION

void consumeRescources(Resources &r, bool conserving) {
    if(conserving) {
        r.oxygen -= 7;
        r.water -= 8;
        r.food -= 6;
        r.power -= 5;
    }
    else {
        r.oxygen -= 10;
        r.water  -= 12;
        r.food -= 8;
        r.power -= 8;
    }

    limitResources(r);
}

//   EMERGENCY SYSTEM

bool handleEmergency(Resources &r, int &sciencePoints, int &score) {
    
    int emergency = rand() % 4 + 1;
    bool solarBlocked = false;

    cout << "\n!!! EMERGENCY ALERT !!!\n";

    switch(emergency) {

        case 1: {
              cout << "SOLAER DUST STROM DETECTED\n";

              cout << "1. Clean the solar pannels (5 power).\n";
              cout << "2. Wait for storm to pass.\n";

              int choice = getChoice (1 , 2);

              if(choice == 1 && r.power >= 5){
                r.power -= 5;
                cout << "Solar pannel cleaned!\n";
                score += 10;
              }
              else {
                solarBlocked = true;
                cout << "Solar charging blocked today!\n";
              }

              break;
            }
        
         case 2: {
            cout << "WATER LEAKED DETECTED.\n";

            cout << "1. Repair the leak (5 power).\n";
            cout << "2.Ignore the leak.\n";

            int choice = getChoice(1 , 2);

            if(choice == 1 && r.power >= 5) {
                r.power -= 5;
                r.water += 10;
                cout << "Leak repaired!\n";
                score += 10;
            }
            else {
                cout << "Water continues leaking.\n";
            }

            break;
         } 
         
         case 3: {
            cout << "RADIATION ALERT!\n";

            cout << "1. Enter radiation shelter (5 power).\n";
            cout << "2. Conduct outside research.\n";

            int choice = getChoice(1 , 2);

            if (choice == 1 && r.power >= 5) {
                r.power -= 5;
                cout << "You are protected.\n";
                score += 10;
            }
            else {
               r.radiation += 20;
               sciencePoints += 15;
               cout << "Radiation exposure increased.\n";
            }

            break;
         }

         case 4: {

            cout << "OXYGEN FILTARATION WARNING!\n";
            r.oxygen -= 15;

            cout << "1. Repair the filter (5 power).\n";
            cout << "2. Ignore the warning.\n";

            int choice = getChoice(1 , 2);

            if (choice == 1 && r.power >= 5) {
                r.power -= 5;
                cout << "Oxygen filter is repaired!\n";
                score += 10;
            }
            else {
                cout << "Oxygen supply remains low!\n";
            }
         }
    }
    limitResources(r);

    return solarBlocked;
}

//  DIFFICULTY

int chooseDifficulty() {
    cout << "\n------ SELECT MISSION DIFFICULTY --------------\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";

    return getChoice(1 , 3);
}

// FINAL DEBREIF

void showDebrief(Resources r, int sciencePoints, int score, bool failed) {
   
    cout << "\n========================================================\n";
    cout << "                MISSION DEBREIF                            \n";
    cout << "===========================================================\n";
    
    cout << "Science Points: " << sciencePoints << "\n";
    cout << "Mission Score: " << score << "\n";

    cout << "\nFinal resources:\n";

   drawBar("Oxygen    ", r.oxygen);
   drawBar("Water  ", r.water);
   drawBar("Food ", r.food);
   drawBar("Power ", r.power);
   drawBar("Radiation ", r.radiation);

   if(failed) {
    cout << "\nMISSION FAILED!\n";
    cout << "Congratulations, astronaut!\n";
    cout << "You successfully completed your mission.\n";
   }

   cout << "\n------ ASTRONAUT RANK ---------------\n";

   if(failed)
       cout << "Rank: Mission Trainee\n";
    else if (score >= 150) 
       cout << "Rank: Elite Astronaut\n";
     else if (score >= 90)
       cout << "Rank:  Senior Astronaut\n";
     else 
       cout << "Rank: Junior Astronaut\n";
       
     cout << "======================================\n";  
}

void checkNASAData() {
    ifstream file("donki_flaries.json");

    if (!file.is_open()) {
        cout << "Could not open NASA data file!\n";
        return;
    }
    string line;
    bool found = false;

    while(getline(file, line)) {
        if(line.find("\"flrID\" ") != string::npos) {
            cout << "\nNASA DONKI DATA LOADED!\n";
            cout << "\nSolar flare recorded found:\n";
            cout << line << endl;
            found = true;
            break;
        }
    }

    if(!found) {
        cout << "No solar flare record found.\n";
    }

    file.close();
}

//  MAIN FUNCTION

int main() {

    srand(time(0));

    cout << "\n=============================================\n";
    cout << "                  ASTROCADET\n";
    cout << "       JUNIOR ASTRONAUT MISSION TRAINER\n";
    cout << "===============================================\n";

    cout << "\nNASA CHECKED STARTED!\n";
    
    checkNASAData();

    cout << "n1. Learn Mode\n";
    cout << "2. Start Mission\n";

    int menu = getChoice(1 , 2);

    if(menu == 1) {
        showLearnMode();
    }

    int diffculty = chooseDifficulty();

    Resources base;

    int sciencePoints;
    int score = 0;

    bool failed = false;

    cout << "\nMission starting ......\n";

    // Apply difficluty settings

    if(diffculty == 2) {
        base.oxygen = 90;
        base.water = 90;
        base.food = 90;
        base.power = 90;
    }
   else if(diffculty == 3) {
        base.oxygen = 80;
        base.water = 80;
        base.food = 80;
        base.power = 80;
   }

   int totalDays = 7;

   // Main Mission loop

   for(int day = 1; day <= totalDays; day++) {

    cout << "\n\n============ DAY " << day << " ==================\n";
    showStatus(base, day, sciencePoints, score);

    int action = chooseDailyAction();

    bool conserving = performAction(
        base, action, sciencePoints, score
    );

    consumeRescources(base, conserving);

    bool solarBlocked = handleEmergency(
        base, sciencePoints, score
    );

    // Score energy recharge 

    if(!solarBlocked) {
        base.power += 15;
        cout << "\nCRITICAL SYSTEM FAILURE!\n";
        break;
    }

    cout << "\nDay  " << day << " completed!\n";
   }

   // Final mission Report

   showDebrief(base, sciencePoints, score, failed);

   cout << "\nThanks you for playing ASTROCADET!\n";

   return 0;
}
