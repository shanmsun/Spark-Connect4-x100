rows = 6
columns = 7
unused = '-'
red = 'R'
yellow = 'Y'

connect4_board = ['row0', 'row1', 'row2', 'row3', 'row4', 'row5']

def initialize():
	for num in range(0, len(connect4_board)):
		connect4_board[num] = [unused, unused, unused, unused, unused, unused, unused]
	print("Initialization... [Done]")

def printboard():
	for row in range(len(connect4_board)-1 , -1, -1):
		print("Row %i\t " % row, end='')
		for column in range(0, len(connect4_board[row])):
			print(connect4_board[row][column], end='')
		print()

def placetile(colour, x):
	# error
	# if colour.upper() != 'R' or colour.upper() != 'Y':
	# 	print("Incorrect colour")
	# 	return

	# error
	if x < 0 and x >= columns:
		print("Incorrect coordinates")
		return

	for row in range(len(connect4_board)):
		if connect4_board[row][x] == unused:
			connect4_board[row][x] = colour.upper()
			break
	return

def prompt():
	colour = input("Colour: ")
	x = int( input("column: ") )
	print(colour)
	placetile(colour, x)

def printmenu():
	print("Python program")
	initialize()
	while(True):
		printboard()
		prompt()

if __name__ == "__main__":
	printmenu()