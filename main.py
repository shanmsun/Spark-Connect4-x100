import random

rows = 6
columns = 7
unused = '-'
red = 'R'
yellow = 'Y'

#Define Red to go first, will be changed later to choose who to go first
colour = 'Y'
prev_colour = 'R'

#Number of yellow and red on each row, column, diagon
tol_y = tol_r = None
tol_row_y = [None,None,None,None,None,None]
tol_row_r = [None,None,None,None,None,None]
tol_col_y = [None,None,None,None,None,None,None]
tol_col_r = [None,None,None,None,None,None,None]


connect4_board = ['row0', 'row1', 'row2', 'row3', 'row4', 'row5']


def initialize():
	for num in range(0, len(connect4_board)):
		connect4_board[num] = [unused, unused, unused, unused, unused, unused, unused]
	initialize_counts()	
	print("Initialization... [Done]")
	return

def initialize_counts():
	global tol_y, tol_r, tol_row_y, tol_col_y, tol_row_r, tol_col_r
	tol_y = tol_r = 0
	tol_row_y = [0,0,0,0,0,0]
	tol_row_r = [0,0,0,0,0,0]
	tol_col_y = [0,0,0,0,0,0,0]
	tol_col_r = [0,0,0,0,0,0,0]
	return

def printboard():
	for row in range(len(connect4_board)-1 , -1, -1):
		print("Row %i\t " % row, end='')
		for column in range(0, len(connect4_board[row])):
			print(connect4_board[row][column], end='')
		print()
	return

def placetile(tile_colour, x):
	global colour, prev_colour
	global tol_y, tol_r, tol_row_y, tol_col_y, tol_row_r, tol_col_r
	
	if x < 0 or x >= columns:	#won't happen on real machine
		print("Incorrect coordinates")
		temp = colour
		colour = prev_colour
		prev_colour = temp		
		return
	
	else:
		for row in range(0, len(connect4_board) ):
			if connect4_board[row][x] == unused:
				connect4_board[row][x] = tile_colour.upper()
				break
			elif row == 5:
				print("Column Full, Try Again")	#change to a 'buzz' sound or other display
				temp = colour
				colour = prev_colour
				prev_colour = temp
		if tile_colour == 'R':
			tol_r += 1
			tol_row_r[row] = tol_row_r[row] +1
			tol_col_r[x] = tol_col_r[x] +1
		else:
			tol_y += 1
			tol_row_y[row] = tol_row_y[row]+1
			tol_col_y[x] = tol_col_y[x]+1
	return

def prompt():
	global colour		#'colour' can be used to display the current player (add_on)
	global prev_colour
	if colour == 'Y':
		colour = 'R'
		prev_colour = 'Y'
	else:
		colour = 'Y'
		prev_colour = 'R'
	x = int( input("Column: ") )
	print(colour)
	placetile(colour, x)
	return

def printmenu():
	global colour
	global mode
	print("Python program")
	initialize()
	mode = int(input('Single Player Mode? 0 = no, 1 = easy, 2 = fun : '))
	if mode == 0:
		while(True):
			printboard()
			prompt()
			check_win(colour)
	else:
		while(True):
			printboard()
			AI_prompt()
			check_win(colour)
	return		
			
def AI_prompt():
	global colour
	global prev_colour
	
	#Let AI always be Red
	if colour == 'Y':
		check_win(colour)
		check_win(prev_colour)
		colour = 'R'
		prev_colour = 'Y'
		AI_run()
		print('My placement: ')
		check_win(colour)
		check_win(prev_colour)
		return
	else:
		print('Your Turn: ')
		colour = 'Y'
		prev_colour = 'R'
		x = int( input("Column: ") )
		placetile(colour, x)	
		return
	return

def AI_run():
	global mode
	global tol_y, tol_r, tol_row_y, tol_col_y, tol_row_r, tol_col_r
	if mode == 1:
		options = [0,1,2,3,4,5,6,2,3,4,2,3,4,1,5]
		random.shuffle(options)
		x = options[0]
	elif mode == 2:
		chance = [2,3,4]
		for col in range(0, columns):
			print(tol_col_y, tol_col_r)
			if tol_col_y[col] == 3 and tol_col_r[col] == 0:
				red_col = 'R'
				placetile(red_col, col)
				return
			elif tol_col_y[col] == 4 and tol_col_y[col] + tol_col_r[col] <6:
				placetile('R', col)
				return			
			elif tol_col_y[col] > 1 and  tol_col_y[col] + tol_col_r[col] <6:
				chance.insert(0, col)							
		random.shuffle(chance)
		x = chance[0]
	red_col = 'R'
	placetile(red_col, x)
	return


def check_win(tile_colour):

	#return if less than 4 tiles on each side have been placed (no win)
	if tol_r <3 and tol_y <3:
		return
	connected_1 = connected_2 = connected_3 = connected_4 = connected_5 = 0
	connected_6 = connected_7 = connected_8 = connected_9 = connected_10 = 0
	connected_11 = connected_12 = 0
	
	for row in range(0, rows):	#rows-1?
		connected = 0
		for i in range(0, 6):
			if connect4_board[row][i] == tile_colour:
				connected += 1
				if connected == 4:
					winner_is(tile_colour)
			else:
				connected = 0
	for col in range(0, columns):
		connected = 0
		for i in range(0, 5):
			if connect4_board[i][col] == tile_colour:
				connected += 1
				if connected == 4:
					winner_is(tile_colour)
			else:
				connected = 0	
				
	if tol_r + tol_y >9 :
		#4 tiles
		for i in range(0,4):
			if connect4_board[2+i][0+i] == tile_colour:
				connected_1 += 1
				if connected_1 == 4:
					winner_is(tile_colour)
			else:
				connected_1 = 0
			
			if connect4_board[0+i][3+i] == tile_colour:
				connected_6 += 1
				if connected_6 == 4:
					winner_is(tile_colour)
			else:
				connected_6 = 0	
				
			if connect4_board[3-i][0+i] == tile_colour:
				connected_7 += 1
				if connected_7 == 4:
					winner_is(tile_colour)
			else:
				connected_7 = 0		
				
			if connect4_board[5-i][3+i] == tile_colour:
				connected_12 += 1
				if connected_12 == 4:
					winner_is(tile_colour)
			else:
				connected_12 = 0
		
		#5 tiles
		for i in range(0,5):
			if connect4_board[1+i][0+i] == tile_colour:
				connected_2 += 1
				if connected_2 == 4:
					winner_is(tile_colour)
			else:
				connected_2 = 0
			
			if connect4_board[0+i][2+i] == tile_colour:
				connected_5 += 1
				if connected_5 == 4:
					winner_is(tile_colour)
			else:
				connected_5 = 0	
				
			if connect4_board[4-i][0+i] == tile_colour:
				connected_8 += 1
				if connected_8 == 4:
					winner_is(tile_colour)
			else:
				connected_8 = 0		
				
			if connect4_board[5-i][2+i] == tile_colour:
				connected_11 += 1
				if connected_11 == 4:
					winner_is(tile_colour)
			else:
				connected_11 = 0
		#6 tiles
		for i in range(0,5):
			if connect4_board[0+i][0+i] == tile_colour:
				connected_3 += 1
				if connected_3 == 4:
					winner_is(tile_colour)
			else:
				connected_3 = 0
			
			if connect4_board[0+i][1+i] == tile_colour:
				connected_4 += 1
				if connected_4 == 4:
					winner_is(tile_colour)
			else:
				connected_4 = 0	
				
			if connect4_board[5-i][0+i] == tile_colour:
				connected_9 += 1
				if connected_9 == 4:
					winner_is(tile_colour)
			else:
				connected_9 = 0		
				
			if connect4_board[5-i][1+i] == tile_colour:
				connected_10 += 1
				if connected_10 == 4:
					winner_is(tile_colour)
			else:
				connected_10 = 0			
	return
					
def winner_is(player):
	printboard()
	print("The Winner is", player)
	#somehow display winner and wait there untill reset is asked
	
	printmenu()
	return

if __name__ == "__main__":
	printmenu()
	