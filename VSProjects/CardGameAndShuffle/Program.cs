using System;
using System.Collections.Generic;

namespace Assessment3
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Card> newDeck = new List<Card>(); //Creates a new list of cards
            Human player1 = new Human(); //Creates a new human player
            Computer player2 = new Computer(); //Creates a new computer player
            string suit; 
            int trickNumber = 1; //Sets the trick number to 1 intially
            for (int i = 1; i <= 4; i++) //For loop which creates the deck of cards
            {
                for (int j = 2; j <= 14; j++) //nested for loop so there are 13 cards in each suit
                {
                    if (i == 1) //adds 13 spades
                    {
                        suit = "spades";
                    }
                    else if (i == 2) //adds 13 clubs
                    {
                        suit = "clubs";
                    }
                    else if (i == 3) //adds 13 diamonds
                    {
                        suit = "diamonds";
                    }
                    else //add 13 hearts
                    {
                        suit = "hearts";
                    }
                    Card newCard = new Card(); //Creates a card with the correct suit and value
                    newCard.Suit = suit;
                    newCard.CardValue = j;
                    newDeck.Add(newCard); //Adds the new card to the deck
                }
            }

            Deck deck = new Deck(newDeck); //Creates a new deck using the list of cards
            bool exitMenu = false;
            bool exitGame = false; //bools for menu navigation
            bool startGame = false;
            while (exitMenu == false)
            {
                Console.WriteLine("Please select an option" +  //Menu for easy user navigation
                    "\n" + "1: Show current deck" +
                    "\n" + "2: Suffle and show new deck" +
                    "\n" + "3: Play Game" +
                    "\n" + "4: Quit");
                string menuChoice = Console.ReadLine(); //Gets user input for menu
                int choiceInt;
                if (int.TryParse(menuChoice, out choiceInt) == false) //Checks if input is an integer
                {
                    Console.WriteLine("Please input a value option");
                }
                else if (menuChoice == "1") //If input is "1" then display the current deck
                {
                    Console.WriteLine("=======Current Deck=======");
                    deck.DisplayDeck();
                }
                else if (menuChoice == "2") //If input is "2" then shuffle the deck and display it
                {
                    deck.Shuffle();
                    Console.WriteLine("=======Newly Shuffled Deck=======");
                    deck.DisplayDeck();
                }

                else if (menuChoice == "3") //If input is "3" then start the game
                {
                    deck.Shuffle(); //shuffle the deck before start
                    for (int i = 0; i < 10; i++) //loop through 10 times to add 10 cards to each hand
                    {
                        startGame = true;
                        player1.Hand.Add(deck.Deal()); //add card to players hand
                        player2.Hand.Add(deck.Deal()); //add card to computers hand
                    }
                }

                else if (menuChoice == "4") //If input is "4" then exit the program
                {
                    exitMenu = true;
                    exitGame = true;
                }
                else //If input isn't one of the above then it must be invalid
                {
                    Console.WriteLine("Please input a value option");
                }

                while (exitGame == false && startGame == true) //Loop for the game
                {
                    bool correctCards = false; //Bool to check if valid options have been chosen
                    int humanTotal; //int for player's trick total
                    int computerTotal; //int for computer's trick total
                    string card1 = ""; //card first chosen by player
                    string card2 = ""; //card second chosen by player
                    player1.ShowHand(); //Shows the player their hand
                    while (correctCards == false) //Loops until correct inputs are given
                    {
                        Console.WriteLine("Please choose 2 cards to play: ");
                        card1 = Console.ReadLine();
                        card2 = Console.ReadLine();
                        if ((int.TryParse(card1, out choiceInt) == false) || (int.TryParse(card2, out choiceInt) == false)) //Checks if inputs are integers
                        {
                            Console.WriteLine("Please input a value option");
                        }

                        else if (card1 != card2 && 
                            Int32.Parse(card1) <= player1.Hand.Count && 
                            Int32.Parse(card2) <= player1.Hand.Count &&
                            Int32.Parse(card1) > 0 &&
                            Int32.Parse(card2) > 0) //Checks if inputs are in range of the hand
                        {
                            correctCards = true; ;
                        }

                        else //If input doesn't meet any requirements then it must be invalid
                        {
                            Console.WriteLine("Please input a value option"); 
                        }
                    }

                    humanTotal = player1.PlayCards(Int32.Parse(card1) - 1, Int32.Parse(card2) - 1); //Adds the player's chosen card values together
                    computerTotal = player2.PickCards(); //Picks and adds values for the computer

                    if (humanTotal > computerTotal) //Checks to see who has won
                    {
                        Console.WriteLine("Player 1 wins the trick");
                        player1.AddTrick(trickNumber); //Adds the trick number to trick total for the player
                        trickNumber = 1;
                    }
                    else if (humanTotal < computerTotal)
                    {
                        Console.WriteLine("Player 2 wins the trick");
                        player2.AddTrick(trickNumber); //Adds the trick number to trick total for the computer
                        trickNumber = 1; //Sets the number of tricks that are won back to 1
                    }
                    else //If it's a draw then the whoever wins the next trick will get both tricks
                    {
                        Console.WriteLine("Draw. Winner of the next hand will win this trick as well");
                        trickNumber += 1; //adds 1 to the trick number so that the next winner will get all previous draws
                    }
                    if (player1.HandEmpty() == true || player1.TrickTotal == 3 || player2.TrickTotal == 3) //Checks if someone has won or if there are no more cards left
                    {
                        if (player1.TrickTotal > player2.TrickTotal) //Checks if the player has won
                        {
                            Console.WriteLine("Player 1 wins the game!");
                            exitGame = true; //exits the game and returns to menu
                        }
                        else if (player1.TrickTotal < player2.TrickTotal) //checks if computer has won
                        {
                            Console.WriteLine("Player 2 wins the game!");
                            exitGame = true;
                        }

                        else //If no one has won then it must be a draw and final cards must be drawn
                        {
                            Console.WriteLine("Number of tricks is equal so one last card must be drawn to see who wins"); 
                            bool draw = true;
                            while (draw == true) //Keeps drawing cards until someone wins or deck becomes empty
                            {
                                Card lastCard1 = deck.Deal(); //Deals 1 card for computer and player
                                Card lastCard2 = deck.Deal();
                                Console.WriteLine("Player 1's last card's value was " + lastCard1.CardValue + ". Player 2's last card's value was " + lastCard2.CardValue);
                                if (lastCard1.CardValue > lastCard2.CardValue) //Checks who won
                                {
                                    Console.WriteLine("Player 1 wins the game!");
                                    draw = false;
                                    exitGame = true; //exits the game and returns to menu
                                }
                                else if (lastCard1.CardValue < lastCard2.CardValue)
                                {
                                    Console.WriteLine("Player 2 wins the game!");
                                    draw = false;
                                    exitGame = true;
                                }
                                else //If the value of both cards are equal then it draws cards again
                                {
                                    draw = true;
                                    if (deck.DeckOfCards.Count == 0) //If the deck is empty then the game has to end in a draw
                                    {
                                        Console.WriteLine("It's a draw!");
                                        draw = false;
                                        exitGame = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }


        }
    }

    class Card //Class for Cards with polymorphic method
    {
        public string Suit //Each card is assigned a suit
        { get; set; }
        public int CardValue //Each card has a value
        { get; set; }

        public void DisplayCard() //Displays the value and suit of any given card. Is polymorphic so the Deck class can also use it
        {
            Console.WriteLine(CardValue + " of " + Suit);
        }

    }

    class Deck : Card //Deck class which inherites from Card class so card values can be access
    {
        public List<Card> DeckOfCards //List of cards
        { get; } //Can only be fetched and can't be set
        public Deck(List<Card> cardList) //Initiator for deck that recieves a list of cards for the deck
        {
            DeckOfCards = cardList;
        }

        public bool IsEmpty(List<Card> deck) //Method to check if deck is empty, if it is then return true, else return false
        {
            if (deck.Count == 0)
            {
                return true;
            }

            else
            {
                return false;
            }
        }

        public void DisplayDeck() //Method to display the deck
        {
            string stringValue;
            for (int i = 0; i < 52; i++) //Iterates through the deck
            {
                if (DeckOfCards[i].CardValue == 11) //If the value of the card is 11 then it's an jack
                {
                    stringValue = "Jack";
                }
                else if (DeckOfCards[i].CardValue == 12) //If the value of the card is 12 then it's an queen
                {
                    stringValue = "Queen";
                }
                else if (DeckOfCards[i].CardValue == 13) //If the value of the card is 13 then it's an king
                {
                    stringValue = "King";
                }
                else if (DeckOfCards[i].CardValue == 14) //If the value of the card is 14 then it's an ace
                {
                    stringValue = "Ace";
                }
                else //Else it's value is string value is just its value
                {
                    stringValue = DeckOfCards[i].CardValue.ToString();
                }
                Console.WriteLine("\t" + stringValue + " of " + DeckOfCards[i].Suit); //Displays each card
            }
        }

        public List<Card> Shuffle() //Method to shuffle the deck
        {
            for (int i = 0; i < DeckOfCards.Count - 1; i++) //Iterates through the deck
            {
                Random random = new Random(); //Creates new random
                int randomPosition = random.Next(0, DeckOfCards.Count);  //Chooses a random card from the deck
                Card temp = DeckOfCards[i]; //Holds the current card in a temp variable
                DeckOfCards[i] = DeckOfCards[randomPosition]; //Switches the cards
                DeckOfCards[randomPosition] = temp; //Switches the cards
            }
            return DeckOfCards; //Returns the newly suffled deck
        }

        public Card Deal() //Method to deal a card
        {
            if (IsEmpty(DeckOfCards)) //First checks if deck is empty, if so it returns nothing
            {
                return null;
            }
            else //Else it deals the card from the top of the deck
            {
                Card dealtCard = DeckOfCards[0]; //Gets the card from the top
                DeckOfCards.RemoveAt(0); //Removes the card
                return dealtCard; //Returns the card
            }
        }

        public new void DisplayCard() //Polymorphic method to display the top card of the deck
        {
            Card topCard = DeckOfCards[0]; //Gets the card at the top of the deck
            Console.WriteLine(topCard.CardValue + " of " + topCard.Suit); //Displays the value and suit of the card
        }
    }

    interface IPlayers //Interface for methods in Human and Computer class
    {
        int PlayCards(int card1, int card2); //Interface for playing cards

        bool HandEmpty(); //Interface for checking if hand is empty

        void AddTrick(int trickNumber); //Interface for adding tricks to total tricks

    }

    class Human : IPlayers //Human class which inherites from Player interface
    {
        public List<Card> Hand //Players hand is a list of cards
        { get; } //Can't be set for better abtraction
        public int TrickTotal //Variable for the number of tricks the player has
        { get; set; }

        public Human() //Initialiser for Human class
        {
            Hand = new List<Card>(); //Sets Hand to be a new list of cards
        }
        public void ShowHand() //Method to show the players hand
        {
            string stringValue;
            Console.WriteLine("This is your hand"); 
            for (int i = 0; i < Hand.Count; i++) //Iterates through the players hand
            {
                if (Hand[i].CardValue == 11) //Changes numbers to Jack, Queen, King or Ace if needed
                {
                    stringValue = "Jack";
                }
                else if (Hand[i].CardValue == 12)
                {
                    stringValue = "Queen";
                }
                else if (Hand[i].CardValue == 13)
                {
                    stringValue = "King";
                }
                else if (Hand[i].CardValue == 14)
                {
                    stringValue = "Ace";
                }
                else
                {
                    stringValue = Hand[i].CardValue.ToString();
                }
                Console.WriteLine(i + 1 + ":  " + stringValue + " of " + Hand[i].Suit); //Displays each card
            }
        }

        public int PlayCards(int card1, int card2) //Method to add and play the chosen cards
        {
            int total = Hand[card1].CardValue + Hand[card2].CardValue; //Adds the 2 chosen cards
            Hand.RemoveAll(t => t == Hand[card1] || t == Hand[card2]); //Removes the cards from the players hand
            Console.WriteLine("Player 1's total is: " + total); //Displays total
            return total; //Returns total
        }

        public bool HandEmpty() //Method to check if hand is empty
        {
            bool handEmpty = false; //Bool to return 
            if (Hand.Count == 0) //Checks if hand is empty
            {
                handEmpty = true; 
            }
            return handEmpty; //Return true or false
        }

        public void AddTrick(int trickNumber) //Method to add trick
        {
            TrickTotal += trickNumber;
        }
    }

    class Computer : IPlayers //Computer class which inherites from Player interface
    {
        public List<Card> Hand //Computer hand of cards
        { get; }

        public int TrickTotal //Total number of tricks for computer
        { get; set; }

        public Computer() //Initialiser for computer
        {
            Hand = new List<Card>(); //Creates new list of cards for hand
        }
        public int PickCards() //Method to pick cards for computer
        {
            int computerCard1 = 0;
            int computerCard2 = 0;
            while (computerCard1 == computerCard2) //Chooses new options until they aren't the same
            {
                Random random = new Random(); //New random
                computerCard1 = random.Next(0, Hand.Count); //Chooses value between 0 and the hand size
                computerCard2 = random.Next(0, Hand.Count); //Chooses a second value
            }
            int computerTotal = PlayCards(computerCard1, computerCard2); //Plays the chosen cards

            return computerTotal; //Returns the total
        }

        public int PlayCards(int card1, int card2) //Method to add and play the cards chosen by the computer
        {
            int total = Hand[card1].CardValue + Hand[card2].CardValue; //Adds the value of the cards
            Hand.RemoveAll(t => t == Hand[card1] || t == Hand[card2]); //Removes them from the computers hand
            Console.WriteLine("Player 2's total is: " + total); //Displays the total
            return total; //Returns the total
        }

        public bool HandEmpty() //Method to check if computer hand is empty
        {
            bool handEmpty = false;
            if (Hand.Count == 0)
            {
                handEmpty = true;
            }
            return handEmpty;
        }

        public void AddTrick(int trickNumber) //Method to add tricks to the computers total
        {
            TrickTotal += trickNumber;
        }

    }
}
