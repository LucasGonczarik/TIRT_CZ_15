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

//
// TODO auto-generated type
//
simple FCFS
{
    parameters:
        @class(FCFS);
		@signal[bufferSizeSignal](type="long");
    	@statistic[bufferSizeSignal](title="Buffer size"; source="bufferSizeSignal"; record=vector,stats,histogram; interpolationmode=none);
    	@signal[acceptedSignal](type="long");
    	@statistic[acceptedSignal](title="Accepted messages"; source="acceptedSignal"; record=vector,stats,histogram; interpolationmode=none);
    	@signal[rejectedSignal](type="long");
    	@statistic[rejectedSignal](title="Rejected messages"; source="rejectedSignal"; record=vector,stats,histogram; interpolationmode=none);
        int bufferCapacity = default(20);
        int messageHandlingTime = default(1);
    gates:
        output out;
        input in[];
}
