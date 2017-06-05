package submodule;

simple LeakyBucket
{
	parameters:
		@class(LeakyBucket);
		@signal[qsize](type="long");
    	@statistic[qsize](title="Queue size"; source="qsize"; record=vector,stats,histogram; interpolationmode=none);
		@signal[temporaryAcceptedCount](type="long");
     	@statistic[temporaryAcceptedCount](title="Accepted messages during interval"; source="temporaryAcceptedCount"; record=vector,stats,histogram; interpolationmode=none);
    	@signal[packetLossRate](type="double");
    	@statistic[packetLossRate](title="Packet Loss Rate"; source="packetLossRate"; record=vector,stats,histogram; interpolationmode=none);
		int bucketSize;
		int transferSpeed;
	  	double temporaryAcceptedInterval;
	gates:
		input in;

}