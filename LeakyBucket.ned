import submodule.PoissonGenerator;
import submodule.LeakyBucket;

network LeakyBucket
{
    submodules:
        generator: PoissonGenerator;
        leakyBucket: LeakyBucket;
    connections:
        generator.out --> leakyBucket.in;
}