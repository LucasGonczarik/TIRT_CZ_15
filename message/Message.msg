message Message {
    int src;
    int dst;
    int sessionID;
    int messageID;
    int priority; // low, normal, high
    int hopCount = 0; // do we need this?
    double creationTime;
}