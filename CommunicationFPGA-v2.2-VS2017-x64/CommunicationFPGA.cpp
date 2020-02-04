/*
*   Ce programme Ã©crit et lit des donnÃ©es sur la carte FPGA afin de faire
*   quelques tests fonctionnels. Il utilise la classe CommunicationFPGA
*   qui est distribuÃ©e dans le cadre de S2.
*
*   Il est assumÃ© que la communication est faite avec la carte FPGA qui
*   a Ã©tÃ© prÃ©alablement configurÃ©e correctement.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 fÃ©vr. 2018) $
*   $Revision: 108 $
*   $Id: TestCommunicationFPGA.cpp 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2018 DÃ©partement de gÃ©nie Ã©lectrique et gÃ©nie informatique
*                  UniversitÃ© de Sherbrooke  
*/

#include <iostream>
#include "CommunicationFPGA.h"

using namespace std;

enum Registre {SW=8, BTN=9, LD=10, AN0=11, AN1=12, AN2=13, AN3=14};

int main(int argc, char * argv[]) {
	CommunicationFPGA fpga;
	int val;

	if(!fpga.estOk())
	{
		cout << fpga.messageErreur() << endl;
		return 1;
	}

	if(!fpga.lireRegistre(SW, val))
	{
		cout << fpga.messageErreur() << endl;
		return 1;
	}
	
	cout << "SW: " << hex << val << endl;

	if(!fpga.lireRegistre(BTN, val))
	{
		cout << fpga.messageErreur() << endl;
		return 1;
	}

	cout << "BTN: "  << hex << val  << endl;

	val = 0xac;
	if(!fpga.ecrireRegistre(LD, val))
	{
		cout << fpga.messageErreur() << endl;
		return 1;
	}

    val = 0xa;
	if(!fpga.ecrireRegistre(AN3, val))
	{
		cout << fpga.messageErreur() << endl;
		return 1;
	}

	val++;
	if(!fpga.ecrireRegistre(AN2, val))
	{
		cout << fpga.messageErreur() << endl;
		return 1;
	}

	val++;
	if(!fpga.ecrireRegistre(AN1, val))
	{
		cout << fpga.messageErreur() << endl;
		return 1;
	}

	val++;

	if(!fpga.ecrireRegistre(AN0, val))
	{
		cout << fpga.messageErreur() << endl;
		return 1;
	}

	return 0;
}
