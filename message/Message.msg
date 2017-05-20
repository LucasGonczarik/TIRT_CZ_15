message Message {
    int src;
    int dst;
    int sessionID;
    int messageID;
    int priority;
    int hopCount = 0;
    double creationTime;
}