import submodule.ParetoGenerator;
import submodule.LeakyBucket;
import submodule.TokenBucket;
import submodule.Sink;

network BothBucketsNetwork
{
    @display("bgb=268,262");
    submodules:
        generator: ParetoGenerator {
            @display("p=117,225");
        }
        leakyBucket: LeakyBucket {
            @display("p=194,152");
        }
        tokenBucket: TokenBucket {
            @display("p=49,152");
        }
        sink: Sink {
            @display("p=117,61");
        }
    connections:
        generator.out++ --> leakyBucket.in;
        generator.out++ --> tokenBucket.in;
        tokenBucket.out --> sink.in++;
        leakyBucket.out --> sink.in++;
}
