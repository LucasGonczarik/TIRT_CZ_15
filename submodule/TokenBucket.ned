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

package submodule;

simple TokenBucket {
    parameters:
        @class(TokenBucket);
    	@signal[event](type="simtime_t");
    	double tokenGenerationInterval = default(20.0);
    	int maxTokenCount = default(5);
    gates:
        input in;
        output out;
}
