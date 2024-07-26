# Tweet Sentiment Analyzer

## Project Overview
This project involves the development of a sentiment analysis classifier in C++ to determine whether tweets express positive or negative sentiment. The classifier uses custom string and vector classes to tokenize and count word occurrences in a training dataset. Frequency counts are then employed to classify unseen tweets, achieving an accuracy of 84%.

## Skills Utilized
- Algorithms
- Data Analysis
- C++
- Machine Learning

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Results](#results)
- [Conclusion](#conclusion)
- [Acknowledgments](#acknowledgments)
- [References](#references)

## Introduction
Sentiment analysis is a valuable tool for understanding public opinion and sentiment from text data, such as tweets. This project aims to create a C++ based sentiment analysis classifier that can determine the sentiment of tweets as positive or negative. The classifier leverages custom implementations of string and vector classes for efficient text processing and analysis.

## Features
- **Sentiment Classification:** Classifies tweets as positive or negative based on frequency counts.
- **Custom Data Structures:** Utilizes custom string and vector classes for efficient tokenization and word counting.
- **High Accuracy:** Achieves an accuracy of 84% on the test dataset.

## Usage
To use the Tweet Sentiment Analyzer, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/Tweet-Sentiment-Analyzer.git
   ```

2. **Navigate to the Project Directory:**
   ```bash
   cd Tweet-Sentiment-Analyzer
   ```

3. **Build the Project:**
   Use your preferred build system (e.g., Make, CMake) to compile the project. For example, using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Run the Sentiment Analyzer:**
   Execute the compiled binary to start the sentiment analysis. Ensure that you have the necessary training and test datasets in the correct format.
   ```bash
   ./tweet_sentiment_analyzer
   ```

## Results
The sentiment analysis classifier achieves an accuracy of 84% on the test dataset, effectively distinguishing between positive and negative sentiments in tweets. The results demonstrate the classifier's ability to process and analyze tweet data with high accuracy.

## Conclusion
This project successfully demonstrates the development of a sentiment analysis classifier using C++. The implementation of custom string and vector classes for text processing and the use of frequency counts for classification result in a robust and efficient sentiment analysis tool. The insights gained from this project can be applied to various applications requiring sentiment analysis of text data.

## Acknowledgments
- The project leverages libraries and tools such as the C++ Standard Library for basic data structures and file handling.
- Thanks to the contributors and maintainers of these libraries for their valuable work.

## References
- [C++ Standard Library Documentation](https://en.cppreference.com/w/)
- [Sentiment Analysis Algorithms](https://en.wikipedia.org/wiki/Sentiment_analysis)
- [Natural Language Processing with C++](https://www.geeksforgeeks.org/introduction-to-natural-language-processing/)
