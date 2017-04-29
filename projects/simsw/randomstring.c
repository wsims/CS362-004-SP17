Random Testing Quiz 2
Author: Will Sims

I developed my solution for the random tester by first looking at the code that I needed to test. The code showed that for the error message to be displayed, I would ned to randomly generate characters, and a string that spells "reset" with a null terminator.

I implemented the inputChar() function by using the built in rand() function and returning a number from 32 to 127 which would then be converted to ASCII. This ignores the control characters. After enough iterations, the state should be set to 9 rather quickly, because you only need to return the correct correct 9 times to set the state.

I implemented my inputString() function by filling a string with numbers from 97 to 122 which are all the lowercase ASCII values. I had initially had this the same as inputChar() which was 32 to 127 which would test more cases, but it was taking a very long time to eventually return "reset". Since I don't know exactly how the program is going to be used, I think using only lowcase letters is fine for this context and I could make changes if more requirements were introduced.

After enough interations (took 1312477 the first time, 18339963 the second time), inputString should randomly generate the string "reset" which will cause the program to end and the error to be displayed. The state is set to 9 so quickly, that it has very little effect on the number of iterations.
