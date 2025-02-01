#include <iostream>
#include "PubSub.h"
using namespace std;

int main() {
    Broker b;
    Publisher p(b);
    Subscriber alpha(b), beta(b);

    alpha.subscribe("A");
    beta.subscribe("B");

    p.publish("A", new Message("Hello, topic A!"));
    p.publish("B", new Message("Message for topic B;"));
    return 0;
}