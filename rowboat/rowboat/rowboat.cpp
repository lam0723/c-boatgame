//Chan Cheuk Lam 1155129258 1155129258@link.cuhk.edu.hk
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int digitno(int);

int main() {
	int M = 0, C = 0, B = 0; //M = total no. of missionaries, C = total no. of cannibals, B = boat capacity
	int mb = 0, cb = 0, trip = 1;//mb = on - boat missionaries, cb = on - boat cannibals, trip = no. of trials
	int state[3] = { 0, 0, 1 }; //state[0] =no. of missionaries left, state[1] =no. of cannibals left, state[2] = boat position (1 = left, 0 = right)
	bool ok = false, win = false, lose = false;

	do { //validate initial state
		cout << "Enter boat capacity: ";
		cin >> B;
		cout << "Enter #missionaries: ";
		cin >> M;
		cout << "Enter #cannibals: ";
		cin >> C;
		if (!((M == 0) || (C == 0) || (B < 2) || (M < C))) ok = true;
		if (M <= C) { //check known special case
			switch (B) {
			case 2:
				if ((M > 3) || (C > 3)) ok = false;
				break;
			case 3:
				if ((M > 5) || (C > 5)) ok = false;
				break;
			default:
				break;
			}
		}
		if (!ok) cout << "Invalid input!" << endl;
	} while (!ok);

	state[0] = M; //initialize game state
	state[1] = C;

	cout << "State "; //print out initial state
	if (digitno(M) >= digitno(C)) cout << setw(digitno(M));
	else cout << setw(digitno(C));
	cout << trip << ": [" << setw(digitno(M)) << state[0] << "m, " << setw(digitno(C)) << state[1] << "c]";
	if (state[2] == 1) cout << "v ~~~  [" << setw(digitno(M)) << M - state[0] << "m, " << setw(digitno(C)) << C - state[1] << "c]" << endl;
	else cout << "  ~~~ v[" << setw(digitno(M)) << M - state[0] << "m, " << setw(digitno(C)) << C - state[1] << "c]" << endl;

	do { //loop until win or lose
		ok = false;
		do { //ask for input
			cout << "Enter #m #c aboard boat: ";
			cin >> mb >> cb;
			if (state[2] == 1) {
				if ((mb + cb >= 1) && ((mb >= cb) || (mb == 0)) && (mb + cb <= B) && (mb <= state[0]) && (cb <= state[1])) ok = true;
				else cout << "Invalid input!" << endl;
			}
			else if (state[2] == 0) {
				if ((mb + cb >= 1) && ((mb >= cb) || (mb == 0)) && (mb + cb <= B) && (mb <= M - state[0]) && (cb <= C - state[1])) ok = true;
				else cout << "Invalid input!" << endl;
			}
		} while (!ok);

		trip++; //compute game state
		if (state[2] == 1) {
			state[0] = state[0] - mb;
			state[1] = state[1] - cb;
			state[2] = 0;
		}
		else if (state[2] == 0) {
			state[0] = state[0] + mb;
			state[1] = state[1] + cb;
			state[2] = 1;
		}

		if ((state[0] == 0) && (state[1] == 0) && (state[2] == 0)) win = true; //check winning
		if (!(M - state[0] == 0) && !(state[0] == 0)) //check losing
			if ((M - state[0] < C - state[1]) || (state[0] < state[1])) lose = true;

		cout << "State "; //print out the state
		if (digitno(M) >= digitno(C)) cout << setw(digitno(M));
		else cout << setw(digitno(C));
		cout << trip << ": [" << setw(digitno(M)) << state[0] << "m, " << setw(digitno(C)) << state[1] << "c]";
		if (state[2] == 1) cout << "v ~~~  [" << setw(digitno(M)) << M - state[0] << "m, " << setw(digitno(C)) << C - state[1] << "c]" << endl;
		else cout << "  ~~~ v[" << setw(digitno(M)) << M - state[0] << "m, " << setw(digitno(C)) << C - state[1] << "c]" << endl;
	} while (!win && !lose);

	if (win) cout << "Congratulations! You win!"; //print out winning statement
	if (lose) cout << "Game over! Missionaries eaten!"; //print out losing statement

	return 0;
}

int digitno(int n) { //find how many digits in an integer variable
	return (log10(n) + 1);
}