#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include <list>
#pragma warning(disable:4996)

using namespace std;

//class declarations
struct Helper;
struct RubikCube;
struct Phase;
struct Node;
struct Tree;

//class declarations
struct Helper {

	static void skipLine(ifstream& fin, int totalLines)//skip 'n' lines
	{
		int bufferSize = 120;
		char* buffer = new char[bufferSize];
		for (int i = 0; i < totalLines; i++)
			fin.getline(buffer, bufferSize);
		delete[] buffer;
	}
};

struct Phase {
	//
	int* entries;

	Phase() {
		entries = new int[9];//left to right, top to bottom

		for (int i = 0; i < 9; i++)
			this->entries[i] = 0;
	}
	~Phase() {
		if (entries) {
			delete[] entries;
			entries = nullptr;
		}
	}
};
struct RubikCube {
	Phase* phases;
	char* transitionMessage;

	RubikCube() {
		transitionMessage = new char[3];
		phases = new Phase[6]; //front-0, back-1, up-2, down-3, left-4, right-5
	}

	~RubikCube() {
		if (phases) {
			delete[] phases;
			phases = nullptr;
		}
		if (this->transitionMessage) {
			delete[] this->transitionMessage;
		}
	}

	RubikCube& operator=(RubikCube& c1) {
		if (this != &c1) {
			//assignment operator write code here
			int phaseAddress, entryAddress = 0;
			for (int i = 0; i < 54; i++) {
				phaseAddress = i / 9;
				entryAddress = i % 9;
				this->phases[phaseAddress].entries[entryAddress] = c1.phases[phaseAddress].entries[entryAddress];
			}
		}
		return *this;
	}

	bool operator==(RubikCube& c1) {
		if (this != &c1) {
			int phaseAddress, entryAddress = 0;
			for (int i = 0; i < 54; i++) {
				phaseAddress = i / 9;
				entryAddress = i % 9;
				if (this->phases[phaseAddress].entries[entryAddress] != c1.phases[phaseAddress].entries[entryAddress]) {
					return false;
				}
			}
		}
		return true;
	}

	int getHeuristicValue(RubikCube* goalCubePtr) { //needs to be refined
		int phaseAddress, entryAddress = 0, count = 0;
		int phaseAddressGoal, entryAddressGoal = 0;

		for (int i = 0; i < 54; i++) {
			phaseAddress = i / 9;
			entryAddress = i % 9;
			if (this->phases[phaseAddress].entries[entryAddress] != goalCubePtr->phases[phaseAddress].entries[entryAddress]) {
				for (int j = 0; i < 54; j++) {
					phaseAddressGoal = i / 9;
					entryAddressGoal = i % 9;
					if (this->phases[phaseAddress].entries[entryAddress] == goalCubePtr->phases[phaseAddressGoal].entries[entryAddressGoal]) {
						//calculating Z-axis distance
						if ((phaseAddress - phaseAddressGoal == 1) || (phaseAddress - phaseAddressGoal == -1)) {
							count += 2;//means phases are on opposite side of cubes and minimum distance required is 2 to move to that phase
						}
						else {
							count += 1; //else in only one move element of this phase can move to goal phase
						}
						//now calculating X-axis and Y-Axis distance
						if ((entryAddress == 0 && entryAddressGoal == 1) || (entryAddress == 1 && entryAddressGoal == 0)) {
							count += 1;
						}
						else if ((entryAddress == 0 && entryAddressGoal == 2) || (entryAddress == 2 && entryAddressGoal == 0)) {
							count += 2;
						}
						else if ((entryAddress == 0 && entryAddressGoal == 3) || (entryAddress == 3 && entryAddressGoal == 0)) {
							count += 1;
						}
						else if ((entryAddress == 0 && entryAddressGoal == 4) || (entryAddress == 4 && entryAddressGoal == 0)) {
							count += 2;
						}
						else if ((entryAddress == 0 && entryAddressGoal == 5) || (entryAddress == 5 && entryAddressGoal == 0)) {
							count += 3;
						}
						else if ((entryAddress == 0 && entryAddressGoal == 6) || (entryAddress == 6 && entryAddressGoal == 0)) {
							count += 2;
						}
						else if ((entryAddress == 0 && entryAddressGoal == 7) || (entryAddress == 7 && entryAddressGoal == 0)) {
							count += 3;
						}
						else if ((entryAddress == 0 && entryAddressGoal == 8) || (entryAddress == 8 && entryAddressGoal == 0)) {
							count += 4;
						}
						else if ((entryAddress == 1 && entryAddressGoal == 2) || (entryAddress == 2 && entryAddressGoal == 1)) {
							count += 1;
						}
						else if ((entryAddress == 1 && entryAddressGoal == 3) || (entryAddress == 3 && entryAddressGoal == 1)) {
							count += 2;
						}
						else if ((entryAddress == 1 && entryAddressGoal == 4) || (entryAddress == 4 && entryAddressGoal == 1)) {
							count += 1;
						}
						else if ((entryAddress == 1 && entryAddressGoal == 5) || (entryAddress == 5 && entryAddressGoal == 1)) {
							count += 2;
						}
						else if ((entryAddress == 1 && entryAddressGoal == 6) || (entryAddress == 6 && entryAddressGoal == 1)) {
							count += 3;
						}
						else if ((entryAddress == 1 && entryAddressGoal == 7) || (entryAddress == 7 && entryAddressGoal == 1)) {
							count += 2;
						}
						else if ((entryAddress == 1 && entryAddressGoal == 8) || (entryAddress == 8 && entryAddressGoal == 1)) {
							count += 3;
						}
						else if ((entryAddress == 2 && entryAddressGoal == 3) || (entryAddress == 3 && entryAddressGoal == 2)) {
							count += 3;
						}
						else if ((entryAddress == 2 && entryAddressGoal == 4) || (entryAddress == 4 && entryAddressGoal == 2)) {
							count += 2;
						}
						else if ((entryAddress == 2 && entryAddressGoal == 5) || (entryAddress == 5 && entryAddressGoal == 2)) {
							count += 1;
						}
						else if ((entryAddress == 2 && entryAddressGoal == 6) || (entryAddress == 6 && entryAddressGoal == 2)) {
							count += 4;
						}
						else if ((entryAddress == 2 && entryAddressGoal == 7) || (entryAddress == 7 && entryAddressGoal == 2)) {
							count += 3;
						}
						else if ((entryAddress == 2 && entryAddressGoal == 8) || (entryAddress == 8 && entryAddressGoal == 2)) {
							count += 2;
						}
						else if ((entryAddress == 3 && entryAddressGoal == 4) || (entryAddress == 4 && entryAddressGoal == 3)) {
							count += 1;
						}
						else if ((entryAddress == 3 && entryAddressGoal == 5) || (entryAddress == 5 && entryAddressGoal == 3)) {
							count += 2;
						}
						else if ((entryAddress == 3 && entryAddressGoal == 6) || (entryAddress == 6 && entryAddressGoal == 3)) {
							count += 1;
						}
						else if ((entryAddress == 3 && entryAddressGoal == 7) || (entryAddress == 7 && entryAddressGoal == 3)) {
							count += 2;
						}
						else if ((entryAddress == 3 && entryAddressGoal == 8) || (entryAddress == 8 && entryAddressGoal == 3)) {
							count += 3;
						}
						else if ((entryAddress == 4 && entryAddressGoal == 5) || (entryAddress == 5 && entryAddressGoal == 4)) {
							count += 1;
						}
						else if ((entryAddress == 4 && entryAddressGoal == 6) || (entryAddress == 6 && entryAddressGoal == 4)) {
							count += 2;
						}
						else if ((entryAddress == 4 && entryAddressGoal == 7) || (entryAddress == 7 && entryAddressGoal == 4)) {
							count += 1;
						}
						else if ((entryAddress == 4 && entryAddressGoal == 8) || (entryAddress == 8 && entryAddressGoal == 4)) {
							count += 2;
						}
						else if ((entryAddress == 5 && entryAddressGoal == 6) || (entryAddress == 6 && entryAddressGoal == 5)) {
							count += 3;
						}
						else if ((entryAddress == 5 && entryAddressGoal == 7) || (entryAddress == 7 && entryAddressGoal == 5)) {
							count += 2;
						}
						else if ((entryAddress == 5 && entryAddressGoal == 8) || (entryAddress == 8 && entryAddressGoal == 5)) {
							count += 1;
						}
						else if ((entryAddress == 6 && entryAddressGoal == 7) || (entryAddress == 7 && entryAddressGoal == 6)) {
							count += 1;
						}
						else if ((entryAddress == 6 && entryAddressGoal == 8) || (entryAddress == 8 && entryAddressGoal == 6)) {
							count += 2;
						}
						else if ((entryAddress == 7 && entryAddressGoal == 8) || (entryAddress == 8 && entryAddressGoal == 7)) {
							count += 1;
						}

					}
				}
			}
		}

		return count;
	}

	void loadCurrentStateFromFile(ifstream& fin) { //file NOT closed here
		fin.open("testFile1.txt");

		int color1 = 0, color2 = 0, color3 = 0, color4 = 0, color5 = 0, color6 = 0;
		if (fin.is_open()) {

			Helper::skipLine(fin, 2);

			int bucket;
			int phaseNumber = 0;
			int entryInPhase = 0;
			for (int i = 0; i < 54; i++) {
				fin >> bucket;

				if (bucket == 1)
					color1++;
				else if (bucket == 2)
					color2++;
				else if (bucket == 3)
					color3++;
				else if (bucket == 4)
					color4++;
				else if (bucket == 5)
					color5++;
				else if (bucket == 6)
					color6++;
				else {
					cout << "ERROR! Color code does NOT match...\n";
					throw exception("Color Code Does Not Match...\n");
				}


				phaseNumber = i / 9;//starting from zero
				entryInPhase = i % 9;//starting from zero

				this->phases[phaseNumber].entries[entryInPhase] = bucket;
				//cout << this->phases[phaseNumber].entries[entryInPhase] << " ";

			}
			cout << "\n";
			if ((color1 > 9) || (color2 > 9) || (color3 > 9) || (color4 > 9) || (color5 > 9) || (color6 > 9)) {
				cout << "ERROR! Color code exceeds limit...\n";
				throw exception("ERROR! Color code exceeds limit...\n");
			}
		}
		else
		{
			cout << "ERROR in opening testFile.txt\n";
		}
	}

	void loadGoalStateFromFile(ifstream& fin) { //file closed here
		if (fin.is_open()) {

			Helper::skipLine(fin, 2);

			int bucket;
			int phaseNumber = 0;
			int entryInPhase = 0;
			int color1 = 0, color2 = 0, color3 = 0, color4 = 0, color5 = 0, color6 = 0;
			for (int i = 0; i < 54; i++) {
				fin >> bucket;
				if (bucket == 1)
					color1++;
				else if (bucket == 2)
					color2++;
				else if (bucket == 3)
					color3++;
				else if (bucket == 4)
					color4++;
				else if (bucket == 5)
					color5++;
				else if (bucket == 6)
					color6++;
				else {
					cout << "ERROR! Color code does NOT match...\n";
					throw exception("Color Code Does Not Match...\n");
				}

				phaseNumber = i / 9;//starting from zero
				entryInPhase = i % 9;//starting from zero

				this->phases[phaseNumber].entries[entryInPhase] = bucket;
				//cout << this->phases[phaseNumber].entries[entryInPhase] << " ";
			}
			cout << "\n";
			fin.close();
			if ((color1 > 9) || (color2 > 9) || (color3 > 9) || (color4 > 9) || (color5 > 9) || (color6 > 9)) {
				cout << "ERROR! Color code exceeds limit...\n";
				throw exception("ERROR! Color code exceeds limit...\n");
			}
		}
		else
		{
			cout << "ERROR in opening testFile.txt\n";
		}
	}

	void copyCube(RubikCube* c1, RubikCube* c2) {
		int phaseAddress, entryAddress = 0;
		for (int i = 0; i < 54; i++) {
			phaseAddress = i / 9;
			entryAddress = i % 9;
			c1->phases[phaseAddress].entries[entryAddress] = c2->phases[phaseAddress].entries[entryAddress];
		}
	}

	RubikCube* produceNextPossibleStates() {
		RubikCube* possibleStates = new RubikCube[12];

		for (int i = 0; i < 12; i++) { //copying current state in all states, then we will make changes to that copied states min: 12, max: 21 per transition
			copyCube(&possibleStates[i], this);
		}

		int i1, i2, i3;

		//column1-clockwise 12+8=20 changes
		i1 = i2 = i3 = 0;

		i1 = possibleStates[0].phases[0].entries[0]; //saving copy to swap
		i2 = possibleStates[0].phases[0].entries[3];
		i3 = possibleStates[0].phases[0].entries[6];

		//changes
		possibleStates[0].phases[0].entries[0] = possibleStates[0].phases[2].entries[0];
		possibleStates[0].phases[0].entries[3] = possibleStates[0].phases[2].entries[3];
		possibleStates[0].phases[0].entries[6] = possibleStates[0].phases[2].entries[6];

		possibleStates[0].phases[2].entries[0] = possibleStates[0].phases[1].entries[0];
		possibleStates[0].phases[2].entries[3] = possibleStates[0].phases[1].entries[3];
		possibleStates[0].phases[2].entries[6] = possibleStates[0].phases[1].entries[6];

		possibleStates[0].phases[1].entries[0] = possibleStates[0].phases[3].entries[0];
		possibleStates[0].phases[1].entries[3] = possibleStates[0].phases[3].entries[3];
		possibleStates[0].phases[1].entries[6] = possibleStates[0].phases[3].entries[6];

		possibleStates[0].phases[3].entries[0] = i1;
		possibleStates[0].phases[3].entries[3] = i2;
		possibleStates[0].phases[3].entries[6] = i3;


		i1 = possibleStates[0].phases[4].entries[0];
		possibleStates[0].phases[4].entries[0] = possibleStates[0].phases[4].entries[6];
		possibleStates[0].phases[4].entries[3] = possibleStates[0].phases[4].entries[7];
		possibleStates[0].phases[4].entries[6] = possibleStates[0].phases[4].entries[8];
		possibleStates[0].phases[4].entries[7] = possibleStates[0].phases[4].entries[5];

		possibleStates[0].phases[4].entries[8] = possibleStates[0].phases[4].entries[2];
		possibleStates[0].phases[4].entries[5] = possibleStates[0].phases[4].entries[1];
		possibleStates[0].phases[4].entries[2] = i1;
		possibleStates[0].phases[4].entries[1] = possibleStates[0].phases[4].entries[3];
		strcpy(possibleStates[0].transitionMessage, "L");

		//column1-anticlockwise	12+8=20 changes
		i1 = i2 = i3 = 0;
		i1 = possibleStates[1].phases[0].entries[0]; //saving copy to swap
		i2 = possibleStates[1].phases[0].entries[3];
		i3 = possibleStates[1].phases[0].entries[6];

		//changes
		possibleStates[1].phases[0].entries[0] = possibleStates[1].phases[3].entries[0];
		possibleStates[1].phases[0].entries[3] = possibleStates[1].phases[3].entries[3];
		possibleStates[1].phases[0].entries[6] = possibleStates[1].phases[3].entries[6];

		possibleStates[1].phases[3].entries[0] = possibleStates[1].phases[1].entries[0];
		possibleStates[1].phases[3].entries[3] = possibleStates[1].phases[1].entries[3];
		possibleStates[1].phases[3].entries[6] = possibleStates[1].phases[1].entries[6];

		possibleStates[1].phases[1].entries[0] = possibleStates[1].phases[2].entries[0];
		possibleStates[1].phases[1].entries[3] = possibleStates[1].phases[2].entries[3];
		possibleStates[1].phases[1].entries[6] = possibleStates[1].phases[2].entries[6];

		possibleStates[1].phases[2].entries[0] = i1;
		possibleStates[1].phases[2].entries[3] = i2;
		possibleStates[1].phases[2].entries[6] = i3;

		i1 = possibleStates[1].phases[4].entries[0];
		possibleStates[1].phases[4].entries[0] = possibleStates[1].phases[4].entries[2];
		possibleStates[1].phases[4].entries[3] = possibleStates[1].phases[4].entries[1];
		possibleStates[1].phases[4].entries[6] = i1;
		possibleStates[1].phases[4].entries[7] = possibleStates[1].phases[4].entries[3];

		possibleStates[1].phases[4].entries[8] = possibleStates[1].phases[4].entries[6];
		possibleStates[1].phases[4].entries[5] = possibleStates[1].phases[4].entries[7];
		possibleStates[1].phases[4].entries[2] = possibleStates[1].phases[4].entries[8];
		possibleStates[1].phases[4].entries[1] = possibleStates[1].phases[4].entries[5];

		strcpy(possibleStates[1].transitionMessage, "L-");

		//column3-clockwise 12+8=20 changes.......
		i1 = i2 = i3 = 0;

		i1 = possibleStates[2].phases[0].entries[2]; //saving copy to swap
		i2 = possibleStates[2].phases[0].entries[5];
		i3 = possibleStates[2].phases[0].entries[8];

		//changes
		possibleStates[2].phases[0].entries[2] = possibleStates[2].phases[3].entries[2];
		possibleStates[2].phases[0].entries[5] = possibleStates[2].phases[3].entries[5];
		possibleStates[2].phases[0].entries[8] = possibleStates[2].phases[3].entries[8];

		possibleStates[2].phases[3].entries[2] = possibleStates[2].phases[1].entries[2];
		possibleStates[2].phases[3].entries[5] = possibleStates[2].phases[1].entries[5];
		possibleStates[2].phases[3].entries[8] = possibleStates[2].phases[1].entries[8];

		possibleStates[2].phases[1].entries[2] = possibleStates[2].phases[2].entries[2];
		possibleStates[2].phases[1].entries[5] = possibleStates[2].phases[2].entries[5];
		possibleStates[2].phases[1].entries[8] = possibleStates[2].phases[2].entries[8];

		possibleStates[2].phases[2].entries[2] = i1;
		possibleStates[2].phases[2].entries[5] = i2;
		possibleStates[2].phases[2].entries[8] = i3;

		i1 = possibleStates[2].phases[5].entries[0];
		possibleStates[2].phases[5].entries[0] = possibleStates[2].phases[5].entries[6];
		possibleStates[2].phases[5].entries[3] = possibleStates[2].phases[5].entries[7];
		possibleStates[2].phases[5].entries[6] = possibleStates[2].phases[5].entries[8];
		possibleStates[2].phases[5].entries[7] = possibleStates[2].phases[5].entries[5];

		possibleStates[2].phases[5].entries[8] = possibleStates[2].phases[5].entries[2];
		possibleStates[2].phases[5].entries[5] = possibleStates[2].phases[5].entries[1];
		possibleStates[2].phases[5].entries[2] = i1;
		possibleStates[2].phases[5].entries[1] = possibleStates[2].phases[5].entries[3];
		strcpy(possibleStates[2].transitionMessage, "R");

		//column3-anticlockwise 12+8=20 changes
		i1 = i2 = i3 = 0;
		i1 = possibleStates[2].phases[0].entries[2]; //saving copy to swap
		i2 = possibleStates[2].phases[0].entries[5];
		i3 = possibleStates[2].phases[0].entries[8];

		//changes

		possibleStates[3].phases[0].entries[2] = possibleStates[3].phases[2].entries[2];
		possibleStates[3].phases[0].entries[5] = possibleStates[3].phases[2].entries[5];
		possibleStates[3].phases[0].entries[8] = possibleStates[3].phases[2].entries[8];

		possibleStates[3].phases[2].entries[2] = possibleStates[3].phases[1].entries[2];
		possibleStates[3].phases[2].entries[5] = possibleStates[3].phases[1].entries[5];
		possibleStates[3].phases[2].entries[8] = possibleStates[3].phases[1].entries[8];

		possibleStates[3].phases[1].entries[2] = possibleStates[3].phases[3].entries[2];
		possibleStates[3].phases[1].entries[5] = possibleStates[3].phases[3].entries[5];
		possibleStates[3].phases[1].entries[8] = possibleStates[3].phases[3].entries[8];

		possibleStates[3].phases[3].entries[2] = i1;
		possibleStates[3].phases[3].entries[5] = i2;
		possibleStates[3].phases[3].entries[8] = i3;

		i1 = possibleStates[3].phases[5].entries[0];
		possibleStates[3].phases[5].entries[0] = possibleStates[3].phases[5].entries[2];
		possibleStates[3].phases[5].entries[1] = possibleStates[3].phases[5].entries[5];
		possibleStates[3].phases[5].entries[2] = possibleStates[3].phases[5].entries[8];
		possibleStates[3].phases[5].entries[5] = possibleStates[3].phases[5].entries[7];

		possibleStates[3].phases[5].entries[8] = possibleStates[3].phases[5].entries[6];
		possibleStates[3].phases[5].entries[7] = possibleStates[3].phases[5].entries[3];
		possibleStates[3].phases[5].entries[6] = i1;
		possibleStates[3].phases[5].entries[3] = possibleStates[3].phases[5].entries[1];
		strcpy(possibleStates[0].transitionMessage, "R-");

		//row1-clockwise 12+8=20 changes
		i1 = i2 = i3 = 0;

		i1 = possibleStates[4].phases[0].entries[0]; //saving copy to swap
		i2 = possibleStates[4].phases[0].entries[1];
		i3 = possibleStates[4].phases[0].entries[2];

		//changes
		possibleStates[4].phases[0].entries[0] = possibleStates[4].phases[5].entries[0];
		possibleStates[4].phases[0].entries[1] = possibleStates[4].phases[5].entries[1];
		possibleStates[4].phases[0].entries[2] = possibleStates[4].phases[5].entries[2];

		possibleStates[4].phases[5].entries[0] = possibleStates[4].phases[1].entries[8];
		possibleStates[4].phases[5].entries[1] = possibleStates[4].phases[1].entries[7];
		possibleStates[4].phases[5].entries[2] = possibleStates[4].phases[1].entries[6];

		possibleStates[4].phases[1].entries[8] = possibleStates[4].phases[4].entries[0];
		possibleStates[4].phases[1].entries[7] = possibleStates[4].phases[4].entries[1];
		possibleStates[4].phases[1].entries[6] = possibleStates[4].phases[4].entries[2];

		possibleStates[4].phases[4].entries[0] = i1;
		possibleStates[4].phases[4].entries[1] = i2;
		possibleStates[4].phases[4].entries[2] = i3;

		i1 = possibleStates[4].phases[2].entries[0];
		possibleStates[4].phases[2].entries[0] = possibleStates[4].phases[2].entries[6];
		possibleStates[4].phases[2].entries[3] = possibleStates[4].phases[2].entries[7];
		possibleStates[4].phases[2].entries[6] = possibleStates[4].phases[2].entries[8];
		possibleStates[4].phases[2].entries[7] = possibleStates[4].phases[2].entries[5];

		possibleStates[4].phases[2].entries[8] = possibleStates[4].phases[2].entries[2];
		possibleStates[4].phases[2].entries[5] = possibleStates[4].phases[2].entries[1];
		possibleStates[4].phases[2].entries[2] = i1;
		possibleStates[4].phases[2].entries[1] = possibleStates[4].phases[2].entries[3];
		strcpy(possibleStates[0].transitionMessage, "U");
		//row1-anticlockwise 12+8=20 changes
		i1 = i2 = i3 = 0;

		i1 = possibleStates[5].phases[0].entries[0]; //saving copy to swap
		i2 = possibleStates[5].phases[0].entries[1];
		i3 = possibleStates[5].phases[0].entries[2];

		//changes
		possibleStates[5].phases[0].entries[0] = possibleStates[5].phases[4].entries[0];
		possibleStates[5].phases[0].entries[1] = possibleStates[5].phases[4].entries[1];
		possibleStates[5].phases[0].entries[2] = possibleStates[5].phases[4].entries[2];

		possibleStates[5].phases[4].entries[0] = possibleStates[5].phases[1].entries[8];
		possibleStates[5].phases[4].entries[1] = possibleStates[5].phases[1].entries[7];
		possibleStates[5].phases[4].entries[2] = possibleStates[5].phases[1].entries[6];

		possibleStates[5].phases[1].entries[8] = possibleStates[5].phases[5].entries[0];
		possibleStates[5].phases[1].entries[7] = possibleStates[5].phases[5].entries[1];
		possibleStates[5].phases[1].entries[6] = possibleStates[5].phases[5].entries[2];

		possibleStates[5].phases[5].entries[0] = i1;
		possibleStates[5].phases[5].entries[1] = i2;
		possibleStates[5].phases[5].entries[2] = i3;

		i1 = possibleStates[5].phases[2].entries[0];
		possibleStates[5].phases[2].entries[0] = possibleStates[5].phases[2].entries[2];
		possibleStates[5].phases[2].entries[3] = possibleStates[5].phases[2].entries[1];
		possibleStates[5].phases[2].entries[6] = i1;
		possibleStates[5].phases[2].entries[7] = possibleStates[5].phases[2].entries[3];

		possibleStates[5].phases[2].entries[8] = possibleStates[5].phases[2].entries[6];
		possibleStates[5].phases[2].entries[5] = possibleStates[5].phases[2].entries[7];
		possibleStates[5].phases[2].entries[2] = possibleStates[5].phases[2].entries[8];
		possibleStates[5].phases[2].entries[1] = possibleStates[5].phases[2].entries[5];
		strcpy(possibleStates[0].transitionMessage, "U-");


		//row3-clockwise 12+8=20 changes
		i1 = i2 = i3 = 0;
		i1 = possibleStates[6].phases[0].entries[6]; //saving copy to swap
		i2 = possibleStates[6].phases[0].entries[7];
		i3 = possibleStates[6].phases[0].entries[8];

		//changes
		possibleStates[6].phases[0].entries[6] = possibleStates[6].phases[4].entries[6];
		possibleStates[6].phases[0].entries[7] = possibleStates[6].phases[4].entries[7];
		possibleStates[6].phases[0].entries[8] = possibleStates[6].phases[4].entries[8];

		possibleStates[6].phases[4].entries[6] = possibleStates[6].phases[1].entries[2];
		possibleStates[6].phases[4].entries[7] = possibleStates[6].phases[1].entries[1];
		possibleStates[6].phases[4].entries[8] = possibleStates[6].phases[1].entries[0];

		possibleStates[6].phases[1].entries[2] = possibleStates[6].phases[5].entries[6];
		possibleStates[6].phases[1].entries[1] = possibleStates[6].phases[5].entries[7];
		possibleStates[6].phases[1].entries[0] = possibleStates[6].phases[5].entries[8];

		possibleStates[6].phases[5].entries[6] = i1;
		possibleStates[6].phases[5].entries[7] = i2;
		possibleStates[6].phases[5].entries[8] = i3;

		i1 = possibleStates[6].phases[3].entries[0];
		possibleStates[6].phases[3].entries[0] = possibleStates[6].phases[3].entries[6];
		possibleStates[6].phases[3].entries[1] = possibleStates[6].phases[3].entries[3];
		possibleStates[6].phases[3].entries[2] = i1;
		possibleStates[6].phases[3].entries[5] = possibleStates[6].phases[3].entries[1];

		possibleStates[6].phases[3].entries[8] = possibleStates[6].phases[3].entries[2];
		possibleStates[6].phases[3].entries[7] = possibleStates[6].phases[3].entries[5];
		possibleStates[6].phases[3].entries[6] = possibleStates[6].phases[3].entries[8];
		possibleStates[6].phases[3].entries[3] = possibleStates[6].phases[3].entries[7];
		strcpy(possibleStates[0].transitionMessage, "D");
		//row3-anticlockwise 12+8=20 changes
		i1 = i2 = i3 = 0;
		i1 = possibleStates[7].phases[0].entries[6]; //saving copy to swap
		i2 = possibleStates[7].phases[0].entries[7];
		i3 = possibleStates[7].phases[0].entries[8];

		//changes
		possibleStates[7].phases[0].entries[6] = possibleStates[7].phases[5].entries[6];
		possibleStates[7].phases[0].entries[7] = possibleStates[7].phases[5].entries[7];
		possibleStates[7].phases[0].entries[8] = possibleStates[7].phases[5].entries[8];

		possibleStates[7].phases[5].entries[6] = possibleStates[7].phases[1].entries[2];
		possibleStates[7].phases[5].entries[7] = possibleStates[7].phases[1].entries[1];
		possibleStates[7].phases[5].entries[8] = possibleStates[7].phases[1].entries[0];

		possibleStates[7].phases[1].entries[2] = possibleStates[7].phases[4].entries[6];
		possibleStates[7].phases[1].entries[1] = possibleStates[7].phases[4].entries[7];
		possibleStates[7].phases[1].entries[0] = possibleStates[7].phases[4].entries[8];

		possibleStates[7].phases[4].entries[6] = i1;
		possibleStates[7].phases[4].entries[7] = i2;
		possibleStates[7].phases[4].entries[8] = i3;

		i1 = possibleStates[7].phases[3].entries[0];
		possibleStates[7].phases[3].entries[0] = possibleStates[7].phases[3].entries[2];
		possibleStates[7].phases[3].entries[3] = possibleStates[7].phases[3].entries[1];
		possibleStates[7].phases[3].entries[6] = i1;
		possibleStates[7].phases[3].entries[7] = possibleStates[7].phases[3].entries[3];

		possibleStates[7].phases[3].entries[8] = possibleStates[7].phases[3].entries[6];
		possibleStates[7].phases[3].entries[5] = possibleStates[7].phases[3].entries[7];
		possibleStates[7].phases[3].entries[2] = possibleStates[7].phases[3].entries[8];
		possibleStates[7].phases[3].entries[1] = possibleStates[7].phases[3].entries[5];
		strcpy(possibleStates[0].transitionMessage, "D-");
		//frontFace-clockwise 12+8=20 changes
		i1 = i2 = i3 = 0;
		i1 = possibleStates[8].phases[2].entries[6]; //saving copy to swap
		i2 = possibleStates[8].phases[2].entries[7];
		i3 = possibleStates[8].phases[2].entries[8];

		//changes
		possibleStates[8].phases[2].entries[6] = possibleStates[8].phases[4].entries[8];
		possibleStates[8].phases[2].entries[7] = possibleStates[8].phases[4].entries[5];
		possibleStates[8].phases[2].entries[8] = possibleStates[8].phases[4].entries[2];

		possibleStates[8].phases[4].entries[8] = possibleStates[8].phases[3].entries[2];
		possibleStates[8].phases[4].entries[5] = possibleStates[8].phases[3].entries[1];
		possibleStates[8].phases[4].entries[2] = possibleStates[8].phases[3].entries[0];

		possibleStates[8].phases[3].entries[2] = possibleStates[8].phases[5].entries[0];
		possibleStates[8].phases[3].entries[1] = possibleStates[8].phases[5].entries[3];
		possibleStates[8].phases[3].entries[0] = possibleStates[8].phases[5].entries[6];

		possibleStates[8].phases[5].entries[0] = i1;
		possibleStates[8].phases[5].entries[3] = i2;
		possibleStates[8].phases[5].entries[6] = i3;

		i1 = possibleStates[8].phases[0].entries[0];
		possibleStates[8].phases[0].entries[0] = possibleStates[8].phases[0].entries[6];
		possibleStates[8].phases[0].entries[1] = possibleStates[8].phases[0].entries[3];
		possibleStates[8].phases[0].entries[2] = i1;
		possibleStates[8].phases[0].entries[5] = possibleStates[8].phases[0].entries[1];

		possibleStates[8].phases[0].entries[8] = possibleStates[8].phases[0].entries[2];
		possibleStates[8].phases[0].entries[7] = possibleStates[8].phases[0].entries[5];
		possibleStates[8].phases[0].entries[6] = possibleStates[8].phases[0].entries[8];
		possibleStates[8].phases[0].entries[3] = possibleStates[8].phases[0].entries[7];
		strcpy(possibleStates[0].transitionMessage, "F");
		//frontFace-anticlockwise 12+8=20 changes
		i1 = i2 = i3 = 0;
		i1 = possibleStates[9].phases[2].entries[6]; //saving copy to swap
		i2 = possibleStates[9].phases[2].entries[7];
		i3 = possibleStates[9].phases[2].entries[8];

		//changes
		possibleStates[9].phases[2].entries[6] = possibleStates[9].phases[5].entries[0];
		possibleStates[9].phases[2].entries[7] = possibleStates[9].phases[5].entries[3];
		possibleStates[9].phases[2].entries[8] = possibleStates[9].phases[5].entries[6];

		possibleStates[9].phases[5].entries[0] = possibleStates[9].phases[3].entries[2];
		possibleStates[9].phases[5].entries[3] = possibleStates[9].phases[3].entries[1];
		possibleStates[9].phases[5].entries[6] = possibleStates[9].phases[3].entries[0];

		possibleStates[9].phases[3].entries[2] = possibleStates[9].phases[4].entries[8];
		possibleStates[9].phases[3].entries[1] = possibleStates[9].phases[4].entries[5];
		possibleStates[9].phases[3].entries[0] = possibleStates[9].phases[4].entries[2];

		possibleStates[9].phases[4].entries[8] = i1;
		possibleStates[9].phases[4].entries[5] = i2;
		possibleStates[9].phases[4].entries[2] = i3;

		i1 = possibleStates[9].phases[0].entries[0];
		possibleStates[9].phases[0].entries[0] = possibleStates[9].phases[0].entries[2];
		possibleStates[9].phases[0].entries[3] = possibleStates[9].phases[0].entries[1];
		possibleStates[9].phases[0].entries[6] = i1;
		possibleStates[9].phases[0].entries[7] = possibleStates[9].phases[0].entries[3];

		possibleStates[9].phases[0].entries[8] = possibleStates[9].phases[0].entries[6];
		possibleStates[9].phases[0].entries[5] = possibleStates[9].phases[0].entries[7];
		possibleStates[9].phases[0].entries[2] = possibleStates[9].phases[0].entries[8];
		possibleStates[9].phases[0].entries[1] = possibleStates[9].phases[0].entries[5];
		strcpy(possibleStates[0].transitionMessage, "F-");
		//backface-clockwise 12+8=20 changes
		i1 = i2 = i3 = 0;
		i1 = possibleStates[10].phases[2].entries[0]; //saving copy to swap
		i2 = possibleStates[10].phases[2].entries[1];
		i3 = possibleStates[10].phases[2].entries[2];

		//changes
		possibleStates[10].phases[2].entries[0] = possibleStates[10].phases[5].entries[2];
		possibleStates[10].phases[2].entries[1] = possibleStates[10].phases[5].entries[5];
		possibleStates[10].phases[2].entries[2] = possibleStates[10].phases[5].entries[8];

		possibleStates[10].phases[5].entries[2] = possibleStates[10].phases[3].entries[8];
		possibleStates[10].phases[5].entries[5] = possibleStates[10].phases[3].entries[7];
		possibleStates[10].phases[5].entries[8] = possibleStates[10].phases[3].entries[6];

		possibleStates[10].phases[3].entries[8] = possibleStates[10].phases[4].entries[6];
		possibleStates[10].phases[3].entries[7] = possibleStates[10].phases[4].entries[3];
		possibleStates[10].phases[3].entries[6] = possibleStates[10].phases[4].entries[0];

		possibleStates[10].phases[4].entries[6] = i1;
		possibleStates[10].phases[4].entries[3] = i2;
		possibleStates[10].phases[4].entries[0] = i3;

		i1 = possibleStates[10].phases[1].entries[0];
		possibleStates[10].phases[1].entries[0] = possibleStates[10].phases[1].entries[6];
		possibleStates[10].phases[1].entries[1] = possibleStates[10].phases[1].entries[3];
		possibleStates[10].phases[1].entries[2] = i1;
		possibleStates[10].phases[1].entries[5] = possibleStates[10].phases[1].entries[1];

		possibleStates[10].phases[1].entries[8] = possibleStates[10].phases[1].entries[2];
		possibleStates[10].phases[1].entries[7] = possibleStates[10].phases[1].entries[5];
		possibleStates[10].phases[1].entries[6] = possibleStates[10].phases[1].entries[8];
		possibleStates[10].phases[1].entries[3] = possibleStates[10].phases[1].entries[7];
		strcpy(possibleStates[0].transitionMessage, "B");
		//backFace-anticlockwise 12+8=20 changes
		i1 = i2 = i3 = 0;
		i1 = possibleStates[11].phases[2].entries[0]; //saving copy to swap
		i2 = possibleStates[11].phases[2].entries[1];
		i3 = possibleStates[11].phases[2].entries[2];

		//changes
		possibleStates[11].phases[2].entries[0] = possibleStates[11].phases[4].entries[6];
		possibleStates[11].phases[2].entries[1] = possibleStates[11].phases[4].entries[3];
		possibleStates[11].phases[2].entries[2] = possibleStates[11].phases[4].entries[0];

		possibleStates[11].phases[4].entries[6] = possibleStates[11].phases[3].entries[8];
		possibleStates[11].phases[4].entries[3] = possibleStates[11].phases[3].entries[7];
		possibleStates[11].phases[4].entries[0] = possibleStates[11].phases[3].entries[6];

		possibleStates[11].phases[3].entries[8] = possibleStates[11].phases[5].entries[2];
		possibleStates[11].phases[3].entries[7] = possibleStates[11].phases[5].entries[5];
		possibleStates[11].phases[3].entries[6] = possibleStates[11].phases[5].entries[8];

		possibleStates[11].phases[5].entries[2] = i1;
		possibleStates[11].phases[5].entries[5] = i2;
		possibleStates[11].phases[5].entries[8] = i3;

		i1 = possibleStates[11].phases[1].entries[0];
		possibleStates[11].phases[1].entries[0] = possibleStates[11].phases[1].entries[2];
		possibleStates[11].phases[1].entries[3] = possibleStates[11].phases[1].entries[1];
		possibleStates[11].phases[1].entries[6] = i1;
		possibleStates[11].phases[1].entries[7] = possibleStates[11].phases[1].entries[3];

		possibleStates[11].phases[1].entries[8] = possibleStates[11].phases[1].entries[6];
		possibleStates[11].phases[1].entries[5] = possibleStates[11].phases[1].entries[7];
		possibleStates[11].phases[1].entries[2] = possibleStates[11].phases[1].entries[8];
		possibleStates[11].phases[1].entries[1] = possibleStates[11].phases[1].entries[5];
		strcpy(possibleStates[0].transitionMessage, "B-");

		return possibleStates;
	}

};

struct Node {
	RubikCube* cubePtr;
	Node* childsPtr;
	Node* parentPtr;
	int gx;
	int hx;
	int fx;

	Node() {
		this->cubePtr = new RubikCube;
		childsPtr = nullptr;
		parentPtr = nullptr;
		gx = hx = fx = -1;
	}

	Node(RubikCube* rhs) {
		this->cubePtr = rhs;
		childsPtr = nullptr;
		parentPtr = nullptr;
		gx = hx = fx = -1;
	}

	~Node() {
		if (childsPtr)
			delete[] childsPtr;

		if (cubePtr)
			delete cubePtr;
	}

	void degenerateNode() {
		RubikCube* baseAddressPtr = cubePtr->produceNextPossibleStates();
		this->childsPtr = new Node[12];
		for (int i = 0; i < 12; i++) {
			childsPtr[i].cubePtr = baseAddressPtr + i;
			childsPtr[i].gx = this->gx + 1;
			//childsPtr[i].hx = childsPtr[i].cubePtr->getHeuristicValue(goalCubePtr);
			//childsPtr[i].fx = childsPtr[i].gx + childsPtr[i].hx;
			childsPtr[i].parentPtr = this;
		}
	}

	bool testSkipSuccessor(list<Node*> openList, Node* childsPtr) {
		list<Node*>::iterator i1;
		for (i1 = openList.begin(); i1 != openList.end(); i1++) {
			if ((*i1)->cubePtr[0] == childsPtr->cubePtr[0]) {
				if ((*i1)->fx < childsPtr->fx) {
					return true;
				}
			}

		}
		return false;
	}

	bool testSuccessorForClosedList(list<Node*>closedList, Node* childsPtr, Node*& getThatPtrIfExist) {
		list<Node*>::iterator i1;
		for (i1 = closedList.begin(); i1 != closedList.end(); i1++) {
			if ((*i1)->cubePtr[0] == childsPtr->cubePtr[0]) {
				if ((*i1)->fx < childsPtr->fx) {
					getThatPtrIfExist = (*i1);
					return true;
				}
			}

		}
		return false;
	}

	bool successorAlreadyInClosedList(list<Node*> closedList, Node* childsPtr) {
		list<Node*>::iterator i1;
		for (i1 = closedList.begin(); i1 != closedList.end(); i1++) {
			if ((*i1) == childsPtr) {
				return true;
			}
			else if ((*i1)->cubePtr[0] == childsPtr->cubePtr[0]) {
				return true;
			}

		}
		return false;
	}

	void printPath(list<Node*>* closedList) {
		list<Node*>::iterator i1;

		/*list<Node*> printableList;
		i1 = closedList.end();

		printableList.push_front((*i1));
		while ((*i1) != (*closedList.begin())) {

			printableList.push_front((*i1)->parentPtr);
			(*i1) == (*i1)->parentPtr;
		}
		printableList.push_front((*i1));*/

	
		for (i1 = closedList->begin(); i1 != closedList->end(); i1++) {
			cout << (*i1)->cubePtr->transitionMessage << endl;
		}
	}

	void performAStarSearch(RubikCube* goalCubePtr, RubikCube* currentCube) {

		list<Node*> openList;
		list<Node*> closedList;
		Node* leastFNode = nullptr;
		list<Node*>::iterator it;

		//int* myiptr = new int(1);
		Node* startNode = new Node(currentCube);
		startNode->gx = 0;

		openList.push_back(startNode);
		leastFNode = startNode;

		while (!openList.empty()) { //traverse the open list


			//find the node with the least f on
			//the open list, call it "q"
			for (it = openList.begin(); it != openList.end(); it++) {
				if (leastFNode->fx > (*(*it)).fx) {
					leastFNode = *it;
				}
			}

			if ((*(leastFNode->cubePtr)) == (*goalCubePtr)) {
				cout << "Reached Goal State!\n";
				// push q on the closed list
				closedList.push_back(leastFNode);
				printPath(&closedList); //verify again
				return;
			}
			else
			{
				//pop q off the open list
				openList.remove(leastFNode);
			}

			//generate q's 12 successors and set their
			//parents to q

			leastFNode->degenerateNode();
			Node* getThatPtrIfExist = nullptr;
			// for each successor*/ //before adding to open list, check that CUBE should not exist in CLOSED list
			for (int i = 0; i < 12; i++) {

				if ((*(leastFNode->childsPtr[i].cubePtr)) == (*goalCubePtr)) {
					leastFNode->childsPtr[i].hx = leastFNode->childsPtr[i].cubePtr->getHeuristicValue(goalCubePtr);
					leastFNode->childsPtr[i].fx = leastFNode->childsPtr[i].gx + leastFNode->childsPtr[i].hx;
					cout << "Reached Goal State!\n";
					// push q on the closed list
					closedList.push_back(&leastFNode->childsPtr[i]);
					printPath(&closedList); //verify again
					return;
				}
				else if (testSkipSuccessor(openList, &(leastFNode->childsPtr[i]))) {
					/*ii) if a node with the same position (i.e entries of CUBE matches) as
						successor is in the OPEN list which has a
					   lower f than successor, skip this successor i.e don't add this successor to openList*/
				}
				else if (testSuccessorForClosedList(closedList, &(leastFNode->childsPtr[i]), getThatPtrIfExist)) {

					//closedList.remove(getThatPtrIfExist);
					openList.push_back(getThatPtrIfExist);
					getThatPtrIfExist->parentPtr = leastFNode;
					/*iii) if a node with the same position (i.e entries of CUBE matches) as
						successor  is in the CLOSED list which has
						a lower f than successor, skip this successor
						otherwise (bcz its already visited), add the node to the open list and set node' parent to currently using leastFNode*/
				}
				else if (!successorAlreadyInClosedList(closedList, &(leastFNode->childsPtr[i]))) {
					//add successor to OPEN list
					openList.push_back(&(leastFNode->childsPtr[i]));
				}
				// push q on the closed list
				closedList.push_back(&leastFNode->childsPtr[i]);
			} //		 end (for loop)

			

		}//end(while loop)



		if (startNode) {
			delete startNode;
		}

	}
	bool IDDFS(RubikCube* src, RubikCube* target, int max_depth)
	{
		// Repeatedly depth-limit search till the
		 //maximum depth.
		for (int i = 0; i <= max_depth; i++) {
			if (DLS(src, target, i) == true) {
				cout << "GOAL FOUND using IDDFS!!\n";
				return true;
			}

		}
		cout << "SORRY ...can't find goal within these levels using IDDFS!!\n";
		return false;
	}


	bool DLS(RubikCube* src, RubikCube* target, int limit)
	{
		if (*src == *target)
			return true;

		// If reached the maximum depth, stop recursing.
		if (limit <= 0)
			return false;

		RubikCube* childs = src->produceNextPossibleStates();
		for (int i = 0; i < 12; i++) {
			if (DLS(&childs[i], target, limit - 1) == true)
				return true;
		}
		return false;
	}

};

//main entry point
int main() {
	RubikCube cube;
	RubikCube goalCube;

	ifstream fin;

	cube.loadCurrentStateFromFile(fin);
	goalCube.loadGoalStateFromFile(fin);

	Node* startNode = nullptr;
	


	RubikCube* nextGoalPtr = nullptr;
	nextGoalPtr = goalCube.produceNextPossibleStates();
	for (int i = 0; i < 3; i++) {
		nextGoalPtr = nextGoalPtr->produceNextPossibleStates();
	}
	//nextGoalPtr[0] = nextGoalPtr[7];//placing 7th index child at 0th index



	startNode->performAStarSearch(nextGoalPtr, &goalCube);
	startNode->IDDFS(&goalCube, nextGoalPtr, 20);

	startNode->performAStarSearch(&goalCube, &cube);
	startNode->IDDFS(&cube, &goalCube, 10);
	system("pause");
}

//------------------------------------------------------------------------------------------------
