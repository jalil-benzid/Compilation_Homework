# NFA Epsilon Transition Removal

A C program that removes epsilon (ε) transitions from a Non-deterministic Finite Automaton (NFA), producing an equivalent NFA without epsilon transitions.

## Authors
- **Bezai Ayoub** - G01 Security
- **Benzid Ahmed Abdeldjalil** - G01 AI  
- **Boukhelfa Abderrahim** - G01 Security

## Overview

This program implements the epsilon-closure algorithm to eliminate ε-transitions from an NFA while preserving the language it accepts. The transformation is a key step in converting NFAs to DFAs and in various compiler design applications.

## Features

- Read NFA specification with epsilon transitions
- Compute epsilon closure for all states
- Build new transition table without epsilon moves
- Update final states based on epsilon reachability
- Display the resulting epsilon-free NFA

## Algorithm

The program uses three main steps:

1. **Epsilon Closure Computation**: For each state, finds all states reachable through epsilon transitions (transitive closure)
2. **Transition Building**: Creates new transitions by composing: state → ε-closure → symbol → ε-closure
3. **Final State Update**: Marks states as final if they can reach any original final state via epsilon

## Compilation
```bash
gcc -o nfa_epsilon_removal nfa_epsilon_removal.c
```

## Usage

Run the program and provide input interactively:
```bash
./nfa_epsilon_removal
```

### Input Format

1. Number of states
2. Number of input symbols
3. Input symbols (space-separated characters)
4. Initial state
5. Number of final states
6. Final state numbers
7. Regular transitions: `from_state symbol to_state` (enter -1 to finish)
8. Epsilon transitions: `from_state to_state` (enter -1 to finish)

### Example Input
```
How many states? 4
How many symbols? 2
Enter symbols: a b
Start state: 0
Number of final states: 1
Final states: 3
Transitions (-1 to stop):
0 a 1
2 b 3
-1
Epsilon transitions (-1 to stop):
0 2
1 3
-1
```

### Example Output
```
====== NFA after epsilon removal ======
Initial state: 0
Final states: 0 1 3 
Transitions:
0 --a--> 1
0 --a--> 3
0 --b--> 3
2 --b--> 3
```

## Limitations

- Maximum 10 states (`MAXS`)
- Maximum 5 input symbols (`MAXSYM`)
- No input validation for out-of-range values
- Memory usage is fixed regardless of actual automaton size

## Technical Details

### Data Structures

- `oldt[MAXS][MAXSYM][MAXS]`: Original transition table (3D array for NFA)
- `newt[MAXS][MAXSYM][MAXS]`: New transition table without epsilon
- `eps[MAXS][MAXS]`: Epsilon transition matrix
- `eclos[MAXS][MAXS]`: Epsilon closure matrix
- `finalFlag[MAXS]`: Boolean array marking final states

### Time Complexity

- Epsilon closure: O(n³) where n is the number of states
- Transition building: O(n² × m × n²) where m is the number of symbols
- Overall: O(n³ × m)

## Potential Improvements

- Dynamic memory allocation for larger automata
- Input validation and error handling
- File I/O for batch processing
- Graphical visualization of automata
- Support for UTF-8 symbols
- Optimization using adjacency lists instead of matrices

## Applications

- Compiler design (lexical analysis)
- Regular expression processing
- Pattern matching systems
- Formal language theory education

