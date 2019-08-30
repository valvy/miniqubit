#!/usr/bin/env python
from PyMiniQbt import getVersion, getName,  QasmAsyncInterpreter

import os, re, time, sys

setQubit = re.compile(r'@\{QUBIT_OPPONENT}')
setInput =re.compile(r'@\{INPUT_DATA\}')


print("\n\n\n\n===== Welcome to Cat/Box/Scissors! =====\n\n")
print("  ~~ A game by the Decodoku project ~~ \n\n")
print("Altered version using", getName(), "version:", getVersion())
raw_input()

def printMiniQbtHelp():
	print("Choose a qubit as opponent")
	print("There are two boxes")
	print("This qubit will place secretly a cat in one box")
	print("after that you have to shred one box to pieces with scissors")
	print("When you and the qubit chooses the same box, the cat will be dead and you lose")




def runProgramWithAssembly(assembly):
	interpreter = QasmAsyncInterpreter()
	# get human player to choose opponent
	chosen = 0
	while (chosen==0):
		try:
			opponent = int(input("\nWhich qubit will be your opponent? (1,2,3, or 4)\n") )
			if ( (opponent >= 1) & (opponent <= 4) ):
				chosen = 1
			else:
				print("u wot m8? Try that again.")
		except ValueError:
			pass

	# here 1 and 2 mean qubits 0 and 1, so change accordingly
	if (opponent<3):
		opponent = opponent - 1

	assembly = setQubit.sub(str(opponent), assembly)
	print("The qubit is quitely doing his stuff..\n")
	time.sleep(1)
	print("You hear some faint miauwing...\n")
	time.sleep(1)
	print("The qubit placed the cat in one of the boxes")
	time.sleep(1)
	print("You've got the sudden urge to shred a box with your scissors... one of the two boxes in front of you")
	time.sleep(1)
	
	# get human player to choose move
	chosen = 0
	while (chosen==0):
		#humanMove = input("\nChoose your move (s or sdg)\n")
		humanMove = raw_input("\nWhich box do you want to shred (left or right)\n")
		if ( (humanMove == "left") | (humanMove == "right") ):
			chosen = 1
		else:
			print("u wot m8? Try that again.")

	print("It will take your opponents move and compare them.")
	if(humanMove == "left"):
		assembly = setInput.sub("s q[2];//Input from python :)",assembly)
	else:
		assembly = setInput.sub("sdg q[2]; // input from python :D",assembly)

	interpreter.interpret(assembly)
	hadError = interpreter.hasErrors()
	while interpreter.hasErrors():
		print(interpreter.getError())
	print("\nChecking to remaining box\n")
	time.sleep(1)
	result = interpreter.readClassicResult("c")
	#print(result)
	if int(result.getData(0)):
		print("Miauw, the cat is still alive!\n")
		print("\t /\___/\\\n\t(  o o  )\n\t/   *   \\\n\t\\__\_/__/ meow!\n\t / ___ \\\n\t \/___\/")
		raw_input()
		return True
	else:
		print("You shredded the cat :(\n")
		print("\t /\___/\\\n\t(  X X  )\n\t/   *   \\\n\t\\_______/ DEAD!\n\t *|*|*|* \n\n\t *|*|*|*\n\t / ___ \\\n\t \/___\/")
		raw_input()
		return False



try:
	#load in the assembly for use in MiniQbt

	with open(os.path.abspath("CatBoxScissors.qasm")) as dat:
		src = dat.read()
		amountWon = 0
		amountLost = 0
		while(True):
			printMiniQbtHelp()
			if not amountLost + amountWon == 0:
				percentageWon =  100 / (amountWon + amountLost )  * amountWon
				print("From the %i cats only %i survived your onslaught!" % (amountLost + amountWon, amountWon))
				print("You saved %d%% of the cats" % percentageWon)
			if runProgramWithAssembly(src):
				amountWon += 1
			else:
				amountLost += 1


			
except KeyboardInterrupt:
	print("\nStopping game\n")