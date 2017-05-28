//import submodule.PoissonGenerator;
import submodule.MMPPGenerator;
import submodule.Sink;
import submodule.RED;

network RED
{
    submodules:
        red: RED {
            @display("p=196,393");
        }
        sink: Sink {
            @display("p=412,393");
        }
        mmppGenerator1: MMPPGenerator {
            @display("p=70,124");
        }
        mmppGenerator2: MMPPGenerator {
            @display("p=62,234");
        }
        mmppGenerator3: MMPPGenerator {
            @display("p=70,309");
        }
        mmppGenerator4: MMPPGenerator {
            @display("p=62,366");
        }
        mmppGenerator5: MMPPGenerator {
            @display("p=70,432");
        }
    connections:
        red.out --> sink.in++;
        mmppGenerator1.out --> red.in++;
        mmppGenerator2.out --> red.in++;
        mmppGenerator3.out --> red.in++;
        mmppGenerator4.out --> red.in++;
        mmppGenerator5.out --> red.in++;
}
