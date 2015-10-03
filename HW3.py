from random import *

# Seed the random number function
seed()

# Version A (Computer Guesses)

print ("Think of a number between 1 - 50 inclusive.")
print ("The computer will now try to guess your number with a few hints of course.")
input("Press Enter when done thinking...")

L = 1
H = 50
computer_guess = randint(L,H)
user_answer = 0
while(user_answer != 'c'):
    print ("\nMy guess is: %d" % computer_guess)
    user_answer = input("Is my guess too high (h) too low(l) or correct(c)?")
    if (user_answer == 'h'):
        H = computer_guess - 1
        computer_guess = randint(L,H)
    else:
        L = computer_guess + 1
        computer_guess = randint(L,H)
    

print ("\nYay! I guessed correctly. Thanks for the game.")
print ("\nNow it's your turn!")


# Version B (Player guesses)

print ("\nI am thinking of a number between 1 - 100. Try to guess it.")
user_answer = int(input(""))
computer_number = randint(1,100)
L = 1
H = 100

while (user_answer != computer_number):
   
    if (user_answer > computer_number):
        user_answer = int(input("Too high guess again: "))
    else:
        user_answer = int(input("Too low guess again: "))

print ("\n\nYes, you guessed my number!")