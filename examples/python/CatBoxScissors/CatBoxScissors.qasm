//===== Welcome to Cat/Box/Scissors! =====


//  ~~ A game by the Decodoku project ~~ 


include "qelib1.inc";
qreg q[5];
creg c[5];

// prepare the referee qubit q[2] as a |+> state
h q[2];

/////////////// INPUT HERE ///////////////
// Make your move by choosing s or sdg
// Comment the one you don't want


@{INPUT_DATA}


/////////////////////////////////////////

// next a quantum opponent also chooses a move
// then a referee compares your choices
// if you chose the same, the opponent wins
// if you chose different, you win

// the quantum player q[@{QUBIT_OPPONENT}] makes its move
h q[@{QUBIT_OPPONENT}]; // hadamard to make it random
s q[2]; // apply an s to the referee
// then use a controlled-Z to turn this into sdq if q[0] is |1>
h q[2];
cx q[@{QUBIT_OPPONENT}],q[2];
h q[2];

// referee is now in |+> state if you lose and |-> if you win, so measure
h q[2];
measure q[2] -> c[4];

// the result 10000 means you win
// the result 00000 means you lose


