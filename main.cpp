#include<bits/stdc++.h>


using namespace std;
int base_x; // The corner of the map representing your base
int base_y;
int heroes_per_player; // Always 3
int my_health,op_health; // Each player's base health
int my_mana,op_mana; // Spend ten mana to cast a spell
int entity_count; // Amount of heros and monsters you can see

int id; // Unique identifier
int type; // 0=monster, 1=your hero, 2=opponent hero
int x; // Position of this entity
int y;
int shield_life; // Ignore for this league; Count down until shield spell fades
int is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell
int health; // Remaining health of this monster
int vx; // Trajectory of this monster
int vy;
int near_base; // 0=monster with no target yet, 1=monster targeting a base
int threat_for; // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
int defence_mode=1;
int need_shield3=0;
int need_shield2=0;
int need_shield1=0;
int go_to1=1;
int go_to2=1;
int go_to3=1;
int attack=0;
int prevOpHealth=3;



int numberIn;

struct entity{
    int id; // Unique identifier
    int type; // 0=monster, 1=your hero, 2=opponent hero
    int x; // Position of this entity
    int y;
    int shield_life; // Ignore for this league; Count down until shield spell fades
    int is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell
    int health; // Remaining health of this monster
    int vx; // Trajectory of this monster
    int vy;
    int near_base; // 0=monster with no target yet, 1=monster targeting a base
    int threat_for;
};

struct point{
    int x,y;
};

point A;


//our Entity
        map<int,entity> mEnemy;
        map<int,entity> opHero;
        map<int,entity> opHero3;
        map<int,entity> myHero;
        map<int,entity> nEnemy;
        map<int,entity> nEnemy1;
        map<int,entity> nEnemy2;
        map<int,entity> nEnemy3;
        map<int,entity> myEnemy0;
        map<int,entity> myEnemy01;
        map<int,entity> myEnemy02;
        map<int,entity> myEnemy03;
        map<int,entity> myEnemy1;
        map<int,entity> myEnemy11;
        map<int,entity> myEnemy12;
        map<int,entity> opEnemy0;
        map<int,entity> opEnemy02;
        map<int,entity> opEnemy03;
        map<int,entity> opEnemy1;
        map<int,entity> opEnemy12;
        map<int,entity> opEnemy13;
//our Entity

//our list of Entity
        vector<pair<int,int>>listNEnemy;//sort by life dec
        vector<pair<int,int>>listNEnemy1;//sort by life dec
        vector<pair<int,int>>listNEnemy2;//sort by life dec
        vector<pair<int,int>>listNEnemy3;//sort by life dec
        vector<pair<double,int>>listMyEnemy0;//sort by distance dec
        vector<pair<double,int>>listMyEnemy01;//sort by distance dec
        vector<pair<double,int>>listMyEnemy02;//sort by distance dec
        vector<pair<double,int>>listMyEnemy03;//sort by distance dec
        vector<pair<double,int>>listMyEnemy1;//sort by distance dec
        vector<pair<double,int>>listMyEnemy11;//sort by distance dec
        vector<pair<double,int>>listMyEnemy12;//sort by distance dec
        vector<pair<double,int>>listOpEnemy0;//sort by distance dec
        vector<pair<double,int>>listOpEnemy02;//sort by distance dec
        vector<pair<double,int>>listOpEnemy03;//sort by distance dec
        vector<pair<double,int>>listOpEnemy1;//sort by distance dec
        vector<pair<double,int>>listOpEnemy12;//sort by distance dec
        vector<pair<double,int>>listOpEnemy13;//sort by distance dec
        vector<pair<double,int>>listOpHero;//sort by distance dec
        vector<pair<double,int>>listOpHero3;//sort by distance dec
//our list of Entity



double threatLvl(int x,int y,int baseX,int baseY,int near_base){
    int curr_dist=sqrt(pow(x-baseX,2)+pow(y-baseY,2));
    return ((1.0/curr_dist)+near_base)*1000;
}
double threatLvlEnemy(int x,int y,int baseX,int baseY,int near_base){
    int curr_dist=sqrt(pow(x-(17630-baseX),2)+pow(y-(9000-baseY),2));
    return ((1.0/curr_dist)+near_base)*1000;
}
double distance(int x,int y,int baseX,int baseY){
    int curr_dist=sqrt(pow(x-baseX,2)+pow(y-baseY,2));
    return curr_dist;
}

bool giveItShield(int life,double distance, int opHeros){
    if(opHeros==0) opHeros=1;
    if((life-(distance/400)*2)>=0) return true;
    else return false;
}

void defenceMovment(){
    point hero0;
    string action0="MOVE";
    entity enemy0;
    point hero1;
    string action1="MOVE";
    entity enemy1;
    int id0;
    int id1;
    if(base_x==0){
        id0=0;
        id1=1;
    }else{
        id0=3;
        id1=4;
    }
    if(myEnemy1.size()>1){
        int distance0=distance(myHero[id0].x,myHero[id0].y,myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y);
        int distance1=distance(myHero[id1].x,myHero[id1].y,myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y);
        if(distance0<=distance1){
            if(myEnemy1[listMyEnemy1[0].second].shield_life==0&&my_mana>=10&&(distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,base_x,base_y)<=800||(opHero.size()>0&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,opHero[listOpHero[0].second].x,opHero[listOpHero[0].second].y)<=2080))&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id0].x,myHero[id0].y)<=1280){
                action0="WIND";
                hero0.x=17630-base_x;
                hero0.y=9000-base_y;
                my_mana-=10;
            }else if(myEnemy1[listMyEnemy1[0].second].shield_life==0&&my_mana>=10&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,base_x,base_y)<=1000&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id0].x,myHero[id0].y)<=2200&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id0].x,myHero[id0].y)>1280){
                action0="CONTROL10";
                hero0.x=17630-base_x;
                hero0.y=9000-base_y;
                my_mana-=10;
            }else{
                action0="MOVE";
                hero0.x=myEnemy1[listMyEnemy1[0].second].x;
                hero0.y=myEnemy1[listMyEnemy1[0].second].y;
            }
            if(myEnemy1[listMyEnemy1[1].second].shield_life==0&&my_mana>=10&&(distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,base_x,base_y)<=800||(opHero.size()>0&&distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,opHero[listOpHero[0].second].x,opHero[listOpHero[0].second].y)<=2080))&&distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,myHero[id1].x,myHero[id1].y)<=1280){
                action1="WIND";
                hero1.x=17630-base_x;
                hero1.y=9000-base_y;
            }else if(myEnemy1[listMyEnemy1[1].second].shield_life==0&&my_mana>=10&&distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,base_x,base_y)<=1000&&distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,myHero[id1].x,myHero[id1].y)<=2200&&distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,myHero[id1].x,myHero[id1].y)>1280){
                action1="CONTROL11";
                hero1.x=17630-base_x;
                hero1.y=9000-base_y;
                my_mana-=10;
            }else{
                action1="MOVE";
                hero1.x=myEnemy1[listMyEnemy1[1].second].x;
                hero1.y=myEnemy1[listMyEnemy1[1].second].y;
            }

        }else{
            if(myEnemy1[listMyEnemy1[1].second].shield_life==0&&my_mana>=10&&(distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,base_x,base_y)<=800||(opHero.size()>0&&distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,opHero[listOpHero[0].second].x,opHero[listOpHero[0].second].y)<=2080))&&distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,myHero[id0].x,myHero[id0].y)<=1280){
                action0="WIND";
                hero0.x=17630-base_x;
                hero0.y=9000-base_y;
                my_mana-=10;
            }else if(myEnemy1[listMyEnemy1[1].second].shield_life==0&&my_mana>=10&&distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,base_x,base_y)<=1000&&distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,myHero[id0].x,myHero[id0].y)<=2200&&distance(myEnemy1[listMyEnemy1[1].second].x,myEnemy1[listMyEnemy1[1].second].y,myHero[id0].x,myHero[id0].y)>1280){
                action0="CONTROL11";
                hero0.x=17630-base_x;
                hero0.y=9000-base_y;
                my_mana-=10;
            }else{
                action0="MOVE";
                hero0.x=myEnemy1[listMyEnemy1[1].second].x;
                hero0.y=myEnemy1[listMyEnemy1[1].second].y;
            }
            if(myEnemy1[listMyEnemy1[0].second].shield_life==0&&my_mana>=10&&(distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,base_x,base_y)<=800||(opHero.size()>0&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,opHero[listOpHero[0].second].x,opHero[listOpHero[0].second].y)<=2080))&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id1].x,myHero[id1].y)<=1280){
                action1="WIND";
                hero1.x=17630-base_x;
                hero1.y=9000-base_y;
            }else if(myEnemy1[listMyEnemy1[0].second].shield_life==0&&my_mana>=10&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,base_x,base_y)<=1000&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id1].x,myHero[id1].y)<=2200&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id1].x,myHero[id1].y)>1280){
                action1="CONTROL10";
                hero1.x=17630-base_x;
                hero1.y=9000-base_y;
                my_mana-=10;
            }else{
                action1="MOVE";
                hero1.x=myEnemy1[listMyEnemy1[0].second].x;
                hero1.y=myEnemy1[listMyEnemy1[0].second].y;
            }
        }
    }else if(myEnemy1.size()==1){
        int distance0=distance(myHero[id0].x,myHero[id0].y,myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y);
        int distance1=distance(myHero[id1].x,myHero[id1].y,myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y);
        if(distance0<distance1){
            if(myEnemy1[listMyEnemy1[0].second].shield_life==0&&my_mana>=10&&(distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,base_x,base_y)<=800||(opHero.size()>0&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,opHero[listOpHero[0].second].x,opHero[listOpHero[0].second].y)<=2080))&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id0].x,myHero[id0].y)<=1280){
                action0="WIND";
                hero0.x=17630-base_x;
                hero0.y=9000-base_y;
                my_mana-=10;
            }else if(myEnemy1[listMyEnemy1[0].second].shield_life==0&&my_mana>=10&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,base_x,base_y)<=1000&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id0].x,myHero[id0].y)<=2200&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id0].x,myHero[id0].y)>1280){
                action0="CONTROL10";
                hero0.x=17630-base_x;
                hero0.y=9000-base_y;
                my_mana-=10;
            }else{
                action0="MOVE";
                hero0.x=myEnemy1[listMyEnemy1[0].second].x;
                hero0.y=myEnemy1[listMyEnemy1[0].second].y;
            }
            if(myEnemy02.size()>0&&distance(myEnemy02[listMyEnemy02[0].second].x,myEnemy02[listMyEnemy02[0].second].y,base_x,base_y)<=8000){
                hero1.x=myEnemy02[listMyEnemy02[0].second].x;
                hero1.y=myEnemy02[listMyEnemy02[0].second].y;
            }else{
                action1="MOVE";
                hero1.x=myEnemy1[listMyEnemy1[0].second].x;
                hero1.y=myEnemy1[listMyEnemy1[0].second].y;
            }

        }else{
            if(myEnemy1[listMyEnemy1[0].second].shield_life==0&&my_mana>=10&&(distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,base_x,base_y)<=800||(opHero.size()>0&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,opHero[listOpHero[0].second].x,opHero[listOpHero[0].second].y)<=2080))&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id1].x,myHero[id1].y)<=1280){
                action1="WIND";
                hero1.x=17630-base_x;
                hero1.y=9000-base_y;
            }else if(myEnemy1[listMyEnemy1[0].second].shield_life==0&&my_mana>=10&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,base_x,base_y)<=1000&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id1].x,myHero[id1].y)<=2200&&distance(myEnemy1[listMyEnemy1[0].second].x,myEnemy1[listMyEnemy1[0].second].y,myHero[id1].x,myHero[id1].y)>1280){
                action1="CONTROL10";
                hero1.x=17630-base_x;
                hero1.y=9000-base_y;
                my_mana-=10;
            }else{
                action1="MOVE";
                hero1.x=myEnemy1[listMyEnemy1[0].second].x;
                hero1.y=myEnemy1[listMyEnemy1[0].second].y;
            }
            if(myEnemy01.size()>0&&distance(myEnemy01[listMyEnemy01[0].second].x,myEnemy01[listMyEnemy01[0].second].y,base_x,base_y)<=8000){
                hero0.x=myEnemy01[listMyEnemy01[0].second].x;
                hero0.y=myEnemy01[listMyEnemy01[0].second].y;
            }else{
                action0="MOVE";
                hero0.x=myEnemy1[listMyEnemy1[0].second].x;
                hero0.y=myEnemy1[listMyEnemy1[0].second].y;
            }
        }
    }else if(myEnemy0.size()>1){
        int distance0=distance(myHero[id0].x,myHero[id0].y,myEnemy0[listMyEnemy0[0].second].x,myEnemy0[listMyEnemy0[0].second].y);
        int distance1=distance(myHero[id1].x,myHero[id1].y,myEnemy0[listMyEnemy0[0].second].x,myEnemy0[listMyEnemy0[0].second].y);
        if(distance0<=distance1){
            hero0.x=myEnemy0[listMyEnemy0[0].second].x;
            hero0.y=myEnemy0[listMyEnemy0[0].second].y;
            hero1.x=myEnemy0[listMyEnemy0[1].second].x;
            hero1.y=myEnemy0[listMyEnemy0[1].second].y;
        }else{
            hero0.x=myEnemy0[listMyEnemy0[1].second].x;
            hero0.y=myEnemy0[listMyEnemy0[1].second].y;
            hero1.x=myEnemy0[listMyEnemy0[0].second].x;
            hero1.y=myEnemy0[listMyEnemy0[0].second].y;
        }
    }else if(myEnemy0.size()==1){
        int distance0=distance(myHero[id0].x,myHero[id0].y,myEnemy0[listMyEnemy0[0].second].x,myEnemy0[listMyEnemy0[0].second].y);
        int distance1=distance(myHero[id1].x,myHero[id1].y,myEnemy0[listMyEnemy0[0].second].x,myEnemy0[listMyEnemy0[0].second].y);
        if(distance0<distance1){
            hero0.x=myEnemy0[listMyEnemy0[0].second].x;
            hero0.y=myEnemy0[listMyEnemy0[0].second].y;
            if(nEnemy2.size()>0/*&&distance(nEnemy2[listNEnemy2[0].second].x,nEnemy2[listNEnemy2[0].second].y,base_x,base_y)<=8000*/){
                hero1.x=nEnemy2[listNEnemy2[0].second].x;
                hero1.y=nEnemy2[listNEnemy2[0].second].y;
            }else{
                if(base_x==0){
                    hero1.x=rand()%1800+2000;
                    hero1.y=rand()%1900+4100;
                }else{
                    hero1.x=rand()%1800+13700;
                    hero1.y=rand()%1900+3100;
                }

            }
        }else{

            hero1.x=myEnemy0[listMyEnemy0[0].second].x;
            hero1.y=myEnemy0[listMyEnemy0[0].second].y;
            if(nEnemy1.size()>0&&distance(nEnemy1[listNEnemy1[0].second].x,nEnemy1[listNEnemy1[0].second].y,base_x,base_y)<=7000){
                hero0.x=nEnemy1[listNEnemy1[0].second].x;
                hero0.y=nEnemy1[listNEnemy1[0].second].y;
            }else{
                if(base_x==0){
                    hero0.x=rand()%2300+3500;
                    hero0.y=rand()%1800+2000;
                }else{
                    hero0.x=rand()%1800+11600;
                    hero0.y=rand()%1800+5100;
                }

            }
        }
    }else{
        if(nEnemy1.size()>0&&distance(nEnemy1[listNEnemy1[0].second].x,nEnemy1[listNEnemy1[0].second].y,base_x,base_y)<=7000){
            hero0.x=nEnemy1[listNEnemy1[0].second].x;
            hero0.y=nEnemy1[listNEnemy1[0].second].y;
        }else{
            if(base_x==0){
                hero0.x=rand()%2300+3500;
                hero0.y=rand()%1800+2000;
            }else{
                hero0.x=rand()%1800+11600;
                hero0.y=rand()%1800+5100;
            }

        }

        if(nEnemy2.size()>0/*&&distance(nEnemy2[listNEnemy2[0].second].x,nEnemy2[listNEnemy2[0].second].y,base_x,base_y)<=6000*/){
            hero1.x=nEnemy2[listNEnemy2[0].second].x;
            hero1.y=nEnemy2[listNEnemy2[0].second].y;
        }else{
            if(base_x==0){
                hero1.x=rand()%1800+2000;
                hero1.y=rand()%1900+4100;
               /* hero1.x=rand()%5000+3000;
                hero1.y=rand()%2000+5100;*/
            }else{
                hero1.x=rand()%1800+13700;
                hero1.y=rand()%1900+3100;
            }

        }



    }
    if(action0=="MOVE"){
        cout<<"MOVE "<<hero0.x<<" "<<hero0.y<<" #1"<<endl;
    }else if(action0=="CONTROL10"){
        cout<<"SPELL CONTROL "<<listMyEnemy1[0].second<<" "<<hero0.x<<" "<<hero0.y<<" #1"<<endl;
    }else if(action0=="CONTROL11"){
        cout<<"SPELL CONTROL "<<listMyEnemy1[1].second<<" "<<hero0.x<<" "<<hero0.y<<" #1"<<endl;
    }else{
        cout<<"SPELL WIND "<<hero0.x<<" "<<hero0.y<<" #1"<<endl;
    }
    if(action1=="MOVE"){
        cout<<"MOVE "<<hero1.x<<" "<<hero1.y<<" #2"<<endl;
    }else if(action1=="CONTROL10"){
        cout<<"SPELL CONTROL "<<listMyEnemy1[0].second<<" "<<hero1.x<<" "<<hero1.y<<" #1"<<endl;
    }else if(action1=="CONTROL11"){
        cout<<"SPELL CONTROL "<<listMyEnemy1[1].second<<" "<<hero1.x<<" "<<hero1.y<<" #1"<<endl;
    }else{
        cout<<"SPELL WIND "<<hero1.x<<" "<<hero1.y<<" #2"<<endl;
    }

}

void hero3(){
    if(base_x==0){
        if(myHero[2].x==12630&&myHero[2].y==8000){
            A.x=16630;
            A.y=4000;
        }else if(myHero[2].x==16630&&myHero[2].y==4000)
        {
            A.x=12630;
            A.y=8000;
        }
        if(attack&&prevOpHealth!=op_health){
            attack=0;
        }
        if(opEnemy13.size()>0){
            if(opEnemy13[listOpEnemy13[0].second].shield_life==0&&distance(myHero[2].x,myHero[2].y,opEnemy13[listOpEnemy13[0].second].x,opEnemy13[listOpEnemy13[0].second].y)<=1280&&my_mana>=20){
                int oPbase_x=17630-base_x;
                int oPbase_y=9000-base_y;
                float slope_of_Enemy=((float)oPbase_y-opEnemy13[listOpEnemy13[0].second].y)/((float)oPbase_x-opEnemy13[listOpEnemy13[0].second].x);
                int new_x=myHero[2].x+1000;
                float new_yD=(slope_of_Enemy*(new_x-myHero[2].x))+myHero[2].y;
                int new_y=round(new_yD);
                cout<<"SPELL WIND "<<new_x<<" "<<new_y<<" #3"<<endl;
                my_mana-=10;
                attack=1;
            }else if(giveItShield(opEnemy13[listOpEnemy13[0].second].health,distance(opEnemy13[listOpEnemy13[0].second].x,opEnemy13[listOpEnemy13[0].second].y,(17630-base_x),(9000-base_y)),opHero3.size())&&opEnemy13[listOpEnemy13[0].second].shield_life==0&&distance(myHero[2].x,myHero[2].y,opEnemy13[listOpEnemy13[0].second].x,opEnemy13[listOpEnemy13[0].second].y)<=2200&&my_mana>=20){
                cout<<"SPELL SHIELD "<<opEnemy13[listOpEnemy13[0].second].id<<" #3"<<endl;
            }else if(opHero3.size()>0&&opHero3[listOpHero3[0].second].shield_life==0&&opEnemy13[listOpEnemy13[0].second].shield_life!=0&&distance(myHero[2].x,myHero[2].y,opHero3[listOpHero3[0].second].x,opHero3[listOpHero3[0].second].y)<=2200&&my_mana>=20){
                cout<<"SPELL CONTROL "<<opHero3[listOpHero3[0].second].id<<" "<<base_x<<" "<<base_y<<" #3"<<endl;
            }else{
                if(opEnemy13[listOpEnemy13[0].second].shield_life==0){
                    cout<<"MOVE "<<opEnemy13[listOpEnemy13[0].second].x+opEnemy13[listOpEnemy13[0].second].vx<<" "<<opEnemy13[listOpEnemy13[0].second].y+opEnemy13[listOpEnemy13[0].second].vy<<" #3"<<endl;
                }else{
                    cout<<"MOVE "<<opEnemy13[listOpEnemy13[0].second].x-1000<<" "<<opEnemy13[listOpEnemy13[0].second].y-500<<" #3"<<endl;
                }
            }
        }else if(attack&&prevOpHealth==op_health){
            cout<<"MOVE "<<17630-base_x<<" "<<9000-base_y<<" #3"<<endl;
            attack=0;
        }else if(opEnemy03.size()>0){
            if(distance(myHero[2].x,myHero[2].y,opEnemy03[listOpEnemy03[0].second].x,opEnemy03[listOpEnemy03[0].second].y)<=1280&&my_mana>=30){
                int oPbase_x=17630-base_x;
                int oPbase_y=9000-base_y;
                float slope_of_Enemy=((float)oPbase_y-opEnemy03[listOpEnemy03[0].second].y)/((float)oPbase_x-opEnemy03[listOpEnemy03[0].second].x);
                int new_x=myHero[2].x+1000;
                float new_yD=(slope_of_Enemy*(new_x-myHero[2].x))+myHero[2].y;
                int new_y=round(new_yD);
                cout<<"SPELL WIND "<<new_x<<" "<<new_y<<" #3"<<endl;
                my_mana-=10;
            }else{
                cout<<"MOVE "<<opEnemy03[listOpEnemy03[0].second].x<<" "<<opEnemy03[listOpEnemy03[0].second].y<<" #3"<<endl;
            }
        }else if(myEnemy03.size()>0&&my_mana>=30) //there is myEnemy0 and distance of 2200 of hero 0
        {
            if(distance(myHero[2].x,myHero[2].y,myEnemy03[listMyEnemy03[0].second].x,myEnemy03[listMyEnemy03[0].second].y)<=1280&&my_mana>=20){
                int oPbase_x=17630-base_x;
                int oPbase_y=9000-base_y;
                float slope_of_Enemy=((float)oPbase_y-myEnemy03[listMyEnemy03[0].second].y)/((float)oPbase_x-myEnemy03[listMyEnemy03[0].second].x);
                int new_x=myHero[2].x+1000;
                float new_yD=(slope_of_Enemy*(new_x-myHero[2].x))+myHero[2].y;
                int new_y=round(new_yD);
                cout<<"SPELL WIND "<<new_x<<" "<<new_y<<" #3"<<endl;
                my_mana-=10;
            }else{
                cout<<"MOVE "<<myEnemy03[listMyEnemy03[0].second].x<<" "<<myEnemy03[listMyEnemy03[0].second].y<<" #3"<<endl;
            }
        }else if(nEnemy3.size()>0&&my_mana>=30) //there is myEnemy0 and distance of 2200 of hero 0
        {
            if(distance(myHero[2].x,myHero[2].y,nEnemy3[listNEnemy3[0].second].x,nEnemy3[listNEnemy3[0].second].y)<=1280&&my_mana>=20){
                int oPbase_x=17630-base_x;
                int oPbase_y=9000-base_y;
                float slope_of_Enemy=((float)oPbase_y-nEnemy3[listNEnemy3[0].second].y)/((float)oPbase_x-nEnemy3[listNEnemy3[0].second].x);
                int new_x=myHero[2].x+1000;
                float new_yD=(slope_of_Enemy*(new_x-myHero[2].x))+myHero[2].y;
                int new_y=round(new_yD);
                cout<<"SPELL WIND "<<new_x<<" "<<new_y<<" #3"<<endl;
                my_mana-=10;
            }else{
                cout<<"MOVE "<<nEnemy3[listNEnemy3[0].second].x<<" "<<nEnemy3[listNEnemy3[0].second].y<<" #3"<<endl;
            }
        }else{
            cout<<"MOVE "<<A.x<<" "<<A.y<<" #3"<<endl;
        }
    }else{
        if(myHero[5].x==5000&&myHero[5].y==1000){
            A.x=1000;
            A.y=5000;
        }else if(myHero[5].x==1000&&myHero[5].y==5000)
        {
            A.x=5000;
            A.y=1000;
        }
        if(attack&&prevOpHealth!=op_health){
            attack=0;
        }
        if(opEnemy13.size()>0){
            if(opEnemy13[listOpEnemy13[0].second].shield_life==0&&distance(myHero[5].x,myHero[5].y,opEnemy13[listOpEnemy13[0].second].x,opEnemy13[listOpEnemy13[0].second].y)<=1280&&my_mana>=20){
                int oPbase_x=17630-base_x;
                int oPbase_y=9000-base_y;
                float slope_of_Enemy=((float)oPbase_y-opEnemy13[listOpEnemy13[0].second].y)/((float)oPbase_x-opEnemy13[listOpEnemy13[0].second].x);
                int new_x=myHero[5].x-1000;
                float new_yD=(slope_of_Enemy*(new_x-myHero[5].x))+myHero[5].y;
                int new_y=round(new_yD);
                cout<<"SPELL WIND "<<new_x<<" "<<new_y<<" #3"<<endl;
                my_mana-=10;
                attack=1;
            }else if(opEnemy13[listOpEnemy13[0].second].shield_life==0&&distance(17630-base_x,9000-base_y,opEnemy13[listOpEnemy13[0].second].x,opEnemy13[listOpEnemy13[0].second].y)<=1600&&distance(myHero[5].x,myHero[5].y,opEnemy13[listOpEnemy13[0].second].x,opEnemy13[listOpEnemy13[0].second].y)<=1280&&my_mana>=20){
                int oPbase_x=17630-base_x;
                int oPbase_y=9000-base_y;
                float slope_of_Enemy=((float)oPbase_y-opEnemy13[listOpEnemy13[0].second].y)/((float)oPbase_x-opEnemy13[listOpEnemy13[0].second].x);
                int new_x=myHero[5].x-1000;
                float new_yD=(slope_of_Enemy*(new_x-myHero[5].x))+myHero[5].y;
                int new_y=round(new_yD);
                cout<<"SPELL WIND "<<new_x<<" "<<new_y<<" #3"<<endl;
                my_mana-=10;
                attack=1;
            }else if(giveItShield(opEnemy13[listOpEnemy13[0].second].health,distance(opEnemy13[listOpEnemy13[0].second].x,opEnemy13[listOpEnemy13[0].second].y,(17630-base_x),(9000-base_y)),opHero3.size())&&opEnemy13[listOpEnemy13[0].second].shield_life==0&&distance(myHero[5].x,myHero[5].y,opEnemy13[listOpEnemy13[0].second].x,opEnemy13[listOpEnemy13[0].second].y)<=2200&&my_mana>=20){
                cout<<"SPELL SHIELD "<<opEnemy13[listOpEnemy13[0].second].id<<" #3"<<endl;
            }else if(opHero3.size()>0&&opHero3[listOpHero3[0].second].shield_life==0&&opEnemy13[listOpEnemy13[0].second].shield_life!=0&&distance(myHero[5].x,myHero[5].y,opHero3[listOpHero3[0].second].x,opHero3[listOpHero3[0].second].y)<=2200&&my_mana>=20){
                cout<<"SPELL CONTROL "<<opHero3[listOpHero3[0].second].id<<" "<<base_x<<" "<<base_y<<" #3"<<endl;
            }else{
                if(opEnemy13[listOpEnemy13[0].second].shield_life==0){
                    cout<<"MOVE "<<opEnemy13[listOpEnemy13[0].second].x+opEnemy13[listOpEnemy13[0].second].vx<<" "<<opEnemy13[listOpEnemy13[0].second].y+opEnemy13[listOpEnemy13[0].second].vy<<" #3"<<endl;
                }else{
                    cout<<"MOVE "<<opEnemy13[listOpEnemy13[0].second].x+1000<<" "<<opEnemy13[listOpEnemy13[0].second].y+500<<" #3"<<endl;
                }
            }
        }else if(attack&&prevOpHealth==op_health){
            cout<<"MOVE "<<17630-base_x<<" "<<9000-base_y<<" #3"<<endl;
            attack=0;
        }else if(opEnemy03.size()>0){
            if(distance(myHero[5].x,myHero[5].y,opEnemy03[listOpEnemy03[0].second].x,opEnemy03[listOpEnemy03[0].second].y)<=1280&&my_mana>=30){
                int oPbase_x=17630-base_x;
                int oPbase_y=9000-base_y;
                float slope_of_Enemy=((float)oPbase_y-opEnemy03[listOpEnemy03[0].second].y)/((float)oPbase_x-opEnemy03[listOpEnemy03[0].second].x);
                int new_x=myHero[5].x-1000;
                float new_yD=(slope_of_Enemy*(new_x-myHero[5].x))+myHero[5].y;
                int new_y=round(new_yD);
                cout<<"SPELL WIND "<<new_x<<" "<<new_y<<" #3"<<endl;
                my_mana-=10;
            }else{
                cout<<"MOVE "<<opEnemy03[listOpEnemy03[0].second].x<<" "<<opEnemy03[listOpEnemy03[0].second].y<<" #3"<<endl;
            }
        }else if(myEnemy03.size()>0&&my_mana>=30) //there is myEnemy0 and distance of 2200 of hero 0
        {
            if(distance(myHero[5].x,myHero[5].y,myEnemy03[listMyEnemy03[0].second].x,myEnemy03[listMyEnemy03[0].second].y)<=1280&&my_mana>=20){
                int oPbase_x=17630-base_x;
                int oPbase_y=9000-base_y;
                float slope_of_Enemy=((float)oPbase_y-myEnemy03[listMyEnemy03[0].second].y)/((float)oPbase_x-myEnemy03[listMyEnemy03[0].second].x);
                int new_x=myHero[5].x-1000;
                float new_yD=(slope_of_Enemy*(new_x-myHero[5].x))+myHero[5].y;
                int new_y=round(new_yD);
                cout<<"SPELL WIND "<<new_x<<" "<<new_y<<" #3"<<endl;
                my_mana-=10;
            }else{
                cout<<"MOVE "<<myEnemy03[listMyEnemy03[0].second].x<<" "<<myEnemy03[listMyEnemy03[0].second].y<<" #3"<<endl;
            }
        }else if(nEnemy3.size()>0&&my_mana>=30) //there is myEnemy0 and distance of 2200 of hero 0
        {
            if(distance(myHero[5].x,myHero[5].y,nEnemy3[listNEnemy3[0].second].x,nEnemy3[listNEnemy3[0].second].y)<=1280&&my_mana>=20){
                int oPbase_x=17630-base_x;
                int oPbase_y=9000-base_y;
                float slope_of_Enemy=((float)oPbase_y-nEnemy3[listNEnemy3[0].second].y)/((float)oPbase_x-nEnemy3[listNEnemy3[0].second].x);
                int new_x=myHero[5].x-1000;
                float new_yD=(slope_of_Enemy*(new_x-myHero[5].x))+myHero[5].y;
                int new_y=round(new_yD);
                cout<<"SPELL WIND "<<new_x<<" "<<new_y<<" #3"<<endl;
                my_mana-=10;
            }else{
                cout<<"MOVE "<<nEnemy3[listNEnemy3[0].second].x<<" "<<nEnemy3[listNEnemy3[0].second].y<<" #3"<<endl;
            }
        }else{
            cout<<"MOVE "<<A.x<<" "<<A.y<<" #3"<<endl;
        }
    }
}

int main()
{
    cin >> base_x >> base_y; cin.ignore();
    cin >> heroes_per_player; cin.ignore();
    if(base_x==0){
        A.x=12630;
        A.y=8000;
    }else{
        A.x=5000;
        A.y=1000;
    }

    // game loop
    while (1) {

        mEnemy.clear();
        opHero.clear();
        myHero.clear();
        nEnemy.clear();
        nEnemy1.clear();
        nEnemy2.clear();
        nEnemy3.clear();
        myEnemy0.clear();
        myEnemy01.clear();
        myEnemy02.clear();
        myEnemy03.clear();
        myEnemy1.clear();
        myEnemy11.clear();
        myEnemy12.clear();
        opEnemy0.clear();
        opEnemy1.clear();
        opEnemy02.clear();
        opEnemy12.clear();
        opEnemy03.clear();
        opEnemy13.clear();
        listNEnemy.clear();//sort by life dec
        listNEnemy1.clear();//sort by life dec
        listNEnemy2.clear();//sort by life dec
        listNEnemy3.clear();//sort by life dec
        listMyEnemy0.clear();//sort by distance dec
        listMyEnemy01.clear();//sort by distance dec
        listMyEnemy02.clear();//sort by distance dec
        listMyEnemy03.clear();//sort by distance dec
        listMyEnemy1.clear();//sort by distance dec
        listMyEnemy11.clear();//sort by distance dec
        listMyEnemy12.clear();//sort by distance dec
        listOpEnemy0.clear();//sort by distance dec
        listOpEnemy1.clear();//sort by distance dec
        listOpEnemy02.clear();//sort by distance dec
        listOpEnemy12.clear();//sort by distance dec
        listOpEnemy03.clear();//sort by distance dec
        listOpEnemy13.clear();//sort by distance dec
        listOpHero.clear();//sort by distance dec
        listOpHero3.clear();//sort by distance dec




        cin >> my_health >> my_mana>>op_health>>op_mana; cin.ignore();
        cin >> entity_count; cin.ignore();
        for (int i = 0; i < entity_count; i++) {
            cin >> id >> type >> x >> y >> shield_life >> is_controlled >> health >> vx >> vy >> near_base >> threat_for; cin.ignore();


            if(threat_for==1) numberIn+=near_base;
            entity curr;
            curr.x=x;
            curr.y=y;
            curr.id=id; // Unique identifier
            curr.type=type; // 0=monster, 1=your hero, 2=opponent hero
            curr.x=x; // Position of this entity
            curr.y=y;
            curr.shield_life=shield_life; // Ignore for this league; Count down until shield spell fades
            curr.is_controlled=is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell
            curr.health=health; // Remaining health of this monster
            curr.vx=vx; // Trajectory of this monster
            curr.vy=vy;
            curr.near_base=near_base; // 0=monster with no target yet, 1=monster targeting a base
            curr.threat_for=threat_for;
            mEnemy[id]=curr;
            clog <<"Entity "<< id <<" "<< type <<" "<< x <<" "<< y <<" "<< shield_life <<" "<< is_controlled <<" "<< health <<" "<< vx <<" "<< vy <<" "<< near_base <<" "<< threat_for<<endl;
            if(type==0){

                if(threat_for==0){

                    if(base_x==0){
                            if(distance(curr.x,curr.y,myHero[0].x,myHero[0].y)<=2200){
                                nEnemy1[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[0].x,myHero[0].y,0);
                                temp.second=id;
                                listNEnemy1.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[1].x,myHero[1].y)<=2200){
                                nEnemy2[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[1].x,myHero[1].y,0);
                                temp.second=id;
                                listNEnemy2.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[2].x,myHero[2].y)<=2200){
                                nEnemy3[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[2].x,myHero[2].y,0);
                                temp.second=id;
                                listNEnemy3.push_back(temp);
                            }
                        }else{
                            if(distance(curr.x,curr.y,myHero[3].x,myHero[3].y)<=2200){
                                nEnemy1[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[3].x,myHero[3].y,0);
                                temp.second=id;
                                listNEnemy1.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[4].x,myHero[4].y)<=2200){
                                nEnemy2[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[4].x,myHero[4].y,0);
                                temp.second=id;
                                listNEnemy2.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[5].x,myHero[5].y)<=2200){
                                nEnemy3[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[5].x,myHero[5].y,0);
                                temp.second=id;
                                listNEnemy3.push_back(temp);
                            }
                        }


                    nEnemy[id]=curr;
                    pair<int,int> temp;
                    temp.first=health;
                    temp.second=id;
                    listNEnemy.push_back(temp);
                }else if(threat_for==1){
                    if(near_base){
                        if(base_x==0){
                            if(distance(curr.x,curr.y,myHero[0].x,myHero[0].y)<=2200){
                                myEnemy11[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[0].x,myHero[0].y,0);
                                temp.second=id;
                                listMyEnemy11.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[1].x,myHero[1].y)<=2200){
                                myEnemy12[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[1].x,myHero[1].y,0);
                                temp.second=id;
                                listMyEnemy12.push_back(temp);
                            }
                        }else{
                            if(distance(curr.x,curr.y,myHero[3].x,myHero[3].y)<=2200){
                                myEnemy11[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[3].x,myHero[3].y,0);
                                temp.second=id;
                                listMyEnemy11.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[4].x,myHero[4].y)<=2200){
                                myEnemy12[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[4].x,myHero[4].y,0);
                                temp.second=id;
                                listMyEnemy12.push_back(temp);
                            }
                        }



                        myEnemy1[id]=curr;
                        pair<double,int> temp;
                        temp.first=threatLvl(x,y,base_x,base_y,near_base);
                        temp.second=id;
                        listMyEnemy1.push_back(temp);
                    }else{
                        if(base_x==0){
                            if(distance(curr.x,curr.y,myHero[0].x,myHero[0].y)<=2200){
                                myEnemy01[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[0].x,myHero[0].y,0);
                                temp.second=id;
                                listMyEnemy01.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[1].x,myHero[1].y)<=2200){
                                myEnemy02[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[1].x,myHero[1].y,0);
                                temp.second=id;
                                listMyEnemy02.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[2].x,myHero[2].y)<=2200){
                                myEnemy03[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[2].x,myHero[2].y,0);
                                temp.second=id;
                                listMyEnemy03.push_back(temp);
                            }
                        }else{
                            if(distance(curr.x,curr.y,myHero[3].x,myHero[3].y)<=2200){
                                myEnemy01[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[3].x,myHero[3].y,0);
                                temp.second=id;
                                listMyEnemy01.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[4].x,myHero[4].y)<=2200){
                                myEnemy02[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[4].x,myHero[4].y,0);
                                temp.second=id;
                                listMyEnemy02.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[5].x,myHero[5].y)<=2200){
                                myEnemy03[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[5].x,myHero[5].y,0);
                                temp.second=id;
                                listMyEnemy03.push_back(temp);
                            }
                        }
                        if(distance(curr.x,curr.y,base_x,base_y)<=10000){
                            myEnemy0[id]=curr;
                            pair<double,int> temp;
                            temp.first=threatLvl(x,y,base_x,base_y,near_base);
                            temp.second=id;
                            listMyEnemy0.push_back(temp);
                        }

                    }
                }else if(threat_for==2){
                    if(near_base){
                        if(base_x==0){
                            if(distance(curr.x,curr.y,myHero[1].x,myHero[1].y)<=2200){
                                opEnemy12[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvlEnemy(x,y,base_x,base_y,near_base);
                                temp.second=id;
                                listOpEnemy12.push_back(temp);

                            }
                            if(distance(curr.x,curr.y,myHero[2].x,myHero[2].y)<=2200){
                                opEnemy13[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvlEnemy(x,y,base_x,base_y,near_base);
                                temp.second=id;
                                listOpEnemy13.push_back(temp);
                            }
                        }else{
                            if(distance(curr.x,curr.y,myHero[4].x,myHero[4].y)<=2200){
                                opEnemy12[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvlEnemy(x,y,base_x,base_y,near_base);
                                temp.second=id;
                                listOpEnemy12.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[5].x,myHero[5].y)<=2200){
                                opEnemy13[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvlEnemy(x,y,base_x,base_y,near_base);
                                temp.second=id;
                                listOpEnemy13.push_back(temp);
                            }
                        }

                        opEnemy1[id]=curr;
                        pair<double,int> temp;
                        temp.first=threatLvlEnemy(x,y,base_x,base_y,near_base);
                        temp.second=id;
                        listOpEnemy1.push_back(temp);
                    }else{
                        if(base_x==0){
                            if(distance(curr.x,curr.y,myHero[1].x,myHero[1].y)<=2200){
                                opEnemy02[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[1].x,myHero[1].y,0);
                                temp.second=id;
                                listOpEnemy02.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[2].x,myHero[2].y)<=2200){
                                opEnemy03[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[2].x,myHero[2].y,0);
                                temp.second=id;
                                listOpEnemy03.push_back(temp);
                            }
                        }else{
                            if(distance(curr.x,curr.y,myHero[4].x,myHero[4].y)<=2200){
                                opEnemy02[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[4].x,myHero[4].y,0);
                                temp.second=id;
                                listOpEnemy02.push_back(temp);
                            }
                            if(distance(curr.x,curr.y,myHero[5].x,myHero[5].y)<=2200){
                                opEnemy03[id]=curr;
                                pair<double,int> temp;
                                temp.first=threatLvl(x,y,myHero[5].x,myHero[5].y,0);
                                temp.second=id;
                                listOpEnemy03.push_back(temp);
                            }
                        }
                        opEnemy0[id]=curr;
                        pair<double,int> temp;
                        temp.first=threatLvlEnemy(x,y,base_x,base_y,near_base);
                        temp.second=id;
                        listOpEnemy0.push_back(temp);
                    }
                }


            }else if(type==1){
                clog<<"hero id "<<id<<endl;
                myHero[id]=curr;
            }
            else if(type==2){
                if(base_x==0){
                    if(distance(myHero[2].x,myHero[2].y,x,y)<=2200){
                        opHero3[id]=curr;
                        pair<double,int> temp;
                        temp.first=threatLvl(x,y,base_x,base_y,0);
                        temp.second=id;
                        listOpHero3.push_back(temp);
                    }

                }else{
                    if(distance(myHero[5].x,myHero[5].y,x,y)<=2200){
                        opHero3[id]=curr;
                        pair<double,int> temp;
                        temp.first=threatLvl(x,y,base_x,base_y,0);
                        temp.second=id;
                        listOpHero3.push_back(temp);
                    }
                }
                opHero[id]=curr;
                pair<double,int> temp;
                temp.first=threatLvl(x,y,base_x,base_y,0);
                temp.second=id;
                listOpHero.push_back(temp);
            }
        }
        sort(listNEnemy.rbegin(),listNEnemy.rend());
        sort(listMyEnemy0.rbegin(),listMyEnemy0.rend());
        sort(listMyEnemy01.rbegin(),listMyEnemy01.rend());
        sort(listMyEnemy02.rbegin(),listMyEnemy02.rend());
        sort(listMyEnemy03.rbegin(),listMyEnemy03.rend());
        sort(listMyEnemy1.rbegin(),listMyEnemy1.rend());
        sort(listOpEnemy0.rbegin(),listOpEnemy0.rend());
        sort(listOpEnemy1.rbegin(),listOpEnemy1.rend());
        sort(listOpHero.rbegin(),listOpHero.rend());
        /*hero1();
        hero2();*/
        defenceMovment();
        hero3();
        prevOpHealth=op_health;
    }
}
