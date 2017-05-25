message Message {
    int src;
    int dst;
    int sessionID;
    int messageID;
    int priority; // low, normal, high
    int hopCount = 0; // do we need this?
    simtime_t creationTime; // need to be 'simetime_t' everywhere where we want to get a time, 
    // shoudn't be cast to others (e.g. 'double') cause of lost precision effect
    //  (simtime_t is 64 bit when 'double' has only a 52 bit mantissa ref. doc 4.1.4) 
}
