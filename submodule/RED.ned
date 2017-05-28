package submodule;

simple RED {
    parameters:
        @class(RED);
		@signal[bufferSizeSignal](type="long");
    	@statistic[bufferSizeSignal](title="Buffer size"; source="bufferSizeSignal"; record=vector,stats,histogram; interpolationmode=none);
    	@signal[acceptedSignal](type="long");
    	@statistic[acceptedSignal](title="Accepted messages"; source="acceptedSignal"; record=vector,stats,histogram; interpolationmode=none);
    	@signal[rejectedSignal](type="long");
    	@statistic[rejectedSignal](title="Rejected messages"; source="rejectedSignal"; record=vector,stats,histogram; interpolationmode=none);
        int messageHandlingTime = default(1);
    gates:
        output out;
        input in[];
}