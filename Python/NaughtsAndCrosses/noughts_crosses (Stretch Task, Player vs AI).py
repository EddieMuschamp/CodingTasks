from random import randint
# The following function print the current board to the command window.
def print_board(board):
    print()
    print(board[:3])
    print(board[3:6])
    print(board[6:])
    
# This function takes the existing board, position input from player,
# maker type (either x or o) and returns the updated board based on the arguments.
def draw_board(board, position, marker):
    board[position-1] = marker
    return board
#This function handles the player input and validates it
def player_input(board):
    valid_input = False
    #Keeps asking for input if one of the inputs isn't valid
    while valid_input == False:
        #Asks for inputs for moving an existing piece
        move = input("Would you like to move a piece y/n? ")
        if move. lower() == "y":
            piece_start = input("Enter the position of the piece: ")
            piece_end = input("Enter where you want to move it: ")
            #Validates the inputs
            if piece_start.isnumeric() == True and piece_end.isnumeric():
                    piece_start = int(piece_start)
                    piece_end = int(piece_end)
                    if piece_start > 0 and piece_start < 10 and piece_end > 0 and piece_end < 10:
                        #Checks for an existing piece and for an empty space for it to move to
                        if board[piece_start - 1] != " " and board[piece_end - 1] == " ":
                            #Calls draw_board to overwrite piece and place a new one
                            board = draw_board(board, piece_end, board[piece_start - 1])
                            board = draw_board(board, piece_start, " ")
                            valid_input = True
        if move.lower() == "n":
            #Asks what marker the player wants to place
            x_or_o = input("Would you like to place an x or an o? ")
            #Validates input
            if x_or_o == "x" or x_or_o == "o":
                pos_input = input("Please enter a position: ")
                if pos_input.isnumeric() == True:
                    pos_input = int(pos_input)
                    if pos_input >0 and pos_input < 10:
                        if board[pos_input - 1] == " ":
                            #Places new marker on board
                            board = draw_board(board, pos_input, x_or_o)
                            valid_input = True
        if valid_input == False:
            print("Please enter a valid input")
    return board
                
#Function for determining where the AI will place an x or an o
def ai_turn(board):
    valid_choice = False
    #While loop to check if AI input is valid and has been complete
    while valid_choice == False:
        #2D array of all possible winning combinations
        pos_wins = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]]
        #Loops through each possible combination
        for i in range(len(pos_wins)):
            x_num = 0
            o_num = 0
            #Loops through each position in each combination
            for k in pos_wins[i]:
                if valid_choice == True:
                    break
                #Checks if there are 2 o's to see if there is a possible win
                if board[k] == "o":
                    o_num += 1
                    if o_num == 2:
                        #Loops through each position in the combination of 2 to find the missing space
                        for m in pos_wins[i]:
                            if board[m] == " ":
                                #Places the o in the 3rd spot to win
                                board = draw_board(board, m + 1, "o")
                                valid_choice = True
                                #Breaks the loop because the game is over
                                break
                        break
                #Checks for 2 x's
                if board[k] == "x":
                    x_num += 1
                    if x_num == 2:
                        #Loops through each position in the combination of 2 to find the missing space
                        for n in pos_wins[i]:
                            if board[n] == " ":
                                #Places the x in the 3rd spot to win
                                board = draw_board(board, n + 1, "x")
                                valid_choice = True
                                #Breaks the loop because the game is over
                                break
                        break
        #If the AI can't find a spot to win, it will place an x or and o in a random spot
        ai_rand = randint(1,9)
        x_num = 0
        o_num = 0
        #Validates the random choice
        if board[ai_rand - 1] == " " and valid_choice == False:
            valid_choice = True
            #Loops through board to find how many x's and o's there are
            for i in board:
                if i == "x":
                    x_num += 1
                if i == "o":
                    o_num += 1
            #If there are more o's then x's, it will place an x to reduce the chance of giving the player a triple
            if x_num <= o_num:
                board = draw_board(board, ai_rand, "x")
            #If there are more x's then o's, it will place an o
            elif o_num < x_num:
                board = draw_board(board, ai_rand, "o")
    return board
    
    
#Function to check if someone has won or if it is a draw    
def game_check(board, game_end, player):
    empty_space = 0
    #2D array for each possible win combination
    pos_wins = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]]
    #Loops through the board to look if there are no empty spaces, and therefore a draw
    for i in range(len(board)):
        if board[i] == " ":
            empty_space += 1
    #Loops through each combination of wins
    for i in range(len(pos_wins)):
        #If it is a draw then it will stop looking for a possible win
        if empty_space == 0 and game_end == False:
            print("It's a draw!")
            break
        x_num = 0
        o_num = 0
        #Loops through each combination and checks if there are 3 x's or o's
        for k in pos_wins[i]:
            if board[k] == "x":
                x_num += 1
            if board[k] == "o":
                o_num += 1
        #If there are 3 x's or o's then the game is over
        if x_num == 3 or o_num == 3:
            #If it was the players turn last then the player has won
            if player == "Player":
                print("Human player wins!")
            #If it was the AI's turn last then the AI has won
            if player == "AI":
                print("AI wins!")
            game_end = True
    return game_end

#This function contains the general game loop (Player turn, check for win, AI turn, check for win)
def game_loop(board):
    game_end = False
    #Loops while no-one has won yet
    while game_end == False:
        #Player goes first
        board = player_input(board)
        #Prints out the board after player turn
        print_board(board)
        player = "Player"
        #Checks if the player has won
        game_end = game_check(board, game_end, player)
        #Checks if the game has ended and stops the loop so the AI doesn't get another turn
        if game_end == True:
            break
        #AI goes second
        board = ai_turn(board)
        #Prints the board after AI turn
        print_board(board)
        player = "AI"
        #Checks if AI has won
        game_end = game_check(board, game_end, player)
    


# Program main starts from here, feel free to edit it.
board = [" "," "," "," "," "," "," "," "," "]
position = ['1','2','3','4','5','6','7','8','9']
#Prints out the board with numbered positions
print_board(position)
#Starts the game loop
game_loop(board)

