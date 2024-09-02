

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
    print_board(board)
    return board

def player_input(board, player_turn):
    valid_input = False
    while valid_input == False:
        pos_input = input("Player " + str(player_turn) + " please enter a position: ")
        if pos_input.isnumeric() == True:
            pos_input = int(pos_input)
            if pos_input >0 and pos_input < 10:
                if board[pos_input - 1] == " ":
                    valid_input = True
                    return pos_input
                

def game_check(board, player_turn):
    game_end = False
    while game_end == False:
        pos_input = player_input(board, player_turn)
        if player_turn == 1:
            player_turn += 1
            board = draw_board(board, pos_input, "x")
        elif player_turn == 2:
            player_turn -= 1
            board = draw_board(board, pos_input, "o")
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

            if x_num == 3:
                print("Player 1 wins!")
                game_end = True
            if o_num == 3:
                print("Player 2 wins!")
                game_end = True
        if empty_space == 0 and game_end == False:
            print("It's a draw!")
        
    



# Program main starts from here, feel free to edit it.
player_turn = 1
board = [" "," "," "," "," "," "," "," "," "]
position = ['1','2','3','4','5','6','7','8','9']
#print_board(board)
print_board(position)
game_check(board, player_turn)

