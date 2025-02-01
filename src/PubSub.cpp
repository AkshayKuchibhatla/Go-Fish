#include "PubSub.h"
#include <string>
using namespace std;

// ========== MESSAGE ==========

Message::Message(string m) {
    message = string(m);
}
string Message::getMessage() const {
    return message;
}

// ========== BROKER ==========

void Broker::subscribe(const string &topic, Subscriber *sub) {
    subscribers[topic].push_back(sub); // Add subscriber with topic to map.
}
void Broker::publish(const string &topic, Message *message) {
    int i;
    topics[topic].push(message);
    for (i = 0; i < subscribers[topic].size(); i++) {
        subscribers[topic].at(i)->receive(message, topic);
    }
}

// ========== PUBLISHER ==========

Publisher::Publisher(Broker &brkr) {
    broker = &brkr;
}
void Publisher::publish(const string &topic, Message *message) {
    broker->publish(topic, message);
}

// ========== SUBSCRIBER ==========

Subscriber::Subscriber(Broker &brkr) {
    broker = &brkr;
}
void Subscriber::subscribe(const string&topic) {
    broker->subscribe(topic, this);
}
void Subscriber::receive(const Message *message, const string &topic)  {
    cout << "Message arrived: " << message->getMessage() << ", from topic: " << topic << "\n\r";
}