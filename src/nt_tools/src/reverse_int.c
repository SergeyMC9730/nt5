/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  Sergei Baigerov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact Sergei Baigerov -- @dogotrigger in Discord
*/

int _ntReverseInt(int _val) {
    // convert value into 4 chars
    unsigned char *bytes;
    bytes = &_val;

    // now create new array with reversed order
    unsigned char _result[4];
    _result[0] = bytes[3];
    _result[1] = bytes[2];
    _result[2] = bytes[1];
    _result[3] = bytes[0];

    // convert it into int
    int val = *((int *)_result);

    return val;
}