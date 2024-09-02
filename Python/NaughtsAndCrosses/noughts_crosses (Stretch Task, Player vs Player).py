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

def player_input(board, player_turn):
    valid_input = False
    print("Player " + str(player_turn) + "'s turn")
    while valid_input == False:
        move = input("Would you like to move a piece y/n? ")
        if move. lower() == "y":
            piece_start = input("Enter the position of the piece: ")
            piece_end = input("Enter where you want to move it: ")
            if piece_start.isnumeric() == True and piece_end.isnumeric():
                    piece_start = int(piece_start)
                    piece_end = int(piece_end)
                    if piece_start > 0 and piece_start < 10 and piece_end > 0 and piece_end < 10:
                        if board[piece_start - 1] != " " and board[piece_end - 1] == " ":
                            
                            board = draw_board(board, piece_end, board[piece_start - 1])
                            board = draw_board(board, piece_start, " ")
                            valid_input = True
        if move.lower() == "n":
            x_or_o = input("Would you like to place an x or an o? ")
            if x_or_o == "x" or x_or_o == "o":
                pos_input = input("Please enter a position: ")
                if pos_input.isnumeric() == True:
                    pos_input = int(pos_input)
                    if pos_input >0 and pos_input < 10:
                        if board[pos_input - 1] == " ":
                            valid_input = True
                            board = draw_board(board, pos_input, x_or_o)
        if valid_input == False:
            print("Please enter a valid input")
    return board
             
def game_check(board, game_end, player_turn):
    empty_space = 0
    pos_wins = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]]
    for i in range(len(board)):
        if board[i] == " ":
            empty_space += 1
    for i in range(len(pos_wins)):
        x_num = 0
        o_num = 0
        for k in pos_wins[i]:
            if board[k] == "x":
                x_num += 1
            if board[k] == "o":
                o_num += 1
        if x_num == 3 or o_num == 3:
            if player_turn == 1:
                print("Player 1 wins!")
            if player_turn == 2:
                print("Player 2 wins!")
            game_end = True
        
    if empty_space == 0 and game_end == False:
        print("It's a draw!")
    return game_end
    
def game_loop(board, player_turn):
    game_end = False
    while game_end == False:
        player_turn -= 1
        board = player_input(board, player_turn)
        print_board(board)
        game_end = game_check(board, game_end, player_turn)
        if game_end == True:
            break
        player_turn += 1
        board = player_input(board, player_turn)
        print_board(board)
        game_end = game_check(board, game_end, player_turn)
    


# Program main starts from here, feel free to edit it.
board = [" "," "," "," "," "," "," "," "," "]
position = ['1','2','3','4','5','6','7','8','9']
player_turn = 2
print_board(position)
game_loop(board, player_turn)
