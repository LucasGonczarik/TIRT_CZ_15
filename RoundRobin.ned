//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
import submodule.MMPPGenerator;
import submodule.Sink;


//
// TODO documentation
//
network RoundRobin
{
    @display("bgb=428,345");
    submodules:
        mmppGenerator: MMPPGenerator {
            @display("p=59,30");
        }
        mmppGenerator1: MMPPGenerator {
            @display("p=59,98");
        }
        mmppGenerator2: MMPPGenerator {
            @display("p=59,160");
        }
        mmppGenerator3: MMPPGenerator {
            @display("p=59,228");
        }
        mmppGenerator4: MMPPGenerator {
            @display("p=59,298");
        }
        sink: Sink {
            @display("p=317,180");
        }
        roundRobin: submodule.RoundRobin {
            @display("p=201,180");
        }
    connections:
        mmppGenerator.out --> roundRobin.in++;
        mmppGenerator1.out --> roundRobin.in++;
        mmppGenerator2.out --> roundRobin.in++;
        mmppGenerator3.out --> roundRobin.in++;
        mmppGenerator4.out --> roundRobin.in++;
        roundRobin.out --> sink.in++;
}

