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
import submodule.PoissonGenerator;
import submodule.Sink;


//
// TODO auto-generated type
//
network FCFS
{
    @display("bgb=310,302");
    submodules:
        sink: Sink {
            @display("p=266,142");
        }
        mmppGenerator: MMPPGenerator {
            @display("p=64,33");
        }
        mmppGenerator1: MMPPGenerator {
            @display("p=64,92");
        }
        mmppGenerator2: MMPPGenerator {
            @display("p=64,142");
        }
        mmppGenerator3: MMPPGenerator {
            @display("p=64,204");
        }
        mmppGenerator4: MMPPGenerator {
            @display("p=64,258");
        }
        fcfs: submodule.FCFS {
            @display("p=165,142");
        }
    connections:
        mmppGenerator.out++ --> fcfs.in++;
        mmppGenerator1.out++ --> fcfs.in++;
        mmppGenerator2.out++ --> fcfs.in++;
        mmppGenerator3.out++ --> fcfs.in++;
        mmppGenerator4.out++ --> fcfs.in++;
        fcfs.out --> sink.in++;
}
