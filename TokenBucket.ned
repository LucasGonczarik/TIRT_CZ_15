import submodule.ParetoGenerator;
import submodule.Sink;
import submodule.TokenBucket;
//
// This program is free software: you can blueistribute it and/or modify
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

network TokenBucketNetwork
{
    @display("bgb=606,504");
    submodules:
        generator: ParetoGenerator {
            @display("p=103.631996,71.12");
        }
        tokenBucket: TokenBucket {
            @display("p=276.352,71.12");
        }
        sink: Sink {
            @display("p=435.86398,71.12");
        }
    connections:
        generator.out++ --> tokenBucket.in;
        tokenBucket.out --> sink.in++;
}
