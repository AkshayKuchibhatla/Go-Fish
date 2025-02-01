#ifndef PUBSUB_H
#define PUBSUB_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;
/* This header file contains all of the classes necessary to
implement a message queue.*/

class Subscriber; // Forward declaration

class Message { // A container class for a string message.
    private:
        string message;
    public:
        Message(string m);
        string getMessage() const;
};

class Broker { // Stores all of the subscribers and the topics.
    private:
        unordered_map<string, queue<Message*> > topics;
        unordered_map<string, vector<Subscriber*> > subscribers;
    public:
        // Connects a subscriber to a client.
        void subscribe(const string &topic, Subscriber *sub);
        // Publishes a message to a topic.
        void publish(const string &topic, Message *message);
};

class Publisher { // Publishes messages to topics.
    Broker *broker;
    public:
        Publisher(Broker &brkr);
        void publish(const string &topic, Message *message);
};

class Subscriber { // Subscribes to (i. e. listens in on) topics.
    private:
        Broker *broker;
    public:
        Subscriber(Broker &broker);
        void subscribe(const string &topic);
        void receive(const Message *message, const string &topic);
};
#endif