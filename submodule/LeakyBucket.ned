package submodule;

simple LeakyBucket
{
	parameters:
		@class(LeakyBucket);
		int bucketSize;
		int transferSpeed;
	gates:
		input in;

}