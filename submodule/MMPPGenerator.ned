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

simple MMPPGenerator extends BasicGenerator {
    parameters:
        @class(MMPPGenerator);
        double lambda = default(1.0);
        double lambda1 = default(0.2);
        double lambda2 = default(0.4);
        double lambda3 = default(0.6);
        double p11 = default(0.4);
        double p12 = default(0.6);
        double p21 = default(0.2);
        double p22 = default(0.4);
        double p23 = default(0.4);
        double p32 = default(0.6);
        double p33 = default(0.4);
        
        
}