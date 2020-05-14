import re
from nltk.tokenize import word_tokenize
from string import punctuation
from nltk.corpus import stopwords


class TweetFilter:
    def __init__(self):
        self._stopwords = set(stopwords.words(
            'english') + list(punctuation) + ['AT_USER', 'URL'])

    def processTweets(self, tweetsList):
        processedTweets = []
        for tweet in tweetsList:
            processedTweets.append(
                (self.__processTweet(tweet["text"]), tweet["label"]))
        return processedTweets

    def __processTweet(self, tweet):
        tweet = tweet.lower()  # convert text to lower-case
        tweet = re.sub('((www\.[^\s]+)|(https?://[^\s]+))',
                       'URL', tweet)  # remove URLs
        tweet = re.sub('@[^\s]+', 'AT_USER', tweet)  # remove usernames
        tweet = re.sub(r'#([^\s]+)', r'\1', tweet)  # remove the # in #hashtag
        # remove repeated characters (helloooooooo into hello)
        tweet = word_tokenize(tweet)
        return [word for word in tweet if word not in self._stopwords]


filter = TweetFilter()

tweets = filter.processTweets([
    {"label": "desisto", "text": "@person1 retweeted @person2: Corn has got to be the most delllllicious crop in the world!!!! #corn #thoughts..."}])

print(tweets)
