#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

//check a number is a prime number or not
bool Prime(int MaxHP)
{
	if (MaxHP < 2)
		return 0;
	for (int i = 2; i <= MaxHP/2; i++) {
		if (MaxHP%i == 0)
			return 0;
	}
	return 1;
}

// check two number are friendly number or not
bool friendly(int a, int b)
{
  int Sum1 = 1;
  int Sum2 = 1;
  for (int i = 2; i < a; i++){
    if (a%i == 0) Sum1 += Sum1;
  }
  for (int i = 2; i < b; i++){
    if (b%i == 0) Sum2 += Sum2;
  }
  float A = static_cast<float>(Sum1)/a;
  float B = static_cast<float>(Sum2)/b;
  if (A == B) return 1;
  else return 0;
}

//Check the knight who is Dragon knight
bool Dragon(int HP)
{
	for (int a = HP/2; a > 0; a--) {
		for (int b = 1; b < a; b++) {
			if ( HP == 2 * a*(a + b)) 
				return true;
				break;
			}
		}
	return false;
}

//sort an array
void sort(int *arr){
    int temp;
    if (arr[0] > arr[1]){
      temp = arr[1];
      arr[1] = arr[0];
      arr[0] = temp;
    }
    temp = arr[2];
    if (arr[1] > temp) {
      arr[2] = arr[1];
      if (arr[0] > temp){
        arr[1] = arr[0];
        arr[0] = temp;
      }
      else  arr[1] = temp;
    }
}

// Fight with MadBear, Amazon MoonBringer, Elf, Saxon, Troll here
void Fight(knight& theKnight, report* pReturn, int levelO, int sword, float baseDamage, bool poison,int Odin, int Mythril, int figure)
{
  int damage = (baseDamage * levelO * 10); 
	if (poison == true) theKnight.HP = theKnight.HP - damage;
  if (theKnight.level < levelO) {
    pReturn->nLose+=1;
    if(!Mythril)  theKnight.HP = theKnight.HP - damage;
  }
  if (theKnight.level >= levelO || sword%2 == 1 || Odin == 1 || figure > 80){ 
    theKnight.gil += 100 * baseDamage;
    pReturn->nWin+=1;
  }
}

//Fight with Ghost Tornbery here
int Ghost(knight& theKnight, report* pReturn, int levelO, int sword, bool& poison, int Odin, int figure){
  if (theKnight.level < levelO) {
    poison = true;
    pReturn->nLose+=1;
  }
  if (theKnight.level >= levelO || sword%2 == 1 || Odin == 1 || figure == 99 || figure == 88){ 
    theKnight.level += 1;
    pReturn->nWin+=1;
  }
  if (figure == 101) poison = false;
	return 0;
}

// Play card with Queen of Cards
void Queen(knight& theKnight, report* pReturn, int levelO,int sword , int Odin, bool Hakama, int figure){
  if (theKnight.level < levelO) {
    pReturn->nLose+=1;
    if (Hakama == false && figure != 77) theKnight.gil /= 2;
  }
  if (theKnight.level >= levelO || sword %2 == 1 || Odin == 1 || figure == 99 || figure == 88){ 
    theKnight.gil *= 2;
    pReturn->nWin+=1;
  }
}

// Fight with Hades here
int Hades(knight& theKnight, report* pReturn, int levelO, int sword , bool& Mythril, bool TrueLove, int& Odin, int figure)
{
  if (theKnight.level < levelO){
    pReturn->nLose+=1;
    if (!Mythril) theKnight.HP = 0;
  }
  if (theKnight.level >= levelO || TrueLove == true || sword %2 == 1){ 
    Mythril = true;
    pReturn->nWin+=1;
  }
  if (Odin == 1 && figure != 12)
    Odin = -1;
	return 0;
}

// Trade with Funny Merchant Nina De Rings here
int Merchant(knight& theKnight, int MaxHP, bool LionHeart, bool& poison, int & countSw, bool Hakama, int figure)
{ 
  if (!friendly(theKnight.HP, theKnight.gil))
  {
    if (theKnight.gil < 50) return 1;
    else{
      if (figure == 101 || figure == 77 || Hakama == true){
        theKnight.HP = MaxHP;
        poison = false;
        if (figure == 77) theKnight.gil += 50;
      }
      else
      {
        if(poison){
          theKnight.gil -= 50;
          poison = false;
        }
        while (theKnight.gil != 0 && theKnight.HP != MaxHP){
          theKnight.HP++;
          theKnight.gil--;
        if (theKnight.gil == 0 || theKnight.HP == MaxHP) break;
       } 
      }
    }
  }
  else 
  {
    poison = false;
    theKnight.HP = MaxHP;
    LionHeart = true;
    if (figure != 101) countSw = 1;
  }
  return 0;
}

// Fight with Omega here
void Omega(knight& theKnight, report* pReturn, int MaxHP, int sword, bool& OmegaWin, int figure){
  if (theKnight.level == 10 && sword == 10 || figure == 12 && sword%2 == 1){
    OmegaWin = true;
    theKnight.gil = 999;
    MaxHP += 10*(10 - theKnight.level);
    theKnight.level = 10;
  }
  else theKnight.HP = 0;
}

// Fight with Ultimecia here
void Ulti(knight& theKnight, report* pReturn, int sword, bool poison, bool& Win, int figure, int Mythril){ 
  if (poison) theKnight.HP /=3;
  if (sword != 0){
    Win = true;        
  }
  else{
    pReturn->nLose++;
    if (figure != 77 && Mythril != 1) theKnight.HP /=3;
    if (theKnight.HP < 3) theKnight.HP = 1;
    }
}

// Check special figure
void Figure(int& figure, int MaxHP, bool& Lance, bool& Shield, bool& Hairpiece)
{
  if (MaxHP == 999) figure = 99; //ARTHUR
  else if (Dragon(MaxHP)) figure = 12; //Dragon Knight
  else if (Prime(MaxHP)) {
    figure = 101; // Paladin
    Shield = 1;
  }
  else if (MaxHP == 888) {
    figure = 88; //LANCELOT 
    Lance = 1;
    } 
  else if (MaxHP == 777) {
    figure = 77; //GUINEVERE
    Hairpiece = true;
    }
  
  else figure = 0;
}

// Check the Eternal_Love is exist or not
bool Eternal_Love(bool Excalibur, bool Lance, bool Hairpiece, int figure){
  if (figure = 77 && Lance) return true;
  if (figure != 77 && Hairpiece){
      if (figure == 88 || figure == 99 || Lance && !Excalibur) return true;
  }
  return false;
}

report*  walkthrough(knight& theKnight, castle arrCastle[], int nCastle, int mode, int nPetal)
{
  report* pReturn = new report;
  int bFlag;
  //fighting for the existence of mankind here

  bool Win = false;
  bool poison = false;
  bool TrueLove = false;
  bool OmegaWin = false;
  bool Hakama = false;
  bool Shield = false;
  bool LionHeart = false;
  bool Lance = false;
  bool Hairpiece = false;
  bool Excalibur = false;
  bool Mythril = false;
  int Odin = 0;
  int number = 0;
  int MaxHP = theKnight.HP;
  pReturn->nWin = 0;
  pReturn->nLose = 0;
  int levelO, count, countSw, countOdin, figure, sword, arr[3];
  float baseDamage;

  Figure(figure, MaxHP, Lance, Shield, Hairpiece); 
  if (mode == 1){
    for (int i = 0; i < 3; ++i)
      arr[i] = ::hash(95 + i);
    sort(arr);
  }
  while (!Win)
  {
    for (int i = 0; i < nCastle; i++)
    {
    castle Walk = arrCastle[i];
    for (int j = 0; j < Walk.nEvent; j++)
    {
      int b = (j+1) %10;
      levelO = (j+1)>6? (b > 5 ? b : 5) : b;

      sword = Excalibur == true ? (LionHeart == false ?  10 : 19) : (LionHeart == true ? 9 : 0);
      switch (Walk.arrEvent[j])
      {
        case 1: //MADBEAR
          baseDamage = 1;
          Fight(theKnight, pReturn, levelO, sword, baseDamage, poison, Odin, Mythril, figure);
          break;

        case 2: //MOONBRINGER
          baseDamage = 1.5;
          Fight(theKnight, pReturn, levelO, sword, baseDamage, poison, Odin, Mythril, figure);
          if (figure == 77) theKnight.HP = theKnight.HP + baseDamage * 10 * levelO;
          break;

        case 3: //LORDLUPIN
          baseDamage = 4.5;
          Fight(theKnight, pReturn, levelO, sword, baseDamage, poison, Odin, Mythril, figure);
          break;

        case 4: //ELF
          baseDamage = 6.5;
          Fight(theKnight, pReturn, levelO, sword, baseDamage, poison, Odin, Mythril, figure);
          break;

        case 5: //TROLL
          baseDamage = 8.5;
          Fight(theKnight, pReturn, levelO, sword, baseDamage, poison, Odin, Mythril, figure);
          break;

        case 6: //GHOST TORNBERY
          Ghost(theKnight, pReturn, levelO, sword, poison, Odin, figure);
          if (poison) count = j;
          break;

        case 7: //Queen of Cards
          Queen(theKnight, pReturn,levelO, sword, Odin, Hakama, figure);
          break;

        case 8: // funny merchant NINA DE RINGS,
          Merchant(theKnight, MaxHP, LionHeart, poison, countSw, Hakama, figure);
          break;

        case 9: //DURIAN garden
          poison = false;
          theKnight.HP = MaxHP;
          nPetal+=5;
          if (Hakama == true) nPetal = 99;
          break;

        case 10: //Antidote
          theKnight.antidote+=1;
          break;

        case 11: //ODIN phế vật
          if (Odin == 0){
            Odin = 1;
            countOdin = j;
          }
          break;

        case 12: //MERLIN the witcher
          poison = false;
          theKnight.level += 1;
          MaxHP += 100;
          theKnight.HP = MaxHP;
          break;

        case 13: // OMEGA WEAPON monster
          if (OmegaWin == true) break;
          else Omega(theKnight, pReturn, MaxHP, sword, OmegaWin, figure);
          break;

        case 14:  //Hades
          if (Eternal_Love(sword, Lance, Hairpiece, figure)) TrueLove == true;          
          Hades(theKnight, pReturn, levelO, sword, Mythril, TrueLove, Odin, figure);
          break;

        case 15: //  Scarlet Hakama
          Hakama = true;
          break;

        case 16: // LockedDoor
          if (b < theKnight.level || figure == 99 || figure == 88 || figure == 12) break;
          else j = Walk.nEvent - 1;            
          break;

        case 95: // PALADIN'S Shield
          if (mode == 0) Shield = true;
          if (mode == 1){
            if (::hash(95) == arr[2]){
              if (Lance && Hairpiece) Shield = true;
            }
            else if (::hash(95) == arr[1]){
              if (::hash(97) == arr[0]){
                if (Hairpiece) Shield = true;
              }
              else 
                if (Lance) Shield = true;
            } 
            else Shield = true;
          }
          break;

        case 96: // LANCELOT'S Lance
          if (mode == 0) Lance = true;
          if (mode == 1) {
            if (::hash(96) == arr[2]){
              if (Shield && Hairpiece) Lance= true;
            }
            else if (::hash(96) == arr[1]){
              if (::hash(97) == arr[0]){
                if (Hairpiece) Lance = true;
              }
              else 
                if (Shield) Lance = true;
            } 
            else Lance = true;
          }
          break;

        case 97: // GUINEVERE'S Hairpiece
          if (mode == 0) Hairpiece = true;
          if (mode == 1) {
            if (::hash(97) == arr[2]){
              if (Shield && Lance) Hairpiece = true;
            }
            else if (::hash(97) == arr[1]){
              if (::hash(96) == arr[0]){
                if (Shield) Hairpiece = true;
              }
              else 
                if (Lance) Hairpiece = true;
            } 
            else Hairpiece = true;
          }
          break;

        case 98: //EXCALIBUR
          if ((Shield == 1 && Hairpiece == 1 && Lance == 1) || figure == 99) Excalibur = true;
          break;

        case 99: // Ultimecia
          Ulti( theKnight, pReturn, sword, poison, Win, figure, Mythril);
          break;

      }
      nPetal--;
      if (nPetal < 0) nPetal = 0;
      if (Win){
        pReturn->nPetal = nPetal;
        pReturn->nWin++;
        return pReturn;
      }
      if (countSw == 1){
        countSw++;
        if(countSw == 5){
          LionHeart = false;
          countSw = 0;
        }
      }
      if (poison == true){
        if (theKnight.antidote >= 1){
          theKnight.antidote--;
          poison = false;
        }
        if (count == j - 4) poison = false;
      }
      if (Odin == 1){
        if (countOdin == j - 4){
          countOdin = 0;
          Odin = 0;
        }
      }
      if (theKnight.gil > 999) theKnight.gil = 999;
      if (theKnight.antidote > 99)  theKnight.antidote = 99;
      if (MaxHP > 999) MaxHP = 999;
      if (nPetal > 99) nPetal = 99;
      
      if (figure != 99 && nPetal == 0) {    
        pReturn = NULL;
        return pReturn;
      }
      if (theKnight.HP <= 0)  callPhoenix(theKnight, MaxHP);
    }
    theKnight.level++;
    if (theKnight.level > 10) theKnight.level = 10;
    MaxHP+=100;
    }
  }
  
  // suAess or failure?	
  pReturn = (bFlag)? new report : NULL;
  return pReturn;
}