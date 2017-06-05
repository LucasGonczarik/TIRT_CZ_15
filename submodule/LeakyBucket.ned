package submodule;

simple LeakyBucket
{
	parameters:
		@class(LeakyBucket);
		@signal[qsize](type="long");
    	@statistic[qsize](title="Queue size"; source="qsize"; record=vector,stats,histogram; interpolationmode=none);
    	@signal[accepted](type="double");
    	@statistic[accepted](title="Accepted packages"; source="accepted"; record=vector,stats,histogram; interpolationmode=none);
    	@signal[rejected](type="double");
    	@statistic[rejected](title="Rejected Packages"; source="rejected"; record=vector,stats,histogram; interpolationmode=none);
    	@signal[packetLossRate](type="double");
    	@statistic[packetLossRate](title="Packet Loss Rate"; source="packetLossRate"; record=vector,stats,histogram; interpolationmode=none);
		int bucketSize;
		int transferSpeed;
	gates:
		input in;

}