# Assignment: Don't Be Sentimental!


## Introduction
Have you ever read a tweet and thought, “Gee, what a positive outlook!” or “Wow, why so negative, friend?”  Can computers make the same determination?  They can surely try!

In Machine Learning, the task of assigning a **label** to a data item is called **classification** (putting things into different classes or categories).  The more specific name for what we’re going to do is sentiment analysis because you’re trying to determine the “sentiment” or attitude based on the words in a tweet.  The goal of the project is to build a sentiment classifier! 

1. Training Phase
   - Input is a set of tweets with each tweet’s associated sentiment value.  This is the training data set.
   - Example: Assume you have 10 tweets and each is pre-classified with positive or negative sentiment.  How might you go about analyzing the words in these 10 tweets to find words more commonly associated with negative sentiment and words more commonly associated with positive sentiment?
   - The result of the training step will be one list of words that have an associated positive or negative sentiment with them depending on which type of tweet they appeared in more frequently.  Or, you might have 2 lists of words: one list is positive, one list is negative.

2. Testing Phase
   - In the testing phase, for a set of tweets called the testing data set, you predict the sentiment by using the list or lists of words extracted during the training phase.
   - Behind the scenes, you already know the sentiment of each of the tweets in the testing data set.  We’ll call this the actual sentiment or ground truth.  You then compare your predicted sentiment to the known sentiment for each of the testing tweets. Some of the predictions will be correct; some will be wrong.  The percentage correct is the accuracy, but more on this later.
