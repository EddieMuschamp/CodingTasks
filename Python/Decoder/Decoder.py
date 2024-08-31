def decode(message_file):
  words = {}
  for line in message_file:  #Iterates through text file
    num = [int(n) for n in line.split() if n.isdigit()][0]  #Gets number from line
    if ((num*8) + 1)**0.5 % 1 == 0: #Checks if number is in sequence
      words[num] = ''.join([i for i in line if not i.isdigit() and i != " "])  #Adds number as key and word to dictionary
  words = dict(sorted(words.items()))
  for word in words.values():  #Iterates through dictionary values
    print(word.strip("\n"), end = " ") #Prints only words

message = open("C:/Users/User/Coding/CodingTasks/Python/Decoder/message.txt", "r")
decode(message)
