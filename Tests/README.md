# Task description
This dataset was prepared using a subset of the data released on kaggle (https://www.kaggle.com/datafiniti/hotel-reviews).
Your task is to use the features provided in each csv file to develop a decision tree that can determine the label of each review.
A csv file is a comma-separated file where each row represents one of the reviews and the columns in each line are separated by lines.

e.g:
The following line represents a single hotel review.
0,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,Stayed a the Conrad with my wife over the weekend for a night away. The staff was incredible every step of the way. The room was clean and everything we could have needed was available. The whole process was seamless and I would recommend this hotel to anyone.Dear Oldt1mer23 Thank you for your great review. I'm glad all went well during your stay and that you enjoyed your night away with your wife. We look forward to welcome you again!Kind Regards  Kelly Vohs,Positive

# How to use the data?
You are provided with three files:
1) sample_train.csv: the hotel reviews that you should use to build the decision tree.
2) sample_dev.csv: the hotel reviews that you DON'T use to build the tree but use it to evaluate the already-built tree. In other words, you use it to check how the decision tree works for reviews that it didn't see before.
3) sample_test.csv: the hotel reviews that YOU DON'T KNOW their labels/targets. These reviews will be used to rank the teams that attempt to work on this project.

# Data description
The train and development datasets contain the following 27 columns in the same order:
contains_No, contains_Please, contains_Thank, contains_apologize, contains_bad, contains_clean, contains_comfortable, contains_dirty, contains_enjoyed, contains_friendly, contains_glad, contains_good, contains_great, contains_happy, contains_hot, contains_issues, contains_nice, contains_noise, contains_old, contains_poor, contains_right, contains_small, contains_smell, contains_sorry, contains_wonderful, reviews.text, rating

- The first 25 columns are binary features that indicate whether the review contains a certain word or not.
e.g: contains_glad is equal to 0 if the word "glad" isn't used in the review and is equal to 1 if it's used in the review.
- The following column contains the hotel review as raw text. IT IS GUARANTEED THAT THE RAW TEXT DOESN'T CONTAIN A COMMA ,
- The last column indicates the binary rating of the review (Positive or Negative)

The test dataset contains the same columns but after hiding the last column (the rating).