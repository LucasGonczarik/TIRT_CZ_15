import submodule.ParetoGenerator;
import submodule.LeakyBucket;

network LeakyBucket
{
    submodules:
        generator: ParetoGenerator;
        leakyBucket: LeakyBucket;
    connections:
        generator.out++ --> leakyBucket.in;
}